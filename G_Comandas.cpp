#include <iostream>
#include <string>
#include "Pedido.hpp"
#include "Comanda.hpp"
#include "Cliente.hpp"
#include "Delivery.hpp"

<<<<<<< HEAD
=======
#define MAX_PRATOS 5    //Máximo de pratos no "cardapio".
#define MAX_DESC 25    //Máximo de caracteres de cada prato.
>>>>>>> ae31f81a490403d1d064ebc3a187c9153eaa21a8
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

<<<<<<< HEAD
int fecharComanda(){       // zera comanda
    
=======
int fecharComanda(Cliente *cli, Delivery *del){       // zera comanda
    int i;
    Cliente idClient;

    cout << "Numero/nome da comanda a fechar: " << endl;
    cin >> idClient;
    cout << "Prato a retirar: " << endl;
    cin >> prato;
    if(prato < 0 && prato > 9){
        cout << "Opcao invalida" << endl;
    }
    cout << "Quantidade a retirar: " << endl;
    cin >> quant;
    if(quant < 0){
        cout << "Opcao invalida" << endl;
    }

    if (idClient[0] >= '0' && idClient[0] <= '9')
    {
        int nComanda = std::stoi(idClient);
        if (nComanda >= 1 && nComanda <= MAX_CLIENTE)
        {
            *cli[nComanda].mComanda.setZero();
        }
    }
    else
    {
        for (size_t i = 0; i < MAX_CLIENTE; i++)
        {
            if (*del[i].getIdentidade().find(idClient) != std::string::npos)
            {
                *del[i].mComanda.setZero();
            }
        }
    } else {
        cout << "Opcao invalida para: " << idClient << endl;
    }

>>>>>>> ae31f81a490403d1d064ebc3a187c9153eaa21a8
    return 0;
    }

int EditaComanda(Cliente* client, Delivery* deliv, int operacao)       // adiciona / cria comandas
{
    int prato, quant;
    string idClient;

<<<<<<< HEAD
    std::cout << "Numero/nome da comanda: ";
    cin >> idClient;
    
    while (1)
=======
    cout << "\n         Selecione \"0\" a qualquer momento para encerrar operacao.";
    cout << "\nMesa: ";       // Pergunta para qual mesa a comanda vai ser criada, e qual prato vai ser adicionado, depois verifica se a mesa existe.
    cin >> *mesa;

        if (*mesa < 1 || *mesa > MAX_MESA)      // verificação e retorno de erro
        {
            return *mesa;
        }

    printf("Numero do prato a %s", operacao > 0 ? "adicionar: " : "remover: ");
    //cout << "Numero do prato a adicionar: ";
    cin >> prato;

    while (prato && prato <= MAX_PRATOS)    // verificação e retorno de erro
>>>>>>> ae31f81a490403d1d064ebc3a187c9153eaa21a8
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

void Menu(int opcao, int *tpedidos, int *erro, Cliente *clien, Delivery *deli)     //menu para selecao das opcoes
{
    Comanda cmd;

    switch (opcao)
    {
        /* Na primeira opção, vai ser feita uma nova comanda, atraves da função "EditaComanda".
                Além disso, o número total de pedidos é incrementado*/
    case 1:
        *erro = EditaComanda(1);
        if(*erro == 0){
            *tpedidos += 1;
            cmd.setOrdem(*tpedidos);
        }
        break;

    case 2:     // Usa a mesma função de criação da comanda para adicionar um novo prato.
        *erro = EditaComanda(1);
        break;

    case 3:     // diminui um pedido
        *erro = EditaComanda(-1);
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

    if (*clien[0] >= '0' && *clien[0] <= '9')
    {
        for (size_t i = 0; i < MAX_CLIENTE; i++)     // Define a mesa com menor ordem e maior prioridade
    {
        if (*clien[i].mComanda.getOrdem != 0 && primeiro > *clien[i].mComanda.getOrdem)  // primeira iteração para permitir comparações
        {
            *clien[i].mComanda.setOrdem(primeiro);
        }
    }

    cout << "\n-----------------------------------------------------\n";

    while (imprimiu)    //confere se a impresão de todas as comandas está completa
    {
        imprimiu = 0;
        for (size_t i = 0; i < MAX_CLIENTE ; i++)  //procura as mesas na ordem correta e imprime-as
        {
            if (*clien[i].mComanda.getOrdem == primeiro)
            {
                primeiro++;
                imprimiu = 1;

                cout << "\nPedido N.: " << *clien[i].mComanda.getOrdem << " ----- Mesa: " << *clien[i].getIdentidade() << endl;  // cabeçalho

                for (size_t j = 0; j < MAX_CLIENTE; j++)     //imprime pedidos da mesa
                {
                    if (*clien[i].mComanda.getQuantidade(j) > 0)
                    {
                        cout << "        -> " << *clien[i].mComanda.getQuantidade(j) << " " << *clien[i].mComanda.getStrPrato << endl;
                    }
                }
            }
        }
    }
    cout << "\n-----------------------------------------------------\n";
    }
    else
    {
        for (size_t i = 0; i < MAX_CLIENTE; i++)     // Define a mesa com menor ordem e maior prioridade
    {
        if (*deliv[i].mComanda.getOrdem != 0 && primeiro > *deliv[i].mComanda.getOrdem)  // primeira iteração para permitir comparações
        {
            *deliv[i].mComanda.setOrdem(primeiro);
        }
    }

    cout << "\n-----------------------------------------------------\n";

    while (imprimiu)    //confere se a impresão de todas as comandas está completa
    {
        imprimiu = 0;
        for (size_t i = 0; i < MAX_CLIENTE ; i++)  //procura as mesas na ordem correta e imprime-as
        {
            if (*deliv[i].mComanda.getOrdem == primeiro)
            {
                primeiro++;
                imprimiu = 1;

                cout << "\nPedido N.: " << *deliv[i].mComanda.getOrdem << " ----- Delivery: " << *deliv[i].getIdentidade << endl;  // cabeçalho

                for (size_t j = 0; j < MAX_CLIENTE; j++)     //imprime pedidos da mesa
                {
                    if (*deliv[i].mComanda.getQuantidade(j) > 0)
                    {
                        cout << "        -> " << *deliv[i].mComanda.getQuantidade(j) << " " << *deliv[i].mComanda.getStrPrato << endl;
                    }
                }
            }
        }
    }
    cout << "\n-----------------------------------------------------\n";
    }
}

int main(int argc, char const *argv[])
{
<<<<<<< HEAD
    int opcao = 0, tpedidos = 0, erro = 0;
    client[MAX_CLIENTE];
    deliv[MAX_CLIENTE];
=======
    int opcao = 0, erro = 0, tPedidos = 0;
    Cliente client[MAX_CLIENTE];
    Delivery deli[MAX_CLIENTE];
>>>>>>> ae31f81a490403d1d064ebc3a187c9153eaa21a8


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

        Menu(opcao, &tpedidos, &erro, client, deli);

        Clear();        // mantem limpo o terminal padrão do Windows / Linux / Apple e evita poluição

        ExibePedidos(client, deli);
    }
    return 0;
}
