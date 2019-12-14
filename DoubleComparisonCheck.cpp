//===--- DoubleComparisonCheck.cpp - clang-tidy -----------------===//

#include "DoubleComparisonCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Lex/Lexer.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace students {

void DoubleComparisonCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      binaryOperator(anyOf(hasOperatorName("=="), hasOperatorName("!=")),
                     hasLHS(hasType(realFloatingPointType())),
                     hasRHS(hasType(realFloatingPointType())))
          .bind("comp"),
      this);
}

void DoubleComparisonCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *Comp = Result.Nodes.getNodeAs<BinaryOperator>("comp");

  diag(Comp->getBeginLoc(),
       "when comparing doubles for equality, consider using a threshold");
}

} // namespace students
} // namespace tidy
} // namespace clang
