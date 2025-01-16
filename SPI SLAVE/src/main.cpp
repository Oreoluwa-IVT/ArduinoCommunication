#include <Arduino.h>
// #include <SPI.h>

// int reciveSpiData = 5;

// void setup() {
//   // put your setup code here, to run once:

//   SPI.begin();
//   Serial.begin(19200);
//   pinMode(reciveSpiData, INPUT); 
// }

// void loop() {
//   // put your main code here, to run repeatedly:


//   uint8_t receivedData = SPI.transfer(0x00);  // The 0x00 is a dummy value to read data
//   // Print the received data to the Serial Monitor
//   Serial.print("Received from master: ");
//   Serial.println(receivedData); 
//   delay(2000);
// }


#include <SPI.h>
const int slaveSelectPin = 10; // SS pin for the Mega (must match the Uno's SS pin)

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