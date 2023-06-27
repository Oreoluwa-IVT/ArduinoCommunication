#include<SPI.h>
char rxMsg[20] = "";
volatile bool flag1 = false;
bool flag2 = false;
int i = 0;
void setup()
{
  Serial.begin(9600);
  pinMode(SS, INPUT_PULLUP);  //SPI.h helps to get the meaning of SS
  pinMode(MOSI, OUTPUT);      //should be made output to send data to Master
  SPCR |= _BV(SPE);         //SPI Port is enabled
  SPI.attachInterrupt();    //SPI interrupt is enabled
}
void loop()
{
  if (flag1 == true)  //SPDR has data
  {
    if (flag2 == false) //start mark of message not yet received
    {
      char q = SPDR;
      if (q == '<')
      {
        flag2 = true;   //start mark is detected
        flag1 = false;  //must be made false for the next cycle
      }
    }
    else
    {
      if (SPDR == '>')  //checking if end mark has arived
      {
        flag1 = false;
        flag2 = false;
        i = 0;
        Serial.print(rxMsg);  //end mark has arrived; show the received message
        Serial.println();     //insert newline
      }
      else
      {
        rxMsg[i] = SPDR;    //save received charcater/data byte in array
        i++;                //adjust array pointer
        flag1 = false;      //must be false for next cycle
      }
    }
  }
}
ISR (SPI_STC_vect)   //MCU comes here when there is a data byte in SPDR
{
  flag1 = true;   //flag to indicate there is data in the SPDR register
}
//Updated on 12/12/2018