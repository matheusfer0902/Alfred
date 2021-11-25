#include "Contadora.hpp" 
#include <fstream> 
#include <iostream>
#include <string>

using namespace std;
using namespace pkt_comanda;
	
Contadora::Contadora()
{
	
}
	
Contadora::~Contadora()
{
	
}

double Contadora::calculaValor(){
    double total = 0.0;

    for(int i = 0; i < MAX_PRATOS; i++){
        total += preco[i] * contador[i];
    }

    return total;
}

void Contadora::adicionaPrato(int prato, int quantidade){
    contador[prato] += quantidade; 
}

void Contadora::retiraPrato(int prato, int quantidade){
    contador[prato] -= quantidade;
}

void Contadora::setContPedidos(int pedidos){
    contPedidos += pedidos;
}
void Contadora::setContDelivery(int delivery){
    contDelivery += delivery;
}

int Contadora::getContPedidos(){
    return contPedidos;
}
int Contadora::getContDelivery(){
    return contDelivery;
}
int Contadora::getContador(int prato){
    return contador[prato];
}
double Contadora::getPreco(int prato){
    return preco[prato];
}
std::string Contadora::getCardapio(int prato){
    return cardapio[prato];
}
