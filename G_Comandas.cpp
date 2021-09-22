#include <iostream>
#include <string.h>

#define MAX_PRATOS 5    //Máximo de pratos no "cardapio".
#define MAX_DESC 25    //Máximo de caracteres de cada prato.
#define MAX_MESA 10    //Máximo de mesas no restaurante.

using namespace std;

typedef struct      // Struct definida para os pedidos. Para primeira versão, a struct vai ter o nome dos pratos já prontos.
{
    int ordem = 0;  // Variável responsável por guiar a ordem de chegada.
    char pedido[MAX_PRATOS][MAX_DESC] {"Executivo", "Feijoada", "Galinha de Capoeira", "Picado", "Rubacao"};
    int quantidade[MAX_PRATOS] {0}; // Quantidade do mesmo prato no pedido mesa.
} Comandas;

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

int fecharUmItemComanda(Comandas *comanda){
    int prato = 0, mesa;
    int q = 0;

    cout << "\n         Selecione \"0\" a qualquer momento para encerrar operacao.";
    cout << "\nMesa: ";
    cin >> mesa;

    if (mesa < 1 || mesa > MAX_MESA){
        return mesa;
    }

    cout << "\nEscolha o prato que quer retirar:" << endl;
    cin >> prato;                                       // ID do prato de acordo com o cardapio

    if (prato < 1 || prato > MAX_PRATOS){               //verifica validade da opção digitada
        return prato;
    }

    cout << "Escolha a quantidade que quer retirar:" << endl;
    cin >> q;     // quantidade do prato que quer retirar

    if (q < 1 || comanda[mesa - 1].quantidade[prato - 1] < q){      //verifica validade da opção digitada
        return q;
    }

    comanda[mesa - 1].quantidade[prato - 1] = comanda[mesa - 1].quantidade[prato - 1] - q;  //subtrai o prato

    return 0;
}

int fecharComanda(Comandas *comanda){       // zera comanda
    int i, mesa;

    cout << "\n         Selecione \"0\" a qualquer momento para encerrar operacao.";
    cout << "\nMesa: ";
    cin >> mesa;

    if (mesa < 1 || mesa > MAX_MESA){
        return mesa;
    }

    // Para fechar toda a comanda eu vejo qual a comanda da mesa e a zero toda a quantidade.
    for(i = 0; i < MAX_PRATOS; i++){
        comanda[mesa - 1].quantidade[i] = 0;
    }

    comanda[mesa - 1].ordem = 0;    // ordem = 0 para pois nao tem mais pedidos para a mesa.

    return 0;
    }

int AdicionaComanda(Comandas *comanda, int *mesa)       // adiciona / cria comandas
{
    int prato, adicao = 0;

    cout << "\n         Selecione \"0\" a qualquer momento para encerrar operacao.";
    cout << "\nMesa: ";       // Pergunta para qual mesa a comanda vai ser criada, e qual prato vai ser adicionado, depois verifica se a mesa existe.
    cin >> *mesa;

        if (*mesa < 1 || *mesa > MAX_MESA)      // verificação e retorno de erro
        {
            return *mesa;
        }

    cout << "Numero do prato a adicionar: ";
    cin >> prato;

    while (prato && prato <= MAX_PRATOS)    // verificação e retorno de erro
    {
        cout << "Quantidade: ";
        cin >> adicao;

        if (adicao < 1){
            return adicao;
        }                                                    //adição do prato

        comanda[*mesa-1].quantidade[prato-1] += adicao;      //prato e mesa 5 equivale, no array, ao [4]

        cout << "\nNumero do prato a adicionar: ";
        cin >> prato;
    }
    return prato;       // retorna prato como possivel erro
}

void Menu(int opcao, Comandas *comanda, int *tpedidos, int *erro)     //menu para selecao das opcoes
{
    int mesa;
    switch (opcao)
    {           /* Na primeira opção, vai ser feita uma nova comanda, atraves da função "AdicionaComanda".
                Além disso, o número total de pedidos é incrementado*/
    case 1:
        *erro = AdicionaComanda(comanda, &mesa);
        if(mesa >= 1 && mesa <= MAX_MESA && (*erro == 0)){
            *tpedidos += 1;
            comanda[mesa-1].ordem = *tpedidos;
        }
        break;

    case 2:     // Usa a mesma função de criação da comanda para adicionar um novo prato.
        *erro = AdicionaComanda(comanda, &mesa);
        break;

    case 3:     // diminui um pedido
        *erro = fecharUmItemComanda(comanda);
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
    Comandas comanda[MAX_MESA];

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
