#include "Cliente.hpp"  

using namespace pkt_comanda;
	
Cliente::Cliente()
{
    identidade = "vazio";
}
	
void Cliente::setIdentidade(std::string id){
    identidade = id;
}

std::string Cliente::getIdentidade(){
    return identidade;
}