#include <SPI.h>
#include <Ethernet.h>
#include <string.h>
#include <DHT.h>
#define RESET asm ("jmp (0x0000)")
#define DHTPIN 5//Pino digital 5 conectado ao DHT11
#define DHTTYPE DHT11//DHT 11

// MAC address from Ethernet shield sticker under board
byte mac[]= { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 116); // IP address, may need to change depending on network
EthernetServer server(80);  // create a server at port 80




String comando;
String grupo = "GTZ08#";
String erro = "ERRO#";
String mensagem;
int d = 0;
String valBuzzer = "000";
String val;
String confereErro;

//Pinos
int Buzzer = 4;
DHT dht(DHTPIN, DHTTYPE);//Inicializando o objeto dht do tipo DHT passando como parâmetro o pino (DHTPIN) e o tipo do sensor (DHTTYPE)

//Funções
void ApitarBuzzer(int porcentagem){
    int frequencia = porcentagem*15;
    tone(Buzzer, frequencia);
    String aux = String(porcentagem);
    int tal = aux.length();
    
    switch (tal)
    {
    case 1:
        mensagem.concat("00");
        mensagem.concat(String(porcentagem));
        valBuzzer = "";
        valBuzzer.concat("00");
        valBuzzer = String(porcentagem);
        break;
    case 2:
        mensagem.concat("0");
        mensagem.concat(String(porcentagem));
        valBuzzer = "";
        valBuzzer.concat("0");
        valBuzzer = String(porcentagem);
        break;
    case 3:
        mensagem.concat(String(porcentagem));
        valBuzzer = "";
        valBuzzer = String(porcentagem);
        break;
    
    default:
        break;
    }
}



void setup()
{
    Ethernet.begin(mac, ip);  // initialize Ethernet device
    server.begin();           // start to listen for clients
    dht.begin();
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

                char c = client.read();

                switch (c)
                {
                case 'G':
                    client.println(grupo);
                    break;
                case 'E':
                        noTone(Buzzer);
                            client.stop(); // close the connection

                    // for (int i = 0; i < 4; i++)
                    // {
                    //     c = client.read();
                    //     confereErro += c;

                    //     if(confereErro == "XIT#"){
                    //         noTone(Buzzer);
                    //         client.stop(); // close the connection
                    //     }else{
                    //         client.println(erro);
                    //     }
                    // }
                    
                    break;
                case 'L':
                    c = client.read();
                    switch (c)
                    {
                    case '1':
                        mensagem = "T";
                        c = client.read();
                        c = client.read();
                        c = client.read();
                        int valor = c - '0';


                         for (int i = 0; i < valor; i++)
                         {
                            String aux = String((int)dht.readTemperature());
                            int tal = aux.length();

                            switch (tal)
                            {
                            case 2:
                                mensagem.concat("00");
                                mensagem.concat(String((int)dht.readTemperature()));
                                break;
                            case 3:
                                mensagem.concat("0");
                                mensagem.concat(String((int)dht.readTemperature()));
                                break;

                            default:
                                break;
                            }
                        }
                        mensagem.concat('C');
                        mensagem.concat('#');
                        client.println(mensagem);
                        mensagem = "";
                        break;
                    case '0':
                        mensagem = "Z0";
                        c = client.read();
                        c = client.read();
                        c = client.read();
                        int valor2 = c - '0';

                        for (int i = 0; i < valor2; i++)
                        {
                            mensagem.concat(valBuzzer);
                        }

                        mensagem.concat('P');
                        mensagem.concat('#');
                        client.println(mensagem);
                        mensagem = ""; 
                        break;
                    
                    default:
                        client.println(erro);
                        break;
                    }
                    

                    break;
                case 'A':
                    mensagem = "Z0";
                    c = client.read();
                    switch (c)
                    {
                    case '0':
                        
                        for (int i = 0; i < 3; i++)
                        {
                            c = client.read();
                            val += c;
                        }

                        int valor = val.toInt();
                        ApitarBuzzer(valor);
                        mensagem.concat('P');
                        mensagem.concat('#');
                        client.println(mensagem);
                        mensagem = ""; 
                        break;
                    case '1':
                        client.println(erro);
                        break;
                    
                    default:
                        client.println(erro);
                        break;
                    }

                    break;

                
                default:
                    client.println(erro);
                    break;
                }

            } // end if (client.available())
        } // end while (client.connected())
        delay(5);
        // give the web browser time to receive the data
        //RESET;
        //client.stop();
    } // end if (client)
    
}
