#include <SPI.h>

const int slaveSelectPin = 53; // SS pin for the Mega (must match the Uno's SS pin)

void setup() {
  SPI.begin();
  pinMode(slaveSelectPin, INPUT); // Set SS pin as input to enable SPI Slave mode
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(slaveSelectPin) == LOW) {
    int messageLength = SPI.transfer(0); // Read the message length
    delay(10); // Small delay to ensure the message is ready to read
    String receivedMessage = "";
    for (int i = 0; i < messageLength; i++) {
      char c = SPI.transfer(0); // Read each character of the message
      receivedMessage += c;
      delay(10); // Small delay between characters
    }
    Serial.println("Received message: " + receivedMessage);
    delay(100); // Add a small delay to avoid repeated processing
  }
}



//////////////////////////////////////////////////////////////////////////////
// ADD A DECOUPLING CAPACITOR TO SS INCASE YOU GET GIBERISH. IT WILL STABILIZE THE SS PIN TO LOW" 
// I TRIED IT AND IT WORKED 
//////////////////////////////////////////////////////////////////////////////
