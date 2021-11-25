#ifndef DELIVERY_H
#define DELIVERY_H
#pragma once
	
#include "ICliente.hpp"

namespace pkt_comanda {

class Delivery: public ICliente
{
	private:

		std::string contato, endereco;

	public:

		Delivery();

		void setIdentidade(std::string id);
		std::string getIdentidade();

		void setContato(std::string tell);
		void setEndereco(std::string end);

		std::string getContato();
		std::string getEndereco();

};
};
#endif