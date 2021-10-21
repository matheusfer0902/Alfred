#include <iostream>
#include <string>
#include "Pedido.hpp"
#include "Comanda.hpp"
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

int fecharComanda(){       // zera comanda
    
    return 0;
    }

int EditaComanda(Cliente* client, Delivery* deliv, int operacao)       // adiciona / cria comandas
{
    int prato, quant;
    string idClient;

    std::cout << "Numero/nome da comanda: ";
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

void Menu(int opcao, Comandas *comanda, int *tpedidos, int *erro)     //menu para selecao das opcoes
{
    int mesa;
    switch (opcao)
    {           
        /* Na primeira opção, vai ser feita uma nova comanda, atraves da função "EditaComanda".
                Além disso, o número total de pedidos é incrementado*/
    case 1:
        *erro = EditaComanda(comanda, &mesa, 1);
        if(mesa >= 1 && mesa <= MAX_MESA && (*erro == 0)){
            *tpedidos += 1;
            comanda[mesa-1].ordem = *tpedidos;
        }
        break;

    case 2:     // Usa a mesma função de criação da comanda para adicionar um novo prato.
        *erro = EditaComanda(comanda, &mesa, 1);
        break;

    case 3:     // diminui um pedido
        *erro = EditaComanda(comanda, &mesa, -1);
        break;

    case 4:
        *erro = fecharComanda(comanda);
        break;

    default:   // retorno de valores inesperados
        *erro = opcao;
        break;
    }
}

void ExibePedidos(Comandas *comanda)        // imprime as comandas em ordem
{
    int primeiro = 10000, imprimiu = 1;

    for (size_t i = 0; i < MAX_MESA; i++)     // Define a mesa com menor ordem e maior prioridade
    {
        if (comanda[i].ordem != 0 && primeiro > comanda[i].ordem)  // primeira iteração para permitir comparações
        {
            primeiro = comanda[i].ordem;
        }
    }

    cout << "\n-----------------------------------------------------\n";

    while (imprimiu)    //confere se a impresão de todas as comandas está completa
    {
        imprimiu = 0;
        for (size_t i = 0; i < MAX_MESA ; i++)  //procura as mesas na ordem correta e imprime-as
        {
            if (comanda[i].ordem == primeiro)
            {
                primeiro++;
                imprimiu = 1;                             
                                                
                cout << "\nPedido N.: " << comanda[i].ordem << " ----- Mesa: " << i+1 << endl;  // cabeçalho

                for (size_t j = 0; j < MAX_PRATOS; j++)     //imprime pedidos da mesa
                {
                    if (comanda[i].quantidade[j] > 0)
                    {
                        cout << "        -> " << comanda[i].quantidade[j] << " " << comanda[i].pedido[j] << endl;
                    }
                }
            }
        }
    }
    cout << "\n-----------------------------------------------------\n";
}

int main(int argc, char const *argv[])
{
    int opcao = 0, tpedidos = 0, erro = 0;
    client[MAX_CLIENTE];
    deliv[MAX_CLIENTE];

    // A variável "opcao" guarda o valor inteiro para ser usado no switch case.
    // A variável tpedidos guarda o total de pedidos no dia e orienta a ordem
    // É definido também, o array das comandas

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

        Menu(opcao, comanda, &tpedidos, &erro);

        Clear();        // mantem limpo o terminal padrão do Windows / Linux / Apple e evita poluição

        ExibePedidos(comanda);
    }
    return 0;
}
