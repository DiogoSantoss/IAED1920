/*
 * Ficheiro: proj1.c
 * Autor: Diogo Santos
 * Descricao: Um projeto de sistema de logistica que gera produtos e encomendas e operacoes sobre esses.
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>


/*tamanho maximo de uma string para cada descricao*/
#define descMAX 64 /*200*/
/*numero maximo de produtos*/
#define prodMAX 10000
/*numero maximo de encomendas*/
#define encomMAX 500
/*numero maximo de produtos numa encomenda*/
#define prodencomMAX 200
/*Facilita a leitura da variavel estado*/
#define ON 1
#define OFF 0


/*(Variaveis Globais) Controla os identificadores dos produtos/encomendas, ditam qual o identificador do proximo produto/encomenda */
int contador_produto=0;
int contador_encomenda=0;


/*(Estruturas) Definem o que eh um produto/encomenda*/
typedef struct{
    char descricao[descMAX];
    int preco;
    int peso;
    int qtd;
}produto;

typedef struct{  /*Dentro de uma encomenda so temos de saber o identificador e a quantidade (Ocupa menos espaco)*/
    int idp;
    int qtd;
}produto_enc;

typedef struct{
    int qntprods;
    produto_enc produto[prodencomMAX];
}encomenda;


/*(Prototipos)*/
void add_prod(produto sistema[]);
void add_stock(produto sistema[]);
void nova_encom(encomenda encomenda[]);
int peso(produto sistema[],encomenda encomendas[],int ide);
int encontra_idp_local(encomenda encomendas[],int ide,int idp);
void add_prod_encom(produto sistema[], encomenda encomendas[]);
void remo_stock(produto sistema[]);
void remo_prod_encom(produto sistema[],encomenda encomendas[]);
void custo_encom(produto sistema[],encomenda encomendas[]);
void alt_preco(produto sistema[]);
void lista_prod_encom(produto sistema[],encomenda encomendas[]);
void lista_prodfreq_encom(encomenda encomendas[]);
void merge(produto sistema[],int copia[],int aux[],int esq,int m,int dir);
void mergesort(produto sistema[],int copia[],int esq,int dir);
void ordena_preco_prods(produto sistema[]);
void merge_encom(produto sistema[],encomenda encomendas[],int ide,produto_enc aux[],int esq,int m,int dir);
void mergesort_encom(produto sistema[],encomenda encomendas[],int ide,int esq,int dir);
void ordena_descr_encom(produto sistema[],encomenda encomendas[]);


int main(){

    /*o indice de cada produto/encomenda corresponde ao seu identificador*/
    produto sistema[prodMAX]; 
    encomenda encomendas[encomMAX];

    int estado=ON;
    /*Dita qual o comando a ser executado*/
    char comando;

    while (estado){

        comando=getchar();

        switch(comando){

            case 'a':
                add_prod(sistema);
                break;

            case 'q':
                add_stock(sistema);
                break;

            case 'N':
                nova_encom(encomendas);
                break;

            case 'A':
                add_prod_encom(sistema,encomendas);
                break;

            case 'r':
                remo_stock(sistema);
                break;
            
            case 'R':
                remo_prod_encom(sistema,encomendas);
                break;

            case 'C':
                custo_encom(sistema,encomendas);
                break;

            case 'p':
                alt_preco(sistema);
                break;

            case 'E':
                lista_prod_encom(sistema,encomendas);
                break;

            case 'm':
                lista_prodfreq_encom(encomendas);
                break;

            case 'l':
                ordena_preco_prods(sistema);
                break;

            case 'L':
                ordena_descr_encom(sistema,encomendas);
                break;

            case 'x':
                estado=OFF;
        }
    }
    return 0;
}

/*Adiciona um novo produto ao sistema*/
void add_prod(produto sistema[]){

    produto prod;

    scanf(" %[^:]:%d:%d:%d",prod.descricao,&prod.preco,&prod.peso,&prod.qtd);

    sistema[contador_produto]=prod;

    printf("Novo produto %d.\n",contador_produto);

    contador_produto++;
}

/*Adiciona stock a um produto existente no sistema*/
void add_stock(produto sistema[]){

    int idp,qtd;

    scanf(" %d:%d",&idp,&qtd);

    /*Erros*/
    /*visto que um produto nunca eh apagado, se existe tem identificador menor que o valor do contador_produto*/
    if (idp >= contador_produto){
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n",idp);
        return;
    }
    /*Fim dos Erros*/

    sistema[idp].qtd += qtd;
}

/*Adiciona uma nova encomenda as encomendas*/
void nova_encom(encomenda encomenda[]){

    encomenda[contador_encomenda].qntprods=0;

    printf("Nova encomenda %d.\n",contador_encomenda);

    contador_encomenda++;
}

/*Funcao auxiliar:Calcula o peso de uma encomenda*/
int peso(produto sistema[],encomenda encomendas[],int ide){

    int i;
    int nrprodutos,idp,peso=0;

    /*Esta variavel vai ser usadas varias vezes ao longo do programa para se referir ao numero de produtos de uma encomenda*/
    nrprodutos=encomendas[ide].qntprods;

    for (i=0; i<nrprodutos; i++){
        idp = encomendas[ide].produto[i].idp;
        peso += sistema[idp].peso*encomendas[ide].produto[i].qtd;
    }

    return peso;
}

/*Encontra o indice do vetor produto (nas encomendas) cujo conteudo corresponde ao idp do produto (no sistema)*/
/* encomendas[ide].produto[a].idp contem o idp de um produto cujo 'idp_local' eh 'a' */
int encontra_idp_local(encomenda encomendas[],int ide,int idp){

    int i;
    int nrprodutos;

    nrprodutos=encomendas[ide].qntprods;

    for (i=0; i<nrprodutos; i++){
        if (encomendas[ide].produto[i].idp == idp){
            return i;
        }
    }
    return -1; /*caso o produto nao exista na encomenda*/
}

/*Adiciona uma certa quantidade de um produto a uma encomenda*/
void add_prod_encom(produto sistema[], encomenda encomendas[]){

    int ide,idp,qtd;
    int nrprodutos,idp_local;

    scanf(" %d:%d:%d",&ide,&idp,&qtd);

    /*Erros*/
    if (ide >= contador_encomenda){
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
        return;
    }
    if (idp >= contador_produto){
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
        return;
    }  
    if (sistema[idp].qtd < qtd){
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n",idp,ide);
        return;
    }   
    if (peso(sistema,encomendas,ide)+sistema[idp].peso*qtd > 200){
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n",idp,ide);   
        return;
    }
    /*Fim Erros*/

    nrprodutos=encomendas[ide].qntprods;

    /*devolve -1 caso o produto nao exista na encomenda*/
    idp_local=encontra_idp_local(encomendas,ide,idp);

    if (idp_local >= 0){
        encomendas[ide].produto[idp_local].qtd += qtd;
        sistema[idp].qtd -= qtd;
    }else{
        encomendas[ide].produto[nrprodutos].idp = idp;
        encomendas[ide].produto[nrprodutos].qtd = qtd;
        encomendas[ide].qntprods++;
        sistema[idp].qtd -= qtd;
    }
}

/*Remove stock a um produto existente*/
void remo_stock(produto sistema[]){

    int idp,qtd;

    scanf(" %d:%d",&idp,&qtd);

    /*Erros*/
    if (idp >= contador_produto){
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n",idp);
        return;
    }  
    if (sistema[idp].qtd < qtd){
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n",qtd,idp);
        return;
    }
    /*Fim dos Erros*/

    sistema[idp].qtd -= qtd;
}

/*Remove um produto de uma encomenda*/
void remo_prod_encom(produto sistema[],encomenda encomendas[]){

    int i;
    int ide,idp;
    int nrproduto,idp_local;

    scanf(" %d:%d",&ide,&idp);

    /*Erros*/
    if (ide >= contador_encomenda){
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n",idp,ide);
        return;
    }
    if (idp >= contador_produto){
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n",idp,ide);
        return;
    }
    /*Fim dos Erros*/

    idp_local=encontra_idp_local(encomendas,ide,idp);
    nrproduto=encomendas[ide].qntprods;

    /*Move os produtos ,que estejam a frente daquele que vai ser removido, para tras*/
    if (idp_local >= 0){

        sistema[idp].qtd += encomendas[ide].produto[idp_local].qtd;

        for (i=idp_local; i<nrproduto-1; i++){
            encomendas[ide].produto[i].idp=encomendas[ide].produto[i+1].idp;
            encomendas[ide].produto[i].qtd=encomendas[ide].produto[i+1].qtd;
        }
        encomendas[ide].qntprods--;
    }
}

/*Calcula o custo de uma encomenda*/
void custo_encom(produto sistema[],encomenda encomendas[]){

    int i;
    int ide,nrprodutos,custo=0;

    scanf(" %d",&ide);

    /*Erros*/
    if (ide >= contador_encomenda){
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n",ide);
        return;
    }
    /*Fim dos Erros*/

    nrprodutos=encomendas[ide].qntprods;

    for (i=0; i<nrprodutos; i++){
        custo += sistema[encomendas[ide].produto[i].idp].preco * encomendas[ide].produto[i].qtd;
    }

    printf("Custo da encomenda %d %d.\n",ide,custo);
}

/*Altera o preco de um produto no sistema*/
void alt_preco(produto sistema[]){

    int idp,preco;

    scanf(" %d:%d",&idp,&preco);

    /*Erros*/
    if (idp >= contador_produto){
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n",idp);
        return;
    }
    /*Fim dos Erros*/

    sistema[idp].preco=preco;
}

/*Lista a descricao e quantidade de um produto numa encomenda*/
void lista_prod_encom(produto sistema[],encomenda encomendas[]){

    int ide,idp,idp_local;

    scanf(" %d:%d",&ide,&idp);

    /*Erros*/
    if (ide >= contador_encomenda){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
        return;
    }
    if (idp >= contador_produto){
        printf("Impossivel listar produto %d. Produto inexistente.\n",idp);
        return;
    }
    /*Fim dos Erros*/
    
    idp_local=encontra_idp_local(encomendas,ide,idp);
    
    if (idp_local >= 0){
        printf("%s %d.\n",sistema[idp].descricao,encomendas[ide].produto[idp_local].qtd);
    }else{
        printf("%s 0.\n",sistema[idp].descricao);
    }
}

/*Lista o identificador da encomenda em que o produto dado ocorre mais vezes*/
void lista_prodfreq_encom(encomenda encomendas[]){

    int i,j;
    int idp;
    int ide,nrprodutos,maior=0,existe_em_encomenda=0;

    scanf(" %d",&idp);

    /*Erros*/
    if (idp >= contador_produto){
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n",idp);
        return;
    }
    /*Fim dos Erros*/

    for (i=0; i<contador_encomenda; i++){  /*Ver todas as encomendas*/

        nrprodutos=encomendas[i].qntprods;

        for (j=0; j<nrprodutos; j++){  /*Itera sobre todos os produtos de cada encomenda*/

            if (encomendas[i].produto[j].qtd > maior && encomendas[i].produto[j].idp == idp){
                ide = i;
                maior = encomendas[i].produto[j].qtd;
                existe_em_encomenda = 1;
            }
        }
    }
    if (contador_encomenda != 0 && existe_em_encomenda){
        printf("Maximo produto %d %d %d.\n",idp,ide,maior);
    }
}

/*Merge Sort*/
void mergesort(produto sistema[],int copia[],int esq,int dir){

    int m=(dir+esq)/2;
    int aux[prodMAX];

    /*Condicao de paragem*/
    if (dir <= esq){
        return;
    }

    /*Processo recurisvo*/
    mergesort(sistema,copia,esq,m);
    mergesort(sistema,copia,m+1,dir);
    merge(sistema,copia,aux,esq,m,dir);
}

/*Funcao Auxiliar do Merge Sort*/
void merge(produto sistema[],int copia[],int aux[],int esq,int m,int dir){

    int i,j,k;
    /*Constroi vetor auxiliar*/
    for (i=m+1; i>esq; i--){
        aux[i-1]=copia[i-1];
    }
    for (j=m; j<dir; j++){
        aux[dir+m-j]=copia[j+1];
    }
    
    for (k=esq; k<=dir; k++){

        if (sistema[aux[j]].preco < sistema[aux[i]].preco){
            copia[k]=aux[j--];

        }else if (sistema[aux[j]].preco == sistema[aux[i]].preco){ /*No caso se serem iguais*/
            /*Ordena os idps por ordem crescente*/
            if (aux[j] < aux[i]){
                copia[k]=aux[j--];
            }else{
                copia[k]=aux[i++];
            }

        }else{
            copia[k]=aux[i++];
        }
    }
}

/*Lista todos os produtos do sistema por ordem crescente de preco*/
void ordena_preco_prods(produto sistema[]){

    int i;
    int copia[prodMAX];

    /*Cria um vetor de ids que vao ser ordenados tendo em conta o seu preco para ser impressos pela ordem correta*/
    for (i=0; i<contador_produto; i++) {
        copia[i] = i;
    }

    /*Eh necessario um algoritmo estavel que perante precos iguais mantenha a ordem crescente dos idp*/
    mergesort(sistema,copia,0,contador_produto-1);

    printf("Produtos\n");

    for(i=0; i<contador_produto; i++){
        printf("* %s %d %d\n",sistema[copia[i]].descricao,sistema[copia[i]].preco,sistema[copia[i]].qtd);
    }
}

/*Merge Sort (encomendas)*/
void mergesort_encom(produto sistema[],encomenda encomendas[],int ide,int esq,int dir){

    int m=(dir+esq)/2;
    produto_enc aux[prodencomMAX];
    
    /*Condicao de paragem*/
    if (dir <= esq){
        return;
    }

    /*Processo Recursivo*/
    mergesort_encom(sistema,encomendas,ide,esq,m);
    mergesort_encom(sistema,encomendas,ide,m+1,dir);
    merge_encom(sistema,encomendas,ide,aux,esq,m,dir);
}

/*Funcao auxiliar do Merge Sort (encomendas)*/
void merge_encom(produto sistema[],encomenda encomendas[],int ide,produto_enc aux[],int esq,int m,int dir){

    int i,j,k;
    
    /*Constroi vetor auxiliar*/
    for (i=m+1; i>esq; i--){
        aux[i-1]=encomendas[ide].produto[i-1];
    }
    for (j=m; j<dir; j++){
        aux[dir+m-j]=encomendas[ide].produto[j+1];
    }
    
    for (k=esq; k<=dir; k++){

        if(strcmp(sistema[aux[j].idp].descricao, sistema[aux[i].idp].descricao) < 0){
            encomendas[ide].produto[k]=aux[j--];

        }else{
            encomendas[ide].produto[k]=aux[i++];
        }
    }
}

/*Lista todos os produtos de uma encomenda por ordem crescente alfabetica*/
void ordena_descr_encom(produto sistema[],encomenda encomendas[]){

    int i;
    int ide,nrprodutos;

    scanf(" %d",&ide);

    /*Erros*/   
    if (ide >= contador_encomenda){
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n",ide);
        return;
    }
    /*Fim dos Erros*/

    nrprodutos = encomendas[ide].qntprods;

    /*Podemos modificar diretamemente o vetor encomendas[ide].produto[] pois os identificadores estao guardados la dentro*/
    mergesort_encom(sistema,encomendas,ide,0,nrprodutos-1);

    printf("Encomenda %d\n",ide);

    for (i=0; i<nrprodutos; i++){
        if (encomendas[ide].produto[i].qtd > 0){
            printf("* %s %d %d\n",sistema[encomendas[ide].produto[i].idp].descricao,sistema[encomendas[ide].produto[i].idp].preco,encomendas[ide].produto[i].qtd);
        }
    }
}