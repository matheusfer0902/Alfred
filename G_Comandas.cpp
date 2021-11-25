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

void cDelivery(Delivery *del, int *tpedidos, Contadora *cont)     // inicia um objeto Delivery, bem como seus atributos
{
    string ende, conta, id;
    size_t vaz;
    int quant, prato;
    EntradaException ex;

    getchar();
    cout << "\nNome: ";
    getline(cin, id);
    cout << "Endereco: ";
    getline(cin, ende);
    cout << "Contato: ";
    getline(cin, conta);
    
    cout << "Quantidade: ";
    cin >> quant;

    if (quant == 0)
        return;

    if (quant < 0)
    {
        ex = EntradaException(1, quant);
        throw ex;
    }
    
    cout << "Prato: ";
    std::cin >> prato;
    
    if (prato == 0)
        return;

    if (prato < 1 && prato > MAX_PRATOS)
        {
            ex = EntradaException(2, prato);
            throw ex;
        }

    cont->adicionaPrato(prato - 1, quant);

    for (size_t i = 0; i < MAX_CLIENTE; i++)    // procura um objeto "vazio" para iniciar o novo Delivery
    {
        if (del[i].getIdentidade().find("vazio") != string::npos)
        {
            vaz = i;
            break;
        }   
    }
    *tpedidos += 1;
    del[vaz].setContato(conta);
    del[vaz].setEndereco(ende);
    del[vaz].setIdentidade(id);
    del[vaz].mComanda.setQuantidade(quant, prato-1);
    del[vaz].mComanda.setOrdem(*tpedidos);
}

void fecharComanda(Cliente *cli, Delivery *del){     // zera um Cliente/Delivery, junto de seus atributos
    string idClient;
    EntradaException ex;
    bool encontrou = false;

    cout << "           \nDigite 0 para encerrar\n";
    cout << "Mesa/nome do Cliente: " << endl;
    cin >> idClient;

    if (idClient[0] >= '0' && idClient[0] <= '9')           // identifica se é Cliente pelo primeiro caractere de sua identidade. Sendo número, é cliente (corresponde à mesa)
    {
        int nComanda = std::stoi(idClient);                 // utiliza a mesa como referencia para encontrar a posição correspondente no array do cliente
        if (nComanda >= 1 && nComanda <= MAX_CLIENTE)
        {
            cli[nComanda-1].mComanda.setZero();
            cli[nComanda-1].setIdentidade("vazio");
        }
        else{
            ex = EntradaException(3, nComanda);
            throw ex;
        }
    }
    else                                                    // nao sendo número, é um Delivery com um nome
    {
        for (size_t i = 0; i < MAX_CLIENTE; i++)            // procura nos Delivery alguém com o nome descrito
        {
            if (del[i].getIdentidade().find(idClient) != std::string::npos)
            {
                encontrou = true;

                del[i].mComanda.setZero();
                del[i].setIdentidade("vazio");
                break;
            }
        }
        if (!encontrou)
        {
            ex = EntradaException(5, idClient);
            throw ex;
        }
    }
}

void EditaComanda(Contadora *cont, Cliente* client, Delivery* deliv, int operacao, int *NumCli)   //adiciona ou remove pedidos das comandas de acordo com a operação
{
    int prato, quant;
    string idClient;
    bool encontrou = false;                                 // flag para erro relativo a identidade no caso de um nome
    EntradaException ex;

    cout << "\n           Digite 0 para encerrar\n";
    std::cout << "\nMesa/nome do Cliente: ";
    cin >> idClient;
    
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

        if (prato < 1 && prato > MAX_PRATOS)
        {
            ex = EntradaException(2, prato);
            throw ex;
        }

        if (idClient[0] >= '0' && idClient[0] <= '9')       // identifica um Cliente por ter um número de mesa com identidade
        {   
            int nMesa = std::stoi(idClient);
            if (nMesa >= 1 && nMesa <= MAX_CLIENTE)         // avalia se a mesa do cliente existe
            {
                if (client[nMesa-1].mComanda.getQuantidade(prato-1) + quant * operacao >= 0)    // avalia se a quantidade a retirar é maior que a atual
                {
                    client[nMesa-1].mComanda.setQuantidade(client[nMesa-1].mComanda.getQuantidade(prato-1) + quant * operacao, prato-1);    // com base na quantidade atual, soma ou subtrai a quantidade desejada
                    client[nMesa-1].setIdentidade(idClient);
                    *NumCli = nMesa-1;
                }
                else{
                    ex = EntradaException(4, quant);
                    throw ex;
                }
            }
            else{
                ex = EntradaException(3, nMesa);
                throw ex;
            }
        }
        else
        {
            for (size_t i = 0; i < MAX_CLIENTE; i++)        // no caso de um Delivery, busca no array o nome digitado
            {
                if (deliv[i].getIdentidade().find(idClient) != std::string::npos)
                {
                    encontrou = true;

                    if (deliv[i].mComanda.getQuantidade(prato-1) + quant * operacao >= 0)       // avalia quantidade digitada
                    {
                        deliv[i].mComanda.setQuantidade(deliv[i].mComanda.getQuantidade(prato-1) + quant * operacao, prato-1);
                        *NumCli = i;
                        break;
                    }
                    else{
                        ex = EntradaException(4, quant);
                        throw ex;
                    }
                }
            }
            if (!encontrou){
                ex = EntradaException(5, idClient);
                throw ex;
            }
        }
        if(operacao == 1) {
            cont->adicionaPrato(prato - 1, quant);
        } else {
            cont->retiraPrato(prato - 1, quant);
        }
    }
}

void buscaDelivery(Delivery *deliv)
{
    string nome;
    bool encontrou = false;
    EntradaException ex;

    cout << "\nNome do Cliente: ";
    getchar();
    getline(cin, nome);

    for (size_t i = 0; i < MAX_CLIENTE; i++)
    {
        if (deliv[i].getIdentidade().find(nome) != string::npos)
        {
            cout << "\nNome: " + deliv[i].getIdentidade() + "\nContato: " + deliv[i].getContato() + "\nEndereco: " + deliv[i].getEndereco() << endl;
            encontrou = true;
            break;
        }
    }
    if (!encontrou)
    {
        ex = EntradaException(5, nome);
        throw ex;
    }
    cout << "\n-----------------------------------------------------\n";
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

    arq << data << endl;

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
    arq << "Renda: " << cont->calculaValor() << endl;
    arq.close();
}

void Menu(int opcao, int *tpedidos, Cliente *clien, Delivery *deli, Contadora *cont)  // retorna para a main os erros das funções
{
    int NumCli;
    EntradaException ex;

    switch (opcao)
    {
    case 1:                                             // inicia um novo cliente, seus atributos, e atribui uma ordem conforme tpedidos incrementa
        EditaComanda(cont, clien, deli, 1, &NumCli);
        *tpedidos += 1;
        clien[NumCli].mComanda.setOrdem(*tpedidos);
        cont->setContPedidos(1);
        break;

    case 2:                                             // adiciona à comanda de um cliente um ou mais pedidos
        EditaComanda(cont, clien, deli, 1, &NumCli);
        break;

    case 3:                                             // retira da comanda de um cliente/delivery um ou mais pedidos
        EditaComanda(cont, clien, deli, -1, &NumCli);
        break;

    case 4:                                             // zera os atributos de um cliente/delivery, além da ordem
        fecharComanda(clien, deli);
        break;

    case 5:                                             // inicia um novo Delivery, seus atributos, e uma ordem também conforme tpedidos incrementa
        cDelivery(deli, tpedidos, cont);
        cont->setContDelivery(1);
        break;

    case 6:
        //buscaDelivery
        break;

    case 7:
        Salvar(cont);
        break;

    default:  
        ex = EntradaException(6, opcao);
        throw ex;
    }
}

void ExibePedidos(Cliente *clien, Delivery *deliv)     // exibe os pedidos em ordem crescente (ordem de chegada)
{
    int primeiro = 10000;           // responsável por orientar a exibição com número de ordem correta
    bool imprimiu = 1;              // manter o método da bolha até que não haja nada a ser impresso

    for (size_t i = 0; i < MAX_CLIENTE; i++)                // procura o Cliente/Delivery com menor ordem para exibir a partir
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

    while (imprimiu)                                        // exibe os pedidos organizados baseado no método da bolha
    {
        imprimiu = 0;
        for (size_t i = 0; i < MAX_CLIENTE ; i++)  
        {
            if (clien[i].mComanda.getOrdem() == primeiro)   // procura o Cliente com a ordem correta para exibição
            {
                primeiro++;
                imprimiu = 1;

                cout << "\nPedido N.: " << clien[i].mComanda.getOrdem() << " ----- Mesa: " << clien[i].getIdentidade() << endl; 

                for (size_t j = 0; j < MAX_PRATOS; j++)     // exibe os pedidos de acordo com a quantidade
                {
                    if (clien[i].mComanda.getQuantidade(j) > 0)
                    {
                        cout << "        -> " << clien[i].mComanda.getQuantidade(j) << " " << clien[i].mComanda.getStrPrato(j) << endl;
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

int main(int argc, char const *argv[])
{
    int opcao = 0, tPedidos = 0;      // erro para retorno de valores inesperados nas entradas das funções
    Cliente client[MAX_CLIENTE];      // tpedidos para controle da ordem das comandas e armazena total de comandas do dia
    Delivery deli[MAX_CLIENTE];
    Contadora cont;

    cout << "           Bem-vindo!\n";

    while (opcao != 7)
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
            Menu(opcao, &tPedidos, client, deli, &cont);
            Clear();
        }
        catch(EntradaException ex)
        {
            cout << ex.msgException();
        }

        ExibePedidos(client, deli);

        if (opcao == 6){
            try
            {
                buscaDelivery(deli);
            }
            catch(EntradaException ex)
            {
                cout << ex.msgException();
            }
        }
    }
    return 0;
}