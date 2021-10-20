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

        int opcao1(int tPedidos);
        int opcao2();
        int opcao3();
        int opcao4();
        int opcao5(int tPedidos);
        int opcao6();

        void setErro(int e);
        int getErro();

        //void exibePedidos();

    protected:

    private:
        Cliente* client[MAX_CLIENTE];
        int erro = 0;                // A classe recebe uma comanda para realização dos metodos.

};

};

#endif