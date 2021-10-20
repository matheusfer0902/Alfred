#include <iostream>
#include <string>
#include "Comanda.hpp"
#include "Pedido.hpp"
#include "Delivery.hpp"
#include "Cliente.hpp"
#include "Menu.hpp"

using namespace std;
using namespace pkt_comanda;

void Clear()
{
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined (__APPLE__)
    system("clear");
#endif
}

int main(){
    int opcao = 0, tPedidos = 0; // Variavel responsavel para opções no menu.
    Menu* mn = new Menu(); // Objeto da classe "Menu", alocado de forma dinamica, responsavel por chamar os metodos da classe.

    cout << "           Bem-vindo!\n";

    while (1)
    {
        cout << "\nSelecione uma opcao:\n"
        << "1 - Nova comanda\n"
        << "2 - Adicionar na comanda\n"
        << "3 - Fechar um item da comanda\n"
        << "4 - Fechar toda a comanda\n"
        << "5 - Delivery\n"
        << "6 - Sair\n";
    
        if(mn->getErro()){
            cout << "\nValor " << mn->getErro() << " incorreto\n" << endl;
        }
    
        cin >> opcao;

        getchar();

        if(opcao == 6){
            break;
        }

        switch(opcao){ // Switch responsavel por direcionar o programa para os metodos do menu.
            case 1:
                tPedidos++;
                mn->opcao1(tPedidos);
                break;
            case 2:
                mn->opcao2();
                break;
            case 3:
                mn->opcao3();
                break;
            case 4:
                mn->opcao4();
                break;
            case 5:
                mn->opcao5(tPedidos);
                break;
        }
         Clear();

    }
    return 0;
}