/**************************************************************************/
/*! 
    @file     find diode voltage
    @author   Adafruit Industries // ELB
    @license  BSD (see license.txt)

    This example will find the voltage of a diode with the MCP4725 DAC.   

    This is an example sketch for the Adafruit MCP4725 breakout board
    ----> http://www.adafruit.com/products/935
 
    Adafruit invests time and resources providing this open source code, 
    please support Adafruit and open-source hardware by purchasing 
    products from Adafruit!
    
    ! ELB - find diode voltage drop - 08.2017
*/
/**************************************************************************/
#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;
int sensorValue;
uint32_t counter;
float R = 1000; // 1k Ohms resistor


void setup(void) {
  Serial.begin(9600);
  Serial.println("Hello!");

  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0 the address is 0x60 or 0x61
  // For MCP4725A2 the address is 0x64 or 0x65
  dac.begin(0x60);

  Serial.println("Diode voltage drop : ");

  // Run through the full 12-bit scale analog output until the diode is on.
  for (counter = 0; counter < 4096; counter += 16 )
  {
    dac.setVoltage(counter, false); // set analog output      
    sensorValue = analogRead(A0); // read analog input

    float Va = counter/4096.*5.; // 12 bits analog output
    float Vc = sensorValue/1024.*5.; // 10 bits analog input
    float Vd = Va-Vc;
       
    Serial.print("Vd = "); Serial.print(Vd);
    Serial.print(", Id = "); Serial.println(Vc/R*1000);
  }
      
}

void loop(void) {}
