#include "Delivery.hpp"

using namespace pkt_comanda;
	
Delivery::Delivery(std::string endereco, std::string contato) // Um pedido vai ser realizado, por isso a chamada do construtor de pedidos
{
    this-> endereco = endereco;
    this-> contato = contato;
}

Delivery::Delivery()
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