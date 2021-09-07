# Skia
#### Instructions to build Skia with Visual Studio and clang-cl on windows

The Derive team uses Visual Studio 2019 Community on Windows 10.
Half of the instructions can be (https://skia.org/docs/user/build/)[found in the skia docs], and half in other places scattered around the web.

1. Install Python 2+
2. Install Visual Studio 2019
3. Install Clang via Visual Studio Installer
4. Build the tools with python
5. Modify build_skia.sh
6. Build skia

## 3 - Install Clang with the Visual Studio Installer

Refer to (https://docs.microsoft.com/en-us/cpp/build/clang-support-cmake?view=msvc-160)[Clang/LLVM support in Visual Studio CMake projects]

* Run the Visual Studio installer and modify visual studio
* Install C++ Clang-cl from the **Desktop development with C++** optional components

## 4 - Modify build_skia.sh

Updated the following information in `dependencies/build/build_skia_[xxxxxx].sh`

`win_vc = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC"`
This should be your Visual Studio installation "VC" directory. Check the path as it can be different on your machine.
Note that the folder slashes should be windows backslash \ format, and not forwardslash / format

`clang_win = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\Llvm"`
This should be the folder to which Visual Studio installed the LLVM clang tools. This is usually found in `Tools\Llvm` inside your VC folder, but check the path as it can be different on your machine. Example:

## 5 - Build skia
Run `dependencies/build/build_skia_[xxxxxx].sh` to build and make your flavor of skia!

If all is well, the generated static library will be found in `dependencies/lib/release` or `dependencies/lib/debug`
