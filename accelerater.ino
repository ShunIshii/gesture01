#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <SparkFunLSM9DS1.h>
#define ADAddr 0x48

LSM9DS1 imu;
void printAccel(); // Print "A: ax, ay, az"

const char * networkName = "000D0BB8E766";
const char * networkPswd = "";
const char * udpAddress = "";
const int udpPort = 3333;
boolean connected= false;

WiFiUDP udp;

float x,y,z;//加速度
float norm;//加速度の大きさ
int frame;//フレーム数
int readFrame=0;
boolean FrameFlg=false;//ジェスチャ認識開始時からフレーム更新
 //------------------------------------------------------------------------
#define LSM9DS1_M 0x1E  // SPIアドレス設定 0x1C if SDO_M is LOW
#define LSM9DS1_AG 0x6B // SPIアドレス設定 if SDO_AG is LOW
uint16_t connectionState = 0;

//----------------------　setup　---------------------------
void setup()
{
    Serial.begin(115200);

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
            Serial.println("---------------------------------------------------------\n");
        }if(connectionState!=1){
          Serial.print("connectionState: ");
          Serial.println(connectionState);
        }
    }
    frame=0;
    //connectToWiFi(networkName, networkPswd);
}


void loop() {
  //imu.readAccel();
}
