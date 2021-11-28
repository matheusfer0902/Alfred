#include "EntradaException.hpp"  

using namespace pkt_comanda;
	
EntradaException::EntradaException()
{
    codigo = 0;
}
	
EntradaException::~EntradaException()
{
	
}

EntradaException::EntradaException(int codigo, int valor)
{
    this->codigo = codigo;
    erro = std::to_string(valor);
}

EntradaException::EntradaException(int codigo, std::string nome)
{
    this->codigo = codigo;
    erro = nome;
}

std::string EntradaException::msgException()
{
    switch (codigo)
    {
    case 1:
        return "\n          Quantidade (" + erro + ") nao pode ser negativa!\n";

    case 2:
        return "\n          Prato " + erro + " inexistente!\n";

    case 3:
        return "\n          Mesa " + erro + " inexistente!\n";

    case 4:
        return "\n          Quantidade (" + erro + ") a retirar nao pode ser maior que a atual!\n";

    case 5:
        return "\n          Cliente \"" + erro + "\" nao encontrado!\n";

    case 6:
        return "\n          Opcao " + erro + " invalida!\n";

    case 7:
        return "\n          Nao foi possivel abrir o arquivo \"" + erro + "\"!\n";

    case 8:
        return "\n          Memoria lotada! Por favor, exclua um " + erro + ".\n";
    
    default:
        return "\n          Erro inesperado\n";
    }
}