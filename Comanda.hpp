#ifndef Comanda_H
#define Comanda_H
#pragma once

#include "Pedido.hpp"
#define MAX_PDD 20

namespace pkt_comanda {

class Comanda
{
    public:
        Comanda(Pedido* pedid); // O construtor de comanda recebe um pedido, pois toda vez que um obejto comanda for criado
        Comanda();                        //   ele vai ser criado com um pedido.
        ~Comanda();

        void addPedido(Pedido* pedid);
        void setOrdem(int o);
        int getOrdem();

        Pedido* getPedidos(int i);
        void fecharUmItem(Pedido* pedid);
        int setQuantidade(int quantidade, std::string prato);

    protected:

    private:
        Pedido* pedidos[MAX_PDD]; // A comanda é composta por pedidos
        int ordem = 0;

};

};
#endif