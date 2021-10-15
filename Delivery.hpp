#ifndef DELIVERY_H
#define DELIVERY_H
#pragma once
	
#include "Cliente.hpp"

namespace pkt_comanda {

class Delivery: public Cliente
{
	private:

		std::string contato, endereco;

	public:

		Delivery();

		void setContato(std::string tell);
		void setEndereco(std::string end);

		std::string getContato();
		std::string getEndereco();

};
};
#endif