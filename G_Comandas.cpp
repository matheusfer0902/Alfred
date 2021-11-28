#include <iostream>
#include <string>
#include "Pedido.hpp"
#include "Comanda.hpp"
#include "ICliente.hpp"
#include "Delivery.hpp"
#include "Mesa.hpp"
#include "EntradaException.hpp"
#include <sstream>
#include <fstream>
#include "Contadora.hpp"
#include <string.h>
#include <ctime>

#include "Pedido.cpp"
#include "Comanda.cpp"
#include "ICliente.cpp"
#include "Delivery.cpp"
#include "Mesa.cpp"
#include "EntradaException.cpp"
#include "Contadora.cpp"

#define MAX_CLIENTE 20
#define MAX_PRATOS 10

using namespace std;
using namespace pkt_comanda;

void Clear()    // limpa a tela do prompt de comando de acordo com o sistema operacional
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

int cDelivery(Delivery *clie)     // inicia um objeto Delivery, bem como seus atributos
{
    string ende, conta, id;
    size_t vaz;
    EntradaException ex;
    bool cheio = true;

    getchar();
    cout << "Nome: ";
    getline(cin, id);
    cout << "Endereco: ";
    getline(cin, ende);
    cout << "Contato: ";
    getline(cin, conta);

    for (size_t i = 0; i < MAX_CLIENTE; i++)    // procura um objeto "vazio" para iniciar o novo Delivery
    {
        if (clie[i].getIdentidade().find("vazio") != string::npos)
        {
            cheio = false;
            vaz = i;
            break;
        }   
    }
    if (cheio)
    {
        ex = EntradaException(8, "delivery");
    }
    
    clie[vaz].setContato(conta);
    clie[vaz].setEndereco(ende);
    clie[vaz].setIdentidade(id);

    return vaz;
}

void fecharComanda(ICliente &clie){     // zera um Cliente/Delivery, junto de seus atributos

    clie.setIdentidade("vazio");
    clie.mComanda.setZero();
}

void EditaComanda(Contadora *cont, ICliente &clie, int operacao)   //adiciona ou remove pedidos das comandas de acordo com a operação
{
    int prato, quant;
    EntradaException ex;
    
    while (1)
    {
        std::cout << "Quantidade: ";
        cin >> quant;
        
        if (quant == 0)
            return;
        
        if (quant < 0)
        {
            ex = EntradaException(1, quant);
            throw ex;
        }
        
        std::cout << "Prato: ";
        cin >> prato;

        if (prato == 0)
            return;

        if (prato < 1 || prato > MAX_PRATOS)
        {
            ex = EntradaException(2, prato);
            throw ex;
        }   
            
        if (clie.mComanda.getQuantidade(prato-1) + quant * operacao >= 0) {   // avalia se a quantidade a retirar é maior que a atual
            clie.mComanda.setQuantidade(clie.mComanda.getQuantidade(prato-1) + quant * operacao, prato-1);    // com base na quantidade atual, soma ou subtrai a quantidade desejada
        }
        else{
            ex = EntradaException(4, quant);
            throw ex;
        }
        
        if(operacao == 1) {
            cont->adicionaPrato(prato - 1, quant);
        } else {
            cont->retiraPrato(prato - 1, quant);
        }
    }
}

void buscaDelivery(ICliente &clie)
{
    EntradaException ex;
    ICliente *Iaux = &clie;
    Delivery *Daux = dynamic_cast <Delivery*> (Iaux);

    cout << "\n-----------------------------------------------------\n";
    cout << "\nNome: " + Daux->getIdentidade() + "\nContato: " + Daux->getContato() + "\nEndereco: " + Daux->getEndereco() << endl;
}

void Salvar(Contadora *cont){
    ofstream arq;
    string tamanho, data;
    EntradaException ex;
    time_t agora = time(0);
    tm *calendario = localtime(&agora);

    arq.open("Relatorio.txt", ios::app);
    if(!arq.is_open()) {
        ex = EntradaException(7, "Relatorio.txt");
        throw ex;
    }

    data = to_string(calendario->tm_mday) + "/" + to_string(calendario->tm_mon + 1) + "/" + to_string(calendario->tm_year + 1900);

    arq << "--------------------------------" + data + "--------------------------------\n\n";

    arq << "Valor total --- " <<  "--- Quantidade --- " <<  "--- preco unitario --- " << "--- Prato --- " << endl;

    for(int i = 0; i < MAX_PRATOS; i++){
        if(cont->getContador(i) > 0){

            ostringstream s;
            s << cont->getContador(i) * cont->getPreco(i);
            tamanho = (s.str());

            if(tamanho.length() <= 4){
                arq << "   " << cont->getContador(i) * cont->getPreco(i) << "              " <<  "   " << cont->getContador(i) << "               " << "    " << cont->getPreco(i) << "        " << "    " << cont->getCardapio(i) << endl;
            } else if (tamanho.length() == 5){
                arq << "   " << cont->getContador(i) * cont->getPreco(i) << "             " <<  "   " << cont->getContador(i) << "               " << "    " << cont->getPreco(i) << "        " << "    " << cont->getCardapio(i) << endl;
            } else if (tamanho.length() == 6){
                arq << "   " << cont->getContador(i) * cont->getPreco(i) << "            " <<  "   " << cont->getContador(i) << "               " << "    " << cont->getPreco(i) << "        " << "    " << cont->getCardapio(i) << endl;
            }
        }
    }
    arq << "Total clientes: " << cont->getContPedidos() << endl;
    arq << "Total Delivery: " << cont->getContDelivery() << endl;
    arq << "Renda: " << cont->calculaValor() << endl << endl;
    arq.close();
}

void Menu(int opcao, int *tpedidos, ICliente &clie, Contadora *cont)  // retorna para a main os erros das funções
{
    EntradaException ex;

    switch (opcao)
    {
    case 1:                                             // inicia um novo cliente, seus atributos, e atribui uma ordem conforme tpedidos incrementa
        EditaComanda(cont, clie, 1);
        *tpedidos += 1;
        clie.mComanda.setOrdem(*tpedidos);
        cont->setContPedidos(1);
        Clear();
        break;

    case 2:                                             // adiciona à comanda de um cliente um ou mais pedidos
        EditaComanda(cont, clie, 1);
        Clear();
        break;

    case 3:                                             // retira da comanda de um cliente/delivery um ou mais pedidos
        EditaComanda(cont, clie, -1);
        Clear();
        break;

    case 4:                                             // zera os atributos de um cliente/delivery, além da ordem
        fecharComanda(clie);
        Clear();
        break;

    case 5:                                             // inicia um novo Delivery, seus atributos, e uma ordem também conforme tpedidos incrementa
        EditaComanda(cont, clie, 1);
        *tpedidos += 1;
        clie.mComanda.setOrdem(*tpedidos);
        cont->setContDelivery(1);
        Clear();
        break;

    case 6:
        Clear();
        buscaDelivery(clie);
        break;

    default:  
        ex = EntradaException(6, opcao);
        throw ex;
    }
}

void ExibePedidos(Mesa *clie, Delivery *deliv)     // exibe os pedidos em ordem crescente (ordem de chegada)
{
    int primeiro = 10000;           // responsável por orientar a exibição com número de ordem correta
    bool imprimiu = 1;              // manter o método da bolha até que não haja nada a ser impresso

    for (size_t i = 0; i < MAX_CLIENTE; i++)                // procura o Cliente/Delivery com menor ordem para exibir a partir
    {
        if (clie[i].mComanda.getOrdem() != 0 && primeiro > clie[i].mComanda.getOrdem())  
        {
            primeiro = clie[i].mComanda.getOrdem();
        }
        if (deliv[i].mComanda.getOrdem() != 0 && primeiro > deliv[i].mComanda.getOrdem())  
        {
            primeiro = deliv[i].mComanda.getOrdem();
        }
    }

    cout << "\n-----------------------------------------------------\n";

    while (imprimiu)                                        // exibe os pedidos organizados baseado no método da bolha
    {
        imprimiu = 0;
        for (size_t i = 0; i < MAX_CLIENTE ; i++)  
        {
            if (clie[i].mComanda.getOrdem() == primeiro)   // procura o Cliente com a ordem correta para exibição
            {
                primeiro++;
                imprimiu = 1;

                cout << "\nPedido N.: " << clie[i].mComanda.getOrdem() << " ----- Mesa: " << clie[i].getIdentidade() << endl; 

                for (size_t j = 0; j < MAX_PRATOS; j++)     // exibe os pedidos de acordo com a quantidade
                {
                    if (clie[i].mComanda.getQuantidade(j) > 0)
                    {
                        cout << "        -> " << clie[i].mComanda.getQuantidade(j) << " " << clie[i].mComanda.getStrPrato(j) << endl;
                    }
                }
            }
            else if (deliv[i].mComanda.getOrdem() == primeiro) // procura o Delivery com a ordem correta para exibição
            {
                primeiro++;
                imprimiu = 1;

                cout << "\nPedido N.: " << deliv[i].mComanda.getOrdem() << " ----- Delivery: " << deliv[i].getIdentidade() << endl; 

                for (size_t j = 0; j < MAX_PRATOS; j++)    // exibe os pedidos de acordo com a quantidade
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

ICliente &Localizador(Delivery *deli, Mesa *Me)
{
    string idClient;
    EntradaException ex;
    
    cout << "\n           Digite 0 para encerrar\n";
    cout << "Mesa/nome do Cliente: " << endl;
    cin >> idClient;

    if (idClient[0] >= '0' && idClient[0] <= '9')
    {
        int nComanda = std::stoi(idClient);
        if (nComanda >= 1 && nComanda <= MAX_CLIENTE)
        {
            Me[nComanda].setIdentidade(idClient);
            return Me[nComanda];
        }
        else{
            ex = EntradaException(3, nComanda);
            throw ex;
        }
    }
    else
    {
        for (size_t i = 0; i < MAX_CLIENTE; i++)
        {
            if (deli[i].getIdentidade().find(idClient) != std::string::npos)
            {
                return deli[i];
            }
        }
        ex = EntradaException(5, idClient);
        throw ex;
    }
}

int main(int argc, char const *argv[])
{
    int opcao = 0, tPedidos = 0;      // erro para retorno de valores inesperados nas entradas das funções
    Mesa mesas[MAX_CLIENTE];      // tpedidos para controle da ordem das comandas e armazena total de comandas do dia
    Delivery deli[MAX_CLIENTE];
    Contadora cont;

    cout << "           Bem-vindo!\n";

    while (1)
    {
        cout << "\nSelecione uma opcao:\n"
        << "1 - Nova mesa\n"
        << "2 - Adicionar na comanda\n"
        << "3 - Fechar um item da comanda\n"
        << "4 - Fechar comanda\n"
        << "5 - Novo delivery\n"
        << "6 - Busca delivery\n"
        << "7 - Salvar e sair\n";

        cin >> opcao;

        try
        {
            if (opcao == 7)
            {
                Salvar(&cont);
                break;
            }
            if (opcao == 5)
                Menu(opcao, &tPedidos, deli[cDelivery(deli)], &cont);
            else
                Menu(opcao, &tPedidos, Localizador(deli, mesas), &cont);
        }
        catch(EntradaException &ex)
        {
            cout << ex.msgException();
        }

        ExibePedidos(mesas, deli);

    }
    return 0;
}