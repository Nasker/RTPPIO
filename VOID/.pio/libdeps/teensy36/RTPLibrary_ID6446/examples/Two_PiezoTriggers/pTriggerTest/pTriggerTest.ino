#include <RTPPiezoTrigger.h>

RTPPiezoTrigger pTrigger1(0,0x97,36);
RTPPiezoTrigger pTrigger2(1,0x97,40);

void setup() {
  Serial.begin(31250);
  pTrigger1.calibrate(100);
  pTrigger2.calibrate(100);
}

void loop() {
  pTrigger1.readnShoot();
  pTrigger2.readnShoot();
}
