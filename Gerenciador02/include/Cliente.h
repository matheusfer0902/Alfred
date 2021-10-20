#ifndef CLIENTE_H
#define CLIENTE_H
#include <string>
#include "Comanda.h"

class Cliente // Os dados dos clientes são necessarios para o delivery, já que no restaurante o controle vai ser feito pela comanda.
{
    public:
        Cliente(std::string identidade);
        Cliente();
        ~Cliente();
        Comanda cmd;

        void setIdentidade(std::string id);
        std::string getIdentidade(std::string id);


    protected:
        std::string identidade;
    private:
};

#endif // CLIENTE_H
