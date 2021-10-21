#ifndef CLIENTE_H
#define CLIENTE_H
#pragma once

#include "Comanda.hpp"

namespace pkt_comanda {
	
class Cliente // Os dados dos clientes são necessarios para o delivery, já que no restaurante o controle vai ser feito pela comanda.
{
	protected:
		
		std::string identidade;

	public:
		
		Comanda cmd;
		
		Cliente(std::string identidade);
        Cliente();
        ~Cliente();

		void setIdentidade(std::string id);
		std::string getIdentidade();
};

};
#endif