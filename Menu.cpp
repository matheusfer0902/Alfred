#include "Menu.hpp"  
#include "Comanda.hpp"
#include "Cliente.hpp"
#include "Delivery.hpp"
#include "Pedido.hpp"
#include <string>

using namespace std;
using namespace pkt_comanda;

Menu::Menu() /* No construtor no menu, é especificado a inicialização das comandas recebendo "nullptr", ou seja,
                comanda vazias. */
{
    for(int i = 0; i < MAX_CLIENTE; i++){
        this->client[i] = nullptr;
    }
    for(int i = 0; i < MAX_CLIENTE; i++){
        this->delivG[i] = nullptr;
    }
}

Menu::~Menu()
{
    //dtor
}

void Menu::novaCMD(int tPedidos){     // Na opção 1, é criada uma nova comanda, nesse metodo é perguntado qual o prato e a
    int prato, quantidade, i;       // quantidade de pratos desejada. Logo depois, é criado o pedido e a comanda atual, que é
    std::string identidade;         // salva na primeira comanda que recebe "nullptr", ou seja, a primeira comanda vazia.

    cout << "Digite o numero do prato desejado: " << endl;
    cin >> prato;
    if(prato <= 0 || prato > MAX_PRATOS){
        setErro(prato);
        return;
    }
    cout << "Quantidade do prato: " << endl;
    cin >> quantidade;
    if(quantidade <= 0){
        setErro(quantidade);
        return;
    }

    cout << "Mesa: " << endl;
    cin >> identidade;

    Pedido* pdd = new Pedido();
    pdd->setPrato(prato-1);
    pdd->setQuantidade(quantidade);
    Cliente* clie = new Cliente(identidade);

    for(i = 0; i < MAX_CLIENTE; i++){
        if(client[i] == nullptr){
            this->client[i] = clie;
            break;
        }
    }
    delete clie;
    delete pdd;
}

void Menu::adicionaCMD(){        /* Na opção 2, é adicionado um novo pedido em uma comanda que ja existe. A primeira coisa é
                               perguntar em qual comanda vai ser adicionado  o pedido, onde se a comanda for invalida, é
                               informado que a opção foi invalida. */
    int numeroComanda;
    cout << "Numero da comanda para adicionar o pedido: " << endl;
    cin >> numeroComanda;

    if(this->client[numeroComanda] != nullptr){
        int prato, quantidade;

        cout << "Digite o numero do prato desejado: " << endl;
        cin >> prato;
        cout << "Quantidade do prato: " << endl;
        cin >> quantidade;

        Pedido* pdd = new Pedido(prato-1, quantidade); // Se a opção da comanda for valida, é realizado um novo pedido
                                                       // Dentro da comanda "numeroComanda".
        client[numeroComanda]->cmd.addPedido(pdd);
        delete pdd;
    } else {
        cout << "op invalida" << endl;
    }
}

void Menu::fechaItem(){
    std::string idClient;
    int quant, prato;

    cout << "Numero/nome da comanda a alterar: " << endl;
    cin >> idClient;
    cout << "Prato a retirar: " << endl;
    cin >> prato;
    cout << "Quantidade a retirar: " << endl;
    cin >> quant;

    if (idClient[0] >= '0' && idClient[0] <= '9')       
    {
        int nComanda = std::stoi(idClient);
        if (nComanda >= 1 && nComanda <= MAX_CLIENTE)
        {
            client[nComanda]->cmd.fecharUmItem(prato-1, quant);
        }
    }
    else
    {
        for (size_t i = 0; i < MAX_CLIENTE; i++)
        {
            if (delivG[i]->getIdentidade().find(idClient) != std::string::npos)
            {
                delivG[i]->cmd.fecharUmItem(prato-1, quant);
            }
        }
    }
}
void Menu::fechaCMD(){
    std::string idClient;

    cout << "Numero da comanda para fechar: " << endl;
    cin >> idClient;

    if (idClient[0] >= '1' && idClient[0] <= '9')
    {
        int nComanda = std::stoi(idClient);
        if (nComanda >= 0 && nComanda <= MAX_CLIENTE)
        {
            for(size_t j = 0; j < MAX_PRATOS; j++)
            {
                Pedido* pddAUX = client[nComanda]->cmd.getPedidos(j);
                client[nComanda]->cmd.fecharUmItem(pddAUX->getPrato(), pddAUX->getQuantidade());
                delete pddAUX;
            }
            client[nComanda]->cmd.setOrdem(0);
            client[nComanda]->setIdentidade(nullptr);
        }
    }
    else
    {
        for (size_t i = 0; i < MAX_CLIENTE; i++)
        {
            if(delivG[i]->getIdentidade().find(idClient) != std::string::npos)
            {
                for(size_t j = 0; j < MAX_PRATOS; j++)
                {
                    Pedido* pddAUX = delivG[i]->cmd.getPedidos(j);
                    delivG[i]->cmd.fecharUmItem(pddAUX->getPrato(), pddAUX->getQuantidade());
                    delete pddAUX;
                }
                delivG[i]->setContato(nullptr);
                delivG[i]->setEndereco(nullptr);
                delivG[i]->setIdentidade(nullptr);
                delivG[i]->cmd.setOrdem(0);
                break;
            }
        }
    }
}

void Menu::delivery(int tPedidos){
    int prato, quantidade, i;
    string endereco, contato, nome;

    getchar();
    cout << "Nome do cliente: " << endl;
    getline(cin, nome);
    cout << "Endereco do pedido: " << endl;
    getline(cin, endereco);
    cout << "Contato do cliente: " << endl;
    cin >> contato;

    Delivery* deli = new Delivery(endereco, contato);
    deli->setIdentidade(nome);

    cout << "\nPara sair, digite 0\n";
    
    Pedido* pddAUX[MAX_PRATOS];
    
    for (size_t i = 0; i < MAX_PRATOS; i++)
    {
        cout << "Digite o numero do prato desejado: " << endl;
        cin >> prato;
        if(prato <= 0 || prato > MAX_PRATOS){
            setErro(prato);
            break;
        }
        cout << "Quantidade do prato: " << endl;
        cin >> quantidade;
        if(quantidade <= 0){
            setErro(quantidade);
            break;
        }
        pddAUX[i]->setPrato(prato-1);
        pddAUX[i]->setQuantidade(quantidade);
    }
    deli->cmd.addPedido(*pddAUX);
    deli->cmd.setOrdem(tPedidos);

    for(i = 0; i < MAX_CLIENTE; i++){
        if(client[i] == nullptr){
            this->delivG[i] = deli;
            break;
        }
    }
    delete deli;
}

void Menu::setErro(int e){
    erro = e;
}

int Menu::getErro(){
    return erro;
}

void Menu::exibePedidos(){
    int primeiro = 10000, imprimiu = 1;
    for (size_t i = 0; i < MAX_CLIENTE && client[i] != nullptr; i++)     // Define a mesa com menor ordem e maior prioridade
    {
        int ordemAUX = client[i]->cmd.getOrdem();
        if (ordemAUX != 0 && primeiro > ordemAUX)  // primeira iteração para permitir comparações
        {
            primeiro = ordemAUX;
        }
        else
        ordemAUX = delivG[i]->cmd.getOrdem();
        if (ordemAUX != 0 && primeiro > ordemAUX)
        {
            primeiro = ordemAUX;
        }
    }
    cout << "\n-----------------------------------------------------\n";
    while (imprimiu)    //confere se a impresão de todas as comandas está completa
    {
        imprimiu = 0;
        for (size_t i = 0; i < MAX_CLIENTE && client[i] != nullptr; i++)  //procura as mesas na ordem correta e imprime-as
        {
            if (client[i]->cmd.getOrdem() == primeiro)
            {
                primeiro++;
                imprimiu = 1;
                cout << "\nPedido N.: " << client[i]->cmd.getOrdem() << " ----- Mesa: " << client[i]->getIdentidade() << endl;  // cabeçalho
                for (size_t j = 0; j < MAX_PRATOS && client[i]->cmd.getPedidos(j) != nullptr; j++)     //imprime pedidos da mesa
                {
                    Pedido* pddAUX = client[i]->cmd.getPedidos(j);
                    if (pddAUX->getQuantidade() > 0)
                    {
                        cout << "        -> " << pddAUX->getQuantidade() << " " << pddAUX->getStrPrato() << endl;
                    }
                    delete pddAUX;
                }
            }

            if (delivG[i]->cmd.getOrdem() == primeiro)
            {
                primeiro++;
                imprimiu = 1;
                cout << "\nPedido N.: " << delivG[i]->cmd.getOrdem() << " ----- Nome: " << delivG[i]->getIdentidade() << endl;  // cabeçalho
                for (size_t j = 0; j < MAX_PRATOS && delivG[i]->cmd.getPedidos(j) != nullptr ; j++)     //imprime pedidos da mesa
                {
                    Pedido* pddAUX = delivG[i]->cmd.getPedidos(j);
                    if (pddAUX->getQuantidade() > 0)
                    {
                        cout << "        -> " << pddAUX->getQuantidade() << " " << pddAUX->getStrPrato() << endl;
                    }
                    delete pddAUX;
                }
            }
        }
    }
    cout << "\n-----------------------------------------------------\n";
}

void Menu::zeraClientes(){
    for (size_t i = 0; i < MAX_CLIENTE; i++)
    {
        delete client[i];
        delete delivG[i];
    }
}