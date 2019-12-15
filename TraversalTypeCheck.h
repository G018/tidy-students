//===--- TraversalTypeCheck.h - clang-tidy --------------*- C++ -*-===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_STUDENTS_TRAVERSALTYPECHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_STUDENTS_TRAVERSALTYPECHECK_H

#include "../ClangTidy.h"

namespace clang {
namespace tidy {
namespace students {

class TraversalTypeCheck : public ClangTidyCheck {
  const std::string TraversalType;
  static const std::string INDEX;
  static const std::string POINTER;

public:
  TraversalTypeCheck(StringRef Name, ClangTidyContext *Context);
  void storeOptions(ClangTidyOptions::OptionMap &Opts) override;
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

} // namespace students
} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_STUDENTS_TRAVERSALTYPECHECK_H
