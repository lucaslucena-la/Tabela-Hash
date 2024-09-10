#ifndef __TABELA_HASH_H__
#define __TABELA_HASH_H__
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TAM_HASH 100
#define MAX_VALOR 10 // Tamanho máximo do valor 


struct est_no_hash
{
    int chave;//chave que indentifica o conjunto de dados
    char valor [MAX_VALOR] ;//dado que sera armazenado
    struct est_no_hash *prox;//ponteiro para estabelecer o encadeamento 
};
typedef struct est_no_hash tipo_no_hash;

struct est_tab_hash
{
    tipo_no_hash *tabela_hash[TAM_HASH];
};
typedef struct est_tab_hash tipo_tab_hash;


//prototipagem
void inicializaTabHash(tipo_tab_hash*);
tipo_no_hash *alocaNoHash( int, const char*);
int funcaoHash(int);//entrega a chave 
void insereTabHash(tipo_tab_hash*, int, const char*);
void insereTabHashDobra(tipo_tab_hash *, int , const char* );
void insereTabHashMulti(tipo_tab_hash *, int , const char* );
char* removeTabHash(tipo_tab_hash*, int);
tipo_no_hash *buscaTabHash(tipo_tab_hash*, int);//entrega a chave e busca a chave na tabela, devolvendo o indice do no
void imprimeTabHash(tipo_tab_hash*);
int hashDobra(int , int );






#endif
