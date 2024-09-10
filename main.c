#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela_hash.h" // Certifique-se de que este arquivo contém todas as declarações necessárias

int main(int argc, char *argv[]) {
    tipo_tab_hash minha_tab_hash;
    inicializaTabHash(&minha_tab_hash); // Inicializa a tabela hash

    int opcao; // Opção escolhida pelo usuário no menu principal
    int metodo; // Opção escolhida pelo usuário para o método de inserção
    int valor, ch; // Variáveis para uso nas operações da tabela hash
    tipo_no_hash *aux;
    char dado[MAX_VALOR];

    while (1) {
        // Mostra o menu de opções
        printf("\nEscolha uma opção:\n");
        printf("1. Inserir na Tabela Hash\n");
        printf("2. Buscar na Tabela Hash\n");
        printf("3. Remover da Tabela Hash\n");
        printf("4. Imprimir Tabela Hash\n");
        printf("5. Sair\n");
        printf("\nDigite a opção desejada: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
            continue;
        }

        switch (opcao) {
            case 1:
                // Submenu para escolher o método de inserção
                printf("\nEscolha o método de inserção:\n");
                printf("1. Método de Divisão\n");
                printf("2. Método da Dobra\n");
                printf("3. Método da Multiplicação\n");
                printf("Digite a opção desejada: ");
                if (scanf("%d", &metodo) != 1) {
                    printf("Entrada inválida. Tente novamente.\n");
                    while (getchar() != '\n'); // Limpa o buffer de entrada
                    continue;
                }

                printf("Valor a Inserir: ");
                if (scanf("%d", &valor) != 1) {
                    printf("Entrada inválida para o valor. Tente novamente.\n");
                    while (getchar() != '\n');
                    continue;
                }

                printf("Dado a Inserir: ");
                while (getchar() != '\n'); // Limpa o buffer de entrada
                if (fgets(dado, MAX_VALOR, stdin) != NULL) {
                    dado[strcspn(dado, "\n")] = '\0'; // Remove o caractere de nova linha

                    // Verifica o método escolhido e chama a função de inserção correspondente
                    switch (metodo) {
                        case 1: // Método de Divisão
                            insereTabHash(&minha_tab_hash, valor, dado);
                            break;
                        case 2: // Método da Dobra
                            insereTabHashDobra(&minha_tab_hash, valor, dado);
                            break;
                        case 3: // Método da Multiplicação
                            {
                                insereTabHashMulti(&minha_tab_hash, valor, dado);

                            }
                            break;
                        default:
                            printf("Método de inserção inválido. Tente novamente.\n");
                            break;
                    }
                } else {
                    printf("Erro ao ler o dado. Tente novamente.\n");
                }
                break;

            case 2:
                // Busca na tabela hash
                printf("Pesquisar: ");
                if (scanf("%d", &ch) != 1) {
                    printf("Entrada inválida. Tente novamente.\n");
                    while (getchar() != '\n');
                    continue;
                }
                aux = buscaTabHash(&minha_tab_hash, ch);
                if (aux != NULL) {
                    printf("\nChave %d encontrada: dado = %s\n", ch, aux->valor);
                } else {
                    printf("Chave não encontrada\n");
                }
                break;

            case 3:
                // Remoção da tabela hash
                printf("Chave para Remover: ");
                if (scanf("%d", &ch) != 1) {
                    printf("Entrada inválida. Tente novamente.\n");
                    while (getchar() != '\n');
                    continue;
                }
                if (removeTabHash(&minha_tab_hash, ch)) {
                    printf("Chave %d removida com sucesso.\n", ch);
                } else {
                    printf("Chave não encontrada para remoção.\n");
                }
                break;

            case 4:
                // Impressão da tabela hash
                imprimeTabHash(&minha_tab_hash);
                break;

            case 5:
                // Saída do programa
                printf("Saindo do programa.\n");
                return EXIT_SUCCESS;

            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    }
}
