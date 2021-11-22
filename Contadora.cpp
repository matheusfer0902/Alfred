#include "Contadora.hpp" 
#include <fstream> 
#include <iostream>
#include <string>

using namespace std;
using namespace pkt_comanda;
	
Contadora::Contadora()
{
	int contPedidos = 0;
	int contDelivery = 0;
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
/*
void Contadora::operacaoClien(int operacao, int **NumCli, int nMesa,Cliente* client, int prato, int quant){
    client[nMesa-1].mComanda.setQuantidade(client[nMesa-1].mComanda.getQuantidade(prato-1) + quant * operacao, prato-1);    // com base na quantidade atual, soma ou subtrai a quantidade desejada
    **NumCli = nMesa-1;
    if(operacao == 1){
    }
}

void Contadora::operacaoDeli(int operacao, int **NumCli, Delivery* deliv, int prato, int quant, int i){
    deliv[i].mComanda.setQuantidade(deliv[i].mComanda.getQuantidade(prato-1) + quant * operacao, prato-1);
    **NumCli = i;;    // com base na quantidade atual, soma ou subtrai a quantidade desejada
    if(operacao == 1){
    }
}
*/
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
