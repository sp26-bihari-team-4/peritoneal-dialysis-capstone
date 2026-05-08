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

## Important Commands

As mentioned in the setup, you can run the following command to compile the code for Arduino:

```sh
pio run -e uno
```

For convenience, we've added a `compile` target in our Makefile. So with Make installed, you can equivalently run:

```sh
make compile
```

To compile and flash the code to a connected Arduino:

```sh
pio run -e uno -t upload
```

Or equivalently:

```sh
make flash
```

Use one of the following two commands to display the serial console:

```sh
pio device monitor
make serial-console
```

Use one of the following two commands to run our unit tests:

```sh
pio test -e native
make run-tests
```

To run linting:

```sh
pio check -e uno --fail-on-defect high --fail-on-defect medium --fail-on-defect low
```

To check code formatting on all the source files:

```sh
clang-format --dry-run $(find src lib include test -regex ".*\.\(cpp\|h\)")
```

The previous two commands can be easily run with:

```sh
make lint
```

To automatically fix formatting issues identified by clang-format, run one of the following two commands. However, be warned that it may make unwanted formatting changes to your code.

```sh
clang-format -i $(find src lib include test -regex ".*\.\(cpp\|h\)")
make format
```

To generate the Doxygen documentation site in `doc/html`, simply run:

```sh
doxygen
```

Lastly, if you'd like to remove the compiled PlatformIO builds, run:

```sh
pio run -e uno -t clean
pio run -e native -t clean
```

Or equivalently:

```sh
make clean
```

The PlatformIO CLI has many other useful commands, which are all documented in [the CLI guide](https://docs.platformio.org/en/stable/core/userguide/index.html). Likewise, [clang-tidy](https://releases.llvm.org/21.1.2/tools/clang/tools/extra/docs/clang-tidy/index.html) and [clang-format](https://releases.llvm.org/21.1.2/tools/clang/docs/ClangFormat.html) have many interesting options. We have both of them configured using config files (`.clang-tidy` and `.clang-format`). The clang-format docs are also useful for seeing all the [style options](https://releases.llvm.org/21.1.2/tools/clang/docs/ClangFormatStyleOptions.html).

## Circuit Design

### Overview

The goal of the system is to independently control the shapes of two nitinol wires by heating them to the austenitic phase (or allowing them to cool back to the martensitic phase). In order to complete the martensite-to-austenite transition and induce a shape change, the "Af" transition temperature must be reached. In our wires, this is 45 &deg;C. Since the wires are to be implanted in the body, they will normally be at 37 &deg;C. Therefore, we need to heat the nitinol wires by up to 8 &deg;C.

In our system, this heating is accomplished by passing an electric current through the wires (i.e., [Joule heating][joule-heating]). Two power MOSFETs allow significant power to be delivered to the wires from a voltage source. These MOSFETs are switched on or off by a microcontroller using pulse-width modulation (PWM) to achieve a desired average voltage, which is controlled by two potentiometers. A TFT display shows in real-time the PWM duty cycle of each wire. This duty cycle represents the wire voltage, which is proportional to the square root of the power (and the square root of the rate of temperature increase, assuming no heat loss).

### Detailed Description

![The circuit schematic, depicting the Arduino, potentiometers, MOSFETs, and LCD module.](./resource/circuit-schematic.png)

The system is controlled by an [Arduino UNO R3][arduino-uno-r3] microcontroller, which can be programmed and powered via the built-in USB port.

Two 10kΩ rotary potentiometers control the power to the nitinol wires. The resistive track terminals are tied to +5V and (Arduino) GND, and the wiper terminals are tied to analog input pins A0 and A2 of the Arduino; this allows the voltage divider outputs of the potentiometers to be sampled by the Arduino.

The Arduino replicates these input voltages on two digital output pins using PWM. Each digital output is controlled by one analog input; the pair of pins comprise a "channel" that in turn corresponds to one nitinol wire. Channel 1 comprises input A0 and output D5, and channel 2 comprises input A2 and output D6:

|Channel|Input Pin|Output Pin|
|-------|---------|----------|
|1      |A0       |D5        |
|2      |A2       |D6        |

These PWM output pins are used to drive two logic-level MOSFETs ([Infineon IRLZ34N][irlz34n]) that deliver power to the nitinol wires. Each PWM output connects to the gate terminal of one MOSFET. The MOSFET source terminals connect to Arduino GND, and the drain terminals connect to the negative ends of the nitinol wires (the loads). Wiring each MOSFET this way ensures that the gate-to-source voltage ("Vgs") can surpass the threshold voltage ("Vth," approx. 1-2V), which is necessary to conduct current between the drain and source terminals. Indeed, this condition is acheived when the corresponding PWM output is high: the gate will be at 5V, and because the source is 0V (GND), Vgs is 5V&mdash;well in excess of Vth.

While nitinol has a relatively high resistivity, the nitinol wires still don't have a particularly high resistance (around a few ohms, depending on the length and thickness). As a result, for a given voltage across the wires, they'll draw a large amount of current. However, the Arduino 5V line can only provide a few hundred milliamps (depending on the power source). Therefore, an external power supply must be used. The positive terminal should connect to the positive ends of the nitinol wires (labeled VDD in the schematic), and the negative terminal should connect to the MOSFET source terminals (and, by extension, also Arduino GND).

An [Adafruit 0.96" 160&times;80 Color TFT display][tft-display] is used to display the PWM duty cycle of each nitinol wire in real-time. Since the display communicates via SPI, the hardware SPI pins D10, D11, and D13 of the Arduino are tied to the TFTCS, MOSI, and SCK pins, respectively, of the display module. Data and commands are sent via a side channel, from pin D8 on the Arduino to the DC pin on the display. The display is also powered by the Arduino, with VIN and GND tied to the Arduino's +5V and GND, respectively. All other pins on the display are left unconnected (they have internal pull-ups or pull-downs).

[joule-heating]: https://en.wikipedia.org/wiki/Joule_heating
[arduino-uno-r3]: https://docs.arduino.cc/hardware/uno-rev3/
[irlz34n]: https://www.infineon.com/part/IRLZ34N
[tft-display]: https://www.adafruit.com/product/3533
