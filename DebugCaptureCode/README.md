# DebugCaptureCode
This project is an MFC based dialog application.

## Adjusting the output directories of Visual Studio 2019
This is a pet peeve of mine. The default settings of VS 2019 projects outputs and strores 32-bit x86 binaries into different directory structure than 64-bit x64 binaries.

In a word, **annoying!**

### Default directories for 32-bit x86 (dumb!)
**What binaries are these? x86 or x64?**
- `project_root\Release`
- `project_root\Debug`

### Default directories for 64-bit x64
**Hey look, it's obvious what platform binaries are in this directory!**

- `project_root\x64\Release`
- `project_root\x64\Debug`

### Better idea
Why not create directory structures for x86 the same as x64, *with proper names*? Then things will be self-documenting and obvious what platform binary is in the directory.

#### x64
Like the normal default directory structure.

- `project_root\x64\Release`
- `project_root\x64\Debug`

#### x86
New structure is similar to x64 and actually named for the target platform (x86 == Win32)

- `project_root\Win32\Release`
- `project_root\Win32\Debug`

## The fix
To create platform named directory structures for x86 and x64, simply edit the project properties configuration.

Change **Output Directory** and **Intermediate Direcotry** as shown below:

![image](https://user-images.githubusercontent.com/16089554/160507756-e27948df-ebb1-451b-9138-b04df7cf0652.png)

