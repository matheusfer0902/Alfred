#include <iostream>
#include <string.h>
#include "Cliente.hpp"
#include "Delivery.hpp"

#define MAX_CLIENTE 20

using namespace std;
using namespace pkt_comanda;

void Clear()
{
#if defined _WIN32
    system("cls");
    //clrscr(); // conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //ANSI
#elif defined (__APPLE__)
    system("clear");
#endif
}

int fecharComanda(Cliente *cli, Delivery *del){       // zera comanda
    int i, prato, quant;
    string idClient;

    cout << "Numero/nome da comanda a fechar: " << endl;
    cin >> idClient;

    if (idClient[0] >= '0' && idClient[0] <= '9')
    {
        int nComanda = std::stoi(idClient);
        if (nComanda >= 1 && nComanda <= MAX_CLIENTE)
        {
            cli[nComanda].mComanda.setZero();
        }
    }
    else
    {
        for (size_t i = 0; i < MAX_CLIENTE; i++)
        {
            if (del[i].getIdentidade().find(idClient) != std::string::npos)
            {
                del[i].mComanda.setZero();
                break;
            }
        }
    }
    return 0;
}

int EditaComanda(Cliente* client, Delivery* deliv, int operacao, bool* eCliente, int* NumCli)      // adiciona / cria comandas
{
    int prato, quant;
    string idClient;

    std::cout << "\nNumero/nome da comanda: ";
    cin >> idClient;
    
    while (1)
    {
        std::cout << "Quantidade: ";
        cin >> quant;
        
        if (quant <= 0)
        {
            return quant;
        }
        
        std::cout << "Prato: ";
        cin >> prato;

        if (prato >= 0 && prato > MAX_PRATOS)
        {
            return prato;
        }

        if (idClient[0] >= '0' && idClient[0] <= '9')       
        {
            int nComanda = std::stoi(idClient);
            if (nComanda >= 1 && nComanda <= MAX_CLIENTE && (client[nComanda].mComanda.getQuantidade(prato) + quant * operacao) >= 0)
            {
                client[nComanda].mComanda.setQuantidade(client[nComanda].mComanda.getQuantidade(prato) + quant * operacao, prato);
                *eCliente = true;
                *NumCli = nComanda;
            }
            else
            {
                return quant;
            }
        }
        else
        {
            for (size_t i = 0; i < MAX_CLIENTE; i++)
            {
                if (deliv[i].getIdentidade().find(idClient) != std::string::npos && (deliv[i].mComanda.getQuantidade(prato) + quant * operacao) >= 0)
                {
                    deliv[i].mComanda.setQuantidade(deliv[i].mComanda.getQuantidade(prato) + quant * operacao, prato);
                    *eCliente = false;
                    *NumCli = i;
                    break;
                }
                 else
                {
                    return quant;
                }
            }
        }
    }
    return 0;
}

void Menu(int opcao, int *tpedidos, int *erro, Cliente *clien, Delivery *deli)     //menu para selecao das opcoes
{
    bool eCliente;
    int NumCli;

    switch (opcao)
    {
        /* Na primeira opção, vai ser feita uma nova comanda, atraves da função "EditaComanda".
                Além disso, o número total de pedidos é incrementado*/
    case 1:
        *erro = EditaComanda(clien, deli, 1, &eCliente, &NumCli);
        if(*erro == 0){
            *tpedidos += 1;
            if (eCliente)
            {
                clien[NumCli].mComanda.setOrdem(*tpedidos);
            }else{
                deli[NumCli].mComanda.setOrdem(*tpedidos);
            }
        }
        break;

    case 2:     // Usa a mesma função de criação da comanda para adicionar um novo prato.
        *erro = EditaComanda(clien, deli, 1, &eCliente, &NumCli);
        break;

    case 3:     // diminui um pedido
        *erro = EditaComanda(clien, deli, -1, &eCliente, &NumCli);
        break;

    case 4:
        *erro = fecharComanda(clien, deli);
        break;

    default:   // retorno de valores inesperados
        *erro = opcao;
        break;
    }
}

void ExibePedidos(Cliente *clien, Delivery *deliv)        // imprime as comandas em ordem
{
    int primeiro = 10000, imprimiu = 1;

    for (size_t i = 0; i < MAX_CLIENTE; i++)     // Define a mesa com menor ordem e maior prioridade
    {
        if (clien[i].mComanda.getOrdem() != 0 && primeiro > clien[i].mComanda.getOrdem())  // primeira iteração para permitir comparações
        {
            primeiro = clien[i].mComanda.getOrdem();
        }
        if (deliv[i].mComanda.getOrdem() != 0 && primeiro > deliv[i].mComanda.getOrdem())  // primeira iteração para permitir comparações
        {
            primeiro = deliv[i].mComanda.getOrdem();
        }
    }

    cout << "\n-----------------------------------------------------\n";

    while (imprimiu)    //confere se a impresão de todas as comandas está completa
    {
        imprimiu = 0;
        for (size_t i = 0; i < MAX_CLIENTE ; i++)  //procura as mesas na ordem correta e imprime-as
        {
            if (clien[i].mComanda.getOrdem() == primeiro)
            {
                primeiro++;
                imprimiu = 1;

                cout << "\nPedido N.: " << clien[i].mComanda.getOrdem() << " ----- Mesa: " << clien[i].getIdentidade() << endl;  // cabeçalho

                for (size_t j = 0; j < MAX_CLIENTE; j++)     //imprime pedidos da mesa
                {
                    if (clien[i].mComanda.getQuantidade(j) > 0)
                    {
                        cout << "        -> " << clien[i].mComanda.getQuantidade(j) << " " << clien[i].mComanda.getStrPrato(j) << endl;
                    }
                }
            }
            if (deliv[i].mComanda.getOrdem() == primeiro)
            {
                primeiro++;
                imprimiu = 1;

                cout << "\nPedido N.: " << deliv[i].mComanda.getOrdem() << " ----- Delivery: " << deliv[i].getIdentidade() << endl;  // cabeçalho

                for (size_t j = 0; j < MAX_CLIENTE; j++)     //imprime pedidos da mesa
                {
                    if (deliv[i].mComanda.getQuantidade(j) > 0)
                    {
                        cout << "        -> " << deliv[i].mComanda.getQuantidade(j) << " " << deliv[i].mComanda.getStrPrato(j) << endl;
                    }
                }
            }
        }
    }
    cout << "\n-----------------------------------------------------\n";
}

int main(int argc, char const *argv[])
{
    int opcao = 0, erro = 0, tPedidos = 0;
    Cliente client[MAX_CLIENTE];
    Delivery deli[MAX_CLIENTE];


    cout << "           Bem-vindo!\n";

    while (1)
    {
        cout << "\nSelecione uma opcao:\n"
        << "1 - Nova comanda\n"
        << "2 - Adicionar na comanda\n"
        << "3 - Fechar um item da comanda\n"
        << "4 - Fechar toda a comanda\n"
        << "5 - Sair\n";

        if (erro)       // verifica o retorno de erro de todas as funções
        {
            cout << "\n         Valor " << erro << " invalido!\n";
            erro = 0;
        }

        cin >> opcao;

        if(opcao == 5){
            break;
        }

        Menu(opcao, &tPedidos, &erro, client, deli);

        Clear();        // mantem limpo o terminal padrão do Windows / Linux / Apple e evita poluição

        ExibePedidos(client, deli);
    }
    return 0;
}