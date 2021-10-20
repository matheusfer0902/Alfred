#include "Cliente.h"
#include <string>

Cliente::Cliente(std::string identidade)
{
    this->identidade = identidade;
}

Cliente::Cliente()
{
    identidade = nullptr;
}

Cliente::~Cliente()
{
    //dtor
}

void Cliente::setIdentidade(std::string id){
    identidade = id;
}
std::string Cliente::getIdentidade(std::string id){
    return identidade;
}