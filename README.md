# ESP32 Wireless Auditor – Passive Wi-Fi Discovery and Security Monitoring

A portable wireless network discovery and security monitoring project developed using an ESP32-based M5StickC PLUS2 and Arduino IDE.

I recently participated in an ethical hacking masterclass at the University of Cumbria, where we used ESP32 devices to create a wardriving tool. I wanted to build upon what I had learned by developing my own similar project, expanding my knowledge of wireless networking, cybersecurity and embedded systems programming.

The device uses passive Wi-Fi scanning to discover nearby wireless networks without connecting to them or attempting authentication. It filters the results to identify a specific authorised test network, allowing its advertised network characteristics to be examined.

This project explores wireless network security, ESP32 development, C++ programming and hardware/software integration.

## Hardware and Software Used

- M5StickC PLUS2 (ESP32)
- USB-C data cable
- Windows PC for development and analysis
- Arduino IDE
- C++
- ESP32 Wi-Fi library
- M5StickC PLUS2 library

## Current Features

### Passive Wi-Fi Discovery
- Button controlled Wi-Fi scanning.
- Passive wireless network discovery.
- Filtering for an authorised test network. (my home WiFi)
- SSID and BSSID identification.
- Wi-Fi channel detection.
- RSSI measurement.
- Identification of advertised security protocols, including WPA, WPA2 and WPA3.

### Display and User Interface
- Four-page LCD interface.
- Button A controls wireless scanning.
- Button B navigates between information pages.
- Scan summary displaying the number of authorised networks found.
- Separate pages for network identification, signal information and security information.

### Serial Monitor
- Displays the total number of detected networks.
- Outputs detailed information about the authorised test network.
- Reports network characteristics and security protocol information.
- Uses serial communication for debugging and development.

## Responsible Use

This project is intended for educational and defensive security research.

Scanning and analysis are restricted to authorised environments. The device performs passive discovery and observation; it does not attempt to access networks, capture credentials or bypass authentication.

## Full Development Process

To see the complete development process, including research, programming, troubleshooting and testing, check out my `journal.txt`.
