#ifndef DELIVERY_H
#define DELIVERY_H
#pragma once
	
#include "Cliente.hpp"

namespace pkt_comanda {

class Delivery: public Cliente // Delivery herda de pedido porque o delivery tambem vai realizar um pedido
{
	private:

		std::string contato, endereco;

	public:

		Delivery(std::string endereco, std::string contato); // o delivery precisa do pedido e também das informações do cliente
		Delivery();
		~Delivery();

		void setContato(std::string c);
		void setEndereco(std::string e);

		std::string getContato();
		std::string getEndereco();

};
};
#endif