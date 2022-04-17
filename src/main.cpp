/*
   -- Scooter Freedom --

   This source code of graphical user interface
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 2.4.3 or later version
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/
     - for ANDROID 4.3.1 or later version;
     - for iOS 1.3.5 or later version;

   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library
#define REMOTEXY_MODE__ESP32CORE_BLE

#include <RemoteXY.h>
#include <FastCRC.h>
#include <Arduino.h>

// RemoteXY connection settings
#define REMOTEXY_BLUETOOTH_NAME "Scoot_Free"


// RemoteXY configurate
#pragma pack(push, 1)

uint8_t RemoteXY_CONF[] =
  { 255,3,0,2,0,64,0,8,13,1,
  2,1,20,82,22,11,2,26,31,31,
  79,78,0,79,70,70,0,7,52,21,
  61,20,5,2,26,2,65,4,16,37,
  9,9,65,1,37,37,9,9,129,0,
  9,19,49,6,17,83,99,111,111,116,
  101,114,32,70,114,101,101,100,111,109,
  0 };

// this structure defines all the variables of your control interface
struct {

    // input variable
  uint8_t switch_1; // =1 if switch ON and =0 if OFF
  int16_t edit_1;  // −32767.. +32767

    // output variable
  uint8_t led_1_r; // =0..255 LED Red brightness
  uint8_t led_2_b; // =0..255 LED Blue brightness

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_SWITCH_1 13

////////////////////////////////////////////
//         Scooter Starter include        //
///////////////////////////////////////////
#define INTERVAL 1000
unsigned long start_time = 0;
int run_once = 0;

<<<<<<< HEAD
byte messageOff[] = {0xA6, 0x12, 0x02, 0x10, 0x14, 0xCF}; //If the scooter is on turn it off.
//byte messageB[] = {0xA6, 0x12, 0x02, 0x11, 0x14, 0x0B}; //Not sure what this does?
//byte messageStart[] = {0xA6, 0x12, 0x02, 0x15, 0x14, 0x30}; //This is the unlock code.
byte messageStart = 0xFF;
/*byte lightOn = 0xFD;
byte lightflashing = 0xFF;
byte lightOFF = 0;*/
=======
//byte messageTest[] = {0xA6, 0x12, 0x02, 0x85, 0x24, 0x4D}; // CHANGE LOOP TO MODIFY AND TEST
byte messageOff = 0x10;
byte messageStart = 0x15;
byte lightOn = 0xE5;
byte lightFlashing = 0xE3;
byte lightOff = 0xE1; //Still need to figure out headlight off.
>>>>>>> dc67102... Speed Improvements

////////////////////////////////////////////
//         Scooter Command include        //
///////////////////////////////////////////
FastCRC8 CRC8; //Checksum Library
uint32_t crc;

byte commandByte = 0; // for incoming BLE data
byte commandbyteOld = 0; // last incoming BLE data

<<<<<<< HEAD
uint8_t buf[] = {0xA6, 0x12, 0x02, 0x00, 0x14, 0x00};
=======
uint8_t buf[] = {0xA6, 0x12, 0x02, 0x00, 0xE4, 0x00};

>>>>>>> dc67102... Speed Improvements
#define BUFSIZE 5

void setup()
{
  RemoteXY_Init ();

  Serial.begin(115200);
  Serial1.begin(9600);

  pinMode (PIN_SWITCH_1, OUTPUT);

  buf[3] = messageStart;
  crc = CRC8.maxim(buf, BUFSIZE); //CRC-8 MAXIM Check Sum Calculator
  buf[5] = crc;

  Serial1.write(messageOff, sizeof(messageOff));
  delay(500);
  Serial1.write(buf, sizeof(buf));

}

void loop()
{
  RemoteXY_Handler ();

  digitalWrite(PIN_SWITCH_1, (RemoteXY.switch_1==0)?LOW:HIGH);

   if(RemoteXY.switch_1 == 1){
    if(millis() > start_time + INTERVAL){
        start_time = millis();
        Serial1.write(buf, sizeof(buf));
        run_once = 0;
      }
    RemoteXY.led_1_r = 255;
    }
    else{
      RemoteXY.led_1_r = 0;
      if (run_once == 0){
      Serial1.write(messageOff, sizeof(messageOff));
      run_once = 1;
      }
    }
   Serial.print(RemoteXY.switch_1);
   Serial.print(" ");
   Serial.print(RemoteXY.led_1_r);
   Serial.print(" ");
   Serial.println(RemoteXY.connect_flag);

   if(RemoteXY.connect_flag == 1){ //BLE connection indication for the smartphone;
     RemoteXY.led_2_b = 255;
    }
    else{
      RemoteXY.led_2_b = 0;
    }

   commandByte = RemoteXY.edit_1;  //
     if (commandByte != commandbyteOld)
     {
      buf[3] = commandByte;
      crc = CRC8.maxim(buf, BUFSIZE); //CRC-8 MAXIM Check Sum Calculator
      buf[5] = crc;
      commandbyteOld = commandByte;
     }

}
