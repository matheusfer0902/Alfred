#include <iostream>
#include <string>
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

int cDelivery(Delivery *del, int *tpedidos)
{
    string ende, cont, id;
    size_t vaz;
    int quant, prato;
    
    getchar();
    cout << "\nNome: ";
    getline(cin, id);
    cout << "Endereco: ";
    getline(cin, ende);
    cout << "Contato: ";
    getline(cin, cont);
    
    cout << "Quantidade: ";
    cin >> quant;

    if (quant <= 0)
        {
            return quant;
        }
    
    cout << "Prato: ";
    cin >> prato;

    if (prato >= 0 && prato > MAX_PRATOS)
        {
            return prato;
        }

    for (size_t i = 0; i < MAX_CLIENTE; i++)
    {
        if (del[i].getIdentidade().find("vazio") != string::npos)
        {
            vaz = i;
            break;
        }   
    }
    del[vaz].setContato(cont);
    del[vaz].setEndereco(ende);
    del[vaz].setIdentidade(id);
    del[vaz].mComanda.setQuantidade(quant, prato);

    *tpedidos += 1;
    del[vaz].mComanda.setOrdem(*tpedidos);
    return 0;
}

int fecharComanda(Cliente *cli, Delivery *del){
    string idClient;

    cout << "           \nDigite 0 para encerrar\n";
    cout << "Mesa/nome do Cliente: " << endl;
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

int EditaComanda(Cliente* client, Delivery* deliv, int operacao, int* NumCli) 
{
    int prato, quant;
    string idClient;

    cout << "           \nDigite 0 para encerrar\n";
    std::cout << "\nMesa/nome do Cliente: ";
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
            if (nComanda >= 1 && nComanda <= MAX_CLIENTE && (client[nComanda].mComanda.getQuantidade(prato-1) + quant * operacao) >= 0)
            {
                client[nComanda].mComanda.setQuantidade(client[nComanda].mComanda.getQuantidade(prato-1) + quant * operacao, prato-1);
                client[nComanda].setIdentidade(idClient);
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
                if (deliv[i].getIdentidade().find(idClient) != std::string::npos && (deliv[i].mComanda.getQuantidade(prato-1) + quant * operacao) >= 0)
                {
                    deliv[i].mComanda.setQuantidade(deliv[i].mComanda.getQuantidade(prato-1) + quant * operacao, prato-1);
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

void Menu(int opcao, int *tpedidos, int *erro, Cliente *clien, Delivery *deli)     
{
    int NumCli;

    switch (opcao)
    {
    case 1:
        *erro = EditaComanda(clien, deli, 1, &NumCli);
        if(*erro == 0){
            *tpedidos += 1;
            clien[NumCli].mComanda.setOrdem(*tpedidos);
        }
        break;

    case 2:    
        *erro = EditaComanda(clien, deli, 1, &NumCli);
        break;

    case 3:     
        *erro = EditaComanda(clien, deli, -1, &NumCli);
        break;

    case 4:
        *erro = fecharComanda(clien, deli);
        break;

    case 5:
        *erro = cDelivery(deli, tpedidos);
        if(*erro == 0){
            *tpedidos += 1;
        }
        break;

    default:  
        *erro = opcao;
        break;
    }
}

void ExibePedidos(Cliente *clien, Delivery *deliv)     
{
    int primeiro = 10000, imprimiu = 1;

    for (size_t i = 0; i < MAX_CLIENTE; i++)     
    {
        if (clien[i].mComanda.getOrdem() != 0 && primeiro > clien[i].mComanda.getOrdem())  
        {
            primeiro = clien[i].mComanda.getOrdem();
        }
        if (deliv[i].mComanda.getOrdem() != 0 && primeiro > deliv[i].mComanda.getOrdem())  
        {
            primeiro = deliv[i].mComanda.getOrdem();
        }
    }

    cout << "\n-----------------------------------------------------\n";

    while (imprimiu)   
    {
        imprimiu = 0;
        for (size_t i = 0; i < MAX_CLIENTE ; i++)  
        {
            if (clien[i].mComanda.getOrdem() == primeiro)
            {
                primeiro++;
                imprimiu = 1;

                cout << "\nPedido N.: " << clien[i].mComanda.getOrdem() << " ----- Mesa: " << clien[i].getIdentidade() << endl; 

                for (size_t j = 0; j < MAX_PRATOS; j++)     
                {
                    if (clien[i].mComanda.getQuantidade(j) > 0)
                    {
                        cout << "        -> " << clien[i].mComanda.getQuantidade(j) << " " << clien[i].mComanda.getStrPrato(j) << endl;
                    }
                }
            }
            else if (deliv[i].mComanda.getOrdem() == primeiro)
            {
                primeiro++;
                imprimiu = 1;

                cout << "\nPedido N.: " << deliv[i].mComanda.getOrdem() << " ----- Delivery: " << deliv[i].getIdentidade() << endl; 

                for (size_t j = 0; j < MAX_PRATOS; j++)    
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
        << "1 - Nova mesa\n"
        << "2 - Adicionar na comanda\n"
        << "3 - Fechar um item da comanda\n"
        << "4 - Fechar toda a comanda\n"
        << "5 - Novo delivery\n"
        << "6 - Sair\n";

        if (erro) 
        {
            cout << "\n         Valor " << erro << " invalido!\n";
            erro = 0;
        }

        cin >> opcao;

        if(opcao == 6){
            break;
        }

        Menu(opcao, &tPedidos, &erro, client, deli);

        Clear(); 

        ExibePedidos(client, deli);
    }
    return 0;
}