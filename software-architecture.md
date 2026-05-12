```plantuml
@startuml{software_architecture.png}

' Legend
legend top left
Dashed arrow = inheritance/implementation
Solid diamond = ownership (by value)
Open diamond = ownership (by reference)
endlegend

' Interfaces
interface IDisplay
interface IHAL
interface TFTDriver
interface IInput
interface IOutput

' Classes
class SerialDisplay
class TFTDisplay
class ArduinoHAL
class AdafruitTFTDriver
class PotentiometerInput
class PWMOutput
class CatheterController
class Channel

' Structs
struct TFTPoint
struct "TFTDisplay::Layout" as Layout

' Enums
enum TFTColor

' Inheritance/implementation
IDisplay <|.. SerialDisplay
IDisplay <|.. TFTDisplay
IHAL <|.. ArduinoHAL
TFTDriver <|.. AdafruitTFTDriver
IInput <|.. PotentiometerInput
IOutput <|.. PWMOutput

' Ownership (by value)
CatheterController *-- "2" Channel : channel1,\nchannel2
TFTDisplay +-- Layout : Nested\nClass
TFTDisplay *-- "1" Layout : layout
TFTDisplay *-- "2" TFTColor: CLEAR_COLOR,\nTEXT_COLOR
Layout *-- "2" TFTPoint : wire1Text,\nwire2Text

' Ownership (by reference)
CatheterController o-- "1" IDisplay : display
Channel o-- "1" IInput : input
Channel o-- "1" IOutput : output
PotentiometerInput o-- "1" IHAL : hal
PWMOutput o-- "1" IHAL : hal
SerialDisplay o-- "1" IHAL : hal
TFTDisplay o-- "1" TFTDriver : driver

@enduml
```
