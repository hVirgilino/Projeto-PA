/*
    Create a TCP socket
*/

#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define VERMELHO     "\x1b[31m"
#define VERDE   "\x1b[32m"
#define AZUL    "\x1b[34m"
#define RESET   "\x1b[0m"
#define clrscr() printf("\e[1;1H\e[2J")

int main(int argc , char *argv[])
{
    /*################################## CONEXÃO ##################################*/
    clrscr();
    setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

    WSADATA wsa;
    SOCKET s;
    
    struct sockaddr_in server;
    char *message , server_reply[2000], string[4];
    int recv_size, etc, etc2, escolha, escolhaLE, escolhaLES, escolhaAT;
    
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
    }

    printf("Initialised.\n");

    //Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
        return 1;
    }

    printf("Socket created.\n");

    server.sin_addr.s_addr = inet_addr("192.168.0.116");
    server.sin_family = AF_INET;
    server.sin_port = htons(80);

    //Connect to remote server
    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }

    puts("Connected");
    /*#############################################################################*/

    printf("\n\nO que fazer?\n");
    printf("1 - Ler dados\n");
    printf("2 - Enviar comandos\n");
    scanf("%d", &escolha);

    switch (escolha){
        case 1:
            clrscr();
            printf("\n\nO que fazer?\n");
            printf("1 - Ler dados\n");
            printf("2 - Ler dados em serie (max 8)\n");
            scanf("%d", &escolhaLE);

            switch (escolhaLE)
            {
            case 1:
                
                //Send some data
                message = "GET / HTTP/1.1\r\n\r\n";

                if((etc = send(s , message , strlen(message) , 0)) < 0)
                {
                    puts("Send failed");
                }
                printf("Data Sent: %d bytes\n", etc);

                etc2 = recv(s , server_reply , 2000 , 0);

                //Add a NULL terminating character to make it a proper string before printing
                server_reply[etc2] = '\0';
                puts(server_reply);

                break;
            
            case 2:
                
                printf("Digite a quantidade de leituras em serie a serem feitas:\n");
                scanf("%d", &escolhaLES);

                if(escolhaLES < 1){
                    escolhaLES = 1;
                }
                
                if(escolhaLES > 8){
                    escolhaLES = 8;
                }

                message = "GET / HTTP/1.1\r\n\r\n";

                if((etc = send(s , message , strlen(message) , 0)) < 0)
                {
                    puts("Send failed");
                }
                printf("Data Sent: %d bytes\n", etc);

                for(int c = 0; c < escolhaLES; c++)
                {
                    etc = recv(s , server_reply , 2000 , 0);

                    //Add a NULL terminating character to make it a proper string before printing
                    server_reply[etc] = '\0';
                    puts(server_reply);
                }

                break;
            
            default:
                puts("Digite o numero das alternativas que corresponde a acao que deseja realizar.");
                return 1;
                break;
            }

            break;

        case 2:
            clrscr();
            printf("\n\nO que deseja fazer?\n");
            printf("0 - Desligar tudo\n");
            printf("1 - Ligar LED " VERMELHO     "Vermelho"     RESET "\n");
            printf("2 - Ligar LED " AZUL    "Azul"    RESET "\n");
            printf("3 - Ligar LED " VERDE   "Verde"   RESET "\n");
            printf("4 - Apitar Buzzer\n\n");

            scanf("%d", &escolhaAT);

            switch (escolhaAT)
            {
                case 0:
                    message = "R\r\n\r\n";
                    break;
                case 1:
                    message = "ALVR\r\n\r\n";
                    break;
                case 2:
                    message = "ALAZ\r\n\r\n";
                    break;
                case 3:
                    message = "ALVD\r\n\r\n";
                    break;
                case 4:
                    message = "AB\r\n\r\n";   
                    break;
                
                default:
                    puts("Digite o numero das alternativas que corresponde a acao que deseja realizar.");
                    return 1;
                    break;
            }

            

            if((etc = send(s , message , strlen(message) , 0)) < 0)
            {
                puts("Send failed");
            }
            printf("Data Sent: %d bytes\n", etc);

            break;

        default:
            puts("Digite o numero das alternativas que corresponde a acao que deseja realizar.");
            return 1;
            break;
    }
    
    return 0;
}
