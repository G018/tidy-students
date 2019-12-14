//===--- RedundantPointerComparisonCheck.cpp - clang-tidy -----------------===//

#include "RedundantPointerComparisonCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Lex/Lexer.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace students {

void RedundantPointerComparisonCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      ifStmt(hasCondition(
          binaryOperator(anyOf(hasOperatorName("!="), hasOperatorName("==")),
                         hasEitherOperand(ignoringImpCasts(expr(nullPointerConstant()))))
              .bind("comp"))),
      this);
}

void RedundantPointerComparisonCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *Comp = Result.Nodes.getNodeAs<BinaryOperator>("comp");
  diag(Comp->getExprLoc(), "redundant nullptr comparison");
}

} // namespace students
} // namespace tidy
} // namespace clang
