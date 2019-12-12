# tidy-students

A [clang-tidy] module to check for _common_ student non-idioms.

## Setup

In order to run the checks provided in this repository, you will have to build
the `clang-tidy` binary from source after installing this module.

_*Note:* We use `ALLCAPS` for directories that depend on your setup._

### Prerequesites

You should at least have `cmake`, but also highly recommend having `ninja`.

### Setup the LLVM project

 - Get the source of [LLVM], [Clang], and `clang-tools-extra`.

```
$ git clone https://github.com/llvm/llvm-project
```

 - Select a release for the source, below is the one used to develop the module.

```
LLVM_PROJECT$ git checkout llvmorg-8.0.1
```

 - Create a build directory, then use `cmake` to configure the project.

```
BUILD_DIR$ cmake LLVM_PROJECT/llvmi -G Ninja -DLLVM_ENABLE_PROJECTS='clang;clang-tools-extra'
```

 - At this point you could get the first build going, since it takes forever.

### Setup this module

 - Install this repository into the `clang-tidy` source tree.

```
LLVM_PROJECT$ git clone TIDY_STUDENTS_REPO clang-tools-extra/clang-tidy/students
```

 - Add the `students` module to the build system.

```
LLVM_PROJECT$ echo "add_subdirectory(students)" >> clang-tools-extra/clang-tidy/CMakeLists.txt
```

 - Add the `students` module as a tool dependency.

```
LLVM_PROJECT$ echo "target_link_libraries(clang-tidy PRIVATE clangTidyStudentsModule) >> clang-tools-extra/clang-tidy/tools/CMakeLists.txt
```

 - Add the `students` module source anchor to force linkage.

```c++
// Add this snippet inside the tidy::clang namespace in
//  LLVM_PROJECT/clang-tools-extra/clang-tidy/ClangTidyForceLinker.h
extern volatile int StudentsModuleAnchorSource;
static int LLVM_ATTRIBUTE_UNUSED StudentsModuleAnchorDestination =
    StudentsModuleAnchorSource;
```

_*Note:* add them manually, to preserve alphabetic order or avoid duplication._

## Building the tool

Just build the `clang-tidy` target from the build directory!

```
BUILD_DIR$ cmake --build . --target clang-tidy
```

## Use the tool

Run the built `clang-tidy` binary, enabling the `students` checks!

```
$ BUILD_DIR/bin/clang-tidy -checks=students-* SOURCE_FILE -- COMPILE_FLAGS
```

For more options checkout `-help` or [clang-tidy] documentation.

_*Note:* all the [clang-tidy checks] are still be available!._

## Contributing

To add a new check to this module do the following:
 - Pick a descriptive, short and unique `#new-name#` for the check.
 - Create `#NewName#Check.h` and `NewName.cpp` based on existing checks.
   - Make a copy, remove the implementation, then search and replace both
     `#OldName#` with `#NewName#` and `#old-name#` with `#new-name#`.
 - Add `#NewName#.cpp` to the sources of the module in `CMakeLists.cpp`.
 - Register it in `addCheckFactories` function of `StudentsTidyModule.cpp`.
   - Add `CheckFactories.registerCheck<#NewName#Check>("#new-name")`.
   - Remember to include `#NewName#.h` and preserve alphabetical ordering.

[llvm]: https://llvm.org
[clang]: https://clang.llvm.org
[clang-tidy]: https://clang.llvm.org/extra/clang-tidy
[clang-tidy checks]: https://clang.llvm.org/extra/clang-tidy/checks/list.html
