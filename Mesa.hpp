#ifndef MESA_H
#define MESA_H
#pragma once

#include "ICliente.hpp"

namespace pkt_comanda{

class Mesa : public ICliente
{
	private:
		int pessoas;

	public:

		Mesa();
		~Mesa();

		void setIdentidade(std::string id);
		std::string getIdentidade();

};
};
#endif