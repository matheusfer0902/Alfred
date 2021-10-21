#include "Pedido.hpp" 

using namespace pkt_comanda;
	
Pedido::Pedido()
{
    quantidade = 0;
    prato = 0;
}
	
Pedido::~Pedido()
{
	
}

void Pedido::setQuantidade(int q){
    quantidade = q;
}
void Pedido::setPrato(int p){
    prato = p;
}  

int Pedido::getQuantidade(){
    return quantidade;
}
int Pedido::getPrato(){
    return prato;
}
std::string Pedido::getStrPrato(){
    
    std::string sPrato(cardapio[prato]);
    
    return sPrato;
}