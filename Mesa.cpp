#include "Mesa.hpp"  

using namespace pkt_comanda;

Mesa::Mesa()
{
	identidade = "vazio";
}
	
Mesa::~Mesa()
{
	
}

void Mesa::setIdentidade(std::string id)
{
    identidade = id;
}

std::string Mesa::getIdentidade()
{
    return identidade;
}