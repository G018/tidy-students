//===--- FunctionlessClassCheck.cpp - clang-tidy -----------------===//

#include "FunctionlessClassCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Lex/Lexer.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace students {

void FunctionlessClassCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      cxxRecordDecl(
          isClass(), isDefinition(),
          unless(anyOf(isDerivedFrom(anything()),
                       has(cxxMethodDecl(
                           isUserProvided(),
                           unless(hasUnderlyingDecl(cxxConstructorDecl())))))))
          .bind("def"),
      this);
}

void FunctionlessClassCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *Def = Result.Nodes.getNodeAs<RecordDecl>("def");

  diag(Def->getLocation(),
       "class has no member functions and should be rewritten as a struct");
}

} // namespace students
} // namespace tidy
} // namespace clang
