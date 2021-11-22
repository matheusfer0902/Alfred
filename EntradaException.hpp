#ifndef ENTRADAEXCEPTION_H
#define ENTRADAEXCEPTION_H
#pragma once

#include <iostream>
#include <string>
#include <exception>

namespace pkt_comanda{
	
class EntradaException : public std::exception
{
	private:
		int codigo;
		std::string erro;

	public:

		std::string msgException();

		EntradaException();
		EntradaException(int codigo, int valor);
		EntradaException(int codigo, std::string nome);
		~EntradaException();

};
};
#endif