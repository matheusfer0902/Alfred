#ifndef PEDIDO_H
#define PEDIDO_H
#pragma once

#define MAX_PRATOS 10
#define MAX_DESC 30

#include <string>

namespace pkt_comanda {

class Pedido  
{
	private:
	
		int quantidade, prato;
		char cardapio[MAX_PRATOS][MAX_DESC] {"Executivo", "Churrasco", "Sopa suspeita", "Cafe", "Suco", 
		"Feijoada", "Salada", "Pipoca na manteiga", "Pizza", "Sushi"};

	public:

		Pedido(int prato, int quantidade);
		Pedido();
		~Pedido();

		void setQuantidade(int q);
		void setPrato(int p);

		int getQuantidade();
		int getPrato();
		std::string getStrPrato();

};

};
#endif