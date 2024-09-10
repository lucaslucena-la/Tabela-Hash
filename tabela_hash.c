#include "tabela_hash.h"


// Função para inicializar a tabela hash
void inicializaTabHash(tipo_tab_hash *tbh) {
    for (int i = 0; i < TAM_HASH; i++) {
        tbh->tabela_hash[i] = NULL; // Define todas as posições como NULL, indicando que estão vazias.
    }
}

// Função para alocar um novo nó na tabela hash
tipo_no_hash *alocaNoHash(int chave, const char* dado) {
    tipo_no_hash *novo_no = (tipo_no_hash *)malloc(sizeof(tipo_no_hash));
    if (novo_no == NULL) {
        printf("Erro ao alocar memória para o nó.\n");
        exit(1);
    }
    novo_no->chave = chave;
    strncpy(novo_no->valor, dado, MAX_VALOR - 1); // Copia a string para o valor
    novo_no->valor[MAX_VALOR - 1] = '\0'; // Garante que a string esteja terminada    
    novo_no->prox = NULL;
    return novo_no;
}

//método da visião
int funcaoHash(int chave) {
    return chave % TAM_HASH; // Retorna o índice da tabela hash com base na chave
}

//método da dobra
int hashDobra(int chave, int Tb_size) {
    // Dividindo a chave em duas partes de 16 bits cada
    int parte1 = chave >> 16;  // 16 bits mais significativos
    int parte2 = chave & 0xFFFF; // 16 bits menos significativos
    int resultado = parte1 + parte2; // Soma as duas partes
    return resultado % Tb_size; // Retorna o índice calculado
}

//método da multiplicação

int hashMultiplicacao(int chave, int Tb_size) {
    double A = 0.9287;
    double val = (double)chave * A; // Multiplica a chave pela constante como double
    printf("Valor após multiplicação (chave * A): %.20f\n", val); // Depuração

    val = val - (long)val; // Extrai a parte decimal (fracionária)
    printf("Parte fracionária extraída: %.15f\n", val); // Depuração

    int indice = (int)(val * Tb_size); // Converte para um índice dentro do tamanho da tabela
    printf("Índice calculado: %d\n", indice); // Depuração

    return indice;
}


// Função para buscar um nó na tabela hash pela chave
tipo_no_hash *buscaTabHash(tipo_tab_hash *tbh, int chave) {
    int pos = funcaoHash(chave);
    tipo_no_hash *aux = tbh->tabela_hash[pos];

    while (aux != NULL) {
        if (aux->chave == chave) {
            return aux; // Retorna o nó encontrado
        }
        aux = aux->prox;
    }
    return NULL; // Retorna NULL se a chave não for encontrada
}

// Função para inserir um nó na tabela hash
void insereTabHash(tipo_tab_hash *tbh, int chave, const char* dado ) {
    if (buscaTabHash(tbh, chave) == NULL) { // Verifica se a chave já não existe
        int pos = funcaoHash(chave);
        tipo_no_hash *novo_no = alocaNoHash(chave, dado);

        printf("A  posição eh a ser alocada eh: %d\t\n",pos );

        // Insere o novo nó no início da lista da posição hash
        novo_no->prox = tbh->tabela_hash[pos];
        tbh->tabela_hash[pos] = novo_no;
    } else {
        printf("Chave já existente. Inserção não realizada.\n");
    }
}

void insereTabHashDobra(tipo_tab_hash *tbh, int chave, const char* dado) {
    int pos = hashDobra(chave, TAM_HASH); // Calcula o índice usando o método da dobra

    // Verifica se a chave já existe na tabela para evitar duplicatas
    if (buscaTabHash(tbh, chave) == NULL) { 
        tipo_no_hash *novo_no = alocaNoHash(chave, dado);

        // Insere o novo nó no início da lista da posição hash

        printf("A  posição eh a ser alocada eh: %d\t\n",pos );

        novo_no->prox = tbh->tabela_hash[pos];
        tbh->tabela_hash[pos] = novo_no;
    } else {
        printf("Chave já existente. Inserção não realizada.\n");
    }
}


void insereTabHashMulti(tipo_tab_hash *tbh, int chave, const char* dado) {
    int pos = hashMultiplicacao(chave, TAM_HASH); // Calcula o índice usando o método da dobra

    // Verifica se a chave já existe na tabela para evitar duplicatas
    if (buscaTabHash(tbh, chave) == NULL) { 
        tipo_no_hash *novo_no = alocaNoHash(chave, dado);

        // Insere o novo nó no início da lista da posição hash

        printf("A  posição eh a ser alocada eh: %d\t\n",pos );

        novo_no->prox = tbh->tabela_hash[pos];
        tbh->tabela_hash[pos] = novo_no;
    } else {
        printf("Chave já existente. Inserção não realizada.\n");
    }
}



// Função para remover um nó da tabela hash
char* removeTabHash(tipo_tab_hash *tbh, int chave) {
    int pos = funcaoHash(chave);
    tipo_no_hash *aux = tbh->tabela_hash[pos];
    tipo_no_hash *ant = NULL;

    while (aux != NULL && aux->chave != chave) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL) {
        printf("Chave não encontrada para remoção.\n");
        return NULL;
    }

    char* dado = (char*)malloc(MAX_VALOR * sizeof(char)); // Aloca memória para o valor
    if (dado == NULL) {
        printf("Erro ao alocar memória para o valor removido.\n");
        exit(1);
    }
    strncpy(dado, aux->valor, MAX_VALOR - 1);
    dado[MAX_VALOR - 1] = '\0'; // Garante que a string esteja terminada

    if (ant == NULL) {
        tbh->tabela_hash[pos] = aux->prox;
    } else {
        ant->prox = aux->prox;
    }

    free(aux);
    return dado;
}

// Função para imprimir toda a tabela hash
void imprimeTabHash(tipo_tab_hash *tbh) {
    printf("Tabela HASH:\n");
    for (int i = 0; i < TAM_HASH; i++) {
        printf("[%d] -> ", i);
        tipo_no_hash *aux = tbh->tabela_hash[i];

        if (aux == NULL) {
            printf("(NULL)\n");
        } else {
            while (aux != NULL) {
                printf("[ %d | %s ] -> ", aux->chave, aux->valor);
                aux = aux->prox;
            }
            printf("(NULL)\n");
        }
    }
}