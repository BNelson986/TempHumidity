#include <LiquidCrystal.h>
#include <dht11.h>

#define DHT11PIN 8
//  Set pins for Arduino
//  LCD Pins

const int RS = 12, EN = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
dht11 DHT11;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(2,1);
  lcd.print(" Temp / RH ");
  delay(2000);
}

void loop() {  
  //  Clear LCD before each loop
  lcd.clear();

  //  Verify working DHT11 Module
  int chk = DHT11.read(DHT11PIN);

  //  Print to LCD Screen
  lcd.print(" RH (%) = ");
  float humid = DHT11.humidity;
  float temp = DHT11.temperature;
  
  lcd.print((float)humid, 2);

  lcd.setCursor(0, 2);
  lcd.print(" Tmp (C) = ");
  lcd.print((float)temp, 2);


  delay(1500);

}
