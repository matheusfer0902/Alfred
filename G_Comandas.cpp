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

void fecharComanda(Comandas *comanda, int *tPedidos){
    int i, op = 0, mesa;

    cout << "Mesa: ";
    cin >> mesa;

    if (mesa < 1 || mesa > MAX_MESA){
        cout << "Mesa " << mesa <<" invalida" << endl;
        return;
    }

    while(op != 3){         // As opções pra fechar a comanda são: Fechar toda a comanda, zeras so pedidos de X mesa, ou zerar o ultimo pedido.

        cout << "1 - Fechar toda a comanda" << endl;
        cout << "2 - Fechar ultimo item da comanda" << endl;
        cout << "3 - Voltar" << endl;
        cin >> op;

        switch(op){

        case 1:         // Para fechar toda a comanda eu vejo qual a comanda da mesa e a zero toda a quantidade.
            for(i = 0; i < MAX_PRATOS; i++){
                comanda[mesa].quantidade[i] = 0;        //! tem q zerar a ordem tb 
            }
            break;

        case 2:         /* Para fechar o ultimo item eu usei um ponteiro de ponteiro pra saber qual o valor do contador de pedidos,
                        pra usar esse contador como base para zerar a quantidade do ultimo pedido */
            comanda[mesa].quantidade[*tPedidos] = 0;        //* ponteiro de ponteiro deu erro, mas da pra usar o ponteiro normal
            i = 1;
            while(op != 3){
                cout << "1 - Remover mais um item" << endl;
                cout << "2 - Fechar toda a comanda" << endl;
                cout << "3 - Sair" << endl;
                cin >> op;

                // Dentro dessa opção eu pergunto se quer remover mais um item, fechar toda a comanda ou sair.

                switch(op)
                {
                case 1:         // Para remover o novo ultimo pedido eu uso o "i", por isso que eu iniciei ele como 1 antes.
                    comanda[mesa].quantidade[*tPedidos - i] = 0;        //? tpedidos - i?
                    i++;
                    break;

                case 2:         // Mesma logica para remover toda a função novamente
                    for(i = 0; i < MAX_PRATOS; i++){
                        comanda[mesa].quantidade[i] = 0;
                    }
                    break;

                case 3:         //para sair
                    return;

                default:        // Para invalidar a opção
                    cout << "Opcao invalida." << endl;
                    break;
                }
            }
        case 3:
            return;

        default:
            cout << "Opcao invalida" << endl;
            break;
        }
    }
    return;
}

int AdicionaComanda(Comandas *comanda)
{
    int mesa, prato, adicao = 0;

    cout << "Mesa: ";       // Pergunta para qual mesa a comanda vai ser criada, e qual prato vai ser adicionado, depois verifica se a mesa existe.
    cin >> mesa;

        if (mesa < 1 || mesa > MAX_MESA)
        {
            cout << "Mesa " << mesa <<" invalida" << endl;
            return -1;
        }

    cout << "\nAo final, selecione prato \"0\" para encerrar adicao.\n";    
    cout << "Numero do prato a adicionar: ";
    cin >> prato;

        if (prato < 0 || prato > MAX_PRATOS)         // Seleciona o prato desejado e verifica se o prato existe.
        {
            cout << "Prato " << prato <<" invalido" << endl;
            return -1;
        }

    while (prato && prato <= MAX_PRATOS)    //prato != 0 e <= ao MAX_PRATOS
    {
        cout << "Quantidade: ";
        cin >> adicao;

        comanda[mesa-1].quantidade[prato-1] += adicao;      //prato e mesa 5 equivale, no array, ao [4]

        cout << "Numero do prato a adicionar: ";
        cin >> prato;
    }

    // Adiciona a quantidade de pratos, por exemplo, feijoada 2 (duas feijoadas).
    return mesa;
}

void Menu(int opcao, Comandas *comanda, int *tpedidos)     //menu para selecao das opcoes
{
    switch (opcao)
    {           /* Na primeira opção, vai ser feita uma nova comanda, atraves da função "AdicionaComanda".
                Além disso, é verificado se a mesa que vai criar a comanda é válida, se a mesa existir, o número total de pedidos é incrementado
                já que a criação da comanda só pode ser feita com o pedido de um prato.
                É importante perceber, também, que o número de pedidos e a ordem de chegada estão alinhados graças a linha --.*/
    case 1:
    {
        int mesa = AdicionaComanda(comanda);
        if(mesa >= 1){
            *tpedidos += 1;
            comanda[mesa-1].ordem = *tpedidos;
        }
    }
        break;

    case 2:     // Usa a mesma função de criação da comanda para adicionar um novo prato.
    {
        AdicionaComanda(comanda);
    }
        break;

    case 3:     // Fecha uma comanda ou zera o ultimo pedido
        fecharComanda(comanda, tpedidos);
        break;

    case 4:     // Sai do programa
        cout << "Sair\n";
        break;

    default:   // Validação da opção
        cout << "Opcao " << opcao << " invalida.\n";
        break;
    }
}

void ExibePedidos(Comandas *comanda)
{
    int primeiro = 10000, imprimiu = 1;

    for (size_t i = 0; i < MAX_MESA; i++)     // Define a mesa com menor ordem e maior prioridade
    {
        if (comanda[i].ordem != 0 && primeiro > comanda[i].ordem)  // primeira iteração para permitir comparações
        {
            primeiro = comanda[i].ordem;
        }
    }

    while (imprimiu)    //imprime as as comandas de acordo com a "ordem" crescente a partir do primeiro
    {
        imprimiu = 0;
        for (size_t i = 0; i < MAX_MESA ; i++)  //procura a mesa da ordem correta
        {
            if (comanda[i].ordem == primeiro)
            {
                primeiro++;
                imprimiu = 1;
                
                cout << "\nPedido N.: " << comanda[i].ordem << " ----- Mesa: " << i+1 << endl;    //imprime ordem e mesa
                
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
}

int main(int argc, char const *argv[])
{
    int opcao = 0, tpedidos = 0;
    Comandas comanda[MAX_MESA];

    // A variável "opcao" guarda o valor inteiro para ser usado no switch case.
    // A variável tpedidos calcula o total de pedidos no dia.
    // É definido também, o array das comandas, sendo no máximo 5 comandas já que são 5 mesas.

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

        ExibePedidos(comanda);
    }

    /* Na main apenas apresentamos o menu, que fica no loop infinito até que seja enviado pelo teclado o número 4.
       As opções do menu são colocadas em uma função "Menu" onde lá acontece a divisão para cada função do programa.*/

    return 0;
}
