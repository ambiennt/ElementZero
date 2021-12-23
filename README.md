<h1 align="center">
<img src="https://ipfs.io/ipfs/QmYiuQE7WUeawAMTvQf9RUC7wWXb2b1wCFddVBpt6U7e1S/logo.png" width="256px" height="256px" />
</h1>

<a href="https://github.com/Element-0/ElementZero/actions">![status](https://img.shields.io/github/workflow/status/Element-0/ElementZero/CI?style=for-the-badge)</a>
![platform](https://img.shields.io/badge/platform-win--x64%20%7C%20wine--linux--x64-green?style=for-the-badge)</a><br>
<a href="https://github.com/Element-0/ElementZero/releases/latest">![Latest Tag](https://img.shields.io/github/v/tag/Element-0/ElementZero?label=LATEST%20TAG&style=for-the-badge)![GitHub Releases (by Asset)](https://img.shields.io/github/downloads/Element-0/ElementZero/latest/total?style=for-the-badge)</a><br>

Run Windows version of BDS in Linux with mod support (Yes, it also can be run in Windows)

## NOTICE

This fork of ElementZero is currently being updated for BDS version 1.16.20.03 (Windows) ONLY. Note that version 1.16.20.03 shares the same protcol version as version 1.16.40.02, so clients with either version may join.


## Features

0. Compatiable with official BDS
1. And support behavior pack with custom item/recipes/scripts (* vanilla server *does* support them, but disabled in code)
2. Can be run in Windows and Linux (with Wine)
3. Native modding support, with one of the most robust BDS SDKs to date

## FAQ

Q: Why not use a native Linux version?<br>
A: The Windows version has noticeable performance improvements, even when running under Wine.

Q: Can the Windows version run directly under Wine?<br>
A: No, because Microsoft uses Chakra.dll, which contains a lot of references to private dlls. (It also prevents you from running on systems prior to Windows 10.)

Q: How does it work?<br>
A: A DLL was created that simply forwards all APIs to the open source version of Chakra engine i.e. ChakraCore. This version can run directly under Wine.


## Server setup

1. Download bedrock dedicated server binary for [1.16.20.03](https://minecraft.azureedge.net/bin-win/bedrock-server-1.16.20.03.zip) and extract to a folder
2. Download the latest release of ElementZero from the [releases page](https://github.com/ambiennt/ElementZero/releases/)
3. Copy the contents of the ElementZero release to your server folder
4. Run bedrock_server_mod.exe to start server instance. bedrock_server.exe and the bedrock_server.pdb are not required to be in your server folder
5. Configure your server mods after running bedrock_server_mod.exe once to generate the custom.yaml file

## Visual Studio 2019 workloads and components

1. Microsoft.VisualStudio.Workload.NativeDesktop
2. Microsoft.VisualStudio.Workload.ManagedDesktop
3. Microsoft.VisualStudio.Component.VC.Tools.x86.x64
4. Microsoft.VisualStudio.Component.Windows10SDK.18362
5. Microsoft.VisualStudio.ComponentGroup.NativeDesktop.Llvm.Clang

## How to set up a development environment (beginner friendly)

1. Make sure you have all the above workloads and components installed via the Visual Studio Installer
2. Run `git clone https://github.com/ambiennt/ElementZero.git` in your desired repository directory
3. Open the repository in Visual Studio, and create a `Lib` folder in the root of the repository
4. In the `.\Lib` folder, copy [these 3 files](https://github.com/ambiennt/ElementZeroLib) inside the directory
4. Open the developer command prompt, and `cd` to `.\ElementZero>` ($(SolutionDir))
4. Run `git submodule update --init --recursive` to install dependencies
5. In `.\ElementZero>` ($(SolutionDir)), run `cd vcpkg && bootstrap-vcpkg.bat` to install vcpkg in source tree
6. In `.\ElementZero>` ($(SolutionDir)), install vcpkg dependencies by `vcpkg\vcpkg.exe install @vcpkg.txt`; this may take some time
7. In the Visual Studio solution explorer, right click CMakeLists.txt in `.\ElementZero>` ($(SolutionDir)) and click `generate CMake cache`; this may take some time
8. You are now set up! For release builds, it is recommended to set the build type to `Release` and `rebuild all` before starting custom mod development

## How to generate lib files yourself (optional)

0. Download and install [EatPdb](https://github.com/CodeHz/EatPdb)
1. Copy $(SolutionDir)\eatpdb.yaml to bds folder
2. Run `eatpdb exec eatpdb.yaml`
3. Open `x64 Native Tools Command Prompt for VS 2019`, then run `lib /def:bedrock_server_mod.def /machine:x64`
4. Copy bedrock_server_mod.lib, addition_symbols.db, bedrock_server_mod.exe to $(SolutionDir)Lib\

## LICENSE

GPLv3