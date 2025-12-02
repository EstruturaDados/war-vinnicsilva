// Modo Mestre do Jogo War
// Missões Individuais para Jogadores

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define MAX_NOME 30
#define MAX_COR 15
#define N_TERRITORIOS 5
#define MAX_MISSAO 100

// Missões pré-definidas
const char* missoes[N_TERRITORIOS] = {
    "Dominar pelo menos 3 territorios.",
    "Destruir todos os exercitos da cor Vermelha.",
    "Controlar America e Europa.",
    "Conquistar Asia e Oceania.",
    "Impedir que Amarelo conquiste novos territorios."
};

typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

typedef struct {
    char cor[MAX_COR];
    char* missao; // ponteiro para a missão alocada dinamicamente
} Jogador;

/* --- Protótipos --- */
void limparBuffer(void);
Territorio* criarMapa(int n);
void inicializarTerritorios(Territorio* mapa, int n);
void exibirTerritorios(Territorio* mapa, int n);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

void atribuirMissao(Jogador* jogador, Territorio* mapa, const char* missoes[], int totalMissoes);
void exibirMissao(const Jogador jogador);
int verificarMissao(const Jogador jogador, Territorio* mapa, int n);
void liberarMissao(Jogador* jogador);


// Limpar Buffer
void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// Aloca o mapa dinamicamente
Territorio* criarMapa(int n) {
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (!mapa) {
        fprintf(stderr, "Erro: memoria insuficiente\n");
        exit(EXIT_FAILURE);
    }
    return mapa;
}

// inicializa os territórios
void inicializarTerritorios(Territorio* mapa, int n) {
    const char* nomes[N_TERRITORIOS] = {"America", "Europa", "Asia", "Africa", "Oceania"};
    const char* cores[N_TERRITORIOS] = {"Verde", "Azul", "Vermelho", "Amarelo", "Branco"};
    const int tropas[N_TERRITORIOS] = {5, 3, 2, 4, 1};

    for (int i = 0; i < n; i++) {
        strncpy(mapa[i].nome, nomes[i], MAX_NOME - 1);
        mapa[i].nome[MAX_NOME - 1] = '\0';
        strncpy(mapa[i].cor, cores[i], MAX_COR - 1);
        mapa[i].cor[MAX_COR - 1] = '\0';
        mapa[i].tropas = tropas[i];
    }
}

// Exibe os territórios
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n============== MAPA DO MUNDO ===================\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %-12s (Exercito: %-7s) (Tropas: %d)\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("================================================\n");
}

// Função para ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    if (!atacante || !defensor) return;

    printf("\n=== ATAQUE ===\n");
    printf("%s (%s) ATACA %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("Dado do atacante: %d\n", dadoA);
    printf("Dado do defensor: %d\n", dadoD);

    if (dadoA > dadoD) {
        printf("\n>>> O atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        if (defensor->tropas < 1) defensor->tropas = 1;
        printf("O territorio %s agora pertence ao exército %s!\n",
               defensor->nome, defensor->cor);
        printf("Tropas do novo dono: %d\n", defensor->tropas);
    } else {
        if (atacante->tropas > 0) atacante->tropas--;
        printf("\n>>> A defesa resistiu!\n");
        printf("%s perdeu 1 tropa.\n", atacante->nome);
    }
}

// Atribui missão
void atribuirMissao(Jogador* jogador, Territorio* mapa, const char* missoes[], int totalMissoes) {
    int idx = rand() % totalMissoes;
    jogador->missao = (char*) malloc(MAX_MISSAO);
    if (!jogador->missao) {
        fprintf(stderr, "Erro ao alocar memoria para a missao!\n");
        exit(EXIT_FAILURE);
    }
    strncpy(jogador->missao, missoes[idx], MAX_MISSAO - 1);
    jogador->missao[MAX_MISSAO - 1] = '\0';

    // Define cor do jogador baseada no território sorteado
    strncpy(jogador->cor, mapa[idx].cor, MAX_COR - 1);
    jogador->cor[MAX_COR - 1] = '\0';
}

// Exibe a missão
void exibirMissao(const Jogador jogador) {
    printf("\n====== SUA MISSAO (%s) ======================\n", jogador.cor);
    if (!jogador.missao) {
        printf("Nenhuma missao atribuida ainda!\n");
    } else {
        printf("- %s\n", jogador.missao);
    }
    printf("=================================================\n");
}

// Verifica a missão
int verificarMissao(const Jogador jogador, Territorio* mapa, int n) {
    if (!jogador.missao) return 0;

    // Missão 1: Dominar pelo menos 3 territorios
    if (strstr(jogador.missao, "3 territorios")) {
        int cont = 0;
        for (int i = 0; i < n; i++)
            if (strcmp(mapa[i].cor, jogador.cor) == 0) cont++;
        return cont >= 3;
    }

    // Missão 2: Destruir todos os exercitos da cor Vermelha
    if (strstr(jogador.missao, "Vermelha")) {
        for (int i = 0; i < n; i++)
            if (strcmp(mapa[i].cor, "Vermelho") == 0) return 0;
        return 1;
    }

    // Missão 3: Controlar America e Europa
    if (strstr(jogador.missao, "America") && strstr(jogador.missao, "Europa")) {
        int america = 0, europa = 0;
        for (int i = 0; i < n; i++) {
            if (strcmp(mapa[i].nome, "America") == 0 && strcmp(mapa[i].cor, jogador.cor) == 0) america = 1;
            if (strcmp(mapa[i].nome, "Europa") == 0 && strcmp(mapa[i].cor, jogador.cor) == 0) europa = 1;
        }
        return america && europa;
    }

    // Missão 4: Conquistar Asia e Oceania
    if (strstr(jogador.missao, "Asia") && strstr(jogador.missao, "Oceania")) {
        int asia = 0, oceania = 0;
        for (int i = 0; i < n; i++) {
            if (strcmp(mapa[i].nome, "Asia") == 0 && strcmp(mapa[i].cor, jogador.cor) == 0) asia = 1;
            if (strcmp(mapa[i].nome, "Oceania") == 0 && strcmp(mapa[i].cor, jogador.cor) == 0) oceania = 1;
        }
        return asia && oceania;
    }

    // Missão 5: Impedir que Amarelo conquiste novos territorios
    if (strstr(jogador.missao, "Amarelo")) {
        for (int i = 0; i < n; i++) {
            if (strcmp(mapa[i].cor, "Amarelo") == 0 && strcmp(mapa[i].nome, "Africa") != 0) return 0;
        }
        return 1;
    }

    return 0;
}

// Libera a missão
void liberarMissao(Jogador* jogador) {
    if (jogador->missao) {
        free(jogador->missao);
        jogador->missao = NULL;
    }
}

// Libera a memória
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

// Função principal
int main(void) {
    srand((unsigned int) time(NULL));
    setlocale(LC_ALL, "C");

    int n = N_TERRITORIOS;
    Territorio* mapa = criarMapa(n);
    inicializarTerritorios(mapa, n);

    printf("\n=======================\n");
    printf("Bem-vindo ao jogo War!\n");
    printf("=======================\n");

    exibirTerritorios(mapa, n);

    Jogador jogador;
    atribuirMissao(&jogador, mapa, missoes, N_TERRITORIOS);
    exibirMissao(jogador);

    int opcao;
    do {
        printf("\nMENU DE ACOES:\n");
        printf("1. Atacar\n");
        printf("2. Verificar Missao\n");
        printf("3. Sair\n");
        printf("Opcao: ");
        if (scanf("%d", &opcao) != 1) { limparBuffer(); continue; }

        if (opcao == 1) {
            int at, df;
            exibirTerritorios(mapa, n);

            printf("\nEscolha o numero do territorio ATACANTE (1 a %d): ", n);
            if (scanf("%d", &at) != 1) { limparBuffer(); continue; }

            printf("Escolha o numero do territorio DEFENSOR (1 a %d): ", n);
            if (scanf("%d", &df) != 1) { limparBuffer(); continue; }

            if (at < 1 || at > n || df < 1 || df > n) {
                printf("\nSelecao invalida!\n");
                continue;
            }

            if (strcmp(mapa[at - 1].cor, mapa[df - 1].cor) == 0) {
                printf("\nUm territorio nao pode atacar outro da MESMA cor!\n");
                continue;
            }

            atacar(&mapa[at - 1], &mapa[df - 1]);

            // Verifica automaticamente se a missão foi cumprida
            if (verificarMissao(jogador, mapa, n)) {
                printf("\n>>> Parabens! Missao cumprida! %s venceu!\n", jogador.cor);
                break;
            }

        } else if (opcao == 2) {
            exibirMissao(jogador);
        }

    } while (opcao != 3);

    liberarMissao(&jogador);
    liberarMemoria(mapa);
    printf("\nMemoria liberada. Encerrando programa.\n");
    return 0;
}
