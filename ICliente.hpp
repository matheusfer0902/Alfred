#ifndef ICLIENTE_H
#define ICLIENTE_H
#pragma once

#include "Comanda.hpp"

namespace pkt_comanda {
	
class ICliente
{
	protected:
		
		std::string identidade;

	public:
		
		Comanda mComanda;
		
		ICliente();
		~ICliente();

		virtual void setIdentidade(std::string id) = 0;
		virtual std::string getIdentidade() = 0;

};
};
#endif