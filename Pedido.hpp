#ifndef PEDIDO_H
#define PEDIDO_H
#pragma once

#define MAX_PRATOS 10

#include <string>

namespace pkt_comanda {

class Pedido  
{
	private:
	
		int quantidade, prato;
		std::string cardapio[MAX_PRATOS] {"Executivo", "Churrasco", "Sopa suspeita", "Cafe", "Suco", 
		"Feijoada", "Salada", "Pipoca na manteiga", "Pizza", "Sushi"};
		double preco[MAX_PRATOS] {12.50, 24.99, 99.99, 5.0, 4.0, 21.75, 8.50, 2.0, 31.47, 2.50};

	public:

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