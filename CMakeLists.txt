set(LLVM_LINK_COMPONENTS support)

add_clang_library(clangTidyStudentsModule
  DoubleComparisonCheck.cpp
  FunctionlessClassCheck.cpp
  RedundantPointerComparisonCheck.cpp
  TraversalTypeCheck.cpp
  UnusedInitializerListCheck.cpp
  StudentsTidyModule.cpp

  LINK_LIBS
  clangAST
  clangASTMatchers
  clangLex
  clangBasic
  clangTidy
  )
