# Enunciado do Projecto 1 - IAED 2019/20

## 1. Introdução

O objectivo deste projeto é o desenvolvimento, em linguagem C, de um sistema de logística. A interacção com o programa deverá ocorrer através de um conjunto de linhas compostas por uma letra (comando) e um número de argumentos dependente do comando a executar. Os possíveis comandos são listados na Tabela seguinte e indicam as operações a executar.

| Comando | Acção |
|:---:|:---|
| __a__ | adiciona um novo produto ao sistema |
| __q__ | adiciona stock a um produto existente no sistema |
| __N__ | cria uma nova encomenda |
| __A__ | adiciona um produto a uma encomenda |
| __r__ | remove stock a um produto existente |
| __R__ | remove um produto de uma encomenda |
| __C__ | calcula o custo de uma encomenda |
| __p__ | altera o preço de um produto existente no sistema |
| __E__ | retorna a descrição e a quantidade de um produto numa dada encomenda |
| __m__ | retorna o identificador da encomenda em que um dado produto ocorre mais vezes |
| __l__ | lista todos os produtos existentes no sistema por ordem crescente de preço |
| __L__ | lista todos os produtos de uma encomenda por ordem alfabética da descrição |
| __x__ | termina o programa |

## 2. Especificação do problema

O objectivo do projecto é ter um sistema de logística que permite gerir stocks de produtos e encomendas.

Existem vários produtos que podem ser adicionados às encomendas.

Cada __produto__ é caracterizado por:

* um identificador (um número inteiro no intervalo [0, 9 999])
* uma descrição (uma string não vazia com um máximo de 63 caracteres)
* o seu preço (um número inteiro maior que 0)
* o seu peso (um número inteiro maior que 0)
* a sua quantidade em stock (um número inteiro maior ou igual a 0)

Uma __encomenda__ é um conjunto de produtos.

As restrições ao problema são as seguintes:

* Os identificadores dos produtos são únicos.
* Pode assumir que existirão no máximo 10 000 produtos diferentes.
* Os produtos são numerados de 0 a 9 999 e sequencialmente pela sua ordem de introdução.
* Pode assumir que todos os produtos criados com o comando `a` serão distintos.
* Pode assumir que existirão no máximo 500 encomendas
* As encomendas são numeradas de 0 a 499 e sequencialmente pela sua ordem de introdução.
* Cada encomenda poderá pesar no máximo 200 unidades de peso.
* Só podem ser adicionados a encomendas produtos que existam em stock na quantidade necessária.

Pode assumir que todo o input fornecido respeitará os tipos indicados. Por exemplo, nunca será adicionado um produto cujo preço seja uma string, um valor negativo, nem zero.

## 3. Dados de Entrada

O programa deverá ler os dados de entrada a partir da linha de comandos e do terminal.

Durante a execução do programa as instruções devem ser lidas do terminal (standard input) na forma de um conjunto de linhas iniciadas por um carácter, que se passa a designar por comando, seguido de um número de informações dependente do comando a executar; o comando e cada uma das informações são separados pelo caracter `':'`.

Os comandos disponíveis são descritos de seguida. Cada comando indica uma determinada acção que se passa a caracterizar em termos de formato de entrada, formato de saída, e erros a retornar. Se o comando gerar mais do que um erro, deverá ser indicado apenas o primeiro.

* __a__ - adiciona um novo produto ao sistema
  * Formato de entrada: `a descricao:preco:peso:qtd`
  * Formato de saída: `Novo produto <idp>.` onde `<idp>` é o identificador do produto criado.
* __q__ - adiciona stock a um produto existente no sistema
  * Formato de entrada: `q idp:qtd`
  * Formato de saída: NADA (excepto erro)
  * Erros:
    * `Impossivel adicionar produto <idp> ao stock. Produto inexistente.` no caso de não existir nenhum produto criado com esse identificador
* __N__ - cria uma nova encomenda
  * Formato de entrada: `N`
  * Formato de saída: `Nova encomenda <ide>.` onde `<ide>` é o identificador da encomenda criada.
* __A__ - adiciona um produto a uma encomenda. Se o produto já existir na encomenda, adiciona a nova quantidade à quantidade existente
  * Formato de entrada: `A ide:idp:qtd`
  * Formato de saída: NADA (excepto erro)
  * Erros:
    * `Impossivel adicionar produto <idp> a encomenda <ide>. Encomenda inexistente.` no caso de não existir nenhuma encomenda criada com esse identificador
    * `Impossivel adicionar produto <idp> a encomenda <ide>. Produto inexistente.` no caso de não existir nenhum produto criado com esse identificador
    * `Impossivel adicionar produto <idp> a encomenda <ide>. Quantidade em stock insuficiente.` no caso de não existir stock suficiente desse produto para satisfazer a encomenda
    * `Impossivel adicionar produto <idp> a encomenda <ide>. Peso da encomenda excede o maximo de 200.` no caso de a adição desse produto exceder o peso máximo permitido por encomenda
* __r__ - remove stock a um produto existente
  * Formato de entrada: `r idp:qtd`
  * Formato de saída: NADA (excepto erro)
  * Erros:
    * `Impossivel remover stock do produto <idp>. Produto inexistente.` no caso de não existir nenhum produto criado com esse identificador
    * `Impossivel remover <qtd> unidades do produto <idp> do stock. Quantidade insuficiente.` no caso de a quantidade de stock restante após a remoção ser negativa
* __R__ - remove um produto de uma encomenda
  * Formato de entrada: `R ide:idp`
  * Formato de saída: NADA (excepto erro)
  * Erros:
    * `Impossivel remover produto <idp> a encomenda <ide>. Encomenda inexistente.` no caso de não existir nenhuma encomenda criada com esse identificador
    * `Impossivel remover produto <idp> a encomenda <ide>. Produto inexistente.` no caso de não existir nenhum produto criado com esse identificador
* __C__ - calcula o custo de uma encomenda
  * Formato de entrada: `C ide`
  * Formato de saída: `Custo da encomenda <ide> <total>.` onde `<total>` é o valor total da encomenda `<ide>`
  * Erros:
    * `Impossivel calcular custo da encomenda <ide>. Encomenda inexistente.` no caso de não existir nenhuma encomenda criada com esse identificador
* __p__ - altera o preço de um produto existente no sistema
  * Formato de entrada: `p idp:preco`
  * Formato de saída: NADA (excepto erro)
  * Erros:
    * `Impossivel alterar preco do produto <idp>. Produto inexistente.` no caso de não existir nenhum produto criado com esse identificador
* __E__ - lista a descrição e a quantidade de um produto numa encomenda
  * Formato de entrada: `E ide:idp`
  * Formato de saída: `<desc> <qtd>.` onde `<desc>` é a descrição do produto `<idp>` e `<qtd>` é a quantidade desse produto na encomenda `<ide>`
  * Erros:
    * `Impossivel listar encomenda <ide>. Encomenda inexistente.` no caso de não existir nenhuma encomenda criada com esse identificador
    * `Impossivel listar produto <idp>. Produto inexistente.` no caso de não existir nenhum produto criado com esse identificador
* __m__ - lista o identificador da encomenda em que o produto dado ocorre mais vezes. Se houver 2 ou mais encomendas nessa situação, deverá imprimir a encomenda de menor `id`.
  * Formato de entrada: `m idp`
  * Formato de saída:
    * `Maximo produto <idp> <ide> <qtd>.` onde `<ide>` é o número da encomenda em que `<idp>` ocorre mais vezes, sendo essa quantidade `<qtd>`
    * Não deverá listar nada caso o produto `<idp>` não ocorra em nenhuma encomenda, ou caso não haja encomendas
  * Erros:
    * `Impossivel listar maximo do produto <idp>. Produto inexistente.` no caso de não existir nenhum produto criado com esse identificador
* __l__ - lista todos os produtos existentes no sistema por ordem crescente de preço. Se houver 2 ou mais produtos com o mesmo preço, deverá imprimir esses por ordem crescente de `id` de produto
  * Formato de entrada: `l`
  * Formato de saída: Um bloco no formato abaixo, e em que os produtos são listados por ordem crescente de preço

        Produtos
        * <desc1> <preco1> <qtd1 em stock>
        * <desc2> <preco2> <qtd2 em stock>
        ...
        * <descn> <precon> <qtdn em stock>
  * Erros: Não aplicável
* __L__ - lista todos os produtos de uma encomenda por ordem alfabética da descrição
  * Formato de entrada: `L <ide>`
  * Formato de saída: Um bloco no formato abaixo, e em que os produtos são listados por ordem alfabética de descrição

        Encomenda <ide>
        * <desc1> <preco1> <qtd1 na ide>
        * <desc2> <preco2> <qtd2 na ide>
        ...
        * <descn> <precon> <qtdn na ide>
  * Erros:
    * `Impossivel listar encomenda <ide>. Encomenda inexistente.` no caso de não existir nenhuma encomenda criada com esse identificador
* __x__ - termina o programa
  * Formato de entrada: `x`
  * Formato de saída: NADA

## 4. Dados de Saída

O programa deverá escrever no standard output as respostas aos comandos apresentados no standard input. As respostas são igualmente linhas de texto formatadas conforme definido anteriormente neste enunciado. Tenha em atenção ao número de espaços entre elementos do seu output, assim como a ausência de espaços e os pontos finais no final de cada linha. Procure respeitar escrupulosamente as indicações dadas.

## 5. Compilação do Programa

O compilador a utilizar é o `gcc` com as seguintes opções de compilação: `-Wall -Wextra -Werror -ansi -pedantic`. Para compilar o programa deve executar o seguinte comando:

    $ gcc -Wall -Wextra -Werror -ansi -pedantic -o proj1 *.c

Este comando deve ter como resultado a geração do ficheiro executável `proj1`, caso não haja erros de compilação. __A execução deste comando não deverá escrever qualquer resultado no terminal. Caso a execução deste comando escreva algum resultado no terminal, considera-se que o programa não compilou com sucesso__. Por exemplo, durante a compilação do programa, o compilador não deverá escrever mensagens de aviso (warnings).

## 6. Execução do Programa

O programa deve ser executado da forma seguinte:

    $ ./proj1 < test.in > test.myout

Posteriormente poderá comparar o seu output (`*.myout`) com o output previsto (`*.out`) usando o comando `diff`,

    $ diff test.out test.myout
