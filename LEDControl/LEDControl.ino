#include "LedControl.h"
#include <SoftwareSerial.h>
SoftwareSerial BT(8,9); //BT_TX , BT_RX

// Pin 12:Data in, Pin 11: Clock,  Pin 10: CS(Load)
LedControl lc=LedControl(12,11,10,1);
int arrow_up[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x41,0x22,0x14,0x08};
int arrow_down[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x14,0x22,0x41};
int arrow_right[8]={0x080,0x040,0x020,0x010,0x020,0x040,0x080,0x000};
int arrow_left[8]={0x001,0x002,0x004,0x008,0x004,0x002,0x001,0x000};
int arrow_stop[8]={0x4a,0x4a,0x4a,0x7a,0x4a,0x48,0x4a,0x00};
int register_up,register_down;
int i=0,j;

char System_step='0';
char BT_val='0';

int delay_time=150;
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
			if(BT_val=='-' && delay_time<1050) delay_time+=100;
			else if(BT_val=='+' && delay_time>50) delay_time-=100; 
			BT.print(delay_time);
		}else System_step=BT_val;
	}
	switch(System_step){
		case '0'://停
				for(i=0;i<8;i++) lc.setRow(0,i,arrow_stop[i]);
		break;
		case '1'://上
				for(i=0;i<8;i++) lc.setRow(0,i,arrow_up[i]);

		break;
		case '2'://左
				for(i=0;i<8;i++) lc.setRow(0,i,arrow_left[i]);
		break;
		case '3'://右
				for(i=0;i<8;i++) lc.setRow(0,i,arrow_right[i]);
		break;
		case '4'://下
				for(i=0;i<8;i++) lc.setRow(0,i,arrow_down[i]);
		break;
	}
	for(i=0;i<7;i++){
		if(arrow_right[i]==0x01) arrow_right[i]=0x800;
		else arrow_right[i]=arrow_right[i]>>1;
		if(arrow_left[i]==0x800) arrow_left[i]=0x01;
		else arrow_left[i]=arrow_left[i]<<1;
	}
	register_up=arrow_up[11];
	register_down=arrow_down[0];
	for(i=0;i<11;i++){
		arrow_up[11-i]=arrow_up[10-i];
		arrow_down[i]=arrow_down[i+1];
	}
	arrow_up[0]=register_up;
	arrow_down[11]=register_down;
	delay(delay_time);

}

