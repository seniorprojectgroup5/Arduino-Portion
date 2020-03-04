#include <Wire.h>
#include "Adafruit_DRV2605.h"
#include <SoftwareSerial.h>
#include <millisDelay.h>

Adafruit_DRV2605 drv;
millisDelay v_Delay;
millisDelay s_Delay;

long int Data;

class readSerial {
  public:
    void Update() {
     // if (Serial.available() > 0) {
        Serial.println("reading");
        Data = Serial.parseInt();
    //  }
    }
};

class Vibrate {
    long int vibrationEffect;
    int v_times = 5;
  public:
    Vibrate(long int effect) {
      vibrationEffect = effect;
    }
    void Update() {
      Serial.println(vibrationEffect);
      drv.setWaveform(0, vibrationEffect);  // play effect
      drv.setWaveform(1, 0);
      drv.go();
    }
};


int iterate;

Vibrate eff_1(1);
Vibrate eff_4(4);
Vibrate eff_7(7);

readSerial BleData;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.println("Bluetooth test");
  drv.begin();

  drv.selectLibrary(1);

  // I2C trigger by sending 'go' command
  // default, internal trigger when sending GO command
  drv.setMode(DRV2605_MODE_INTTRIG);

  Data = 0;
  iterate = 2;

  v_Delay.start(100);
  s_Delay.start(1000);
}

void loop() {
  // vibrate at a steady pace
  if (v_Delay.justFinished()) {
    v_Delay.repeat();
    switch (Data) {
      case 0:
        // do nothing
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
    }
  }
  // read the serial input away from the main
  BleData.Update();
  
}
