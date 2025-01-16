#include <Arduino.h>
// #include <SPI.h>  // Include SPI library

// int cs = 10;

// void setup() {

//   // put your setup code here, to run once:
//   SPI.begin();
//   pinMode (cs, OUTPUT);
//   digitalWrite(cs, HIGH);
//   Serial.begin(9600);

// }

// void loop() {

//   // put your main code here, to run repeatedly:
//   digitalWrite(cs, LOW);
//   Serial.println(digitalRead(cs));
//   SPI.transfer(9);
//   digitalWrite(cs, HIGH);

//   delay(2000);
// }

// ON ARDUINO UNO 
#include <SPI.h>

const int slaveSelectPin = 10; // SS pin for selecting the slave (can be any digital pin)

void setup() {
  SPI.begin();
  pinMode(slaveSelectPin, OUTPUT);
  digitalWrite(slaveSelectPin, HIGH); // Deselect the slave initially
  Serial.begin(19200);
}

void loop() {
  String message = "Hello, Mega!"; // Message to send
  digitalWrite(slaveSelectPin, LOW); // Select the slave
  delay(10); // Small delay to ensure the slave is ready to receive
  SPI.transfer(message.length()); // Send the message length
  delay(10); // Small delay to ensure the slave is ready to receive
  for (char c : message) {
    int b = SPI.transfer(c); // Send each character of the message
    Serial.println(b);
    delay(10); // Small delay between characters
  }
  digitalWrite(slaveSelectPin, HIGH); // Deselect the slave

  delay(1000); // Wait for 1 second before sending the next message
}