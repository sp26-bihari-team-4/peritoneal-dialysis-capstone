# Repositionable Catheter for Peritoneal Dialysis

This repository contains the software and circuit schematics created by Team 4 for our CSE capstone. At a high level, our system allows a user to control the power provided to two nitinol wires to heat them up and induce them to change shape. If embedded into a catheter, this would cause the catheter to move; in principle, this would allow repositioning of the catheter after it's been implanted into a patient.

The following sections describe how to set up the software environment, important commands, our software architecture, our circuit design, and our CI/CD setup.

## Software Environment Setup

You can get the code in this repository with Git (i.e., `git clone`). Alternatively, you can download and extract the ZIP file from GitHub.

### Compiling and Flashing

To compile the software and flash it to a microcontroller (Arduino), you need to have PlatformIO installed. PlatformIO has their own install instructions in [their docs](https://docs.platformio.org/en/stable/core/installation/methods/index.html), but the following are our recommended methods. Also, please note that links to the PlatformIO docs will point to the latest stable version, which may be different than the version used by this project.

#### Linux/Unix

If your distro's package repository has PlatformIO or PlatformIO Core version 6.1, we recommend installing and using that. Otherwise, install Python 3.14, optionally [set up a virtual environment](https://docs.python.org/3/library/venv.html), and install PlatformIO from PyPI:

```sh
pip install platformio==6.1.19
```

#### macOS

For Mac, we recommend using the [Homebrew package manager](https://brew.sh/). With Homebrew installed, just run:

```sh
brew install platformio@6.1.19
```

#### Windows

PlatformIO is implemented as a Python package, so you'll first need to install Python. We recommend using the Python Install Manager, which you can install with the following PowerShell command:

```powershell
winget install Python.PythonInstallManager
```

With that installed, you can run the following command to get Python 3.14:

```powershell
pymanager install 3.14
```

Next you can install the PlatformIO package with pip:

```powershell
python -m pip install platformio==6.1.19
```

The above command will likely print some warnings about needing to add a directory to your PATH variable. Copy the path to the directory it gives you (it should end with `Scripts`), and follow [a tutorial like this](https://www.wikihow.tech/Add-Path-on-Windows) to add it to your User Path variable. Note that you'll need to restart PowerShell for this change to take effect.

#### Run PlatformIO

With PlatformIO installed, you should be able to run the following command to compile the project:

```sh
pio run -e uno
```

The result should be something like:

```
Environment    Status    Duration
-------------  --------  ------------
uno            SUCCESS   00:00:01.232
```

With an Arduino connected to your computer, you can run the following command to compile and flash the software to the microcontroller:

```sh
pio run -e uno -t upload
```

### Development Dependencies

There are a couple other programs you'll want installed if you plan on making any changes to the code.

#### GCC

While PlatformIO manages the compiler for the microcontroller, our unit tests run natively and require GCC (specifically `g++`) to be installed. On Linux, if you don't already have GCC, it's almost certainly available in your distro's package repository. On macOS, you can install GCC from Homebrew with `brew install gcc`.

On Windows, the easiest way to get GCC is to install a [Mingw-w64 distribution](https://www.mingw-w64.org/downloads/). A relatively small one is [w64devkit](https://github.com/skeeto/w64devkit/releases/tag/v2.7.0). Just download and extract the x64 archive. The resulting directory should have an executable called `w64devkit.exe`. Running this program will give you a Unix-like shell that includes common tools like GCC and Make. There's also a way to add these programs to your User Path variable, but it's not necessary.

With GCC installed (and available in your shell), you can use the following command to run the unit tests:

```sh
pio test -e native
```

#### Clang Tools

PlatformIO manages an installation of [clang-tidy](https://releases.llvm.org/21.1.2/tools/clang/tools/extra/docs/clang-tidy/index.html), but our linting setup also uses [clang-format](https://releases.llvm.org/21.1.2/tools/clang/docs/ClangFormat.html) (version 21), so it needs to be installed separately.

#### Doxygen

Our documentation is generated with [Doxygen](https://doxygen.nl/index.html). If you want to do that locally, install version 1.16.1 from their site or your preferred package manager.

#### KiCad

One last piece of software you might want to install is [KiCad](https://www.kicad.org/) (version 9), which was used to make our circuit schematic. With it installed, you should be able to open the KiCad project file `hardware/capstone.kicad_pro` to see and modify the schematic.
