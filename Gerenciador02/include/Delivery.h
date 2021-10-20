#ifndef DELIVERY_H
#define DELIVERY_H
#include "Comanda.h"
#include <string>
#include "Cliente.h"


class Delivery : public Cliente // Delivery herda de pedido porque o delivery tambem vai realizar um pedido
{
    public:
        Delivery(std::string endereco, std::string contato); // o delivery precisa do pedido
                                                                                        // e também das informações do cliente
        ~Delivery();

        std::string getEndereco();
        std::string getContato();
        void setEndereco(std::string e);
        void setContato(std::string c);

    private:
        std::string endereco, contato;
};

#endif // DELIVERY_H
