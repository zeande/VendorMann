// character LCD example code
// www.hacktronics.com

#include <LiquidCrystal.h>
#include <Servo.h>
Servo myServo;
// Connections:
// rs (LCD pin 4) to Arduino pin 12
// rw (LCD pin 5) to Arduino pin 11
// enable (LCD pin 6) to Arduino pin 10
// LCD pin 15 to Arduino pin 13
// LCD pins d4, d5, d6, d7 to Arduino pins 6, 5, 4, 3
LiquidCrystal lcd(12, 11, 10, 6, 5, 4, 3);

int  val = 0; 
char code[10]; 
int bytesread = 0; 

int backLight = 13;    // pin 13 will control the backlight

void setup()
{
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH); // turn backlight on. Replace 'HIGH' with 'LOW' to turn it off.
  lcd.begin(20,4);              // columns, rows.  use 16,2 for a 16x2 LCD, etc.
  lcd.clear();                  // start with a blank screen
  lcd.setCursor(0,0);           // set cursor to column 0, row 0 (the first row)
  lcd.print("Hello, Member");    // change this text to whatever you like. keep it clean.
  lcd.setCursor(0,1);           // set cursor to column 0, row 1
  lcd.print("Welcome to ACM!");
//  myServo.attach(9);
//  servoMain.write(45);

  lcd.setCursor(0,2);         // set cursor to column 0, row 2
  lcd.print("Please Swipe Card");
  lcd.setCursor(0,3);         // set cursor to column 0, row 3
  lcd.print("to accesss database");
  
  Serial.begin(2400); // RFID reader SOUT pin connected to Serial RX pin at 2400bps 
pinMode(2,OUTPUT);   // Set digital pin 2 as OUTPUT to connect it to the RFID /ENABLE pin 
digitalWrite(2, LOW);
}

void loop()
{
  if(Serial.available() > 0) {          // if data available from reader 
    if((val = Serial.read()) == 10) {   // check for header 
      bytesread = 0; 
      while(bytesread<10) {              // read 10 digit code 
        if( Serial.available() > 0) { 
          val = Serial.read(); 
          if((val == 10)||(val == 13)) { // if header or stop bytes before the 10 digit reading 
            break;                       // stop reading 
          } 
          code[bytesread] = val;         // add the digit           
          bytesread++;                   // ready to read next digit  
        } 
      } 
      if(bytesread == 10) {              // if 10 digit read is complete 
        lcd.clear();
        lcd.setCursor(1,1);
        lcd.print("TAG code is: ");   // possibly a good TAG 
        lcd.setCursor(2,2);
        lcd.print(code);
        //Serial.println(code);            // print the TAG code 
      }
      bytesread = 0; 
      digitalWrite(2, HIGH);                  // deactivate the RFID reader for a moment so it will not flood
      delay(1500);                       // wait for a bit 
      digitalWrite(2, LOW);                  // Activate the RFID reader
    }
  }
}
