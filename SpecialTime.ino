#include <Wire.h>
#include <time.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h>
DS3231 rtc;
DS3231 futureRtc;
RTClib currRtcLib;
RTClib futureRtcLib;


#define CALIBSECONDS 0
#define CALIBMINUTE 55
#define CALIBHOUR 10
#define CALIBDOW 5
#define CALIBDATE 4
#define CALIBMONTH 7
#define CALIBYEAR 24
DateTime future = DateTime(2025, 1, 3, CALIBHOUR, CALIBMINUTE, 0);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  //Serial.begin(57600);
  Wire.begin();
  delay(500);
  
  rtc.setClockMode(true); //set to 12 hour clock
  rtc.setSecond(CALIBSECONDS);
  rtc.setMinute(CALIBMINUTE); //set minute 
  rtc.setHour(CALIBHOUR); //set hour 
  rtc.setDoW(CALIBDOW); //set date of week to thursday
  rtc.setDate(CALIBDATE); //set day
  rtc.setMonth(CALIBMONTH); //set month
  rtc.setYear(CALIBYEAR); //set year
  
  lcd.init();
  lcd.backlight();
}

void loop() {
  delay(30000); //only update every 30 seconds

  char buff[17];
  DateTime now = currRtcLib.now();
  time_t nowTime = now.unixtime();
  time_t futureTime = future.unixtime();
  time_t calcTime = futureTime - nowTime;
  int days = calcTime/60/60/24;
  Serial.println(calcTime);
  lcd.setCursor(0, 0);
  snprintf(buff, 17, "%d%s", days, " Days Left!!!");
  lcd.print(buff);
  lcd.setCursor(0, 1);
  lcd.print("You Got This <33");

}

