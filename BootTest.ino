
#include <M5StickCPlus2.h> // this confused me initally as I thought it was a comment but it really calls the library

void setup() {
  M5.begin();

  M5.Lcd.fillScreen(BLACK); // simply making the screen look cooler
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setTextSize(2); // small so that the test is viisible on the small screen

  M5.Lcd.setCursor(10, 35);
  M5.Lcd.println("WIRELESS"); // I'm used to just a print function rather than println
  M5.Lcd.println("AUDITOR");

  M5.Lcd.setTextSize(1);
  M5.Lcd.println("");
  M5.Lcd.println("Device ready!");
}

void loop() {
  // Waiting for the next stage
}
