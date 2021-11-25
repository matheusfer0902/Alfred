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
    id = identidade;
}

std::string Mesa::getIdentidade()
{
    return identidade;
}

void Mesa::setPessoas(int numeroP)
{
    pessoas = numeroP;
}

int Mesa::getPessoas()
{
    return pessoas;
}