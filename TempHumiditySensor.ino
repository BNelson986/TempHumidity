#include <LiquidCrystal.h>
#include <dht11.h>

#define DHT11PIN 8
#define BUTTON_PIN 13
//  Set pins for Arduino
//  LCD Pins

const int RS = 12, EN = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
dht11 DHT11;

byte lastButtonState = HIGH;
int buttonPress = 1;

void setup() {
  // Set up LCD, DHT11, and pushbutton
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(2,1);
  lcd.print(" Temp / RH ");

  //  No resistor on board, use UNO R3 internal pullup
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  delay(2000);
}

void loop() {  
  //  Clear LCD before each loop
  lcd.clear();

  //  Read button state
  byte buttonState = digitalRead(BUTTON_PIN);
  
  
  //  If button is pressed
  if(buttonState == LOW){
      //  If button is OFF, set to ON
      if(buttonPress % 2 != 0){
        buttonPress = 0;
      }
      //  If button is ON, set to OFF
      else if(buttonPress % 2 == 0){
        buttonPress = 1;
      }
  }

  //  Verify working DHT11 Module
  int chk = DHT11.read(DHT11PIN);

  float humid = DHT11.humidity;
  float temp = DHT11.temperature;
  
  lcd.print(" RH (%) = ");
  lcd.print((float)humid, 2);

  //  If button not pushed, print Celsius Temp
  if (buttonPress == 1){
    //  Print to LCD Screen
    lcd.setCursor(0, 2);
    lcd.print(" Tmp (C) = ");
    lcd.print((float)temp, 2);
  }

  //  If button pushed, print Fahrenheit Temp
  if (buttonPress == 0){
    //  Convert Celsius to Fahrenheit

    temp = (temp * 1.8) + 32;
    lcd.setCursor(0, 2);
    lcd.print(" Tmp (F) = ");
    lcd.print((float)temp, 2);    
  }

  delay(100);

}
