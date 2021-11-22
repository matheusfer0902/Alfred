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
		double preco[MAX_PRATOS] {14.99, 24.99, 99.99, 4.99, 4.99, 21.75, 9.99, 1.99, 31.47, 2.99};

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
