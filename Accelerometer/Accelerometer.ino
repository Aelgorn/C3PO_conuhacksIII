/*
   MPU6050_raw.ino : example of reading raw IMU data from MPU6050 using Teensy 3.X or Teensy LC

   This file is part of MPU6050.

   MPU6050 is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   Hackflight is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with Hackflight.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "MPU6050.h"
#include <math.h>

MPU6050 imu;

int FallPin=5;

void setup()
{
  Serial.begin(115200);

  Wire.begin();

  if (!imu.begin(AFS_2G, GFS_250DPS)) {
    Serial.println("MPU6050 is online...");
  }
  else {
    Serial.println("Failed to init MPU6050");
    while (true);
  }

  pinMode(FallPin,OUTPUT); //The pin which communicates with the Wi-Fi Arduino
  digitalWrite(FallPin,LOW);
//  Serial.begin(9600);
}

void loop()
{
  int16_t ax, ay, az, gx, gy, gz;
  if (imu.getMotion6Counts(&ax, &ay, &az, &gx, &gy, &gz)) {
//            Serial.print(ax);
//            Serial.print(" ");
//            Serial.print(ay);
//            Serial.print(" ");
//            Serial.print(az);
//            Serial.print(" ");
//            Serial.print(gx);
//            Serial.print(" ");
//            Serial.print(gy);
//            Serial.print(" ");
//            Serial.print(gz);
    int16_t magnitude = abs(sqrt(pow(az, 2))-16300);
//    Serial.println(magnitude);
      if(magnitude > 15000){
        digitalWrite(FallPin,HIGH); //If the acceleration is too big, it will tell the Wi-Fi
        Serial.println(1); //Only use for debugging
        delay(1000);  //Arduino that the person fell and that device will do its job.
      }
      digitalWrite(FallPin,LOW);
      Serial.println(0);
  }
}
