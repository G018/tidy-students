//===--- TraversalTypeCheck.cpp - clang-tidy -----------------===//

#include "TraversalTypeCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Lex/Lexer.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace students {

const std::string TraversalTypeCheck::INDEX = "index";
const std::string TraversalTypeCheck::POINTER = "pointer";

TraversalTypeCheck::TraversalTypeCheck(StringRef Name,
                                       ClangTidyContext *Context)
    : ClangTidyCheck(Name, Context),
      TraversalType(Options.get("TraversalType", INDEX)) {}

void TraversalTypeCheck::storeOptions(ClangTidyOptions::OptionMap &Opts) {
  Options.store(Opts, "TraversalType", TraversalType);
}

const VarDecl *getVarDeclaration(const Expr *e) {
  if (const DeclRefExpr *DRE = dyn_cast<DeclRefExpr>(e)) {
    // It's a reference to a declaration...
    return dyn_cast<VarDecl>(DRE->getDecl());
  }
  return nullptr;
}

const VarDecl *getVarDeclaration(const DeclRefExpr *e) {
  return dyn_cast<VarDecl>(e->getDecl());
}

void TraversalTypeCheck::registerMatchers(MatchFinder *Finder) {
  if (TraversalType == INDEX) {
    // Find array + value inside a loop
    Finder->addMatcher(
        binaryOperator(
            anyOf(allOf(hasLHS(hasType(isAnyPointer())),
                        hasRHS(allOf(hasType(isInteger()),
                                     expr(ignoringImpCasts(
                                         declRefExpr().bind("rhs")))))),
                  allOf(hasRHS(hasType(isAnyPointer())),
                        hasLHS(allOf(hasType(isInteger()),
                                     expr(ignoringImpCasts(
                                         declRefExpr().bind("lhs"))))))),
            anyOf(hasOperatorName("+"), hasOperatorName("-")),
            hasAncestor(compoundStmt(hasParent(
                forStmt(hasIncrement(anyOf(binaryOperator().bind("binary"),
                                           unaryOperator().bind("unary"))))
                    .bind("loop"))))),
        this);

    // Find array index inside a loop
    Finder->addMatcher(
        arraySubscriptExpr(
            hasAncestor(compoundStmt(hasParent(
                forStmt(hasIncrement(anyOf(binaryOperator().bind("binary"),
                                           unaryOperator().bind("unary"))))
                    .bind("loop")))),
            hasIndex(ignoringImpCasts(declRefExpr().bind("idx")))),
        this);
  } else {
    Finder->addMatcher(
        forStmt(hasCondition(binaryOperator(hasLHS(hasType(isAnyPointer())))),
                hasIncrement(anyOf(
                    unaryOperator(hasUnaryOperand(hasType(isAnyPointer()))),
                    binaryOperator(hasLHS(hasType(isAnyPointer()))))))
            .bind("for"),
        this);
  }
}

void TraversalTypeCheck::check(const MatchFinder::MatchResult &Result) {
  // Index body usage
  const auto *Lhs = Result.Nodes.getNodeAs<DeclRefExpr>("lhs");
  const auto *Rhs = Result.Nodes.getNodeAs<DeclRefExpr>("rhs");
  const auto *Idx = Result.Nodes.getNodeAs<DeclRefExpr>("idx");
  // Index loop
  const auto *Loop = Result.Nodes.getNodeAs<ForStmt>("loop");
  // Pointer loop
  const auto *For = Result.Nodes.getNodeAs<ForStmt>("for");

  // Handle traversal by pointer
  if (For) {
    diag(For->getBeginLoc(), "for loop uses traversal by pointer");
    return;
  }

  // Handle traversal by index
  const DeclRefExpr *bodyUse = nullptr;
  const Expr *loopIncr = nullptr;

  if (Lhs) {
    bodyUse = Lhs;
  } else if (Rhs) {
    bodyUse = Rhs;
  } else if (Idx) {
    bodyUse = Idx;
  }

  const auto *Bin = Result.Nodes.getNodeAs<BinaryOperator>("binary");
  const auto *Un = Result.Nodes.getNodeAs<UnaryOperator>("unary");

  if (Bin) {
    loopIncr = Bin->getLHS();
  } else if (Un) {
    loopIncr = Un->getSubExpr();
  }

  if (getVarDeclaration(bodyUse) == getVarDeclaration(loopIncr)) {
    diag(Loop->getBeginLoc(), "for loop uses traversal by index");
  }
}

} // namespace students
} // namespace tidy
} // namespace clang
