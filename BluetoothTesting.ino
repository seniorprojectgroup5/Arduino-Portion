#include <Wire.h>
#include "Adafruit_DRV2605.h"
#include <SoftwareSerial.h>

Adafruit_DRV2605 drv;

void setup() {
  Serial.begin(9600);

  Serial.println("Bluetooth test");
  drv.begin();

  drv.selectLibrary(1);

  // I2C trigger by sending 'go' command
  // default, internal trigger when sending GO command
  drv.setMode(DRV2605_MODE_INTTRIG);
}

long int effect = 0;
long int numOfVibrations = 2;

void loop() {
  //  Serial.print("Effect #"); Serial.println(effect);
  // get the value being set via bluetooth


  if (Serial.available() > 0) {
    effect = Serial.parseInt();
    Serial.print("Received: ");
    Serial.println(effect);

    // turn it off
    if (effect == 0) {
      Serial.println(("off"));
    } else {
      switch (effect) {
        case 1:
//          Serial.println("1 - looped");
          break;

        case 4:
//          Serial.println("4 - looped");
          break;

        case 7:
//          Serial.println("7 - looped");
          break;

        case 24:
//          Serial.println("24 - looped");
          break;

        case 47:
//          Serial.println("47 - looped");
          break;
      }
      
      // set the effect to play
      drv.setWaveform(0, effect);  // play effect
      drv.setWaveform(1, 0);       // end waveform
      
      for (int i = 0; i < numOfVibrations; i++) {
        Serial.println(" ~ ");
        // play the effect!
        drv.go();
      }
    }
  }
}
