/*
 * Ficheiros: main.c
 * Autor: Diogo Santos
 * Descricao: Um projeto sobre um sistema de gestao de uma base de dados de jogos de futebol amigaveis.
 *            Ficheiro principal que contem a funcao main e as funcoes principais do projeto.
*/


#include "jogos.h"
#include "equipas.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
      
#define TAMANHO_nome 1024  
#define TAMANHO_hash 31



/*-------------------------------------------PROTOTIPOS-------------------------------------------*/

/*Adiciona um jogo ah base de dados*/
void add_jogo(int NL, hashtable_jogos* hash_jogos, hashtable_equipas* hash_equipas, lista* ls);

/*lista os jogos na base de dados*/
void lista_jogo(int NL, lista* ls);

/*Procura por um jogo na base de dados*/
void procura_jogo(int NL, hashtable_jogos* hash_jogos);

/*Remove um jogo da base de dados*/
void remove_jogo(int NL, hashtable_jogos* hash_jogos, hashtable_equipas* hash_equipas, lista* ls);

/*Altera o score de um jogo na base de dados*/
void altera_score(int NL, hashtable_jogos* hash_jogos,hashtable_equipas* hash_equipas);

/*Adiciona uma equipa ah base de dados*/
void add_equipa(int NL, hashtable_equipas* hash_equipas);

/*Procura por uma equipa na base de dados e devolve numero de vitorias*/
void procura_equipa(int NL, hashtable_equipas* hash_equipas);

/*Funcao auxiliar de comparacao para qsort()*/
int compnome(const void* nome1, const void* nome2);

/*Lista equipas na base de dados por ordem lexicografica com maior numero de vitorias*/
void equipas_maior_vitorias(int NL, hashtable_equipas* hash_equipas);



/*-------------------------------------------MAIN-------------------------------------------*/

int main(){

    /*Contador de comandos e estado do ciclo while*/
    int NL = 1;      
    int estado = true;

    /*Inicializacao das hash tables e da lista*/
    lista* ls = init_lista();
    hashtable_jogos* hash_jogos = init_hash_jogos(TAMANHO_hash);
    hashtable_equipas* hash_equipas = init_hash_equipas(TAMANHO_hash);

    while (estado){

        switch (getchar()){

            case 'a':
                add_jogo(NL,hash_jogos,hash_equipas,ls);
                NL++;
                break;

            case 'l':
                lista_jogo(NL,ls);
                NL++;
                break;

            case 'p':
                procura_jogo(NL,hash_jogos);
                NL++;
                break;

            case 'r':
                remove_jogo(NL,hash_jogos,hash_equipas,ls);
                NL++;
                break;

            case 's':
                altera_score(NL,hash_jogos,hash_equipas);
                NL++;
                break;

            case 'A':
                add_equipa(NL,hash_equipas);
                NL++;
                break;

            case 'P':
                procura_equipa(NL,hash_equipas);
                NL++;
                break;

            case 'g':
                equipas_maior_vitorias(NL,hash_equipas);
                NL++;
                break;

            case 'x':
                estado = false;  
                free_lista(ls);              
                free_hash_jogos(hash_jogos);      
                free_hash_equipas(hash_equipas); 
        }
    }

    return 0;
}



/*-------------------------------------------FUNCOES-------------------------------------------*/

/*Adiciona um jogo ah base de dados*/
void add_jogo(int NL, hashtable_jogos* hash_jogos,hashtable_equipas* hash_equipas,lista* ls){

    equipas* equipa;
    jogos* novo_jogo;
    int score1,score2;
    char nome[TAMANHO_nome],equipa1[TAMANHO_nome],equipa2[TAMANHO_nome];

    scanf(" %[^:]:%[^:]:%[^:]:%d:%d",nome,equipa1,equipa2,&score1,&score2);

    /*Verificacao do input*/

    if (procura_hash_jogos(hash_jogos,nome) != NULL){  
        printf("%d Jogo existente.\n",NL);
        return;
    }
    else if (procura_hash_equipas(hash_equipas,equipa1) == NULL){ 
        printf("%d Equipa inexistente.\n",NL);
        return;
    }
    else if (procura_hash_equipas(hash_equipas,equipa2) == NULL){ 
        printf("%d Equipa inexistente.\n",NL);
        return;
    }

    /*Criacao de um novo jogo*/

    novo_jogo = (jogos*) malloc(sizeof(jogos));

    novo_jogo->score1 = score1;
    novo_jogo->score2 = score2;

    novo_jogo->nome = (char*) malloc(sizeof(char)*(strlen(nome)+1));
    strcpy(novo_jogo->nome,nome);
    novo_jogo->equipa1 = (char*) malloc(sizeof(char)*(strlen(equipa1)+1));
    strcpy(novo_jogo->equipa1,equipa1);
    novo_jogo->equipa2 = (char*) malloc(sizeof(char)*(strlen(equipa2)+1));
    strcpy(novo_jogo->equipa2,equipa2);

    insere_hash_jogos(hash_jogos,novo_jogo);      
    insere_lista_ult(ls,novo_jogo);        

    /*Verificacao de vitorias*/

    if (score1 > score2){
        equipa = procura_hash_equipas(hash_equipas,equipa1);
        equipa->vitorias++;
    }
    else if (score1 < score2){
        equipa = procura_hash_equipas(hash_equipas,equipa2);
        equipa->vitorias++;
    }
}


/*lista os jogos na base de dados*/
void lista_jogo(int NL,lista* ls){
    
    node* aux = ls->head;

    while (aux != NULL){
        printf("%d ",NL);
        printf("%s ",aux->jogo->nome);
        printf("%s ",aux->jogo->equipa1);
        printf("%s ",aux->jogo->equipa2);
        printf("%d ",aux->jogo->score1);
        printf("%d\n",aux->jogo->score2);
        aux = aux->next;
    }
}


/*Procura por um jogo na base de dados*/
void procura_jogo(int NL, hashtable_jogos* hash_jogos){

    jogos* jogo;
    char nome[TAMANHO_nome];

    scanf(" %[^\n]",nome);

    /*Verificacao do input*/

    if ((jogo = procura_hash_jogos(hash_jogos,nome)) == NULL){          
        printf("%d Jogo inexistente.\n",NL);
        return;
    }

    printf("%d ",NL);
    printf("%s ",jogo->nome);
    printf("%s ",jogo->equipa1);
    printf("%s ",jogo->equipa2);
    printf("%d ",jogo->score1);
    printf("%d\n",jogo->score2);
}


/*Remove um jogo da base de dados*/
void remove_jogo(int NL, hashtable_jogos* hash_jogos,hashtable_equipas* hash_equipas, lista* ls){

    jogos* jogo;
    equipas* equipa;
    char nome[TAMANHO_nome];

    scanf(" %[^\n]",nome);

    /*Verificacao do input*/

    if ((jogo = procura_hash_jogos(hash_jogos,nome)) == NULL){          
        printf("%d Jogo inexistente.\n",NL);
        return;
    }

    /*Verificacao de vitorias*/

    if (jogo->score1 > jogo->score2){
        equipa = procura_hash_equipas(hash_equipas,jogo->equipa1);
        equipa->vitorias--;
    }
    else if (jogo->score1 < jogo->score2){
        equipa = procura_hash_equipas(hash_equipas,jogo->equipa2);
        equipa->vitorias--;
    }
    
    remove_lista(ls,nome);
    remove_hash_jogos(hash_jogos,nome);
}


/*Altera o score de um jogo na base de dados*/
void altera_score(int NL, hashtable_jogos* hash_jogos, hashtable_equipas* hash_equipas){

    jogos* jogo;
    int score1,score2;
    char nome[TAMANHO_nome];
    equipas *equipa1,*equipa2;

    scanf(" %[^:]:%d:%d",nome,&score1,&score2);

    /*Verificacao do input*/

    if ((jogo = procura_hash_jogos(hash_jogos,nome)) == NULL){
        printf("%d Jogo inexistente.\n",NL);
        return;
    }

    equipa1 = procura_hash_equipas(hash_equipas,jogo->equipa1);
    equipa2 = procura_hash_equipas(hash_equipas,jogo->equipa2);

    /*Verificao todas as possiblidades de alteracao de vitorias perante os novos scores*/       

    if (jogo->score1 > jogo->score2){           /*Passar de vitoria para*/
        if (score1 < score2){                   /*derrota*/
            equipa1->vitorias--;
            equipa2->vitorias++;
        } 
        else if (score1 == score2){             /*empate*/
            equipa1->vitorias--;
        }
    }
    else if (jogo->score1 < jogo->score2){      /*Passar de derrota para*/
        if (score1 > score2){                   /*vitoria*/
            equipa1->vitorias++;
            equipa2->vitorias--;
        }
        else if (score1 == score2){             /*empate*/
            equipa2->vitorias--;
        }
    }
    else if (jogo->score1 == jogo->score2){    /*Passar de empate para*/
        if (score1 > score2){                  /*vitoria */
            equipa1->vitorias++;
        }
        else if (score1 < score2){             /*derrota*/
            equipa2->vitorias++;
        }
    }
              
    jogo->score1 = score1;
    jogo->score2 = score2;
}


/*Adiciona uma equipa ah base de dados*/
void add_equipa(int NL, hashtable_equipas* hash_equipas){

    char nome[TAMANHO_nome];
    equipas* nova_equipa;

    scanf(" %[^\n]",nome);

    /*Verificacao do input*/

    if (procura_hash_equipas(hash_equipas,nome) != NULL){
        printf("%d Equipa existente.\n",NL);
        return;
    }

    /*Criacao de um novo jogo*/

    nova_equipa = (equipas*) malloc(sizeof(equipas));

    nova_equipa->nome = (char*) malloc(sizeof(char)*(strlen(nome)+1));
    strcpy(nova_equipa->nome,nome);
    nova_equipa->vitorias = 0;

    insere_hash_equipas(hash_equipas,nova_equipa);
}


/*Procura por uma equipa na base de dados e devolve numero de vitorias*/
void procura_equipa(int NL, hashtable_equipas* hash_equipas){

    equipas* equipa;
    char nome[TAMANHO_nome];

    scanf(" %[^\n]",nome);

    /*Verificacao do input*/

    if ((equipa = procura_hash_equipas(hash_equipas,nome))  == NULL){
        printf("%d Equipa inexistente.\n",NL);
        return;
    }
 
    printf("%d ",NL);
    printf("%s ",equipa->nome);
    printf("%d\n",equipa->vitorias);
}

/*Lista equipas na base de dados por ordem lexicografica com maior numero de vitorias*/
void equipas_maior_vitorias(int NL, hashtable_equipas* hash_equipas){

    int i = 0, j = 0;

    int vitorias = 0;         /*Maior valor de vitorias                     */
    int numero_equipas = 0;   /*Numero de equipas com esse valor de vitorias*/
    char** vitorias_equipas;  /*Vetor de nomes dessas equipas               */

    /*Caso nao existam equipas*/

    if (hash_equipas->n_elem == 0){
        return;
    }

    /*Encontra o maior valor de vitorias e o numero de equipas com esse valor*/

    for(; i < hash_equipas->tamanho; i++){  

        if (hash_equipas->hash[i] != NULL){

            if (hash_equipas->hash[i]->vitorias > vitorias){
                vitorias = hash_equipas->hash[i]->vitorias;
                numero_equipas = 1;
            }
            else if (hash_equipas->hash[i]->vitorias == vitorias){
                numero_equipas++;
            }
        }
    }

    /*Guarda o nome dessas equipas num vetor para mais tarde ordenar*/

    vitorias_equipas = (char**) malloc(sizeof(char*)*numero_equipas);

    for(i=0; i < hash_equipas->tamanho; i++){ 

        if (hash_equipas->hash[i] != NULL){

            if (hash_equipas->hash[i]->vitorias == vitorias && j < numero_equipas){
                vitorias_equipas[j] = hash_equipas->hash[i]->nome;
                j++;
            }
        }
    }

    /*Ordena lexicograficamente*/

    qsort(vitorias_equipas,numero_equipas,sizeof(char*),compnome);

    printf("%d Melhores %d\n",NL,vitorias);

    for(i = 0; i < j; i++){
        printf("%d * %s\n",NL,vitorias_equipas[i]);
    }

    free(vitorias_equipas);
}

/*-------------------------------------------FUNCOES-AUXILIARES-------------------------------------------*/

/*Funcao auxiliar de comparacao para qsort()*/
int compnome(const void* nome1, const void* nome2){

    return strcmp(*(const char**)nome1,*(const char**)nome2);
}
