#include <SoftwareSerial.h>
SoftwareSerial BT(8,9); //BT_TX , BT_RX

//char System_step='0';
char BT_val,Serial_val;

void setup(){
	BT.begin(38400);
	Serial.begin(9600);
	Serial.println("BT is Ready!");
	
}

void loop(){
	if(BT.available()){
		BT_val=BT.read();
		Serial.print(BT_val);
	}
	if(Serial.available()){
		Serial_val=Serial.read();
		BT.print(Serial_val);
	}
}

