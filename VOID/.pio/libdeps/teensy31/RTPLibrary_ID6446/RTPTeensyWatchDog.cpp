/*
	RTPTeensyWatchDog.cpp - Class for managing Teensy 3x watchdog.
	Created by Oscar Martínez Carmona @ RockinTechProjects, December 17, 2018.
*/

#include "RTPTeensyWatchDog.h"

RTPTeensyWatchDog::RTPTeensyWatchDog(){

}

void RTPTeensyWatchDog::init(){
	noInterrupts();                                         // don't allow interrupts while setting up WDOG
  	WDOG_UNLOCK = WDOG_UNLOCK_SEQ1;                         // unlock access to WDOG registers
  	WDOG_UNLOCK = WDOG_UNLOCK_SEQ2;
  	delayMicroseconds(1);                                   // Need to wait a bit..

  	// for this demo, we will use 2 second WDT timeout (e.g. you must reset it in < 2 sec or a boot occurs)
  	WDOG_TOVALH = 0x00db; 
  	WDOG_TOVALL = 0xba00;

  	// This sets prescale clock so that the watchdog timer ticks at 7.2MHz
  	WDOG_PRESC  = 0x400;

  	// Set options to enable WDT. You must always do this as a SINGLE write to WDOG_CTRLH
  	WDOG_STCTRLH |= WDOG_STCTRLH_ALLOWUPDATE | WDOG_STCTRLH_WDOGEN | WDOG_STCTRLH_WAITEN |	WDOG_STCTRLH_STOPEN | WDOG_STCTRLH_CLKSRC;
  	interrupts();

}
		
void RTPTeensyWatchDog::kick(){
	noInterrupts();
  	WDOG_REFRESH = 0xA602;
  	WDOG_REFRESH = 0xB480;
  	interrupts();
}