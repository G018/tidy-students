//===--- UnnecessaryThisPointerCheck.cpp - clang-tidy -----------------===//

#include "UnnecessaryThisPointerCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Lex/Lexer.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace students {

void UnnecessaryThisPointerCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      memberExpr(has(cxxThisExpr().bind("p"))).bind("expr"), this);
}

void UnnecessaryThisPointerCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *P = Result.Nodes.getNodeAs<CXXThisExpr>("p");
  const auto *Expr = Result.Nodes.getNodeAs<MemberExpr>("expr");

  if (!P->isImplicit()) {
    diag(Expr->getBeginLoc(),
         "avoid explicit use of this pointer for field access");
  } 
}

} // namespace students
} // namespace tidy
} // namespace clang