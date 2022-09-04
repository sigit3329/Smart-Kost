//www.nyebarilmu.com https://www.nyebarilmu.com/kendali-lampu-rumah-dengan-rf-wireless-4-channel/
//program RF Wireless 4 channel menggunakan arduino pro mini

#include <JC_Button.h>       //https://www.nyebarilmu.com/?file=2844&amp=1

const byte
    RELAY1_PIN(12),    //relay yang terhubung pada pin                  (out)
    RELAY2_PIN(11),
    RELAY3_PIN(10),
    RELAY4_PIN(9),    
            
    RFWIRELESS1_PIN(8), //output RF Wireless yang terhubung pada pin    (in)
    RFWIRELESS2_PIN(7),
    RFWIRELESS3_PIN(6),            
    RFWIRELESS4_PIN(5);             

ToggleButton                     
    rf1(RFWIRELESS1_PIN), //Format untuk mode toggle atau latching
    rf2(RFWIRELESS2_PIN),
    rf3(RFWIRELESS3_PIN),          
    rf4(RFWIRELESS4_PIN); 

void setup()
{
    rf1.begin(); //prosedur pembacaan status
    rf2.begin();
    rf3.begin();
    rf4.begin();
    
    pinMode(RELAY1_PIN, OUTPUT); //deklarasi relay sebagai output
    pinMode(RELAY2_PIN, OUTPUT);
    pinMode(RELAY3_PIN, OUTPUT);
    pinMode(RELAY4_PIN, OUTPUT);

    digitalWrite(RELAY1_PIN, rf1.toggleState()); //nilai awal output relay
    digitalWrite(RELAY2_PIN, rf2.toggleState());
    digitalWrite(RELAY3_PIN, rf3.toggleState());
    digitalWrite(RELAY4_PIN, rf4.toggleState());
}

void loop()
{
    rf1.read(); //prosedur pembacaan kondisi
    rf2.read();
    rf3.read();
    rf4.read();

    if (rf1.changed()) digitalWrite(RELAY1_PIN, rf1.toggleState()); //merubah status jika terjadi 
    if (rf2.changed()) digitalWrite(RELAY2_PIN, rf2.toggleState()); //pembacaan kondisi yang 
    if (rf3.changed()) digitalWrite(RELAY3_PIN, rf3.toggleState()); //berbeda dengan sebelumnya
    if (rf4.changed()) digitalWrite(RELAY4_PIN, rf4.toggleState());
}
