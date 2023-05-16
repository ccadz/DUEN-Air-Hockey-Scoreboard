#include "RGBmatrixPanel.h"
#include "bit_bmp.h"
#include "fonts.h"
#include <string.h>
#include <ezButton.h>
#include <stdlib.h>
#define CLK 11 
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3
#define clear()   fillScreen(0);

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);
const int button1Pin = 7;
int button1State = 0;
const int button2Pin = 3;
int button2State = 0;
long onTime = 0;
int lastReading = LOW;
int reading = LOW;
unsigned long time;
ezButton limitSwitch(7);
void setup()
{
  pinMode(7, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  Serial.begin(9600);
  Reginit();
  matrix.begin();
  Demo_1(0,0);
  limitSwitch.setDebounceTime(50);
//  delay(5000);
}

void loop()
{
//  int press = 0;
//  int notPress = 0;
//  reading = digitalRead(button1Pin);
//  if (reading == HIGH && lastReading == LOW) {
//    onTime = millis();
//    
//    Serial.println("Not Pressed");
//  }else{
//    Serial.println("Pressed");
//  }
//  lastReading = reading;
//
// if(digitalRead(button1Pin) == HIGH){
//  time = millis();
// } 
// else if(digitalRead(button1Pin) == LOW){
//  time = 0;
// }  
// Serial.print("Time: ");
// Serial.println(time);
// if(time > 2000){
//  Serial.println("FUCK");
// }

// greg
  int prevSwitchState = 0;
// chang
  Demo_1(0,0);
  int s1 = 0;
  int s2 = 0;
  game(s1,s2);
  delay(3000);

  }
  void game(int &s1, int &s2) {
    int state = digitalRead(button1Pin);
    bool check = false;
    bool print = false;

    int state2 = digitalRead(button2Pin);
    bool check2 = false;
    bool print2 = false;
    while(s1 < 7 && s2 < 7) {
      state = digitalRead(button1Pin);
        if(state == LOW && check == false) {
          check = true;
        } 
       if(check && state == HIGH) {
         delay(500);
          s1 = s1 + 1;
          check = false;
          print = true;
        }

        
     state2 = digitalRead(button2Pin);
       Serial.println("big");
        if(state2 == LOW && check2 == false) {
          check2 = true;
    } 
    if(check2 && state2 == HIGH) {
      delay(500);
      s2 = s2 + 1;
      check2 = false;
      print2 = true;
    }
    
    if(print || print2) {
      Demo_1(s1,s2);
      print = false;
      print2 = false;
    }
  }
  delay(1000);
  matrix.fillScreen(0);
  if(s1 == 7) {
    display_text(3, 9, "P1WON", NULL, matrix.Color333(1,0,255), 2);
  } else {
    display_text(3, 9, "P2WON", NULL, matrix.Color333(1,0,255), 2);
  
  }
  /*  if(state == HIGH)
  {
    Serial.print(button1Pin);
    Serial.print(": ");
    Serial.println("HIGH");
    prevSwitchState = 0;
  display_text(3, 9, "#duen", NULL, matrix.Color333(1,0,255), 2); // this text need to be printed slightly larger and over the 2 displays, not duplicated.
  }
  else if(state == LOW)
  {
    Serial.print(button1Pin);
    Serial.print(": ");
    Serial.println("LOW"); 
    display_text(3, 9, "PRESSED", NULL, matrix.Color333(1,0,255), 2); // this text need to be printed slightly larger and over the 2 displays, not duplicated.
    state = HIGH;
    prevSwitchState = 1;
  }
  */
//  limitSwitch.loop(); // MUST call the loop() function first
//
//  if(limitSwitch.isPressed())
//    Serial.println("The limit switch: UNTOUCHED -> TOUCHED");
//
//  if(limitSwitch.isReleased())
//    Serial.println("The limit switch: TOUCHED -> UNTOUCHED");
//
//  int state = limitSwitch.getState();
//  if(state == HIGH)
//    Serial.println("The limit switch: UNTOUCHED");
//  else
//    Serial.println("The limit switch: TOUCHED");

}

void display_text(int x, int y, String str, const GFXfont *f, int color, int pixels_size)
{
  matrix.setTextSize(pixels_size);// size 1 == 8 pixels high
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves
  matrix.setFont(f);      //set font
  matrix.setCursor(x, y);
  matrix.setTextColor(color);
  matrix.println(str);
}

void Demo_1(int score1, int score2)
{
  matrix.fillScreen(0);
  String s = String(score1);
  s += " - ";
  s += String(score2);
  display_text(3, 9, s, NULL, matrix.Color333(1,0,255), 2); // this text need to be printed slightly larger and over the 2 displays, not duplicated.
}
void updateScore(){
  int button1State = 0;
  button1State = digitalRead(button1Pin);
  int lastReading = LOW;


//  if (button1State == HIGH) {
//
//    Serial.println("Pressed");
//    display_text(3, 10, "FUCK NO", NULL, matrix.Color333(1,0,255), 2);
//    delay(500);
//    
//  } else {
//
//    Serial.println("Not Pressed");
//    display_text(3, 10, "YES", NULL, matrix.Color333(1,0,255), 2);
//    delay(500);
//  }


//  int s1 = 0;
//  int s2 = 0;
//  while(s1 < 7 && s2 < 7){
//    if(checkFin(s1,s2) == 1) {
//        display_text(3, 10, "P1 WON", NULL, matrix.Color333(1,0,255), 2); // this text need to be printed slightly larger and over the 2 displays, not duplicated.
//        s1 = 0;
//        s2 = 0;
//    }else if (checkFin(s1,s2) == 2){
//      display_text(3, 10, "P2 WON", NULL, matrix.Color333(1,0,255), 2); // this text need to be printed slightly larger and over the 2 displays, not duplicated.
//       s1 = 0;
//       s2 = 0;
//      break;
//    } else {
//      
//    }
//    Demo_1(s1,s2);
//  }
  
}
int checkFin(int score1, int score2) {
  if(score1 == 7) {
    return 1;
  } else if(score2 == 7) {
    return 2;
  } else {
    return 0;
  }
}
void Reginit()
{
    pinMode(24, OUTPUT); //R1
    pinMode(25, OUTPUT); //G1
    pinMode(26, OUTPUT); //B1
    pinMode(27, OUTPUT); //R2
    pinMode(28, OUTPUT); //G2
    pinMode(29, OUTPUT); //B2
    pinMode(CLK, OUTPUT);
    pinMode(OE, OUTPUT);
    pinMode(LAT, OUTPUT);

    digitalWrite(OE, HIGH);
    digitalWrite(LAT, LOW);
    digitalWrite(CLK, LOW);
    int MaxLed = 64;

    int C12[16] = {0, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1};
    int C13[16] = {0, 0, 0, 0, 0,  0, 0, 0, 0, 1, 0,  0, 0, 0, 0, 0};

    for (int l = 0; l < MaxLed; l++)
    {
        int y = l % 16;
        digitalWrite(24, LOW);
        digitalWrite(25, LOW);
        digitalWrite(26, LOW);
        digitalWrite(27, LOW);
        digitalWrite(28, LOW);
        digitalWrite(29, LOW);
        if (C12[y] == 1)
        {
          digitalWrite(24, HIGH);
          digitalWrite(25, HIGH);
          digitalWrite(26, HIGH);
          digitalWrite(27, HIGH);
          digitalWrite(28, HIGH);
          digitalWrite(29, HIGH);
        }
        if (l > MaxLed - 12)
        {
            digitalWrite(LAT, HIGH);
        }
        else
        {
            digitalWrite(LAT, LOW);
        }
        digitalWrite(CLK, HIGH);
        delayMicroseconds(2);
        digitalWrite(CLK, LOW);
    }
    digitalWrite(LAT, LOW);
    digitalWrite(CLK, LOW);

    // Send Data to control register 12
    for (int l = 0; l < MaxLed; l++)
    {
        int y = l % 16;
        digitalWrite(24, LOW);
        digitalWrite(25, LOW);
        digitalWrite(26, LOW);
        digitalWrite(27, LOW);
        digitalWrite(28, LOW);
        digitalWrite(29, LOW);
        if (C13[y] == 1)
        {
            digitalWrite(24, HIGH);
            digitalWrite(25, HIGH);
            digitalWrite(26, HIGH);
            digitalWrite(27, HIGH);
            digitalWrite(28, HIGH);
            digitalWrite(29, HIGH);
        }
        if (l > MaxLed - 13)
        {
            digitalWrite(LAT, HIGH);
        }
        else
        {
            digitalWrite(LAT, LOW);
        }
        digitalWrite(CLK, HIGH);
        delayMicroseconds(2);
        digitalWrite(CLK, LOW);
    }
    digitalWrite(LAT, LOW);
    digitalWrite(CLK, LOW);
}
