# ESP 2 ESP UDP Connection Bridge

Can be used to make simple communication between to ESP8266 Wifi Modules using UDP Protocol


----------------------------------------------
Requirements:

2x ESP8266 with Arduino Core
Download Latest ESP8266 Hardware to the Arduino IDE
----------------------------------------------
STEPS:
1- Simply Upload TX to ESP8266
and Upload RX to another ESP8266


2- Open UART Terminal Of Tx-ESP and Rx-ESP

3- Try to send any message on the Tx Side, Like "n" or "f" (without  double quotation  marks"

4- Customize the decodeMessage function of Rx side to your application needs
----------------------------------------------