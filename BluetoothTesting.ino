#include <Wire.h>
#include "Adafruit_DRV2605.h"

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

long int effect = 1;
boolean canVibrate = false;

void loop() {
  //  Serial.print("Effect #"); Serial.println(effect);
  // get the value being set via bluetooth


  if (Serial.available() > 0) {
    effect = Serial.parseInt();
    Serial.print("got something - ");
    Serial.print(effect);

    // turn it off
    if (effect == 0) {
      Serial.println(("off"));
      canVibrate = false;
    } else {
      canVibrate = true;
    }
  }

  if (canVibrate) {
    if (effect == 1) {
      Serial.println(("1"));
    }

    if (effect == 4) {
      Serial.println(("4"));
    }

    if (effect == 7) {
      Serial.println(("7"));
    }

    if (effect == 24) {
      Serial.println(("24"));
    }

    if (effect == 47) {
      Serial.println(("47"));
    }

    // set the effect to play
    drv.setWaveform(0, effect);  // play effect
    drv.setWaveform(1, 0);       // end waveform

    // play the effect!
    drv.go();

    // wait a bit
    delay(100);
  }
}
