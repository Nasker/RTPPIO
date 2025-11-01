#include <Arduino.h>

#include "USBHost_t36.h"

USBHost myusb;
USBHub hub1(myusb);
//KeyboardController keyboard1(myusb);
MIDIDevice midi1(myusb);

// Track previous device states to detect changes
bool prevMidi1Connected = false;
bool prevHub1Connected = false;
unsigned long lastCheckTime = 0;
const unsigned long CHECK_INTERVAL = 1000; // Check every 1 second

void OnPress(int key){
	Serial.print("key '");
	Serial.print((char)key);
	Serial.print("'  ");
	Serial.println(key);
	//Serial.print("key ");
	//Serial.print((char)keyboard1.getKey());
	//Serial.print("  ");
	//Serial.print((char)keyboard2.getKey());
	//Serial.println();
}

void OnNoteOn(byte channel, byte note, byte velocity){
	Serial.print("Note On, ch=");
	Serial.print(channel);
	Serial.print(", note=");
	Serial.print(note);
	Serial.print(", velocity=");
	Serial.print(velocity);
	Serial.println();
}

void OnNoteOff(byte channel, byte note, byte velocity){
	Serial.print("Note Off, ch=");
	Serial.print(channel);
	Serial.print(", note=");
	Serial.print(note);
	//Serial.print(", velocity=");
	//Serial.print(velocity);
	Serial.println();
}

void OnControlChange(byte channel, byte control, byte value){
	Serial.print("Control Change, ch=");
	Serial.print(channel);
	Serial.print(", control=");
	Serial.print(control);
	Serial.print(", value=");
	Serial.print(value);
	Serial.println();
}

void printDeviceInfo(const char* deviceName, USBDriver& driver) {
	if (driver) {
		Serial.println("====================================");
		Serial.print("Device: ");
		Serial.println(deviceName);
		Serial.println("------------------------------------");
		
		// Print Vendor ID and Product ID
		Serial.print("  Vendor ID:  0x");
		Serial.println(driver.idVendor(), HEX);
		Serial.print("  Product ID: 0x");
		Serial.println(driver.idProduct(), HEX);
		
		// Print manufacturer string
		const uint8_t* mfg = driver.manufacturer();
		if (mfg) {
			Serial.print("  Manufacturer: ");
			Serial.println((const char*)mfg);
		} else {
			Serial.println("  Manufacturer: N/A");
		}
		
		// Print product string
		const uint8_t* prod = driver.product();
		if (prod) {
			Serial.print("  Product: ");
			Serial.println((const char*)prod);
		} else {
			Serial.println("  Product: N/A");
		}
		
		// Print serial number
		const uint8_t* serial = driver.serialNumber();
		if (serial) {
			Serial.print("  Serial Number: ");
			Serial.println((const char*)serial);
		} else {
			Serial.println("  Serial Number: N/A");
		}
		
		Serial.println("====================================");
		Serial.println();
	}
}

void checkAndPrintDevices() {
	bool currentMidi1 = (bool)midi1;
	bool currentHub1 = (bool)hub1;
	
	// Check for MIDI device changes
	if (currentMidi1 != prevMidi1Connected) {
		if (currentMidi1) {
			Serial.println();
			Serial.println("*** MIDI Device Connected ***");
			printDeviceInfo("MIDI Device", midi1);
		} else {
			Serial.println();
			Serial.println("*** MIDI Device Disconnected ***");
			Serial.println();
		}
		prevMidi1Connected = currentMidi1;
	}
	
	// Check for Hub changes
	if (currentHub1 != prevHub1Connected) {
		if (currentHub1) {
			Serial.println();
			Serial.println("*** USB Hub Connected ***");
			printDeviceInfo("USB Hub", hub1);
		} else {
			Serial.println();
			Serial.println("*** USB Hub Disconnected ***");
			Serial.println();
		}
		prevHub1Connected = currentHub1;
	}
}

void printAllConnectedDevices() {
	Serial.println();
	Serial.println("========================================");
	Serial.println("    CONNECTED USB DEVICES SUMMARY");
	Serial.println("========================================");
	
	int deviceCount = 0;
	
	if (midi1) {
		deviceCount++;
		printDeviceInfo("MIDI Device", midi1);
	}
	
	if (hub1) {
		deviceCount++;
		printDeviceInfo("USB Hub", hub1);
	}
	
	if (deviceCount == 0) {
		Serial.println("  No USB devices connected.");
		Serial.println();
	}
	
	Serial.print("Total devices connected: ");
	Serial.println(deviceCount);
	Serial.println("========================================");
	Serial.println();
}

void setup(){
	while (!Serial) ; // wait for Arduino Serial Monitor
	Serial.begin(115200);
	Serial.println("\n\n====================================");
	Serial.println("    USB Host Device Monitor");
	Serial.println("====================================");
	Serial.println("Initializing USB Host...");
	
	myusb.begin();
	
	// Setup MIDI callbacks
	midi1.setHandleNoteOff(OnNoteOff);
	midi1.setHandleNoteOn(OnNoteOn);
	midi1.setHandleControlChange(OnControlChange);
	
	Serial.println("USB Host initialized.");
	Serial.println("Monitoring for USB device connections...");
	Serial.println();
	
	// Wait a moment for initial enumeration
	delay(1000);
	
	// Print initial device status
	printAllConnectedDevices();
}

void loop(){
	myusb.Task();
	midi1.read();
	
	// Periodically check for device changes
	unsigned long currentTime = millis();
	if (currentTime - lastCheckTime >= CHECK_INTERVAL) {
		lastCheckTime = currentTime;
		checkAndPrintDevices();
	}
}