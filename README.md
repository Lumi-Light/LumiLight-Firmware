# Lumi-Light-Firmware
Integrated Open-Source Firmware for LumiLight

## Hardware Components & Connections:
- NodeMCU ESP8266 Module
- LDR Light Sensor Module
  - DO -> D2  |  (+) -> 3v  |  (-) -> Gnd
- AC to DC (5V,1A) Converter
  - (+) -> Vin  |  (-) -> Gnd 
- LED Light Indicator
  - (+) -> D1  |  (-) -> Gnd  

### NodeMCU is a open-source IoT firmware and development kit based on ESP8266 wifi Module.
![image](https://user-images.githubusercontent.com/68856476/157051733-74ef7885-cc2a-4f1e-ac5b-7fdef62eb04a.png)

## Firmware Instalation Steps : 
- **Install Drivers, This modules has plug & play CH340g USB-TTL IC.**
  - Windows Driver : http://www.wch-ic.com/downloads/CH341SER_EXE.html
  - Linux Driver : http://www.wch-ic.com/downloads/CH341SER_LINUX_ZIP.html
  - Mac Driver : http://www.wch-ic.com/downloads/CH341SER_MAC_ZIP.html
  - Linux & Mac Drivers Have Instalation Instructions Inside.
- **Arduino-IDE :**
  - Choose Preferences in the File menu and enter the copied code(http://arduino.esp8266.com/stable/package_esp8266com_index.json) in Additional Board Manager URLs part. Then press OK.
  - Search the word ESP8266 in Boards>boards manager from Tools menu. Then install ESP8266 boards. After complete installation, you will see the INSTALLED label on ESP8266 boards.
  - Open the Arduino Library Manager, Search for “ArduinoJson”, Click install.
  - Select Board : NodeMCU 12E
  - Upload NodeMCU_Firmare.ino
