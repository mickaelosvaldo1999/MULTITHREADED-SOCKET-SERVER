#ifndef GETFILE_H
#define GETFILE_H
#include <string>

class GetFile
{
    public:
        GetFile();
        //Mickael Osvaldo
        std::string mExtract(std::string buff, std::string mp);
        virtual ~GetFile();

    protected:

    private:
    std::string delimiter = " ", line,aux;
};

#endif // GETFILE_H
