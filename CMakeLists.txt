set(LLVM_LINK_COMPONENTS support)

add_clang_library(clangTidyStudentsModule
  BadVariableNameCheck.cpp
  DoubleComparisonCheck.cpp
  FunctionlessClassCheck.cpp
  RedundantPointerComparisonCheck.cpp
  ReimplementAlgorithmCheck.cpp
  TraversalTypeCheck.cpp
  UnnecessaryFunctionWrapperCheck.cpp
  UnnecessaryThisPointerCheck.cpp
  UnusedInitializerListCheck.cpp
  StudentsTidyModule.cpp

  LINK_LIBS
  clangAST
  clangASTMatchers
  clangLex
  clangBasic
  clangTidy
  )
