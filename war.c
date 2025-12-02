// Modo Novato do Jogo War
// Cadastro e Listagem de Territórios

#include <stdio.h>
#include <string.h>

// Definindo constantes
#define MAX_TERRITORIOS 100
#define MAX_NOME 30
#define MAX_COR 10

// Estrutura do tipo Território
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorio;

// Limpar buffer
void LimparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Territorio territorio[MAX_TERRITORIOS];
    int totalTerritorios = 0;
    char opcao;

    do {
        printf("=======================\n");
        printf("Bem-vindo ao jogo War!\n");
        printf("=======================\n");
        printf("Escolha sua opção:\n");
        printf("1. Cadastrar Território\n");
        printf("2. Listar Territórios\n");
        printf("3. Sair\n");
        printf("Opção: ");

        scanf(" %c", &opcao); // espaço ignora enter pendente

        switch (opcao) {
            case '1':
                if (totalTerritorios < MAX_TERRITORIOS) {
                    printf("\nCadastro de Território:\n");

                    printf("1. Nome do Território: ");
                    LimparBuffer(); // limpa antes do fgets
                    fgets(territorio[totalTerritorios].nome, MAX_NOME, stdin);
                    territorio[totalTerritorios].nome[strcspn(territorio[totalTerritorios].nome, "\n")] = 0;

                    printf("2. Cor do Território: ");
                    fgets(territorio[totalTerritorios].cor, MAX_COR, stdin);
                    territorio[totalTerritorios].cor[strcspn(territorio[totalTerritorios].cor, "\n")] = 0;

                    printf("3. Número de Tropas: ");
                    scanf("%d", &territorio[totalTerritorios].tropas);

                    printf("\nTerritório cadastrado com sucesso!\n\n");
                    totalTerritorios++;
                } else {
                    printf("\nCapacidade máxima de territórios atingida!\n\n");
                }
                break;

            case '2':
                printf("\nListagem de Territórios:\n");
                if (totalTerritorios == 0) {
                    printf("Nenhum território cadastrado.\n\n");
                } else {
                    for (int i = 0; i < totalTerritorios; i++) {
                        printf("---------------------------\n");
                        printf("Território %d\n", i + 1);
                        printf("Nome: %s\n", territorio[i].nome);
                        printf("Cor: %s\n", territorio[i].cor);
                        printf("Tropas: %d\n\n", territorio[i].tropas);
                    }
                }
                break;

            case '3':
                printf("\nSaindo... Até a próxima!\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n\n");
        }

    } while (opcao != '3');

    return 0;
}
