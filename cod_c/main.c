/*
    Create a TCP socket
*/

#include<stdio.h>
#include<string.h>
#include<winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define clrscr() printf("\e[1;1H\e[2J")

int recv_size, etc, tamResposta, escolha, escolhaLE, escolhaLES, escolhaAT,leituras, qtdLeitura, qtdAtuacao, dummy;
char *message , server_reply[2000], string[4], comando[6], ip[13];
SOCKET s;
WSADATA wsa;
struct sockaddr_in server;

void MenuEscolhaLeitura();
void MenuAtuador();
void MenuLeitura();
void MenuDigitacaoLivre();
void MenuPrincipal();

void Conectar(char* ip){
    setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
    }

    //Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
        return;
    }
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(80);

    //Connect to remote server
    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        exit(0);
    }   

}

void MenuInicial(){
    //192.168.0.116
    clrscr();
    printf("MENU INICIAL\n\n");
    printf("Digite o ip que deseja conectar: ");
    scanf("%s", &ip);
    Conectar(ip);
    message = "G#";
    send(s , message , strlen(message) , 0);
    tamResposta = recv(s , server_reply , 2000 , 0);
    server_reply[tamResposta] = '\0';
    puts(server_reply);
    printf("Aperte Enter para continuar");
    scanf("%d", &dummy);
    MenuPrincipal();
    
}

void EncerrarConexao(){
    ip[0] = '\0';
    MenuInicial();
}

void MenuPrincipal(){
    clrscr();
    printf("Digite o comando que deseja enviar para o server (seguindo o protocolo)\n");
    scanf("%s", comando);

    

    message = comando; 

    send(s , message , strlen(message) , 0);

    tamResposta = recv(s , server_reply , 2000 , 0);
    tamResposta = recv(s , server_reply , 2000 , 0);
    server_reply[tamResposta] = '\0';
    puts(server_reply);

    if (comando == "EXIT#")
    {
        EncerrarConexao();
    }
    printf("Aperte Enter para continuar");
    scanf("%d", &dummy);
    MenuPrincipal();
}


int main(int argc , char *argv[])
{
    /*################################## CONEXÃO ##################################*/
    clrscr();

    

    
    /*#############################################################################*/


    MenuInicial();
    
    
    return 0;
}
