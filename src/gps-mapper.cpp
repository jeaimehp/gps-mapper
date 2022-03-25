/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/jhpowell/Documents/Particle/gps-mapper/src/gps-mapper.ino"
/*
 * Project gps-mapper
 * Description: Used to collect GPS lat long and cell signal strength for mapping a location.
 * Author: Je'aime Powell
 * Date: 
 */

// This #include statement was automatically added by the Particle IDE.
#include <oled-wing-adafruit.h>

// This #include statement was automatically added by the Particle IDE.
#include <SdFat.h>

// This #include statement was automatically added by the Particle IDE.
#include <Particle-GPS.h>

// This #include statement was automatically added by the Particle IDE.
#include <SPI.h>
#include <SdFat.h>

// This #include statement was automatically added by the Particle IDE.
#include <oled-wing-adafruit.h>

// Copyright © 2016-2017 Daniel Porrey. All Rights Reserved.
//
// This file is part of the Particle.GPS library.
// 
// Particle.GPS library is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Particle.GPS library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Particle.GPS library. If not, 
// see http://www.gnu.org/licenses/.
//
#include "Particle-GPS.h"

// ***
// *** Create a Gps instance. The RX an TX pins are connected to
// *** the TX and RX pins on the electron (Serial1).
// ***
void displayvoltage_button_A (void);
void displayvoltage_button_B (void);
void displayvoltage_button_C (void);
void setup();
void onSerialData();
void loop();
float conv_coords(float in_coords);
#line 48 "/Users/jhpowell/Documents/Particle/gps-mapper/src/gps-mapper.ino"
Gps _gps = Gps(&Serial1);

// ***
// *** Create a timer that fires every 1 ms to capture
// *** incoming serial port data from the GPS.
// ***
Timer _timer = Timer(1, onSerialData);

OledWingAdafruit display;
String myID = System.deviceID();
String datafile_name = String(myID+"-"+Time.year()+Time.month()+Time.day()+Time.hour()+Time.minute()+".csv");


// SDCard Definition

// Adalogger SDCArd CS 
    // SD chip select pin
    const uint8_t chipSelect = D5;
    SdFat sd;
    File myFile;
    
    
unsigned long lastmillis_pub = 0;
//Seconds until publish and/or save to SDCArd (no less than 10 for particle)
unsigned long pub_time = 30;
// Convert pub_time to milliseconds
int pub_time_milli = pub_time * 1000;

bool buttonA = true;
bool buttonB = false;
bool buttonC = false;


void displayvoltage_button_A (void) {
  buttonA = true;
  buttonB = false;
  buttonC = false;
};

void displayvoltage_button_B (void) {
  buttonA = false;
  buttonB = true;
  buttonC = false;
};

void displayvoltage_button_C (void) {
  buttonA = false;
  buttonB = false;
  buttonC = true;
};

void setup()
{
  delay(2000);

  // ***
  // *** Initialize the USB Serial for debugging.
  // ***
  Serial.begin();
  Serial.println("Initializing...");
  // OLED Setup 
  display.setup();
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Initializing...");
  display.display();

  // ***
  // *** Initialize the GPS.
  // ***
  _gps.begin(9600);

  // ***
  // *** Start the timer.
  // ***
  _timer.start();
  
  // Initialize sd card  
  // Initialize SdFat or print a detailed error message and halt
  // Use half speed like the native library.
  //Set SPI to correct mode to write to the SD Card
    SPI.setDataMode(SPI_MODE0);
  
 Particle.publish("SDCard_Setup", "Initializing");
  if (!sd.begin(chipSelect)){
         Particle.publish("SDCard Logger", "Failed");
         //jsonsensor["SDCard"] = "FAILED";
         delay(1000);
         Particle.publish("ALERT", "SDCard_Failure!");
          display.setCursor(0,10);
          display.println("SD Card Init Failed");
          display.display();
     }
     else {
            Particle.publish("SDCard Logger", "OK");
            //jsonsensor["SDCard"] = "OK";
          display.setCursor(0,10);
          display.println("SD Card Init - OK");
          display.display();
            delay(1000);
     }
  
  // -- Button Interupt Setup -- //
 
  // Button A - D2 on Particle Boron with featherwing oled adafruit
    pinMode(D4, INPUT_PULLUP);
    attachInterrupt(D4, displayvoltage_button_A, CHANGE);
  
  // Button B - D3 on Particle Boron with featherwing oled adafruit
    pinMode(D3, INPUT_PULLUP);
    attachInterrupt(D3, displayvoltage_button_B, CHANGE);
  
   // Button C - D2 on Particle Boron with featherwing oled adafruit
    pinMode(D2, INPUT_PULLUP);
    attachInterrupt(D2, displayvoltage_button_C, CHANGE);

}

void onSerialData()
{
  _gps.onSerialData();
}

void loop()
{
  // ***
  // *** Get the Antenna Status ($PGTOP).
  // ***
  Pgtop pgtop = Pgtop(_gps);
  if (pgtop.parse())
  {
    Serial.println("1) Antenna Status ($PGTOP)");
    Serial.println("======================================================");
    Serial.print("Command ID: "); Serial.println(pgtop.commandId);
    Serial.print("Antenna Status: "); Serial.println(pgtop.reference);
    Serial.println("");
  }

  // ***
  // *** Get the Global Positioning System Fixed Data ($GPGGA).
  // ***
  Gga gga = Gga(_gps);
  if (gga.parse())
  {
    Serial.println("2) Global Positioning System Fixed Data ($GPGGA)");
    Serial.println("======================================================");
    Serial.print("UTC Time: "); Serial.println(gga.utcTime);
    Serial.print("Latitude: "); Serial.println(gga.latitude);
    Serial.print("North/SouthIndicator: "); Serial.println(gga.northSouthIndicator);
    Serial.print("Longitude: "); Serial.println(gga.longitude);
    Serial.print("East/WestIndicator: "); Serial.println(gga.eastWestIndicator);
    Serial.print("Position Fix Indicator: "); Serial.println(gga.positionFixIndicator);
    Serial.print("Satellites Used: "); Serial.println(gga.satellitesUsed);
    Serial.print("Horizontal Dilution of Precision: "); Serial.println(gga.hdop);
    Serial.print("Altitude: "); Serial.print(gga.altitude); Serial.print(" "); Serial.println(gga.altitudeUnit);
    Serial.print("Geoidal Separation: "); Serial.print(gga.geoidalSeparation); Serial.print(" "); Serial.println(gga.geoidalSeparationUnit);
    Serial.print("Age of Diff. Corr.: "); Serial.println(gga.ageOfDiffCorr);
    Serial.println("");
    
    // Boron Cell signal strength
    CellularSignal sig = Cellular.RSSI();
    
    // Set timestamp
    String timeStamp = Time.format(Time.now(), TIME_FORMAT_ISO8601_FULL);

    //OELD Display
    // button A (default display)  
    if (buttonA) { 
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("Fix:" + String(gga.positionFixIndicator)+"  " + "Cell-Sig:" + int(sig.getStrength()) +"%");
      
      display.setCursor(0,10);
      display.println("Lat:" + String(gga.northSouthIndicator)+" "+String(conv_coords(gga.latitude.toFloat())));
      display.setCursor(0,20);
      display.println("Long:" + String(gga.eastWestIndicator) +" "+String(conv_coords(gga.longitude.toFloat())));
      display.display();
    }
    else if (buttonB){
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("Current File:");
      display.println(datafile_name);
      display.display();
    }
    else if (buttonC){
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println(timeStamp);
      display.setCursor(0,10);
      display.print("Battery: ");
      display.print(int(System.batteryCharge()));
      display.println(" %");
      display.display();
    }
  
 
	SPI.setDataMode(SPI_MODE0);
	
	if (gga.positionFixIndicator != 0){
	   if (millis() - lastmillis_pub >= pub_time_milli) {
	     if (!myFile.open(datafile_name, O_RDWR | O_CREAT | O_AT_END)) {
            //sd.errorHalt("opening data file for write failed");
            Serial.println("SD Card file deviceID-xxx open failed");
            }
            else{
  
            myFile.println(String(timeStamp + ","+gga.northSouthIndicator+" "+conv_coords(gga.latitude.toFloat())+","+gga.eastWestIndicator+" "+conv_coords(gga.longitude.toFloat())+","+sig.getStrength()));
            myFile.close();
           }
    
	    lastmillis_pub = millis();
	   }
	}  
  }

  // ***
  // *** Get the Recommended Minimum Navigation Information ($GPRMC).
  // ***
  /*
  Rmc rmc = Rmc(_gps);
  if (rmc.parse())
  {
    Serial.println("3) Recommended Minimum Navigation Information ($GPRMC)");
    Serial.println("======================================================");
    Serial.print("UTC Time: "); Serial.println(rmc.utcTime);
    Serial.print("Latitude: "); Serial.println(rmc.latitude);
    Serial.print("North/SouthIndicator: "); Serial.println(rmc.northSouthIndicator);
    Serial.print("Longitude: "); Serial.println(rmc.longitude);
    Serial.print("East/WestIndicator: "); Serial.println(rmc.eastWestIndicator);
    Serial.print("Speed Over Ground: "); Serial.println(rmc.speedOverGround);
    Serial.print("Course Over Ground: "); Serial.println(rmc.courseOverGround);
    Serial.print("Date: "); Serial.println(rmc.date);
    Serial.print("Magnetic Variation: "); Serial.print(rmc.magneticVariation); Serial.print(" "); Serial.println(rmc.magneticVariationDirection);
    Serial.print("Mode: "); Serial.println(rmc.mode);
    Serial.println("");
  }
  */
  delay(1000);
}

float conv_coords(float in_coords)
 {
 //Initialize the location.
 float f = in_coords;
 // Get the first two digits by turning f into an integer, then doing an integer divide by 100;
 // firsttowdigits should be 77 at this point.
 int firsttwodigits = ((int)f)/100; //This assumes that f < 10000.
 float nexttwodigits = f - (float)(firsttwodigits*100);
 float theFinalAnswer = (float)(firsttwodigits + nexttwodigits/60.0);
 return theFinalAnswer;
 }
