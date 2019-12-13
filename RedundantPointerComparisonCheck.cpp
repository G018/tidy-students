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
          binaryOperator(hasOperatorName("=="),
                         hasLHS(expr(hasType(isAnyPointer())).bind("lhs")),
                         hasRHS(ignoringImpCasts(expr(nullPointerConstant()))))
              .bind("comp"))),
      this);
}

void RedundantPointerComparisonCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *Comp = Result.Nodes.getNodeAs<BinaryOperator>("comp");
  const auto *LHS = Result.Nodes.getNodeAs<Expr>("lhs");

  diag(Comp->getExprLoc(), "redundant nullptr comparison")
      << FixItHint::CreateReplacement(
             Comp->getSourceRange(),
             Lexer::getSourceText(
                 CharSourceRange::getTokenRange(LHS->getSourceRange()),
                 *Result.SourceManager, Result.Context->getLangOpts()));
}

} // namespace students
} // namespace tidy
} // namespace clang
