#ifndef POCKETSOCKET_H
#define POCKETSOCKET_H

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

class PocketSocket
{
    public:
        PocketSocket(int p, int b, std::string mp);
        bool mListen();
        void mAcceptConnection();
        virtual ~PocketSocket();

    protected:

    private:
        int mBuffSize,mPort,ear,server;
        std::string requester, mPath,env,evaux;
        char buffer[1024];
        sockaddr_in mServer;
        socklen_t size;
};

#endif // POCKETSOCKET_H
