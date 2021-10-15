#ifndef Comanda_H
#define Comanda_H
#pragma once

#include "Pedido.hpp"

namespace pkt_comanda {

class Comanda
{
	private:

		Pedido cmda[MAX_PRATOS];
		int ordem;

	public:

		Comanda();

		void setOrdem(int o);
		void setQuantidade(int quant, int prato);
		int setQuantidade(int quant,std::string strPrato);
		void setZero();

		int getOrdem();
		int getQuantidade(int prato);
		std::string getStrPrato(int prato);

};

};
#endif