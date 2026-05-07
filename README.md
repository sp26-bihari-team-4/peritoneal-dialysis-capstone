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