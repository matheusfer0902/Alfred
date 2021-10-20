#ifndef Comanda_H
#define Comanda_H
#pragma once

#include "Pedido.hpp"

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
        void fecharUmItem(int prato, int quant);

    protected:

    private:
        Pedido* pedidos[MAX_PRATOS]; // A comanda é composta por pedidos
        int ordem = 0;

};

};
#endif