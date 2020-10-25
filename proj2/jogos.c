/*
 * Ficheiros: jogos.c
 * Autor: Diogo Santos
 * Descricao: Ficheiro auxiliar que contem as funcoes da estrutura de dados jogos.
*/

#include "jogos.h"
#include "equipas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/*-------------------------------------------FUNCOES-------------------------------------------*/

/*Inicializa a lista*/
lista* init_lista(){

    lista* ls = (lista*) malloc(sizeof(lista));

    ls->head = NULL;
    ls->last = NULL;

    return ls;
}


/*Insere elemento no fim da lista*/
void insere_lista_ult(lista* ls,jogos* jogo){

    node* novo_node = (node*) malloc(sizeof(node));

    /*Criacao de um novo node*/

    novo_node->jogo = jogo;
    novo_node->next = NULL;
    novo_node->previous = ls->last;

    if (ls->head == NULL){         /*Caso a lista esteja vazia*/
        ls->head = novo_node;
        ls->last = novo_node;
    }
    else{
        ls->last->next = novo_node;
        ls->last = novo_node;
    }
}


/*Remove elemento da lista*/
void remove_lista(lista* ls,char* nome){

    node* aux = ls->head;

    /*Encontra o node correspondente ao nome*/

    while (strcmp(aux->jogo->nome,nome)){ 
        aux= aux->next;
    }

    /*Verifica as varias possiveis posicoes do node na lista*/
    /* (1) ser o unico                                      */
    /* (2) ser o primeiro elemento                          */
    /* (3) ser o ultimo elemento                            */
    /* (4) estar entre dois nodes                           */

    if (aux == ls->last && aux == ls->head){ 
        ls->head = NULL;
        ls->last = NULL;
    }
    else if (aux->previous == NULL){        
        aux->next->previous = NULL;
        ls->head = aux->next;
    }
    else if (aux->next == NULL){          
        aux->previous->next = NULL;
        ls->last = aux->previous;
    }
    else{                                 
        aux->previous->next = aux->next;
        aux->next->previous = aux->previous;
    }

    free(aux);
}


/*Liberta a memoria associada ah lista*/
void free_lista(lista* ls){

    node* aux;

    while (ls->head != NULL){
        aux = ls->head->next;
        free(ls->head);        
        ls->head = aux;
    }

    free(ls);  
}


/*Inicializa hash table*/
hashtable_jogos* init_hash_jogos(int tamanho){

    int i = 0;
    hashtable_jogos* hash_table = (hashtable_jogos*) malloc(sizeof(hashtable_jogos));

    /*Criacao de uma hash table*/

    hash_table->hash = (jogos**) malloc(sizeof(jogos*)*tamanho);
    hash_table->tamanho = tamanho;
    hash_table->n_elem = 0;

    /*Inicializa todas as posicoes a NULL*/

    for (; i < tamanho; i++){
        hash_table->hash[i] = NULL;
    }

    return hash_table;
}


/*Obtem chave*/
int hash_jogos(hashtable_jogos* hash_table,char* nome){

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
void insere_hash_jogos(hashtable_jogos* hash_table,jogos* jogo){

    int i = hash_jogos(hash_table,jogo->nome);

    /*Se o local correspondente estiver preenchido tenta colocar no proximo*/

    for(; hash_table->hash[i] != NULL; i = (i+1) % hash_table->tamanho);

    hash_table->hash[i] = jogo;
    hash_table->n_elem++;

    /*Expande a hashtable caso esteja a metade da sua capacidade*/

    if (hash_table->n_elem >= hash_table->tamanho/2){
        expandir_hash_jogos(hash_table);
    }
}


/*Procura elemento na hash*/  
jogos* procura_hash_jogos(hashtable_jogos* hash_table,char* nome){

    int i = hash_jogos(hash_table,nome);

    /*Procura no local correspondente se nao encontrar verifica os proximos*/

    for(; hash_table->hash[i] != NULL; i = (i+1) % hash_table->tamanho){
        if (!strcmp(hash_table->hash[i]->nome,nome)){
            return hash_table->hash[i];
        }
    }

    return NULL;
}


/*Remove elemento da hash*/
void remove_hash_jogos(hashtable_jogos* hash_table, char* nome){

    jogos* jogo;
    int i = hash_jogos(hash_table,nome);

    /*Procura elemento a remover*/

    for(; hash_table->hash[i] != NULL; i = ((i+1) % hash_table->tamanho)){
        if (!strcmp(hash_table->hash[i]->nome,nome)){
            break;
        }
    }

    free(hash_table->hash[i]->nome); 
    free(hash_table->hash[i]->equipa1);
    free(hash_table->hash[i]->equipa2);
    free(hash_table->hash[i]);

    hash_table->hash[i] = NULL;
    hash_table->n_elem--;

    /*Realoca todos os elementos a partir de i+1 ate encontrar um NULL*/

    for (i = (i+1) % hash_table->tamanho; hash_table->hash[i] != NULL; i = (i+1) % hash_table->tamanho){  
        jogo = hash_table->hash[i];
        hash_table->hash[i] = NULL;
        insere_hash_jogos(hash_table,jogo);
    }
}


/*Expande a memoria utilizada pela hash*/
void expandir_hash_jogos(hashtable_jogos* hash_table){

    int i = 0;
    hashtable_jogos* nova_hash = init_hash_jogos(hash_table->tamanho*2);

    /*Realoca os elementos na nova hash table*/

    for(; i < hash_table->tamanho; i++){
        if (hash_table->hash[i] != NULL){
            insere_hash_jogos(nova_hash,hash_table->hash[i]);
        }
    }

    /*Troca a hash antiga pela nova*/

    free(hash_table->hash);
    hash_table->hash = nova_hash->hash;
    hash_table->tamanho = nova_hash->tamanho;

    /*Liberta o espaco que foi alocado para a estrutura no init_hash_jogos*/
    free(nova_hash); 
}


/*Liberta a memoria associada ah hash*/
void free_hash_jogos(hashtable_jogos* hash_table){

    int i = 0;

    for (; i != hash_table->tamanho; i++){
        if (hash_table->hash[i] != NULL){
            free(hash_table->hash[i]->nome);
            free(hash_table->hash[i]->equipa1);
            free(hash_table->hash[i]->equipa2);
            free(hash_table->hash[i]);
        }
    }
    
    free(hash_table->hash);
    free(hash_table);
}
