set(LLVM_LINK_COMPONENTS support)

add_clang_library(clangTidyStudents

  LINK_LIBS
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  clangSerialization
  clangTidy
  clangTidyUtils
  clangTooling
  )
