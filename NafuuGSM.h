/*
  NafuuGSM.h - Library for testing GSM modules.
  Created by Ali A. Saleh, April 20, 2021.
  Released with GPL Licence v3.0.
*/
#include "Arduino.h"
#ifndef Nafuu_GSM_H
#define Nafuu_GSM_H
#include <Arduino.h>
#include <SoftwareSerial.h>

class NafuuGSM
{
public:
  void setPhoneNumber(String phoneNumber);
  void makeSelection();
  void changeLanguage();
  void changeOperatingMode();
  void makeSelectionSw();
  void makeSelectionEn();
  String getSelection();
  void clearMonitor();
  void updateSerial(String isFromMenu);
  void readFromMonitor();
  void makeCall(String phoneNumber);
  void acceptCall();
  void hangUpCall();
  void testGSM();
  void sendSMS(String phoneNumber, String message);
  void readingSMS();
  // variables
  String language;
  String serialMode;
  String phoneNumber;
  NafuuGSM(SoftwareSerial *pointer);
  void NafuuGSM::begin(uint32_t baudRate);

private:
  SoftwareSerial *mySerial;
  int _txPin, _rxPin;
};

#endif
