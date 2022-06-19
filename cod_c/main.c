/*
    Create a TCP socket
*/

#include<stdio.h>
#include<string.h>
#include<winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define clrscr() printf("\e[1;1H\e[2J")

int recv_size, etc, tamResposta, escolha, escolhaLE, escolhaLES, escolhaAT,leituras;
char *message , server_reply[2000], string[4], qtdLeitura[1], qtdAtuacao[3];
SOCKET s;

void Sair(){
    clrscr();
    message = "EXIT#";
    send(s , message , strlen(message) , 0);
    return;
}

void MenuPrincipal(){
    clrscr();
    printf("\n\nO que fazer?\n");
    printf("1 - Ler dados do sensor\n");
    printf("2 - Enviar comandos para o atuador\n");
    printf("3 - Sair\n");
    scanf("%d", &escolha);

    switch (escolha)
    {
    case 1:
        MenuEscolhaLeitura();
        break;
    case 2:
        MenuAtuador();
        break;
    case 3:
        Sair();
        break;
    
    default:
        break;
    }
}

void MenuEscolhaLeitura(){
    clrscr();
    message = "L";
    printf("\n\nO que fazer?\n");
    printf("1 - Ler sensor\n");
    printf("2 - Ler atuador\n");
    printf("3 - Voltar\n");
    printf("4 - Sair\n");
    scanf("%d", &escolha);

    switch (escolha)
    {
    case 1:
        strcat(message, "0");
        MenuLeitura();
        break;
    case 2:
        strcat(message, "1");
        MenuLeitura();
        break;
    case 3:
        MenuPrincipal();
        break;
    case 4:
        Sair();
        break;
    
    default:
        break;
    }
}

void MenuLeitura(){
    
    clrscr();
    printf("\n\nO que fazer?\n");
    printf("1 - Leitura única\n");
    printf("2 - Leitura em série\n");
    printf("3 - Voltar\n");
    printf("4 - Sair\n");
    scanf("%d", &escolha);

    switch (escolha)
    {
    case 1:
        strcat(message, "001");
        break;
    case 2:
        clrscr();
        printf("\nInsira \"V\" para retornar ao menu anterior ou \"S\" para encerrar a conexão\nInsira abaixo a quantidade leituras em série desejada: (2 a 4)\n");
        scanf("%d", &qtdLeitura);

        if(qtdLeitura == "V"){
            MenuLeitura();
        }else if(qtdLeitura == "S"){
            Sair();
        }

        strcat(message, "00");
        strcat(message, qtdLeitura);
        break;
    case 3:
        MenuEscolhaLeitura();
        break;
    case 4:
        Sair();
        break;
    
    default:
        break;
    }

    strcat(message, "#");

    send(s , message , strlen(message) , 0);
}

void MenuAtuador(){
    message = "A0";
    printf("\nInsira \"V\" para retornar ao menu anterior ou \"S\" para encerrar a conexão\nInsira abaixo o valor correspondente à porcentagem de atuação desejada\n");
    scanf("%d", &qtdAtuacao);

    if(qtdAtuacao[0] == "V"){
        MenuLeitura();
    }else if(qtdAtuacao[0] == "S"){
        Sair();
    }

    strcat(message, qtdAtuacao);

    strcat(message, "#");

    send(s , message , strlen(message) , 0);
}

int main(int argc , char *argv[])
{
    /*################################## CONEXÃO ##################################*/
    clrscr();
    setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

    WSADATA wsa;
    
    
    struct sockaddr_in server;


    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
    }

    //Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
        return 1;
    }

    server.sin_addr.s_addr = inet_addr("192.168.0.116");
    server.sin_family = AF_INET;
    server.sin_port = htons(80);

    //Connect to remote server
    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }
    message = "G#";
    send(s , message , strlen(message) , 0);
    tamResposta = recv(s , server_reply , 2000 , 0);

    server_reply[tamResposta] = '\0';
    puts(server_reply);
    /*#############################################################################*/

    do
    {
        if(message == "EXIT#"){
            break;
        }else{
            MenuPrincipal();
        }
        
    } while (message != "EXIT#");
    

    
    
    return 0;
}
