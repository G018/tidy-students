set(LLVM_LINK_COMPONENTS support)

add_clang_library(clangTidyStudentsModule
  StudentsTidyModule.cpp

  LINK_LIBS
  clangAST
  clangASTMatchers
  clangBasic
  clangTidy
  )
