#ifndef CONTADORA_H
#define CONTADORA_H
#pragma once
#include <string>
#include <fstream>

#include "Cliente.hpp"
#include "Delivery.hpp"

namespace pkt_comanda {
	
class Contadora  
{
	private:
		int contPedidos;
		int contDelivery;

		std::string cardapio[MAX_PRATOS] {"Executivo", "Churrasco", "Sopa suspeita", "Cafe", "Suco", 
		"Feijoada", "Salada", "Pipoca na manteiga", "Pizza", "Sushi"};
		double preco[MAX_PRATOS] {14.99, 24.99, 99.99, 4.99, 4.99, 21.75, 9.99, 1.99, 31.47, 2.99};
		int contador[MAX_PRATOS] {0};

	public:

		void setContPedidos(int pedidos);
		void setContDelivery(int delivery);

		int getContPedidos();
		int getContDelivery();
		int getContador(int prato);
		double getPreco(int prato);
		std::string getCardapio(int prato);

		void operacaoClien(int operacao, int **NumCli, int nMesa,Cliente* client, int prato, int quant);
		void operacaoDeli(int operacao, int **NumCli, Delivery* deliv, int prato, int quant, int i);
		void adicionaPrato(int prato, int quantidade);
		void retiraPrato(int prato, int quantidade);
		double calculaValor();

		Contadora();
		~Contadora();

};
};
#endif
