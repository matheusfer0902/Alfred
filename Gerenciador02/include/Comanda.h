#ifndef COMANDA_H
#define COMANDA_H
#include "Pedido.h"
#define MAX_PDD 20


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

#endif // COMANDA_H
