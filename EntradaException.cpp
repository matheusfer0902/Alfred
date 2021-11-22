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
        return "Quantidade (" + erro + ") nao pode ser negativa!\n";

    case 2:
        return "Prato " + erro + " inexistente!\n";

    case 3:
        return "Mesa " + erro + " inexistente!\n";

    case 4:
        return "Quantidade (" + erro + ") a retirar nao pode ser maior que a atual!";

    case 5:
        return "Cliente \"" + erro + "\" nao encontrado!";

    case 6:
        return "Opcao " + erro + " invalida!";

    case 7:
        return "Nao foi possivel abrir o arquivo \"" + erro + "\"!\n";
    
    default:
        return "Erro inesperado";
    }
}