#include <iostream>
#include <string.h>

#define MAX_PRATOS 5
#define MAX_DESC 25
#define MAX_MESA 10

using namespace std;

typedef struct 
{
    int ordem;
    char pedido[MAX_PRATOS][MAX_DESC] {"Executivo", "Feijoada", "Galinha de Capoeira", "Picado", "Rubacao"};
    int quantidade[MAX_PRATOS] {0};
} Comandas;

int AdicionaComanda(Comandas *comanda)
{
    int mesa, prato, adicao = 0;

    cout << "Mesa: ";
    cin >> mesa;

        if (mesa < 1 || mesa > MAX_MESA)
        {
            cout << "Mesa " << mesa <<" inválida" << endl;
            return -1;
        }
        
    cout << "\nAo final, selecione prato \"0\" para encerrar adicao.\n";
    cout << "Numero do prato a adicionar: ";
    cin >> prato;

        if (prato < 0 || prato > MAX_PRATOS)
        {
            cout << "Prato " << prato <<" inválido" << endl;
            return -1;
        }
    
    while (prato && prato <= MAX_PRATOS)
    {
        cout << "Quantidade: ";
        cin >> adicao;

        comanda[mesa-1].quantidade[prato] += adicao;

        cout << "Numero do prato a adicionar: ";
        cin >> prato;
    }
    return mesa;
}

void Menu(int opcao, Comandas *comanda, int *tpedidos)     //menu para selecao das opcoes
{                       
    switch (opcao)
    {
    case 1:
        int mesa = AdicionaComanda(comanda);
        if(mesa >= 1){
            *tpedidos++;
            comanda[mesa-1].ordem = *tpedidos;
        }
        break;
    
    case 2:
        AdicionaComanda(comanda);
        break;

    case 3:
        cout << "item 3\n";
        break;

    case 4:
        cout << "Sair\n";
        break;

    default:
        cout << "Opcao " << opcao << " invalida.\n";
        break;
    }
}

/*
void ExibePedidos(Comandas *comanda)
{
    
}
*/

int main(int argc, char const *argv[])
{
    int opcao = 0, tpedidos = 0;
    Comandas comanda[MAX_MESA];

    cout << "Bem-vindo!\n";

    while (opcao != 4)
    {
        cout << "\nSelecione uma opcao:\n" 
        << "1 - Nova comanda\n"
        << "2 - Adicionar na comanda\n"
        << "3 - Fechar comanda\n"
        << "4 - Sair\n";
        
        cin >> opcao;
        
        Menu(opcao, comanda, &tpedidos);
    }
    
    return 0;
}
