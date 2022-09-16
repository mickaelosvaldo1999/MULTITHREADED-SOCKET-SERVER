#include "Controller.h"
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <thread>
#include <vector>
#include "PocketSocket.h"

Controller::Controller(int p, int b, std::string mp)
{
    // buffer[mBuffSize];
    mPort = p;
    mBuffSize = b;
    mPath = mp;
}

void Controller::CreateConeection() {
    //Criando o Socket
    this->mSocket = new PocketSocket(mPort,mBuffSize,mPath);
    //Deixando o Socket em modo passivo (leitura)
    if (this->mSocket->mListen()) {
        //loop de conexão
        while (true) {
            //Cria o socket e inicia o listen
            //Aceitando conexão com o thread
            std::thread t1([this] { this->mSocket->mAcceptConnection(); } );
            //pool[0].join();
            t1.join();
        }
    }
}

Controller::~Controller()
{
    //dtor
}
