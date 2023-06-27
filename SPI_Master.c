#include<SPI.h>
char txMsg[] = "Oreoluwa!";
char rxMasg[20] = "";
void setup()
{
  Serial.begin(9600);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV128); //16 MHz/128
  pinMode(SS, OUTPUT);    //SS is DPin-10
  digitalWrite(SS, LOW);   //Slave is selected
}


void loop()
{
  SPI.transfer('<'); //start mark
  for(int i=0; i< sizeof(txMsg); i++)
  {
    SPI.transfer(txMsg[i]);//SPI transfer is byte-by-byte
  }
  SPI.transfer('>');  //end mark 
  delay(1000);         //test interval
}