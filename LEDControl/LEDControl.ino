#include "LedControl.h"
#include "binary.h"

// Pin 12:Data in, Pin 11: Clock,  Pin 10: CS(Load)
LedControl lc=LedControl(12,11,10,1);
int arrow_left[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x41,0x22,0x14,0x08};
int arrow_right[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x14,0x22,0x41};
int register_left,register_right;
int i=0,j;
void setup(){
	lc.shutdown(0,false);  // 關閉省電模式
	lc.setIntensity(0,8);  // 設定亮度為 8 (介於0~15之間)
	lc.clearDisplay(0);    // 清除螢幕
}

void loop(){
	for(j=0;j<12;j++){
		for(i=0;i<8;i++) lc.setRow(0,i,arrow_left[i]);
		register_left=arrow_left[11];
		for(i=10;i>=0;i--)	arrow_left[i+1]=arrow_left[i];
		arrow_left[0]=register_left;
		delay(100);
	}
	for(j=0;j<12;j++){
		for(i=0;i<8;i++) lc.setRow(0,i,arrow_right[i]);
		register_right=arrow_right[0];
		for(i=0;i<11;i++)	arrow_right[i]=arrow_right[i+1];
		arrow_right[11]=register_right;
		delay(100);
	}

}

