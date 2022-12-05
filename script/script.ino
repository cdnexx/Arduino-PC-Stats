#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// #define cpuTemp 0;
// #define cpuUsage 1;
// #define gpuTemp 2;
// #define gpuUsage 3;
// #define gpuUsedMem 4;
// #define gpuTotalMem 5;
// #define ramUsage 6;
// #define ramUsed 7;
// #define ramTotal 8;

String txt;
LiquidCrystal_I2C lcd (0x3f, 16, 2);
String data[9];
int cnt = 0;
void setup(){
    Serial.begin(9600);
    Wire.begin();
    lcd.begin(16, 2);
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("GPU:   % T:    C");
    lcd.setCursor(0, 1);
    lcd.print("MEM:    /     GB");
    
}

//cpuTemp[0], cpuUsage[1], 
//gpuTemp[2], gpuUsage[3], gpuUsedMem[4], gpuTotalMem[5], 
//ramUsage[6], ramUsed[7], ramTotal[8]
void loop(){
  if(Serial.available()>0){   
    txt = Serial.readString();
    formatData(txt);
    Serial.println("hfasdds");
    lcd.setCursor(4,0);
    lcd.print("   ");
    lcd.setCursor(4,0);
    lcd.print(data[3]);
    lcd.setCursor(4,1);
    lcd.print("    ");
    lcd.setCursor(4,1);
    lcd.print(data[4]);
    lcd.setCursor(9,1);
    lcd.print("     ");
    lcd.setCursor(9,1);
    lcd.print(data[5]);

    // lcd.print("GPU:---%-T:----C");
    // lcd.print("MEM:    /     GB");
    // lcd.print("0123456789012345");
    // lcd.setCursor(0,0);
    // lcd.print("GPU:");
    // lcd.print(data[3]);
    cnt++;
  } 
}

void formatData(String txt){
  int StringCount=0;
  while(txt.length()>0){
    int index = txt.indexOf(',');
    if(index == -1){
      data[StringCount++] = txt;
      break;
    }else{
      data[StringCount++] = txt.substring(0,index);
      txt = txt.substring(index+1);
    }
  }
}


























