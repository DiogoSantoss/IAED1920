/*
 * Ficheiros: equipas.c
 * Autor: Diogo Santos
 * Descricao: Ficheiro auxiliar que contem as funcoes da estrutura de dados equipas.
*/

#include "jogos.h"
#include "equipas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/*-------------------------------------------FUNCOES-------------------------------------------*/

/*Inicializa hash table*/
hashtable_equipas* init_hash_equipas(int tamanho){

    int i = 0;
    hashtable_equipas* hash_table = (hashtable_equipas*) malloc(sizeof(hashtable_equipas));

    /*Criacao de uma hash table*/

    hash_table->hash = (equipas**) malloc(sizeof(equipas*)*tamanho);
    hash_table->tamanho = tamanho;
    hash_table->n_elem = 0;

    /*Inicializa todas as posicoes a NULL*/

    for (; i < tamanho; i++){
        hash_table->hash[i] = NULL;
    }

    return hash_table;
}


/*Obtem chave*/
int hash_equipas(hashtable_equipas* hash_table,char* nome){

    int i = 0;
    int a = 293;
    int chave = 0;  

    /*Para calcular a chave eh utilizado uma soma ponderada dos caracteres da palavra*/

    for (; nome[i] != '\0'; i++){
        chave = (a*chave + nome[i]) % hash_table->tamanho; 
    }

    return chave;
}


/*Insere elemento na hash*/
void insere_hash_equipas(hashtable_equipas* hash_table,equipas* equipa){

    int i = hash_equipas(hash_table,equipa->nome);

    /*Se o local correspondente estiver preenchido tenta colocar no proximo*/

    for(; hash_table->hash[i] != NULL; i = (i+1) % hash_table->tamanho);

    hash_table->hash[i] = equipa;
    hash_table->n_elem++;

    /*Expande a hashtable caso esteja a metade da sua capacidade*/

    if (hash_table->n_elem >= hash_table->tamanho/2){
        expandir_hash_equipas(hash_table);
    }
}


/*Procura elemento na hash*/  
equipas* procura_hash_equipas(hashtable_equipas* hash_table,char* nome){

    int i = hash_equipas(hash_table,nome);

    /*Procura no local correspondente se nao encontrar verifica os proximos*/

    for(; hash_table->hash[i] != NULL; i = (i+1) % hash_table->tamanho){
        if (!strcmp(hash_table->hash[i]->nome,nome)){
            return hash_table->hash[i];
        }
    }

    return NULL;
}


/*Expande a memoria utilizada pela hash*/
void expandir_hash_equipas(hashtable_equipas* hash_table){

    int i = 0;
    hashtable_equipas* nova_hash = init_hash_equipas(hash_table->tamanho*2);

    /*Realoca os elementos na nova hash table*/

    for(; i < hash_table->tamanho; i++){
        if (hash_table->hash[i] != NULL){
            insere_hash_equipas(nova_hash,hash_table->hash[i]);
        }
    }

    /*Troca a hash antiga pela nova*/

    free(hash_table->hash);
    hash_table->hash = nova_hash->hash; 
    hash_table->tamanho = nova_hash->tamanho;

    /*Liberta o espaco que foi alocado para a estrutura no init_hash_equipas*/
    free(nova_hash); 
}


/*Liberta a memoria associada ah hash*/
void free_hash_equipas(hashtable_equipas* hash_table){

    int i = 0;

    for(; i != hash_table->tamanho; i++){
        if (hash_table->hash[i] != NULL){
            free(hash_table->hash[i]->nome);
            free(hash_table->hash[i]);
        }
    }

    free(hash_table->hash);
    free(hash_table);
}