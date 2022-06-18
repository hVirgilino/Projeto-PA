/*--------------------------------------------------------------
  Program:      eth_websrv_page

  Description:  Arduino web server that serves up a basic web
                page. Does not use the SD card.
  
  Hardware:     Arduino Uno and official Arduino Ethernet
                shield. Should work with other Arduinos and
                compatible Ethernet shields.
                
  Software:     Developed using Arduino 1.0.3 software
                Should be compatible with Arduino 1.0 +
  
  References:   - WebServer example by David A. Mellis and 
                  modified by Tom Igoe
                - Ethernet library documentation:
                  http://arduino.cc/en/Reference/Ethernet

  Date:         7 January 2013
 
  Author:       W.A. Smith, http://startingelectronics.org
--------------------------------------------------------------*/

#include <SPI.h>
#include <Ethernet.h>
#define RESET asm ("jmp (0x0000)")

// MAC address from Ethernet shield sticker under board
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 116); // IP address, may need to change depending on network
EthernetServer server(80);  // create a server at port 80

String comando;
int d = 0;
char c;

//Pinos
int Buzzer = 4;


void setup()
{
    Ethernet.begin(mac, ip);  // initialize Ethernet device
    server.begin();           // start to listen for clients

    pinMode(Buzzer, OUTPUT);
    
    
}

void loop()
{
    
    EthernetClient client = server.available();  // try to get client

    if (client) {  // got client?
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {   // client data available to read
                
                //read char by char HTTP request
                while (d < 10) {
                  c = client.read();
                  //store characters to string 
                  comando += c; 
                  d++;
                } 
                
                if(comando.charAt(0) == 'R'){
                    noTone(Buzzer);
                }

                if(comando.charAt(0) == 'A' && comando.charAt(1) == 'L'){

                  if(comando.charAt(2) == 'V' && comando.charAt(3) == 'R'){
                        noTone(Buzzer);
                  }

                  if(comando.charAt(2) == 'V' && comando.charAt(3) == 'D'){
                        noTone(Buzzer);
                  }

                  if(comando.charAt(2) == 'A' && comando.charAt(3) == 'Z'){
                        noTone(Buzzer);
                  }
          
                  
                }
                
                if(comando.charAt(0) == 'A' && comando.charAt(1) == 'B'){

                    tone(Buzzer,1500);   
                    delay(1000);
                    noTone(Buzzer);
                }


                // last line of client request is blank and ends with \n
                // respond to client only after last line received
                if (c == '\n' && currentLineIsBlank) {
                    
                    break;
                }
                // every line of text received from the client ends with \r\n
                if (c == '\n') {
                    // last character on line of received text
                    // starting new line with next character read
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    // a text character was received from client
                    currentLineIsBlank = false;
                }
            } // end if (client.available())
        } // end while (client.connected())
        delay(1);      // give the web browser time to receive the data
        client.stop(); // close the connection
        RESET;
    } // end if (client)
}
