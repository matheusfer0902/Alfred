#ifndef CLIENTE_H
#define CLIENTE_H
#pragma once

#include "Comanda.hpp"

namespace pkt_comanda {
	
class Cliente
{
	protected:
		
		std::string identidade;

	public:
		
		Comanda mComanda;
		
		Cliente();

		void setIdentidade(std::string id);
		std::string getIdentidade();

};

};
#endif