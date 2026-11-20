#include <M5StickCPlus2.h>
#include <WiFi.h> // added the WiFi library to provide the deice  connection

const char* TARGET_SSID = "EE-729RRC"; // my personal wifi network to ensure authorised access

void setup() {
  M5.begin();

  Serial.begin(115200); // the baud rate/bit rate

  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(BLACK);

  WiFi.mode(WIFI_STA); // this sets the ESP within the M5 to station mode, meaning it can discover networks without joininigg an access point
  WiFi.disconnect(); // similarly that makes sure its not connected to any networks

// same startup as earlier, except this time the screeen can be changed with a button click
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setTextSize(2);

  M5.Lcd.setCursor(15, 25);
  M5.Lcd.println("WIRELESS");

  M5.Lcd.setCursor(15, 50);
  M5.Lcd.println("AUDITOR");

  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(1);

  M5.Lcd.setCursor(15, 90);
  M5.Lcd.println("PRESS BUTTON A TO SCAN");

}

void loop() {

  M5.update();

  if (M5.BtnA.wasPressed()) { // checks for click

    scanWiFi(); // calling the function

  }

}


void scanWiFi() { // new function (called above)

  M5.Lcd.fillScreen(BLACK); // resets the screen

  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setCursor(15, 20);
  M5.Lcd.println("SCANNING..."); // makes it easier to debug


  // Print a heading in the computer's Serial Monitor
  Serial.println();
  Serial.println("WIRELESS AUDITOR");

  int networkCount = WiFi.scanNetworks(false, false, true); // perform the scan, false meaning wait for completion, and dont specifically search for hidden SSIDs and true for passsive scanning

  int matchingCount = 0; // keps count of authorised networks found

  Serial.print("Networks detected: "); // displays the number of networrks found
  Serial.println(networkCount);

  for (int i = 0; i < networkCount; i++) { // checks each result

    String ssid = WiFi.SSID(i); // finds the SSID name

    if (ssid == TARGET_SSID) { // makes sure ti only displays info from authorised networks

      matchingCount++;

      Serial.print("SSID: ");
      Serial.println(ssid);


      Serial.print("BSSID: "); // the mac address of the access pointt
      Serial.println(WiFi.BSSIDstr(i));


      Serial.print("Channel: "); // the iwreless channel
      Serial.println(WiFi.channel(i));

      Serial.print("Signal strength: "); 
      Serial.print(WiFi.RSSI(i));
      Serial.println(" dBm");

      if (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) { 

        Serial.println("Security: OPEN");

      } else {

        Serial.println("Security: ENCRYPTED");

      }

    }

  }

// prints all information
  Serial.print("Authorised networks found: ");
  Serial.println(matchingCount);

  M5.Lcd.fillScreen(BLACK);

  M5.Lcd.setCursor(10, 20);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setTextSize(2);

  M5.Lcd.println("SCAN DONE");

  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(1);

  M5.Lcd.setCursor(10, 60);
  M5.Lcd.printf("Matches: %d", matchingCount);

  M5.Lcd.setCursor(10, 90);
  M5.Lcd.println("See Serial Monitor");


  WiFi.scanDelete(); // clears previous scan results from memory

}
