#include <iostream>
//parâmetros primcipais
#include "Controller.h"
#define myPort 13130
#define myBuffSize 1024
/*
Participante:
Mickael Osvaldo de Oliveira
*/
int main()
{
    //Obtem o caminho
    std::string mPath;
    std::cout << "Servidor escutando na porta: " << myPort << "\n";
    std::cout << "Digite um caminho: \n";
    std::cin >> mPath;
    //Cria o servidor nesse determinado caminho
    Controller server(myPort, myBuffSize, mPath);
    server.CreateConeection();
    return 0;
}
