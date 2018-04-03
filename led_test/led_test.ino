#define HW_SERIAL Serial1

// Whether this test should allow USB serial input.
const bool useUsb = true;

// The Teensy has the LED on port 13.
const int ledPin = 13;

void setup() {
  // Open the USB serial port.
  Serial.begin(9600);

  // Open the hardware serial port (pin 0).
  HW_SERIAL.begin(9600);

  // Set up the digital pin to be used as the digital output.
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Whether there is a byte to read.
  bool usbHasByte = Serial.available() > 0;
  bool hwHasByte = HW_SERIAL.available() > 0;

  if (hwHasByte || (usbHasByte && useUsb)) {
    // Store the incoming byte from the given serial port in this.
    int inByte;

    // Check to see if the USB serial has a byte to read, and print if it does.
    if (usbHasByte) {
      inByte = Serial.read();
      Serial.print("USB received: ");
      Serial.println(inByte, HEX);
      HW_SERIAL.print("USB received: ");
      HW_SERIAL.println(inByte, HEX);
    }

    // Check to see if the hardware serial has a byte to read, and print if it does.
    if (HW_SERIAL.available() > 0) {
      inByte = HW_SERIAL.read();
      Serial.print("UART received: ");
      Serial.println(inByte, HEX);
      HW_SERIAL.print("UART received: ");
      HW_SERIAL.println(inByte, HEX);
    }

    // Flash the LED to indicate that an input was received.
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
  }
}
