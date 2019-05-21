#include <SparkFunLSM9DS1.h>
#include "BluetoothSerial.h"

#define LSM9DS1_M 0x1E
#define LSM9DS1_AG 0x6B
#define SW_PIN 7 //pin番号を指定する

LSM9DS1 imu;
BluetoothSerial SerialBT;

float x,y,z;
uint16_t connectionState = 0;

void setup()
{
  Serial.begin(115200);
  SerialBT.begin("ESP32"); //Bluetoothの名前を指定
  pinMode(SW_PIN, INPUT);
  
  imu.settings.device.commInterface = IMU_MODE_I2C;
  imu.settings.device.mAddress = LSM9DS1_M;
  imu.settings.device.agAddress = LSM9DS1_AG;
  if (connectionState == 0)
  {
    connectionState = imu.begin();
    while (connectionState == 0)
    {
      Serial.println("Failed to communicate with LSM9DS1.");
      Serial.println("Double-check wiring.");
      Serial.println("Default settings in this sketch will "
                     "work for an out of the box LSM9DS1 "
                     "Breakout, but may need to be modified "
                     "if the board jumpers are.");
      Serial.print("Connection Status: ");
      Serial.println(imu.begin());
      delay(1000);
      connectionState = imu.begin();
      Serial.println("------------------------------------------------------\n");
    }if(connectionState!=1){
      Serial.print("connectionState: ");
      Serial.println(connectionState);
    }
  }
}


void loop()
{
  imu.readAccel();
  x=imu.calcAccel(imu.ax)*10;
  y=imu.calcAccel(imu.ay)*10;
  z=imu.calcAccel(imu.az)*10;
  if(digitalRead(SW_PIN) == 1){ //スイッチが押されたら1、離すと0
    SerialBT.print("x=");
    SerialBT.print(x);
    SerialBT.print(", y=");
    SerialBT.print(y);
    SerialBT.print(", z=");
    SerialBT.println(z);
  }
  delay(500);
}
