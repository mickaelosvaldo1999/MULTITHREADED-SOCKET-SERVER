#include "GetFile.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
GetFile::GetFile()
{
    //ctor
}

std::string GetFile::mExtract(std::string buff, std::string mp) {

    //Separa (explode) o buffer para obter o caminho
    std::vector<std::string> words{};
    size_t pos;
    while ((pos = buff.find(delimiter)) != std::string::npos) {
        words.push_back(buff.substr(0, pos));
        buff.erase(0, pos + delimiter.length());
    }
    const auto &str = words[1];

    mp = mp + str;
    std::ifstream myfile;
    myfile.open (mp);
    //Verifica se o arquivo é valido ou não.
    if (myfile.is_open() && str.size() > 1)
    {
        std::cout << "   -   Arquivo encontrado \n";
        //Lê tooc o arquivo encontrado
        while ( getline (myfile,aux) )
        {
           line += aux;
        }
        //Fecha o arquivo para evitar dump de memória
        myfile.close();
        //Preparando HTTP com tamanho dinâmico
        mp = std::string("HTTP/1.1 200 OK")
        +"\nConnection: close"
        +"\nServer: CapivaraOs 0.1.1"
        /*+"\nLast-Modified: " */
        +"\nContent-Length:"+ std::to_string(line.size())
        +"\nContent-Type: text/html"
        +"\n\n" + line;
        return mp;
;    } else {
        std::cout << "   -   404 - NOT FOUND \n";
        //prepara o HTTP padrão para 404
        mp = std::string("HTTP/1.1 404 Not Found")
        +"\nConnection: close"
        +"\nServer: CapivaraOs 0.1.1"
        +"\nContent-Length: 236"
        +"\nContent-Type: text/html"
        +"\n\n<!DOCTYPE html><html><head><title>404 Error Page</title><meta charset='UTF-8'/></head><body><div><h1>ERRO - 404</h1><h2>Documento inexistente ou corrompido.</h2> <p>Nossas capivaras ja estão trabalhando nisso!!!</p></div></body></html>";

        //Fecha o arquivo para evitar dump de memória
        myfile.close();
        return mp;
    }
    ;
}
GetFile::~GetFile()
{
    //dtor
}
