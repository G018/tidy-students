//===--- DoubleComparisonCheck.h - clang-tidy --------------*- C++ -*-===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_STUDENTS_DOUBLECOMPARISONCHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_STUDENTS_DOUBLECOMPARISONCHECK_H

#include "../ClangTidy.h"

namespace clang {
namespace tidy {
namespace students {

class DoubleComparisonCheck : public ClangTidyCheck {
public:
  DoubleComparisonCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

} // namespace students
} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_STUDENTS_DOUBLECOMPARISONCHECK_H
