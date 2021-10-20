#include "Delivery.h"
#include "Comanda.h"
#include "Cliente.h"
#include <string>

Delivery::Delivery(std::string endereco, std::string contato) // Um pedido vai ser realizado, por isso a chamada do construtor de pedidos
{
     endereco = nullptr;
     contato = nullptr;
}

Delivery::~Delivery()
{
    //dtor
}

std::string Delivery::getEndereco(){
    return endereco;
}
std::string Delivery::getContato(){
    return contato;
}
void Delivery::setEndereco(std::string e){
    endereco = e;
}
void Delivery::setContato(std::string c){
    contato = c;
}
