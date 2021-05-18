#include <SoftwareSerial.h>
//Create software serial object to communicate with SIM800L
SoftwareSerial sim800l(3,2); //SIM800L Tx & Rx is connected to Arduino #3 & #2
String number = "+XXXXXXXXX"; // write your phone number here
void setup()
{
  sim800l.begin(9600);   // Setting the baud rate of sim800l GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  Serial.println("welcome");
  delay(1000);
  Serial.println("press s for send message");
  Serial.println("press r for receive message");
  Serial.println("press c for call");
  delay(1000);
}

void loop()
{
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
      Send_Message();
      break;
    case 'r':
      Recieve_Message();
      break;
    case 'c':
      Call_Number();
      break;
  }

 if (sim800l.available()>0)
   Serial.write(sim800l.read());
}

 void Send_Message()
{
  sim800l.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  sim800l.println("AT+CMGS=\"" + number + "\"\r"); // this AT command send the message to the given phone number
  delay(1000);
  sim800l.println("Hello Experimentalist");// The SMS text you want to send
  delay(100);
  sim800l.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

 void Recieve_Message()
{
  sim800l.println("AT"); 
  sim800l.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
  delay(1000);
  sim800l.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
 }

void Call_Number() {
  sim800l.println("AT"); //Once the handshake test is successful, i t will back to OK  
  sim800l.println("ATD"+number+";"); //this AT command phone dial the call to given number
  delay(20000); // wait for 20 seconds...
  sim800l.println("ATH"); //hang up
}
