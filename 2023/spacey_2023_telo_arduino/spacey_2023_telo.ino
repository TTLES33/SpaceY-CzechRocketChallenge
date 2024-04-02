#include <TinyGPS++.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define BMP280_ADRESA (0x76)
//create an RF24 object
RF24 radio(9, 8);  // CE, CSN
//address through which two modules communicate.
const byte address[6] = "00001";



int gpsRXPin = 3;
int gpsTXPin = 2;
int GPSBaud = 9600;

float gps_lat = 0;
float gps_lng = 0;
float gps_sat = 0;
String gps_time = "0";

float highest_altitute = 0;
bool parashute_deployment = false;
const int radiorepeat = 10000;
unsigned long startTime;

Adafruit_BMP280 bmp;
TinyGPSPlus gps;
SoftwareSerial gpsSerial(gpsRXPin, gpsTXPin);


void setup() {
  Serial.begin(9600);
  gpsSerial.begin(GPSBaud);

  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);


  //BMP280
  if (!bmp.begin(BMP280_ADRESA)) {
    Serial.println("BMP280 senzor nenalezen, zkontrolujte zapojeni!");
  }else{
    Serial.println("BMP280 found");
  }

  startTime = millis();

  //2,4GHz radio
  radio.begin();
  radio.openWritingPipe(address);
  radio.setChannel( 82);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_1MBPS);
  radio.stopListening();
}



float altitutecalc(float pressure){
  float altitute = 44330.77 * (1 - pow((pressure/1013.25), 0.19) );
  return altitute;
}




void parashute_deploy(){
  digitalWrite(4, HIGH);
  parashute_deployment = true;
}






void radiosent(){
  String output_message = "1-";
  output_message = output_message + String(gps_lat, 6);
  output_message = output_message + "-";
  output_message = output_message + String(gps_lng, 6);
  output_message = output_message + "-";
  output_message = output_message + gps_time;
  output_message = output_message + "-";
  output_message = output_message + String(highest_altitute);

  // Length (with one extra character for the null terminator)
  int str_len = output_message.length() + 1; 

  // Prepare the character array (the buffer) 
  char char_array[str_len];

  // Copy it over 
  output_message.toCharArray(char_array, str_len);
  for(int i = 0; i < 5; i++){
    radio.write(&char_array, sizeof(char_array));
    delay(100);
  }
}





void consolelog(float teplota, float tlak, float altitute){
  Serial.println("----------------------------------------------------");
  Serial.print("GPS: ");
  Serial.print("Lat=");
  Serial.print(gps_lat, 6);
  Serial.print(" lng=");
  Serial.print(gps_lng, 6);
  Serial.print(" sat=");
  Serial.print(gps_sat);
  Serial.print(" gps_time=");
  Serial.println(gps_time);

  Serial.print("BMP280: ");
  Serial.print("temp=");
  Serial.print(teplota);
  Serial.print(" press=");
  Serial.println(tlak);
  Serial.print("altitute=");
  Serial.print(altitute);
  Serial.print(" max. altitute=");
  Serial.print(highest_altitute);
  Serial.print(" parashude deploy=");
  Serial.println(parashute_deployment);
}

int times_passed = 0;
bool gps_fixed = false;
void loop() {
  if(gps_fixed == false){
    while(gps_fixed == false){
      float teplota = bmp.readTemperature();
      float tlak = bmp.readPressure()/100.00;
      float altitute = altitutecalc(tlak);

      if(altitute >= highest_altitute){
        highest_altitute = altitute;
      }else if((altitute + 3) < highest_altitute){
        times_passed++;
        if(times_passed > 25){
          parashute_deploy();
        }
      
      }  

      while (gpsSerial.available() > 0){
      gps.encode(gpsSerial.read());
        if (gps.location.isUpdated()){
          gps_lat = gps.location.lat();
          gps_lng = gps.location.lng();
          gps_sat = gps.satellites.value();
          gps_time = String(gps.time.minute()) + ":" + String(gps.time.second());
          Serial.print("GPS Fixed ");
          gps_fixed = true;
        }   
      }
    }
  }else{
    radiosent();
    gps_fixed = false;
  }   
}