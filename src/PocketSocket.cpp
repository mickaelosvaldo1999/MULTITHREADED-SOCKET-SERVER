#include "PocketSocket.h"
#include "Controller.h"
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <GetFile.h>

using namespace std;
PocketSocket::PocketSocket(int p, int b, string mp)
{
    //Constroi o objeto com os parâmetros informados
    mPort = p;
    mBuffSize = b;
    mPath = mp;
    //inicia o Socket em formato TCP
    ear = socket(AF_INET, SOCK_STREAM, 0);

    if (ear == -1)
    {
        cout << "Erro ao criar Socket EAR_NOT_DEFINED" << endl;
        exit(1);
    }

    //Verifica se a conexão é KEEP ALIVE
    if(setsockopt(ear,SOL_SOCKET,SO_KEEPALIVE | SO_REUSEADDR,&size,sizeof(size))){
        cout<<"Erro ao estabelecer conexão: KEEPALIVE_FALSE"<<endl;
    }

    //Seta os parâmetros da conexão ao ip/porta
    mServer.sin_family = AF_INET;
    mServer.sin_addr.s_addr = htons(INADDR_ANY);
    mServer.sin_port = htons(mPort);

    //Fixa a conexão a uma determinada porta
    if ((bind(ear, (sockaddr*)&mServer,sizeof(mServer))) == -1)
    {
        cout << "Erro ao escutar ip: BIND_ERROR" << endl;
        //Em caso de erro fecha o socket
        close(ear);
        close(server);
        //exit(1);
    }

    cout << "Servidor iniciado em: INADDR_ANY" << endl;
}

bool PocketSocket::mListen() {

    //VERIFICAR SE O SERVIDOR ESTÁ FUNCIONANDO - Mickael
    if(listen(ear, 1) == -1) {
        cout << "Erro ao executar conexão: LISTEN_FALSE" << endl;
        return false;
    } else {
        return true;
    }
}
void PocketSocket::mAcceptConnection() {
    //aceita a conexão do cliente
    bool aux = false;
    socklen_t size = sizeof(mServer);
    server = accept(ear,(sockaddr *)&mServer, &size);

    // Checar se é válido ou não
    if (server == -1)
        cout << "Erro ao aceitar Cliente" << endl;

    //Loop de leitura
    while (!aux) {
        //Seta o buffer em zero
        bzero(buffer,mBuffSize);
        //Lê o socket - Mickael Osvaldo
        int n = read(server,buffer,mBuffSize);
        if (n < 0) {
            cout << ("Erro ao ler do Socket ERR_SOCK_READ");
            aux = true;
        };
        //Transforma o Buffer em string
        requester = string(buffer);
        //Verifica se a mensagem é do tipo HTTP e identifica se não é uma FalseFLag do navegador/cliente - Mickael
        if (requester.length() <= mBuffSize && requester.length() > 0) {
            if (requester.find("HTTP/1.1")) {
                cout << "cabeçalho encontrado" << endl;
                GetFile mfile;
                //Passa o Buffer para a extração
                string as = mfile.mExtract(requester,mPath);
                    //Envia a resposta HTTP
                    n = send(server, as.c_str(), 1024, 0);
                    //Verifica se foi possível enviar o arquivo
                    if (n < 0) {
                        cout << ("Erro ao enviar para o Socket SOCK_ERR_SEND");
                        aux = true;
                    }
            };
    } else {
        aux = true;
        }
    }
}
PocketSocket::~PocketSocket()
{
    //dtor
}
