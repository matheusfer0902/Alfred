#include "Comanda.hpp"

using namespace pkt_comanda;
	
Comanda::Comanda(){

}

Comanda::Comanda(Pedido* pedid)
{
    this->pedidos[0] = pedid;         // É criado o primeiro pedido da comanda
    for(int i = 1; i < MAX_PRATOS; i++){
        this->pedidos[i] = nullptr;   // E todos os outros pedidos recebem null
    }
}

Comanda::~Comanda()
{
    for(int i = 0; i < MAX_PRATOS; i++){
        this->pedidos[i] = nullptr;
    }
}

void Comanda::addPedido(Pedido* pedid){
    int i;
    for(i = 0; i < MAX_PRATOS; i++){
        if(pedidos[i] == nullptr)
            break;
    }
    this->pedidos[i] = pedid;    // Para adicionar um pedido, é verificado qual endereço dentro do array está vazio
                                 // Depois de achar o espaço, é criado o novo pedido
}

Pedido* Comanda::getPedidos(int i){
    return this->pedidos[i];
}

void Comanda::fecharUmItem(int prato, int quant){
    for(int i = 0; i < MAX_PRATOS; i++){
        if(pedidos[i]->getPrato() == prato){
            pedidos[i]->setQuantidade(pedidos[i]->getQuantidade() - quant);

            if (pedidos[i]->getQuantidade() == 0)
            {
                pedidos[i] = nullptr;
            }
        }
    }
}

void Comanda::setOrdem(int o){
    ordem = o;
}
int Comanda::getOrdem(){
    return ordem;
}


