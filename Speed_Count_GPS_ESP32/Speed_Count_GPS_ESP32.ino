/*
 GitHub : samueljovial21
 https://github.com/samueljovial21
*/

#include <TinyGPS++.h>
#include <LiquidCrystal_I2C.h>

#define lcdColumns 16
#define lcdRows 2

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

#define RXD2 16
#define TXD2 17
HardwareSerial neogps(1);

TinyGPSPlus gps;

int speedValue;
int speedValueMph;

void setup() {
    Serial.begin(115200);
  //Begin serial communication Arduino IDE (Serial Monitor)

  //Begin serial communication Neo6mGPS
  neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);

  // initialize LCD
  lcd.init();
  // turn on LCD backlight
  lcd.backlight();

}

void loop() {
  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 100;)
  {
    while (neogps.available())
    {
      if (gps.encode(neogps.read()))
      {
        newData = true;
      }
    }
  }

  //If newData is true
  if (newData == true)
  {
    newData = false;

    if (gps.satellites.value() != 0) {
      speedValue = gps.speed.kmph();
      speedValueMph = gps.speed.mph();
      Serial.print("Speed : ");
      Serial.print(speedValueMph);
      Serial.println(" m/h");
      String printValue = String(speedValue);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Speed :");
      lcd.setCursor(0, 1);
      lcd.print(printValue + " Km/H");
      delay(100);
    }
    else
    {
      Serial.println("No Signal");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Speed :");
      lcd.setCursor(0, 1);
      lcd.print("No Signal");
      delay(100);
    }
  }
}
