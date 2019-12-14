set(LLVM_LINK_COMPONENTS support)

add_clang_library(clangTidyStudentsModule
  RedundantPointerComparisonCheck.cpp
  FunctionlessClassCheck.cpp
  StudentsTidyModule.cpp

  LINK_LIBS
  clangAST
  clangASTMatchers
  clangLex
  clangBasic
  clangTidy
  )
