#include "Delivery.hpp"

using namespace pkt_comanda;
	
Delivery::Delivery()
{
	identidade = "vazio";
}

void Delivery::setContato(std::string tell){
    contato = tell;
}
void Delivery::setEndereco(std::string end){
    endereco = end;
}

std::string Delivery::getContato(){
    return contato;
}
std::string Delivery::getEndereco(){
    return endereco;
}