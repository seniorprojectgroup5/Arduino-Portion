#include <Wire.h>
#include "Adafruit_DRV2605.h"
#include <SoftwareSerial.h>
#include <millisDelay.h>

Adafruit_DRV2605 drv;
millisDelay v_Delay;

long int Data;
char B[1];

// inputs:vibrations
// 0:do nothing, 1:47, 2:24, 3:4, 4:7, 5:1
void readSerialInput() {
  Serial.readBytes(B, 1);
  long int temp = B[0] - '0';
  switch(temp){
    case 0:
      Data = 0;
      break;
    case 1:
      Data = 47;
      break;
    case 2:
      Data = 24;
      break;
    case 3:
      Data = 4;
      break;
    case 4:
      Data = 7;
      break;
    case 5:
      Data = 1;
      break;
  }
  
  Serial.println(Data);
}

class Vibrate {
    long int vibrationEffect;
  public:
    Vibrate(long int effect) {
      vibrationEffect = effect;
    }
    void Update() {
//      Serial.println(vibrationEffect);
      drv.setWaveform(0, vibrationEffect);  // play effect
      drv.setWaveform(1, 0);
      drv.go();
    }
};


long int iterate;
unsigned long endTime;

Vibrate eff_0(0);

Vibrate eff_1(1);
Vibrate eff_4(4);
Vibrate eff_7(7);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.println("Bluetooth test");
  drv.begin();

  drv.selectLibrary(1);

  // I2C trigger by sending 'go' command
  // default, internal trigger when sending GO command
  drv.setMode(DRV2605_MODE_INTTRIG);

  Data = -1;
  iterate = 0;

  endTime = millis() + iterate;
  v_Delay.start(0);
}

void loop() {
  if (millis() > endTime && Serial.available() > 0) {
    endTime = millis() + iterate;
    // read the serial input away from the main
    readSerialInput();
  }

  if (v_Delay.justFinished()) {
    // vibrate at a steady pace
    v_Delay.repeat();
    switch (Data) {
      case 0:
//        eff_0.Update();
        break;

      case 1:
        eff_1.Update();
        break;

      case 4:
        eff_4.Update();
        break;

      case 7:
        eff_7.Update();
        break;
      case -1:
        break;
    }
  }
}
