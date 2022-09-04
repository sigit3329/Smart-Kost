#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLLol0Jcb7"
#define BLYNK_DEVICE_NAME "Kost"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WiFiClientSecure.h>
#include "CTBot.h" //arduinojson wajib 5.13.5
#include <DallasTemperature.h>
#include <OneWire.h> 


#define ONE_WIRE_BUS A0 
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);

char auth[] = "RJoNZYiTx0OTm8EWGmCcMVePcUVgb9yh";
char ssid[] = "SIGIT N";
char pass[] = "sandiapa@";

int val;//val sebagai buffer data
int mq;
int sensorApi;
int data = 0;

unsigned long interval=1000; // the time we need to wait
unsigned long previousMillis=0; // millis() returns an unsigned long.

#include <SPI.h>
#include <MFRC522.h>
#include <PCF8574.h>
#include <Wire.h>

#define pin_alarm 0
#define pin_door 1
#define pin_lampu 2
#define in_api 3
#define in_suara 4
#define in_gas 5
#define button_1 6
#define button_2 7

PCF8574 io(0x20);

constexpr uint8_t RST_PIN = D0;     //Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = D8;     //Configurable, see typical pin layout above

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

String tag;
String sigit="2444123942";
String ktp="514095223";
String kontak="41150178162";
String hp="45718274";

void setup() {
  Serial.begin(115200);
  io.begin();
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  Blynk.begin(auth, ssid, pass);
  sensors.begin(); 
}

WidgetTerminal terminal(V10);

BLYNK_WRITE(V10){

  }

BLYNK_WRITE(V0) // Buzzer
{
  if(param.asInt() == 1)
  {
    io.write(pin_alarm, LOW); 
  }
  
  else
  {
    io.write(pin_alarm, HIGH);   
  }
}

BLYNK_WRITE(V1) // Door Lock
{
  if(param.asInt() == 1)
  {
    io.write(pin_door, LOW);
  }
  else
  {
    io.write(pin_door, HIGH);   
  }
}

BLYNK_WRITE(V2) // Lampu Utama
{
  if(param.asInt() == 1)
  {
    io.write(pin_lampu, LOW); 
  }
  else
  {
    io.write(pin_lampu, HIGH); 
  }
}

BLYNK_WRITE(V4) // Backdoor
{
  if(param.asInt() == 1)
  {
    terminal.print("Backdoor aktif !!!");
    terminal.flush();
    delay(7200000); //2 jam 7200000
    terminal.println("Backdoor tidak aktif");
    terminal.flush();
  }
}

void sensorSuhu(){
  sensors.requestTemperatures();
  Blynk.virtualWrite(V3, sensors.getTempCByIndex(0));
}

void sensorSuara(){
  unsigned long currentMillis = millis(); 
  val=io.read(in_suara);
  if(val==LOW) {
    if ((unsigned long)(currentMillis - previousMillis) >= interval) {
    data++;
    if (data > 1){
      data=0;
      }
    }
    
    if (data == 1){
      io.write(pin_lampu, HIGH);
      }
    if (data == 0){
      io.write(pin_lampu, LOW);
      }
    previousMillis = millis();
    } 
}

void mq2(){
  mq=io.read(in_gas);

  if (mq==LOW){
    io.write(pin_alarm, LOW);
    delay(69);
    io.write(pin_alarm, HIGH);
  }
}

void api(){
  sensorApi=io.read(in_api);

  if (sensorApi==LOW){
    io.write(pin_alarm, LOW);
    delay(69);
    io.write(pin_alarm, HIGH);
  }
}

void bukapintu(){
      io.write(pin_door, LOW);
      io.write(pin_alarm, LOW);
      delay(69);
      io.write(pin_alarm, HIGH);
      delay(5000);
      io.write(pin_door, HIGH);
      terminal.println("Akses diterima!");
  }

void alarm(){
      io.write(pin_alarm, LOW);
      delay(600);
      io.write(pin_alarm, HIGH);
  }

void Run_RFID(){
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
  if (rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    terminal.print("ID TAG= ");
    terminal.println(tag);
    
    if (tag == sigit) {
      terminal.println("Nama Terdaftar = SI-GIT");
      bukapintu(); 
      }
    else if (tag == kontak){
      terminal.println("Nama Terdaftar = Kontak");
      bukapintu();
      } 
    else if (tag == ktp){
      terminal.println("Nama Terdaftar = E-KTP");
      bukapintu();
      }  
    else if (tag == hp){
      terminal.println("Nama Terdaftar = HP");
      bukapintu();
    }
    else {
      alarm();
      terminal.println("RFID tidak dikenal");
      terminal.println("Akses ditolak!");
      }
    tag = "";
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
  }


void button(){
  if (io.read(button_1) == LOW && io.read(button_2) == HIGH){
    io.write(pin_alarm, LOW);
    delay(69);
    io.write(pin_alarm, HIGH);
    delay(2000);
    
    if (io.read(button_1) == HIGH && io.read(button_2) == LOW){
      io.write(pin_alarm, LOW);
      delay(69);
      io.write(pin_alarm, HIGH);
      delay(2000);

      if (io.read(button_1) == LOW && io.read(button_2) == HIGH){
        io.write(pin_alarm, LOW);
        delay(1000);
        io.write(pin_alarm, HIGH);
        delay(2000);

        if (io.read(button_1) == LOW && io.read(button_2) == HIGH){
          io.write(pin_alarm, LOW);
          delay(69);
          io.write(pin_alarm, HIGH);
          delay(2000);

          if (io.read(button_1) == HIGH && io.read(button_2) == LOW){
            io.write(pin_alarm, LOW);
            delay(69);
            io.write(pin_alarm, HIGH);
            delay(69);
            io.write(pin_alarm, LOW);
            delay(69);
            io.write(pin_alarm, HIGH);
            delay(2000);
            bukapintu();
          }
        }
      }
    }
  }

  if (io.read(button_1) == HIGH && io.read(button_2) == LOW){
      io.write(pin_alarm, LOW);
      delay(69);
      io.write(pin_alarm, HIGH);
      delay(2000);
  }
}
  
void loop() {
  Blynk.run();
  button();
  Run_RFID();
  sensorSuara();
  mq2();
  api();
  sensorSuhu();
  terminal.flush();
  }
