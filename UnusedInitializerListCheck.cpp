//===--- UnusedInitializerListCheck.cpp - clang-tidy -----------------===//

#include "UnusedInitializerListCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Lex/Lexer.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace students {

void UnusedInitializerListCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      binaryOperator(isAssignmentOperator(),
                     hasParent(compoundStmt(hasParent(cxxConstructorDecl()))),
                     hasRHS(ignoringImpCasts(anyOf(
                         floatLiteral(), integerLiteral(), imaginaryLiteral(),
                         stringLiteral(), userDefinedLiteral(), memberExpr(),
                         declRefExpr()))))
          .bind("assign"),
      this);
}

void UnusedInitializerListCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *Assign = Result.Nodes.getNodeAs<BinaryOperator>("assign");

  diag(
      Assign->getBeginLoc(),
      "simple variable assignment should be done in a member initializer list");
}

} // namespace students
} // namespace tidy
} // namespace clang
