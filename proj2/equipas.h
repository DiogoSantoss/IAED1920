#ifndef EQUIPAS
#define EQUIPAS


/*-------------------------------------------ESTRUTURAS-------------------------------------------*/

typedef struct str_equipas{
    char* nome;
    int vitorias;
} equipas;

typedef struct hashtable_equipas{
    equipas** hash;
    int tamanho;
    int n_elem;
} hashtable_equipas;


/*-------------------------------------------PROTOTIPOS-HASH-------------------------------------------*/

/*Inicializa hash table*/
hashtable_equipas* init_hash_equipas(int tamanho);

/*Obtem chave*/
int hash_equipas(hashtable_equipas* hash_table,char* nome);

/*Insere elemento na hash*/
void insere_hash_equipas(hashtable_equipas* hash_table,equipas* equipa);

/*Procura elemento na hash*/   
equipas* procura_hash_equipas(hashtable_equipas* hash_table,char* nome);

/*Expande a memoria utilizada pela hash*/
void expandir_hash_equipas(hashtable_equipas* hash_table);

/*Liberta a memoria associada ah hash*/
void free_hash_equipas(hashtable_equipas* hash_table);


#endif
