//===--- BadVariableNameCheck.cpp - clang-tidy -----------------===//

#include "BadVariableNameCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Lex/Lexer.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace students {

void BadVariableNameCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(decl(anyOf(varDecl(), fieldDecl())).bind("var"), this);
  Finder->addMatcher(decl(anyOf(recordDecl(), classTemplateDecl(),
                                classTemplatePartialSpecializationDecl(),
                                classTemplateSpecializationDecl()))
                         .bind("class"),
                     this);
}

void BadVariableNameCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *Var = Result.Nodes.getNodeAs<NamedDecl>("var");
  const auto *Class = Result.Nodes.getNodeAs<NamedDecl>("class");

  if (Var) {
    std::string name = Var->getNameAsString();
    if (isupper(name[0])) {
      diag(Var->getBeginLoc(),
           "non-class variable names should not be capitalized");
    } else if (name[0] == '_') {
      diag(Var->getBeginLoc(), "variables should not begin with _");
    }
  } else if (Class) {
    std::string name = Class->getNameAsString();

    if (!isupper(name[0])) {
      diag(Class->getBeginLoc(),
           "class names should begin with a capital letter");
    }
  }
}

} // namespace students
} // namespace tidy
} // namespace clang