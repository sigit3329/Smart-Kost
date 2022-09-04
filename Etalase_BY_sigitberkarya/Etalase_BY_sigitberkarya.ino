#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <JC_Button.h>       //https://www.nyebarilmu.com/?file=2844&amp=1
#include <Filters.h>

float testFrequency = 50;                     // signal frequency (Hz)
float windowLength = 40.0/testFrequency;     // how long to average the signal, for statistist

int Sensor = 0;                 

float intercept = -0.04;  // adjust untuk kalibrasi
float slope = 0.0964;   // adjust untuk kalibrasi
float current_Volts;    

unsigned long interval=2000; //delay millis
unsigned long previousMillis=0;

LiquidCrystal_I2C lcd(0x27, 20, 4);

const byte
    RELAY1_PIN(12),    //relay yang terhubung pada pin                  (out)
    RELAY2_PIN(11),
    RELAY3_PIN(10),
    RELAY4_PIN(9),    
            
    RFWIRELESS1_PIN(8), //output RF Wireless yang terhubung pada pin    (in)
    RFWIRELESS2_PIN(7),
    RFWIRELESS3_PIN(6),            
    RFWIRELESS4_PIN(5),       

    blynk1_PIN(4),
    blynk2_PIN(13),
    blynk3_PIN(A2),
    blynk4_PIN(A3);

ToggleButton                     
    rf1(RFWIRELESS1_PIN), //Format untuk mode toggle atau latching
    rf2(RFWIRELESS2_PIN),
    rf3(RFWIRELESS3_PIN),          
    rf4(RFWIRELESS4_PIN), 

    bl1(blynk1_PIN),
    bl2(blynk2_PIN),
    bl3(blynk3_PIN),
    bl4(blynk4_PIN);

void setup()
{
  Serial.begin( 9600 );
  lcd.begin();
  lcd.backlight();

    rf1.begin(); //prosedur pembacaan status
    rf2.begin();
    rf3.begin();
    rf4.begin();

    bl1.begin();
    bl2.begin();
    bl3.begin();
    bl4.begin();
    
    pinMode(RELAY1_PIN, OUTPUT); //deklarasi relay sebagai output
    pinMode(RELAY2_PIN, OUTPUT);
    pinMode(RELAY3_PIN, OUTPUT);
    pinMode(RELAY4_PIN, OUTPUT);

    digitalWrite(RELAY1_PIN, HIGH); //nilai awal output relay
    digitalWrite(RELAY2_PIN, HIGH);
    digitalWrite(RELAY3_PIN, HIGH);
    digitalWrite(RELAY4_PIN, HIGH);

}

void loop()
{
  
  pinMode(2, INPUT_PULLUP);
if (digitalRead(2) == LOW){

  RunningStatistics inputStats;               
  inputStats.setWindowSecs( windowLength );
   
  while( true ) {  
     
    Sensor = analogRead(A1);                // read the analog in value:
    inputStats.input(Sensor);                   // log to Stats function

    rf1.read(); //prosedur pembacaan kondisi
    rf2.read();
    rf3.read();
    rf4.read();

    bl1.read();
    bl2.read();
    bl3.read();
    bl4.read();

    if (bl1.changed()) digitalWrite(RELAY1_PIN, bl1.toggleState()); //merubah status jika terjadi 
    if (bl2.changed()) digitalWrite(RELAY2_PIN, bl2.toggleState()); //pembacaan kondisi yang 
    if (bl3.changed()) digitalWrite(RELAY3_PIN, bl3.toggleState()); //berbeda dengan sebelumnya
    if (bl4.changed()) digitalWrite(RELAY4_PIN, bl4.toggleState());
    
    if (rf1.changed()) digitalWrite(RELAY1_PIN, rf1.toggleState()); //merubah status jika terjadi 
    if (rf2.changed()) digitalWrite(RELAY2_PIN, rf2.toggleState()); //pembacaan kondisi yang 
    if (rf3.changed()) digitalWrite(RELAY3_PIN, rf3.toggleState()); //berbeda dengan sebelumnya
    if (rf4.changed()) digitalWrite(RELAY4_PIN, rf4.toggleState());
    
    
    
  unsigned long currentMillis = millis();
 if ((unsigned long)(currentMillis - previousMillis) >= interval) {
  previousMillis = millis();                // update time every second
      
      current_Volts = intercept + slope * inputStats.sigma(); //Calibartions for offset and amplitude
      current_Volts= current_Volts*(49.3231);                //Further calibrations for the amplitude     
      
      Serial.print( "Voltage: " );
      Serial.println( current_Volts );


  unsigned int x=0;
float AcsValue=0.0,Samples=0.0,AvgAcs=0.0,AcsValueF=0.0;

  for (int x = 0; x < 150; x++){ //Get 150 samples
  AcsValue = analogRead(A0);     //Read current sensor values   
  Samples = Samples + AcsValue;  //Add samples together
}
AvgAcs=Samples/150.0;

AcsValueF = (2.56 - (AvgAcs * (5 / 1023.0)) )/0.66;

Serial.println(AcsValueF);//Print the read current on Serial monitor

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Voltase (V)= ");
  lcd.print(current_Volts);
  lcd.setCursor(0,1);
  lcd.print("Arus    (I)= ");
  lcd.print(AcsValueF);
  lcd.setCursor(0,2);
  lcd.print("Power   (W)= ");   
  float W = current_Volts * AcsValueF ;
  lcd.print(W);
  lcd.setCursor(0,3);
  lcd.print(" IG: sigit.berkarya");  
  previousMillis = millis();
 }
 }
 

}

  pinMode(3, INPUT_PULLUP);
if (digitalRead(3) == LOW){
    RunningStatistics inputStats;               
  inputStats.setWindowSecs( windowLength );
   
  while( true ) {  
     
    Sensor = analogRead(A1);                // read the analog in value:
    inputStats.input(Sensor);                   // log to Stats function

    rf1.read(); //prosedur pembacaan kondisi
    rf2.read();
    rf3.read();
    rf4.read();

    bl1.read();
    bl2.read();
    bl3.read();
    bl4.read();

    if (bl1.changed()) digitalWrite(RELAY1_PIN, bl1.toggleState()); //merubah status jika terjadi 
    if (bl2.changed()) digitalWrite(RELAY2_PIN, bl2.toggleState()); //pembacaan kondisi yang 
    if (bl3.changed()) digitalWrite(RELAY3_PIN, bl3.toggleState()); //berbeda dengan sebelumnya
    if (bl4.changed()) digitalWrite(RELAY4_PIN, bl4.toggleState());
    
    if (rf1.changed()) digitalWrite(RELAY1_PIN, rf1.toggleState()); //merubah status jika terjadi 
    if (rf2.changed()) digitalWrite(RELAY2_PIN, rf2.toggleState()); //pembacaan kondisi yang 
    if (rf3.changed()) digitalWrite(RELAY3_PIN, rf3.toggleState()); //berbeda dengan sebelumnya
    if (rf4.changed()) digitalWrite(RELAY4_PIN, rf4.toggleState());
  
  unsigned long currentMillis = millis();
  if ((unsigned long)(currentMillis - 0) >= 2000) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   Jika Mau Hidup    "); 
  lcd.setCursor(0,1);
  lcd.print("        SULIT        "); 
  lcd.setCursor(0,2);
  lcd.print("    Ambil Pilihan   "); 
  lcd.setCursor(0,3);
  lcd.print("       GAMPANG       ");
  delay(2000); 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   Jika Mau Hidup    "); 
  lcd.setCursor(0,1);
  lcd.print("       GAMPANG       "); 
  lcd.setCursor(0,2);
  lcd.print("    Ambil Pilihan   "); 
  lcd.setCursor(0,3);
  lcd.print("        SULIT        ");
  delay(2000); 
   previousMillis = millis();
 }
 
 
} 
}}
