//===--- UnnecessaryFunctionWrapperCheck.cpp - clang-tidy -----------------===//

#include "UnnecessaryFunctionWrapperCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Lex/Lexer.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace students {

void UnnecessaryFunctionWrapperCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      functionDecl(has(compoundStmt(has(returnStmt(has(callExpr()))))))
          .bind("func"),
      this);
}

void UnnecessaryFunctionWrapperCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *Func = Result.Nodes.getNodeAs<FunctionDecl>("func");

  diag(Func->getBeginLoc(), "unnecessary function since only contains return "
                            "statement and function call");
}

} // namespace students
} // namespace tidy
} // namespace clang