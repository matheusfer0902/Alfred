#ifndef PEDIDO_H
#define PEDIDO_H
#include <string>


class Pedido
{
    public:
        Pedido(int prato, int quantidade);
        Pedido(); // Toda vez que o pedido for feito, vai precisar do prato e da quantidade
        ~Pedido();

        std::string cardapio[11] {"Hamburguer", "Executivo", "Churrasco", "Sopa suspeita", "Cafe", "Suco",
		"Feijoada", "Salada", "Pipoca na manteiga", "Pizza", "Sushi"};


        int getPrato();
        int getQuantidade();

        void setPrato(int p);
        void setQuantidade(int q);
        std::string getStrPrato();

    protected:
        int prato, quantidade;

    private:
};

#endif // PEDIDO_H
