//Program to read temperature and humidity values, display to an LCD screen, and connect to bluetooth app
//IMPORTING LCD LIBRARY
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

//IMPORTING DHT LIBRARY
#include <dht.h>

//DEFINING LCD PARAMETERS
#define I2C_ADDR    0x3F 
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

#define dht_apin 7

int led = 13;
dht DHT;

LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup()
{
  Serial.begin(9600);
  //STATING LCD SCREEN DIMENSIONS
 lcd.begin (16,2);

 
//TURNING LCD BACK-LIGHT ON
lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
lcd.setBacklight(HIGH);
lcd.home();   //move cursor to top left corner
//STARTING PRINTING TEXT ON ARDUINO
 lcd.print("STARTING UP");
  delay(500);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  delay(700);
  lcd.clear(); 
}

void loop()
{
 //check temperature and humidity
 int chk = DHT.read11(dht_apin);

 //lcd.autoscroll();
 
 //Print Temperature
 lcd.setCursor (0,0);
 lcd.print("TEMP: ");
 lcd.setCursor (6,0);
 lcd.print(DHT.temperature,1); 
 lcd.setCursor (10,0);
 lcd.print("C\|");

 //Print humidity
 lcd.setCursor (0,1);
 lcd.print("HUMIDITY: ");
 lcd.setCursor (10,1);
 lcd.print(DHT.humidity,1); 
 lcd.setCursor (14,1);
 lcd.print("%  ");

 //check and map light values
 int ldrVal = analogRead(A1);
 ldrVal = map(ldrVal, 0,1023, 0, 100);

 //print light values with custom correcion spaces
 lcd.setCursor (12,0);
 if(ldrVal>=0 && ldrVal<=9){
  lcd.print(" ");
  lcd.print(ldrVal);
  lcd.print("% ");
 }else if(ldrVal>=10 && ldrVal<=99){
  lcd.print(" ");
  lcd.print(ldrVal);
  lcd.print("%");
 }else{
  lcd.print(ldrVal);
  lcd.print("%");
 }
 
 delay(1000);

 //Display the results in serial bluetooth connection
 Serial.println("TEMP - HUM - LDR");
 Serial.print(DHT.temperature,1); 
 Serial.print("C ");
 Serial.print(DHT.humidity,1);
 Serial.print("% ");
 Serial.print(ldrVal);
 Serial.print("%");
 Serial.println();//new line

 if(Serial.available()){
  while(Serial.available()){
    char c = Serial.read();

    switch(c){
      case 'a':
        digitalWrite(led,HIGH);
        break;
      case 'b':
        digitalWrite(led,LOW);
        break;  
    }
  }
 }
 delay(1000);
}
