#include "NafuuGSM.h"
#include <SoftwareSerial.h>

NafuuGSM::NafuuGSM(SoftwareSerial * pointer) {
  mySerial = pointer;
  language = "";
  serialMode = "built_in_menu";
}

void NafuuGSM::begin(uint32_t baudRate) {
  mySerial->begin(baudRate);
  Serial.begin(baudRate);
}

void NafuuGSM::makeSelection() {
  if (language.length() == 0) {
    clearMonitor();
    Serial.println("AT Commands based GSM Tester");
    Serial.println("By: Ali Saleh");
    Serial.println("https://nafuutronics.com");
    changeOperatingMode();
    changeLanguage();
  }else{
      if (language == "en") 
        makeSelectionEn();
      else if (language == "sw")
        makeSelectionSw();
      else
        makeSelectionEn();
  }
}

void NafuuGSM::changeLanguage() {
  clearMonitor();
  Serial.println("Select Language:");
  Serial.println("1. English");
  Serial.println("2. Swahili");

  char selection = getSelection().charAt(0);
  // Serial.print(selection);
  if (selection == '1')
    language = "en";
  else if (selection == '2')
    language = "sw";
  else
    language = "en";
}

void NafuuGSM::changeOperatingMode() {
  clearMonitor();
  Serial.println("Operating Mode:");
  Serial.println("1. Menu Mode");
  Serial.println("2. AT Command Mode");

  char selection = getSelection().charAt(0);
  if (selection == '1')
    serialMode = "built_in_menu";
  else
    serialMode = "serial_monitor";
}

void NafuuGSM::makeSelectionSw() {
  clearMonitor();
  Serial.println("1. Piga Simu");
  Serial.println("2. Tuma Meseji");
  Serial.println("3. Tayarisha kupokea Meseji");
  Serial.println("4. Pokea Simu");
  Serial.println("5. Kata Simu");
  Serial.println("6. Cheki uzima wa GSM");
  Serial.println("7. Badili Lugha");
  Serial.println("8. Badili Utumiaji");
  Serial.println("");
  updateSerial("built_in_menu");
}

void NafuuGSM::makeSelectionEn() {
  clearMonitor();
  Serial.println("1. Make Call");
  Serial.println("2. Send SMS");
  Serial.println("3. Prepare to receive SMS");
  Serial.println("4. Accept Incoming Call");
  Serial.println("5. Hangup Call");
  Serial.println("6. Test GSM");
  Serial.println("7. Change Language");
  Serial.println("8. Change Operating Mode");
  Serial.println("");
  updateSerial("built_in_menu");
}

String NafuuGSM::getSelection() {
  while (!Serial.available()) {}
  return Serial.readString();
}

void NafuuGSM::clearMonitor() {
//  Serial.write(27);
//  Serial.print("[2J");
  Serial.println("");
}

void NafuuGSM::updateSerial(String isFromMenu)
{
  if (isFromMenu == "built_in_menu") {
    char selection = getSelection().charAt(0);
    if (selection == '1')
      makeCall("+255777464655");
    else if (selection == '2')
      sendSMS("+255777464655", "This is a test message from nafuutronics.com");
    else if (selection == '3')
      readingSMS();
    else if (selection == '4')
      acceptCall();
    else if (selection == '5')
      hangUpCall();
    else if (selection == '6')
      testGSM();
    else if (selection == '7')
      changeLanguage();
    else if (selection == '8')
      changeOperatingMode();
  }
  else if (isFromMenu == "serial_monitor") {
    readFromMonitor();
  }
}

void NafuuGSM::readFromMonitor() {
  delay(500);
  while (Serial.available()) 
  {
    mySerial->write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial->available()) 
  {
    Serial.write(mySerial->read());//Forward what Software Serial received to Serial Port
  }
}

void NafuuGSM::makeCall(String phoneNumber)
{
  mySerial->println("AT"); //Once the handshake test is successful, i t will back to OK
  updateSerial("serial_monitor");
  
  mySerial->println("ATD" + phoneNumber); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
  updateSerial("serial_monitor");
  
  delay(20000); // wait for 20 seconds...
  mySerial->println("ATH"); //hang up
  updateSerial("serial_monitor");
}

void NafuuGSM::acceptCall() {
  mySerial->println("ATA"); //accept
  updateSerial("serial_monitor");
}

void NafuuGSM::hangUpCall() {
  mySerial->println("ATH"); //hang up
  updateSerial("serial_monitor");
}

void NafuuGSM::testGSM() {
  mySerial->println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial("serial_monitor");
  mySerial->println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial("serial_monitor");
  mySerial->println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial("serial_monitor");
  mySerial->println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial("serial_monitor");
}

void NafuuGSM::sendSMS(String phoneNumber, String message) {
  mySerial->println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial("serial_monitor");

  mySerial->println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial("serial_monitor");
  mySerial->print("AT+CMGS=\"");
  mySerial->println(phoneNumber + "\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial("serial_monitor");
  mySerial->print(message); //text content
  updateSerial("serial_monitor");
  mySerial->write(26);
}

void NafuuGSM::readingSMS() {
  mySerial->println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial("serial_monitor");
  mySerial->println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial("serial_monitor");
  mySerial->println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
  updateSerial("serial_monitor");
}
