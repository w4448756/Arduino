#include "LedControl.h"
#include <SoftwareSerial.h>
SoftwareSerial BT(8,9); //BT_TX , BT_RX

// Pin 12:Data in, Pin 11: Clock,  Pin 10: CS(Load)
LedControl lc=LedControl(12,11,10,1);
int arrow_left[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x41,0x22,0x14,0x08};
int arrow_right[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x14,0x22,0x41};
int register_left,register_right;
int i=0,j;

char System_step;
char BT_val='0';

int delay_time=100;
void setup(){
	BT.begin(9600);
	Serial.begin(9600);
	Serial.println("BT is Ready!");

	lc.shutdown(0,false);  // 關閉省電模式
	lc.setIntensity(0,8);  // 設定亮度為 8 (介於0~15之間)
	lc.clearDisplay(0);    // 清除螢幕
}

void loop(){

	if(BT.available()){
		while(BT.available()>0) BT_val=BT.read();
		Serial.println(BT_val);
	
		if(BT_val=='+'||BT_val=='-'){
			if(BT_val=='-' && delay_time<1000) delay_time+=50;
			else if(BT_val=='+' && delay_time>100) delay_time-=50; 
			BT.print(delay_time);
		}else System_step=BT_val;
	}
	switch(System_step){
		case '0':

		break;
		case '1':
				for(i=0;i<8;i++) lc.setRow(0,i,arrow_left[i]);

		break;
		case '2':

		break;
		case '3':

		break;
		case '4':
				for(i=0;i<8;i++) lc.setRow(0,i,arrow_right[i]);
		break;
	}
	register_left=arrow_left[11];
	register_right=arrow_right[0];
	for(i=0;i<11;i++){
		arrow_left[11-i]=arrow_left[10-i];
		arrow_right[i]=arrow_right[i+1];
	}
	arrow_left[0]=register_left;
	arrow_right[11]=register_right;
	delay(delay_time);

}

