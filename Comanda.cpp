#include "Comanda.hpp"

using namespace pkt_comanda;
	
Comanda::Comanda()
{
	ordem = 0;

    for (size_t i = 0; i < MAX_PRATOS ; i++)
    {
        cmda[i].setPrato(i);
    }
}

void Comanda::setOrdem(int o){
    ordem = o;
}
void Comanda::setQuantidade(int quant, int prato){
    cmda[prato].setQuantidade(quant);
}
void Comanda::setZero(){
    for (size_t i = 0; i < MAX_PRATOS ; i++)
    {
        cmda[i].setQuantidade(0);
        ordem = 0;
    }
}
int Comanda::setQuantidade(int quant, std::string strPrato){
    
    for (size_t i = 0; i < MAX_PRATOS ; i++)
    {
        if (cmda[i].getStrPrato().find(strPrato) != std::string::npos)
        {
            cmda[i].setQuantidade(quant);
            return 0;
        }
    }
    return 1;
}

int Comanda::getOrdem(){
    return ordem;
}
int Comanda::getQuantidade(int prato){
    return cmda[prato].getQuantidade();
}
std::string Comanda::getStrPrato(int prato){
    return cmda[prato].getStrPrato();
}