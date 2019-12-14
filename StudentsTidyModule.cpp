//===--- StudentsTidyModule.cpp - clang-tidy ------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "FunctionlessClassCheck.h"
#include "RedundantPointerComparisonCheck.h"

namespace clang {
namespace tidy {
namespace students {

class StudentsModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<FunctionlessClassCheck>(
        "students-functionless-class");
    CheckFactories.registerCheck<RedundantPointerComparisonCheck>(
        "students-redundant-pointer-comparison");
  }
};

// Register the StudentsModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<StudentsModule>
    X("students-module", "Adds students-related checks.");

} // namespace students

// This anchor is used to force the linker to link in the generated object file
// and thus register the StudentsModule.
volatile int StudentsModuleAnchorSource = 0;

} // namespace tidy
} // namespace clang
