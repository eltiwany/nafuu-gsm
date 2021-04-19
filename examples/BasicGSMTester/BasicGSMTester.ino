#include <SoftwareSerial.h>
#include "NafuuGSM.h"

SoftwareSerial serial(9, 10);
NafuuGSM gsm(&serial);

void setup() {
  gsm.begin(9600);
}

void loop()
{
  if (gsm.serialMode == "serial_monitor")
    gsm.updateSerial("serial_monitor");
  else
    gsm.makeSelection();
}
