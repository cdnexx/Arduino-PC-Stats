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
int btnVal = HIGH;
int oldBtnVal = HIGH;
int menuOption = 0;
bool hasConnected=false;
String txt;
LiquidCrystal_I2C lcd (0x3f, 16, 2);
String data[9];
int cnt = 0;
void setup(){
    Serial.begin(9600);
    Wire.begin();

    pinMode(8, INPUT_PULLUP);

    lcd.begin(16, 2);
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(4,0);
    lcd.print("AWAITING");
    lcd.setCursor(3, 1);
    lcd.print("CONNECTION");

}

//cpuTemp[0], cpuUsage[1], 
//gpuTemp[2], gpuUsage[3], gpuUsedMem[4], gpuTotalMem[5], 
//ramUsage[6], ramUsed[7], ramTotal[8]
void loop(){
  if(Serial.available()>0){
    if(menuOption==0 && hasConnected==false){
      lcd.clear();
      uiCPU();
    }
    cnt=0;
    hasConnected = true;
    txt = Serial.readString();
    formatData(txt);
    btnVal = digitalRead(8);
    if(btnVal != oldBtnVal && btnVal == LOW){
      menuOption++;
      if(menuOption >2){
        menuOption = 0;
      }
      lcd.clear();
      if(menuOption==0){
        uiCPU();
      }
      if(menuOption==1){
        uiGPU();
      }
      if(menuOption==2){
        uiRAM();
      }
      delay(150);
    }
    oldBtnVal = btnVal;

    if(menuOption==0){
      //MENU CPU
      updateCPU();
    }
    if(menuOption==1){
      //MENU GPU
      updateGPU();
    }
    if(menuOption==2){
      //MENU RAM
      updateRAM();      
    }  
  }else{
    delay(50);
    cnt++;
  }

  if(hasConnected && cnt>100){
    cnt=0;
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("CONNECTION");
    lcd.setCursor(6, 1);
    lcd.print("LOST");
    delay(1000);      
  }
}

void uiCPU(){
  lcd.setCursor(0, 0);
  lcd.print("CPU:   % T:    C");
  lcd.setCursor(14, 0);
  lcd.print((char)223);
  lcd.setCursor(0, 1);
  lcd.print("PC STATS");
}

void updateCPU(){
  lcd.setCursor(4,0);
  lcd.print("   ");
  lcd.setCursor(4,0);
  lcd.print(data[1]);

  lcd.setCursor(11, 0);
  lcd.print("   ");
  lcd.setCursor(11, 0);
  lcd.print(data[0]);  
}

void uiGPU(){
    lcd.setCursor(0,0);
    lcd.print("GPU:   % T:    C");
    lcd.setCursor(14, 0);
    lcd.print((char)223);
    lcd.setCursor(0, 1);
    lcd.print("MEM:    /     GB");
}

void updateGPU(){
  lcd.setCursor(4,0);
  lcd.print("   ");
  lcd.setCursor(4,0);
  lcd.print(data[3]);

  lcd.setCursor(11, 0);
  lcd.print("   ");
  lcd.setCursor(11, 0);
  lcd.print(data[2]);

  lcd.setCursor(4,1);
  lcd.print("    ");
  lcd.setCursor(4,1);
  lcd.print(data[4]);

  lcd.setCursor(9,1);
  lcd.print("     ");
  lcd.setCursor(9,1);
  lcd.print(data[5]);  
}

void uiRAM(){
  lcd.setCursor(0, 0);
  lcd.print("RAM:   %");
  lcd.setCursor(0, 1);  
  lcd.print("USE:    /     GB");
}

void updateRAM(){
  lcd.setCursor(4, 0);
  lcd.print("   ");
  lcd.setCursor(4,0);
  lcd.print(data[6]);

  lcd.setCursor(4,1);
  lcd.print("    ");
  lcd.setCursor(4,1);
  lcd.print(data[7]);

  lcd.setCursor(9,1);
  lcd.print("     ");
  lcd.setCursor(9,1);
  lcd.print(data[8]);     
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


























