// ON ARDUINO UNO 
#include <SPI.h>

const int slaveSelectPin = 10; // SS pin for selecting the slave (can be any digital pin)

void setup() {
  SPI.begin();
  pinMode(slaveSelectPin, OUTPUT);
  digitalWrite(slaveSelectPin, HIGH); // Deselect the slave initially
  Serial.begin(9600);
}

void loop() {
  String message = "Hello, Mega!"; // Message to send
  digitalWrite(slaveSelectPin, LOW); // Select the slave
  delay(10); // Small delay to ensure the slave is ready to receive
  SPI.transfer(message.length()); // Send the message length
  delay(10); // Small delay to ensure the slave is ready to receive
  for (char c : message) {
    SPI.transfer(c); // Send each character of the message
    delay(10); // Small delay between characters
  }
  digitalWrite(slaveSelectPin, HIGH); // Deselect the slave

  delay(1000); // Wait for 1 second before sending the next message
}
