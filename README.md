# Arduino diode voltage drop evaluation
This code permits to compute the voltage drop of a diode or a led with an arduino uno and an MCP4725 DAC.

## MCP4725 12-bit I2C DAC
You need an arduino uno and an MCP4725 Breakout Board which is a 12-bit I2C DAC.
You also need to download the [Adafruit MCP4725 12-bit I2C DAC Driver library](https://github.com/adafruit/Adafruit_MCP4725 "Adafruit MCP4725 library").
On the hardware, you need to plug the MCP4725 DAC to the arduino using an I2C connexion (2 wires).
You can search the web for more info about I2C connexions.

For the software, you will need to find the address of the DAC using an [I2C scanner](http://playground.arduino.cc/Main/I2cScanner "I2C scanner") and replace the value `dac.begin(0x60);` with the right address.

## Output
The drop voltage is printed on the serial monitor of the arduino IDE.

# How it works?
You need to place the DAC output on the + of the diode. 
The - of the diode is linked to the ground via a resistor (1K Ohms). 
The - of the diode is also linked to the analog input A0.

If the DAC voltage is too low, the diode is blocked and A0 is at the ground.
The DAC voltage is increased slowly, until the A0 voltage is above a small constant.
Then the voltage difference is the voltage drop of the component.

VdacOut -- diode -- (resistor -- ground, V A0) 
![Schematic](http://elaurent.benaroya.free.fr/github/diodeVoltageDrop/diode_voltage_drop.png "Schematic")

## Measurement of the voltage drop
The DAC has values between 0 and 4095, the analog input has values between 0 and 1023.
The 0 corresponds to 0 Volt and the max values correspond to 5V.

The voltage across the diode is the difference between the DAC and the A0.

Diode Voltage = DACval/4096.*5. - A0val/1024.*5.

# Comments
## Limitation
The voltage drop is limited to 5V. 
An op amp with a external power supply can handle this limitation, on the DAC output.

## TODO
* Multiple diodes could be handled in parallel (for the fun)...
* Simplified version
* quick version

ELB - 08/2017 


