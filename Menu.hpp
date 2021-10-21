#ifndef MENU_H
#define MENU_H
#include <iostream>
#include "Comanda.hpp"
#include "Cliente.hpp"
#include "Delivery.hpp"
#include "Pedido.hpp"
#define MAX_CLIENTE 20

namespace pkt_comanda {

class Menu
{
    public:
        Menu();
        ~Menu();

        void novaCMD(int tPedidos);
        void adicionaCMD();
        void fechaItem();
        void fechaCMD();
        void delivery(int tPedidos);
        void exibePedidos();
        void zeraClientes();

        void setErro(int e);
        int getErro();

    protected:

    private:
        Cliente* client[MAX_CLIENTE];
        Delivery* delivG[MAX_CLIENTE];
        int erro = 0;                // A classe recebe uma comanda para realização dos metodos.

};

};

#endif