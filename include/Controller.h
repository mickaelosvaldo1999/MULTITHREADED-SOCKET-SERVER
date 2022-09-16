#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "PocketSocket.h"

class Controller
{
    public:
        Controller(int p, int b, std::string mp);
        void CreateConeection();
        virtual ~Controller();

    protected:

    private:
    int connector, mBuffSize,mPort;
    std::string mPath;
    bool aux = false;
    char buffer[1024];
    PocketSocket *mSocket;
};

#endif // CONTROLLER_H
