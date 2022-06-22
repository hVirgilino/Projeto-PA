/*
    Create a TCP socket
*/

#include<stdio.h>
#include<string.h>
#include<winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define clrscr() printf("\e[1;1H\e[2J")

int recv_size, etc, tamResposta, escolha, escolhaLE, escolhaLES, escolhaAT,leituras, qtdLeitura, qtdAtuacao;
char *message , server_reply[2000], string[4], comando[6], ip[13];
SOCKET s;

void MenuEscolhaLeitura();
void MenuAtuador();
void MenuLeitura();
void MenuDigitacaoLivre();
void MenuPrincipal();

void MenuInicial(){
    //192.168.0.116
    clrscr();
    printf("MENU INICIAL\n\n");
    printf("Digite o ip que deseja conectar: ");
    scanf("%s", &ip);
    MenuPrincipal();
}

void EncerrarConexao(){
    ip[0] = '\0';
    MenuInicial();
}
void Sair(){
    clrscr();
    //message = "EXIT#";
    //send(s , message , strlen(message) , 0);
    return;
}

void MenuPrincipal(){
    clrscr();
    printf("MENU INICIAL -> MENU PRINCIPAL\n\n");
    printf("O que fazer?\n");
    printf("0 - Digitacao livre\n");
    printf("1 - Ler dados do sensor\n");
    printf("2 - Enviar comandos para o atuador\n");
    printf("3 - Encerrar conexao\n");
    printf("4 - Sair\n");
    scanf("%d", &escolha);

    switch (escolha)
    {
    case 0:
        MenuDigitacaoLivre();
        break;
    case 1:
        MenuEscolhaLeitura();
        break;
    case 2:
        MenuAtuador();
        break;
    case 3:
        EncerrarConexao();
    case 4:
        Sair();
        break;
    
    default:
        break;
    }
}

    void MenuEscolhaLeitura(){
        clrscr();
        //message = "L";
        printf("MENU INICIAL -> MENU PRINCIPAL -> MENU DE ESCOLHA DE LEITURA\n\n");
        printf("O que fazer?\n");
        printf("1 - Ler sensor\n");
        printf("2 - Ler atuador\n");
        printf("3 - Voltar\n");
        printf("4 - Encerrar conexao\n");
        printf("5 - Sair\n");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            //strcat(message, "0");
            MenuLeitura();
            break;
        case 2:
            //strcat(message, "1");
            MenuLeitura();
            break;
        case 3:
            MenuPrincipal();
            break;
        case 4:
            EncerrarConexao();
            break;
        case 5:
            Sair();
            break;
        
        default:
            break;
        }
    }

void MenuDigitacaoLivre(){
    clrscr();
    printf("MENU INICIAL -> MENU PRINCIPAL -> MENU DE DIGITACAO LIVRE\n\n");
    printf("Insira \"-1\" para retornar ao menu anterior, \"-2\" para encerrar a conexao ou -3 para finalizar o programa\nDigite o comando que deseja enviar para o server (seguindo o protocolo)\n");
    scanf("%s", comando);

    if(comando[1] == '1'){
        MenuPrincipal();
    }else if(comando[1] == '2'){
        EncerrarConexao();
    }else if (comando[1] == '3'){
        Sair();
    }

    // message = comando; 
    // strcat(message, "#");

    // send(s , message , strlen(message) , 0);
}

        void MenuLeitura(){
            
            clrscr();
            printf("MENU INICIAL -> MENU PRINCIPAL -> MENU DE ESCOLHA DE LEITURA -> MENU DE LEITURA\n\n");
            printf("O que fazer?\n");
            printf("1 - Leitura unica\n");
            printf("2 - Leitura em serie\n");
            printf("3 - Voltar\n");
            printf("4 - Encerrar conexao\n");
            printf("5 - Sair\n");
            scanf("%d", &escolha);

            switch (escolha)
            {
            case 1:
                //strcat(message, "001");
                break;
            case 2:
                clrscr();
                printf("MENU INICIAL -> MENU PRINCIPAL -> MENU DE ESCOLHA DE LEITURA -> MENU DE LEITURA -> MENU DE LEITURA EM SERIE\n\n");
                printf("Insira \"-1\" para retornar ao menu anterior, \"-2\" para encerrar a conexao ou -3 para finalizar o programa\n\nInsira abaixo a quantidade leituras em serie desejada: (2 a 4)\n");
                scanf("%d", &qtdLeitura);

                if(qtdLeitura == -1){
                    MenuLeitura();
                }else if(qtdLeitura == -2){
                    EncerrarConexao();
                }else if (qtdLeitura == -3){
                    Sair();
                }

                //strcat(message, "00");
                //strcat(message, qtdLeitura);
                
                break;
            case 3:
                MenuEscolhaLeitura();
                break;
            case 4:
                EncerrarConexao();
                break;
            case 5:
                Sair();
                break;
            
            default:
                break;
            }

            //strcat(message, "#");

            //send(s , message , strlen(message) , 0);

            MenuPrincipal();
        }

    void MenuAtuador(){
        clrscr();
        //message = "A0";
        printf("MENU INICIAL -> MENU PRINCIPAL -> MENU ATUADOR\n\n");
        printf("\nInsira \"-1\" para retornar ao menu anterior, \"-2\" para encerrar a conexao ou -3 para finalizar o programa\nInsira abaixo o valor correspondente a porcentagem de atuacao desejada\n");
        scanf("%d", &qtdAtuacao);    

        if(qtdAtuacao == -1){
            MenuLeitura();
        }else if(qtdAtuacao == -2){
            EncerrarConexao();
        }else if (qtdLeitura == -3){
            Sair();
        }

        //printf("%c", qtdAtuacao);

        //strcat(message, qtdAtuacao);

        //strcat(message, "#");

        //send(s , message , strlen(message) , 0);

        MenuPrincipal();
    }

int main(int argc , char *argv[])
{
    /*################################## CONEXaO ##################################
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

    server.sin_addr.s_addr = inet_addr(ip);
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

    // do
    // {
    //     if(message == "EXIT#"){
    //         break;
    //     }else{
    //         MenuPrincipal();
    //     }
        
    // } while (message != "EXIT#");
    
    MenuInicial();

    
    
    return 0;
}
