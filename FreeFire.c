#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

/* Prototipos */
void listarItens(Item mochila[], int qtd);
int buscarItem(Item mochila[], int qtd, char nomeProcurado[]);
void cadastrarItem(Item mochila[], int *qtd);
void removerItem(Item mochila[], int *qtd);
void buscarItemMenu(Item mochila[], int qtd);

int main() {
    Item mochila[MAX_ITENS];
    int qtd = 0;   // quantidade de itens cadastrados
    int opcao;

    do {
        printf("\n=== MOCHILA ===\n");
        printf("1 - Cadastrar item\n");
        printf("2 - Remover item\n");
        printf("3 - Buscar item por nome\n");
        printf("4 - Listar itens\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpar '\n' do buffer

        switch (opcao) {
        case 1:
            cadastrarItem(mochila, &qtd);
            listarItens(mochila, qtd);
            break;
        case 2:
            removerItem(mochila, &qtd);
            listarItens(mochila, qtd);
            break;
        case 3:
            buscarItemMenu(mochila, qtd);
            break;
        case 4:
            listarItens(mochila, qtd);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}

/* Listagem dos itens */
void listarItens(Item mochila[], int qtd) {
    int i;
    printf("\n--- Itens na mochila (%d) ---\n", qtd);
    if (qtd == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }
    for (i = 0; i < qtd; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Nome: %s\n", mochila[i].nome);
        printf("  Tipo: %s\n", mochila[i].tipo);
        printf("  Quantidade: %d\n", mochila[i].quantidade);
    }
}

/* Busca sequencial por nome: retorna indice ou -1 */
int buscarItem(Item mochila[], int qtd, char nomeProcurado[]) {
    int i;
    for (i = 0; i < qtd; i++) {
        if (strcmp(mochila[i].nome, nomeProcurado) == 0) {
            return i;
        }
    }
    return -1; // não encontrou
}

/* Cadastro de item (até 10) */
void cadastrarItem(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("Mochila cheia! Nao e possivel cadastrar mais itens.\n");
        return;
    }

    Item novo;
    printf("Digite o nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // remove '\n'

    printf("Digite o tipo do item (ex: arma, municao, cura): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar(); // limpar '\n'

    mochila[*qtd] = novo;
    (*qtd)++;

    printf("Item cadastrado com sucesso!\n");
}

/* Remocao de item por nome */
void removerItem(Item mochila[], int *qtd) {
    if (*qtd == 0) {
        printf("Mochila vazia, nada para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("Digite o nome do item a remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int pos = buscarItem(mochila, *qtd, nomeRemover);
    if (pos == -1) {
        printf("Item nao encontrado.\n");
        return;
    }

    int i;
    for (i = pos; i < *qtd - 1; i++) {
        mochila[i] = mochila[i + 1]; // desloca à esquerda
    }
    (*qtd)--;

    printf("Item removido com sucesso!\n");
}

/* Uso da busca sequencial para mostrar dados do item */
void buscarItemMenu(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    char nomeProcurado[30];
    printf("Digite o nome do item a buscar: ");
    fgets(nomeProcurado, sizeof(nomeProcurado), stdin);
    nomeProcurado[strcspn(nomeProcurado, "\n")] = '\0';

    int pos = buscarItem(mochila, qtd, nomeProcurado);
    if (pos == -1) {
        printf("Item nao encontrado.\n");
    } else {
        printf("Item encontrado:\n");
        printf("  Nome: %s\n", mochila[pos].nome);
        printf("  Tipo: %s\n", mochila[pos].tipo);
        printf("  Quantidade: %d\n", mochila[pos].quantidade);
    }
}
