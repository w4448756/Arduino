#include <SoftwareSerial.h>
SoftwareSerial BT(8,9); //BT_TX , BT_RX

char System_step='0';
char BT_val;

void setup(){
	BT.begin(9600);
	Serial.begin(9600);
	Serial.println("BT is Ready!");
	
}

void loop(){
	if(BT.available()){
		while(BT.available()>0) BT_val=BT.read();
		Serial.println(BT_val);
	}
}

