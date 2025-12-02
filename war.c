// Modo Aventureiro do Jogo War
// Modo de Ataque

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOME 30
#define MAX_COR 10

// Struct do território
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// ------------ Funções Auxiliares ------------

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Aloca o mapa dinamicamente
Territorio* criarMapa(int n) {
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    return mapa;
}

// Cadastro dos territórios
void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastro do território %d ---\n", i + 1);

        printf("Nome: ");
        limparBuffer();
        fgets(mapa[i].nome, MAX_NOME, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = 0;

        printf("Cor (exército): ");
        fgets(mapa[i].cor, MAX_COR, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = 0;

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Exibe todos os territórios
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n===== Territórios =====\n");

    for (int i = 0; i < n; i++) {
        printf("\n[%d]\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

// Função principal de ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n=== ATAQUE ===\n");
    printf("%s (%s) ATACA %s (%s)\n",
           atacante->nome, atacante->cor,
           defensor->nome, defensor->cor);

    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("Dado do atacante: %d\n", dadoA);
    printf("Dado do defensor: %d\n", dadoD);

    if (dadoA > dadoD) {
        printf("\n>>> O atacante venceu!\n");

        // Atualização solicitada na regra
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;

        printf("O território %s agora pertence ao exército %s!\n",
               defensor->nome, defensor->cor);
        printf("Tropas do novo dono: %d\n", defensor->tropas);
    } else {
        atacante->tropas--;

        printf("\n>>> A defesa resistiu!\n");
        printf("%s perdeu 1 tropa.\n", atacante->nome);
    }
}

// Libera memória alocada
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

// ------------ Programa Principal ------------

int main() {
    srand(time(NULL));

    int n;

    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);

    Territorio* mapa = criarMapa(n);

    cadastrarTerritorios(mapa, n);

    int opcao;

    do {
        printf("=======================\n");
        printf("Bem-vindo ao jogo War!\n");
        printf("=======================\n");
        printf("Escolha sua opção:\n");
        printf("1. Começar Jogo\n");
        printf("2. Listar Territórios\n");
        printf("3. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        
        if (opcao == 1) {
            int at, df;

            exibirTerritorios(mapa, n);

            printf("\nEscolha o número do território ATACANTE: ");
            scanf("%d", &at);

            printf("Escolha o número do território DEFENSOR: ");
            scanf("%d", &df);

            // Validações obrigatórias
            if (at < 1 || at > n || df < 1 || df > n) {
                printf("\nSeleção inválida!\n");
                continue;
            }

            if (strcmp(mapa[at - 1].cor, mapa[df - 1].cor) == 0) {
                printf("\nUm território não pode atacar outro da MESMA cor!\n");
                continue;
            }

            atacar(&mapa[at - 1], &mapa[df - 1]);
        } else if (opcao == 2) {
            exibirTerritorios(mapa, n);
        }

    } while (opcao != 3);

    liberarMemoria(mapa);

    printf("\nMemória liberada. Encerrando programa.\n");

    return 0;
}
