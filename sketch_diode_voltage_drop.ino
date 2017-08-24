/**************************************************************************/
/*! 
    @file     find diode voltae
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
int sensorValue, sensorThres;
bool checkVoltage;
uint32_t counter;

// check if the arduino is computing using a blinking led
int blinkPin = 13; // Pin 13 has an LED connected on most Arduino boards.
bool onblink;

void setup(void) {
  Serial.begin(9600);
  Serial.println("Hello!");

  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0 the address is 0x60 or 0x61
  // For MCP4725A2 the address is 0x64 or 0x65
  dac.begin(0x60);
  checkVoltage = true; // init - compute voltage drop in loop
  sensorThres = 20; // minmum value for diode on (voltage = sensorThres/1024.*5.)
  Serial.println("Detecting diode voltage drop");
  
  // on board led
  onblink = false;
  pinMode(blinkPin, OUTPUT); 
  digitalWrite(blinkPin, LOW); 
}

void loop(void) {
    
  if (checkVoltage)
  {
    // Run through the full 12-bit scale analog output until the diode is on.
    for (counter = 0; counter < 4096; counter += 16 )
    {
      dac.setVoltage(counter, false); // set analog output
      
      sensorValue = analogRead(A0); // read analog input
      //Serial.println(sensorValue);
      if (sensorValue > sensorThres)
      {
        float up = counter/4096.*5.; // 12 bits analog output
        float down = sensorValue/1024.*5.; // 10 bits analog input
        float voltage = up-down;
        Serial.print("Diode voltage drop : ");
        Serial.print(voltage);
        Serial.println(" V");
        checkVoltage = false;
        break;
      }
      
      // make on board pin 13 blink
      if (counter % 128 == 0)
      {
        onblink = !onblink;
        if (onblink)
          digitalWrite(blinkPin, HIGH);
        else
          digitalWrite(blinkPin, LOW);
      }
      delay(100);
    }
    if ((counter >= 4095) && (checkVoltage))
    {
      Serial.println("Error, maximum voltage reached");
      //checkVoltage = false;
      //digitalWrite(blinkPin, LOW);
    }
    checkVoltage = false;
    digitalWrite(blinkPin, LOW);
    
    // wait 1 sec and set analog output to 0
    delay(1000);
    dac.setVoltage(0, false); // set analog output
  }
  else
    delay(100);
}
