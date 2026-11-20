
#include <M5StickCPlus2.h>
#include <WiFi.h> // added the WiFi library to provide the deice  connection

const char* TARGET_SSID = "EE-729RRC"; // my personal wifi network to ensure authorised access
int currentPage = 0; // page ariable, so tat the display can be placed accross multiple pages on teh decvice, so that it is easier to see and add more infokmation int h future

// New variables to store the scan results
String foundSSID = "";
String foundBSSID = "";
String foundSecurity = "UNKNOWN";
int foundChannel = 0;
int foundSignal = 0;
int matchingCount = 0;
bool scanComplete = false;

void displayPage(); // function declaration

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

  // Button B moves to the next information page
  if (M5.BtnB.wasPressed() && scanComplete) {

    currentPage++;

    if (currentPage > 3) {
      currentPage = 0;
    }

    displayPage();

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

  matchingCount = 0; // keps count of authorised networks found

  // Reset stored results before a new scan
  foundSSID = "";
  foundBSSID = "";
  foundSecurity = "UNKNOWN";
  foundChannel = 0;
  foundSignal = 0;

  Serial.print("Networks detected: "); // displays the number of networrks found
  Serial.println(networkCount);

  for (int i = 0; i < networkCount; i++) { // checks each result

    String ssid = WiFi.SSID(i); // finds the SSID name

    if (ssid == TARGET_SSID) { // makes sure ti only displays info from authorised networks

      matchingCount++;

      Serial.print("SSID: ");
      Serial.println(ssid);

      foundSSID = ssid;

      Serial.print("BSSID: "); // the mac address of the access pointt
      Serial.println(WiFi.BSSIDstr(i));

      foundBSSID = WiFi.BSSIDstr(i);

      Serial.print("Channel: "); // the iwreless channel
      Serial.println(WiFi.channel(i));

      foundChannel = WiFi.channel(i);

      Serial.print("Signal strength: "); 
      Serial.print(WiFi.RSSI(i));
      Serial.println(" dBm");

      foundSignal = WiFi.RSSI(i);

      int encryption = WiFi.encryptionType(i); // getting type

      String security = getSecurityName(encryption); // makes iit readable text

      Serial.print("Security: "); // printing result
      Serial.println(security);

      foundSecurity = security;

    }

  }

  // prints all information
  Serial.print("Authorised networks found: ");
  Serial.println(matchingCount);

  scanComplete = true;
  currentPage = 0;

  WiFi.scanDelete(); // clears previous scan results from memory

  displayPage();

}


void displayPage() {

  M5.Lcd.fillScreen(BLACK);

  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(10, 15);

  if (currentPage == 0) {

    M5.Lcd.println("SCAN DONE");

    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(10, 60);
    M5.Lcd.printf("Matches: %d", matchingCount);

  }

  else if (currentPage == 1) {

    M5.Lcd.println("NETWORK");

    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(1);

    M5.Lcd.setCursor(10, 55);

    if (foundSSID == "") {
      M5.Lcd.println("No authorised network");
    } else {
      M5.Lcd.println("SSID:");
      M5.Lcd.setCursor(10, 70);
      M5.Lcd.println(foundSSID);

      M5.Lcd.setCursor(10, 90);
      M5.Lcd.println("BSSID:");
      M5.Lcd.setCursor(10, 105);
      M5.Lcd.println(foundBSSID);
    }

  }

  else if (currentPage == 2) {

    M5.Lcd.println("SIGNAL");

    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(10, 60);

    if (foundSSID == "") {
      M5.Lcd.println("No network data");
    } else {
      M5.Lcd.printf("Strength: %d dBm", foundSignal);

      M5.Lcd.setCursor(10, 85);
      M5.Lcd.printf("Channel: %d", foundChannel);
    }

  }

  else if (currentPage == 3) {

    M5.Lcd.println("SECURITY");

    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(10, 60);

    if (foundSSID == "") {
      M5.Lcd.println("No network data");
    } else {
      M5.Lcd.print("Protocol: ");
      M5.Lcd.println(foundSecurity);
    }

  }

  // Displays the current page and navigation instructions
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(10, 120);
  M5.Lcd.printf("PAGE %d/4 - B: NEXT", currentPage + 1);

}


String getSecurityName(int encryption) {

  switch (encryption) { // checks the level of encryption switch used instead of multiple if statements

    case WIFI_AUTH_OPEN:
      return "OPEN";

    case WIFI_AUTH_WEP:
      return "WEP";

    case WIFI_AUTH_WPA_PSK:
      return "WPA";

    case WIFI_AUTH_WPA2_PSK:
      return "WPA2";

    case WIFI_AUTH_WPA_WPA2_PSK:
      return "WPA/WPA2";

    case WIFI_AUTH_WPA2_ENTERPRISE:
      return "WPA2 ENTERPRISE";

    case WIFI_AUTH_WPA3_PSK:
      return "WPA3";

    case WIFI_AUTH_WPA2_WPA3_PSK:
      return "WPA2/WPA3";

    default:
      return "UNKNOWN";

  }

}
