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

const VarDecl *getDeclaration(const Expr *e) {
  if (const DeclRefExpr *DRE = dyn_cast<DeclRefExpr>(e)) {
    // It's a reference to a declaration...
    return dyn_cast<VarDecl>(DRE->getDecl());
  }

  return nullptr;
}

void TraversalTypeCheck::registerMatchers(MatchFinder *Finder) {
  if (TraversalType == INDEX) {
    // Find array + value inside a loop
    Finder->addMatcher(
        binaryOperator(
            hasEitherOperand(hasType(isAnyPointer())),
            hasEitherOperand(hasType(isInteger())),
            anyOf(hasOperatorName("+"), hasOperatorName("-")),
            hasAncestor(compoundStmt(hasParent(
                forStmt(hasIncrement(anyOf(binaryOperator().bind("binary"),
                                           unaryOperator().bind("unary"))))
                    .bind("loop")))))
            .bind("op"),
        this);

    // Find array index inside a loop
    Finder->addMatcher(
        arraySubscriptExpr(
            hasAncestor(compoundStmt(hasParent(
                forStmt(hasIncrement(anyOf(binaryOperator().bind("binary"),
                                           unaryOperator().bind("unary"))))
                    .bind("loop")))))
            .bind("arr"),
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
  const auto *Op = Result.Nodes.getNodeAs<BinaryOperator>("op");
  const auto *Arr = Result.Nodes.getNodeAs<ArraySubscriptExpr>("arr");
  const auto *Loop = Result.Nodes.getNodeAs<ForStmt>("loop");
  const auto *For = Result.Nodes.getNodeAs<ForStmt>("for");

  // Handle traversal by pointer
  if (For) {
    diag(For->getBeginLoc(), "for loop uses traversal by pointer");
    return;
  }

  // Handle traversal by index
  const Expr *bodyUse;
  const Expr *loopIncr;
  bool subscript = true;

  if (Arr) {
    bodyUse = Arr->getIdx();
  } else if (Op) {
    subscript = false;

    if (Op->getLHS()->getType()->isIntegerType()) {
      bodyUse = Op->getLHS();
    } else {
      bodyUse = Op->getRHS();
    }
  }

  const auto *Bin = Result.Nodes.getNodeAs<BinaryOperator>("op");
  const auto *Un = Result.Nodes.getNodeAs<UnaryOperator>("arr");

  if (Bin) {
    loopIncr = Bin->getLHS();
  } else if (Un) {
    loopIncr = Un->getSubExpr();
  }

  if (getDeclaration(bodyUse) == getDeclaration(loopIncr)) {
    diag(Loop->getBeginLoc(), "for loop uses traversal by index");
  }
}

} // namespace students
} // namespace tidy
} // namespace clang
