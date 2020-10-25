#ifndef JOGOS
#define JOGOS  


/*-------------------------------------------ESTRUTURAS-------------------------------------------*/

typedef struct str_jogos{
    char *nome, *equipa1, *equipa2;
    int score1, score2;
} jogos;

typedef struct hashtable_jogos{
    jogos** hash;
    int tamanho;
    int n_elem;
} hashtable_jogos;

typedef struct str_node{
    struct str_node *next, *previous;
    jogos* jogo;
} node;

typedef struct {
    struct str_node *head, *last;
} lista;


/*-------------------------------------------PROTOTIPOS-LISTA-------------------------------------------*/

/*Inicializa a lista*/
lista* init_lista();

/*Insere elemento no fim da lista*/
void insere_lista_ult(lista* ls,jogos* jogo);

/*Remove elemento da lista*/
void remove_lista(lista* ls,char* nome);

/*Liberta a memoria associada ah lista*/
void free_lista(lista* ls);


/*-------------------------------------------PROTOTIPOS-HASH-------------------------------------------*/

/*Inicializa hash table*/
hashtable_jogos* init_hash_jogos(int tamanho);

/*Obtem chave*/
int hash_jogos(hashtable_jogos* hash_table,char* nome);

/*Insere elemento na hash*/
void insere_hash_jogos(hashtable_jogos* hash_table,jogos* jogo);

/*Procura elemento na hash*/       
jogos* procura_hash_jogos(hashtable_jogos* hash_table,char* nome);

/*Remove elemento da hash*/
void remove_hash_jogos(hashtable_jogos* hash_table,char* nome);

/*Expande a memoria utilizada pela hash*/
void expandir_hash_jogos(hashtable_jogos* hash_table);

/*Liberta a memoria associada ah hash*/
void free_hash_jogos(hashtable_jogos* hash_table);


#endif