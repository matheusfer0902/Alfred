#include "Pedido.h"
#include <string>
#define MAX_PRATOS 11

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

void Pedido::setPrato(int p){
    prato = p;
}
void Pedido::setQuantidade(int q){
    quantidade = q;
}

std::string Pedido::getStrPrato(){

    std::string sPrato = cardapio[prato];

    return sPrato;
}
