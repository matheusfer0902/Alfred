#include "Pedido.hpp" 

using namespace pkt_comanda;
	
Pedido::Pedido(){
    
}

Pedido::Pedido(int prato, int quantidade)
{
    this->prato = prato;
    this->quantidade = quantidade;
}

Pedido::~Pedido()
{
    //dtor
}

int Pedido::getPrato(){
    return prato;
}

int Pedido::getQuantidade(){
    return quantidade;
}

std::string Pedido::getStrPrato(){

    std::string sPrato = cardapio[prato];

    return sPrato;
}

void Pedido::setPrato(int p){
    prato = p;
}

void Pedido::setQuantidade(int q){
    quantidade = q;
}