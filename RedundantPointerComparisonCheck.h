//===--- RedundantPointerComparisonCheck.h - clang-tidy --------------*- C++ -*-===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_STUDENTS_REDUNDANTPOINTERCOMPARISONCHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_STUDENTS_REDUNDANTPOINTERCOMPARISONCHECK_H

#include "../ClangTidy.h"

namespace clang {
namespace tidy {
namespace students {

/// FIXME: Write a short description.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/students-redundant-pointer-check.html
class RedundantPointerComparisonCheck : public ClangTidyCheck {
public:
  RedundantPointerComparisonCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

} // namespace students
} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_STUDENTS_REDUNDANTPOINTERCHECKCHECK_H
