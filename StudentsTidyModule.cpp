//===--- StudentsTidyModule.cpp - clang-tidy ------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "BadVariableNameCheck.h"
#include "DoubleComparisonCheck.h"
#include "FunctionlessClassCheck.h"
#include "RedundantPointerComparisonCheck.h"
#include "ReimplementAlgorithmCheck.h"
#include "TraversalTypeCheck.h"
#include "UnnecessaryFunctionWrapperCheck.h"
#include "UnnecessaryThisPointerCheck.h"
#include "UnusedInitializerListCheck.h"

namespace clang {
namespace tidy {
namespace students {

class StudentsModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<BadVariableNameCheck>(
        "students-bad-variable-name");
    CheckFactories.registerCheck<DoubleComparisonCheck>(
        "students-double-comparison");
    CheckFactories.registerCheck<FunctionlessClassCheck>(
        "students-functionless-class");
    CheckFactories.registerCheck<RedundantPointerComparisonCheck>(
        "students-redundant-pointer-comparison");
    CheckFactories.registerCheck<ReimplementAlgorithmCheck>(
        "students-reimplement-algorithm-check");
    CheckFactories.registerCheck<TraversalTypeCheck>("students-traversal-type");
    CheckFactories.registerCheck<UnnecessaryFunctionWrapperCheck>(
        "students-unnecessary-function-wrapper");
    CheckFactories.registerCheck<UnnecessaryThisPointerCheck>(
        "students-unnecessary-this-pointer");
    CheckFactories.registerCheck<UnusedInitializerListCheck>(
        "students-unused-initializer-list");
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
