//===--- ReimplementAlgorithmCheck.cpp - clang-tidy -----------------------===//

#include "ReimplementAlgorithmCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Lex/Lexer.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace students {

using internal::Matcher;

// Helper to all uses correspond to the same variable
bool areSameVar(std::initializer_list<const VarDecl *> container) {
  auto &first = *container.begin();
  for (auto var : container) {
    if (!var || var->getCanonicalDecl() != first->getCanonicalDecl())
      return false;
  }
  return true;
}

// Helper to bind the use of a variable
Matcher<Expr> varUseBind(const char *name) {
  return ignoringParenImpCasts(declRefExpr(to(varDecl().bind(name))));
}

// Helper to disregard the use of braces in for/if/etc.
Matcher<Stmt> ignoringBraces(const Matcher<Stmt> &m) {
  return anyOf(m, compoundStmt(hasAnySubstatement(m)));
}

// Helper to disregard a cleanup for an expr
Matcher<Expr> ignoringCleanup(const Matcher<Stmt> &m) {
  return anyOf(m, exprWithCleanups(has(m)));
}

// Helper to normalize operator[] on arrays and std::containers
Matcher<Expr> subscriptExpr(const Matcher<Expr> &base = expr()) {
  auto arr = arraySubscriptExpr(hasBase(base));
  auto cxx = cxxOperatorCallExpr(hasOverloadedOperatorName("[]"),
                                 hasArgument(0, base));
  return expr(anyOf(arr, cxx));
};

// Helper to normalize operator* on pointers and std::iterators
Matcher<Expr> dereferenceExpr(const Matcher<Expr> &target) {
  auto arr = unaryOperator(hasOperatorName("*"), hasUnaryOperand(target));
  auto cxx = cxxOperatorCallExpr(hasOverloadedOperatorName("*"),
                                 hasArgument(0, target));
  return expr(anyOf(arr, cxx));
};

// Helper to match traversals (binds init, incr, comp)
Matcher<Stmt> traversalMatcher(const Matcher<Stmt> &body) {
  auto VarInit =
      declStmt(hasSingleDecl(varDecl(hasInitializer(anything())).bind("init")));
  auto VarComp = anyOf(
      binaryOperator(hasOperatorName("<"), hasLHS(varUseBind("comp"))),
      ignoringCleanup(cxxOperatorCallExpr(hasOverloadedOperatorName("!="),
                                          hasArgument(0, varUseBind("comp")))));
  auto VarIncr = anyOf(
      unaryOperator(hasOperatorName("++"), hasUnaryOperand(varUseBind("incr"))),
      cxxOperatorCallExpr(hasOverloadedOperatorName("++"),
                          hasArgument(0, varUseBind("incr"))));

  return forStmt(hasLoopInit(VarInit), hasCondition(VarComp),
                 hasIncrement(VarIncr), hasBody(ignoringBraces(body)))
      .bind("traversal");
}

// Helper to confirm a traversal match is positive
const ForStmt *traversalMatches(const MatchFinder::MatchResult &Result) {
  const auto Traversal = Result.Nodes.getNodeAs<ForStmt>("traversal");

  const auto VarInit = Result.Nodes.getNodeAs<VarDecl>("init");
  const auto VarComp = Result.Nodes.getNodeAs<VarDecl>("comp");
  const auto VarIncr = Result.Nodes.getNodeAs<VarDecl>("incr");

  if (!areSameVar({VarInit, VarComp, VarIncr}))
    return nullptr; // Not recognized traversal!

  return Traversal;
}

// Helper to recognize access to sequence elements
Matcher<Expr> seqAccess(const Matcher<Expr> &m) {
  return ignoringParenImpCasts(anyOf(subscriptExpr(m), dereferenceExpr(m)));
};

void ReimplementAlgorithmCheck::registerMatchers(MatchFinder *Finder) {
  static auto MinMaxBody =
      ifStmt(hasCondition(binaryOperator(
                 anyOf(hasOperatorName("<"), hasOperatorName(">")),
                 hasEitherOperand(varUseBind("min-max-check")),
                 hasEitherOperand(seqAccess(varUseBind("seq-check"))))),
             hasThen(ignoringBraces(binaryOperator(
                 hasOperatorName("="), hasLHS(varUseBind("min-max-assign")),
                 hasRHS(seqAccess(varUseBind("seq-assign")))))));

  Finder->addMatcher(traversalMatcher(MinMaxBody), this);

  static auto FindBody = ifStmt(
      hasCondition(binaryOperator(
          hasOperatorName("=="), hasEitherOperand(varUseBind("find-check")),
          hasEitherOperand(seqAccess(varUseBind("seq-check"))))),
      hasThen(ignoringBraces(stmt())));

  Finder->addMatcher(traversalMatcher(FindBody), this);
}

void ReimplementAlgorithmCheck::check(const MatchFinder::MatchResult &Result) {
  if (auto Traversal = traversalMatches(Result)) {
    auto SeqCheck = Result.Nodes.getNodeAs<VarDecl>("seq-check");
    auto SeqAssign = Result.Nodes.getNodeAs<VarDecl>("seq-check");
    if (SeqCheck && !areSameVar({SeqCheck, SeqAssign}))
      return; // Sequence false positive!

    if (auto MinMaxCheck = Result.Nodes.getNodeAs<VarDecl>("min-max-check")) {
      auto MinMaxAssign = Result.Nodes.getNodeAs<VarDecl>("min-max-assign");
      if (!areSameVar({MinMaxCheck, MinMaxAssign}))
        return; // Min-Max false positive!

      diag(Traversal->getForLoc(), "think about using std::min/max_element!",
           DiagnosticIDs::Note);
    }
    if (auto FindCheck = Result.Nodes.getNodeAs<VarDecl>("find-check")) {
      diag(Traversal->getForLoc(), "think about using std::find/find_if!",
           DiagnosticIDs::Note);
    }
  }
}

} // namespace students
} // namespace tidy
} // namespace clang
