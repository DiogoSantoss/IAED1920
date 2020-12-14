# Enunciado do Projecto 2 - IAED 2019/20

## 1. Introdução

O objectivo deste projeto é o desenvolvimento, em linguagem C, de um sistema de
gestão de uma base de dados de jogos de futebol amigáveis.
A interacção com o programa deverá ocorrer através de um
conjunto de linhas compostas por uma letra (comando) e um número de argumentos
dependente do comando a executar. Os possíveis comandos são listados na tabela
seguinte e indicam as operações a executar.

| Comando | Acção |
|:---:|:---|
| __a__ | Adiciona um novo jogo. |
| __A__ | Adiciona uma nova equipa. |
| __l__ | Lista todos os jogos pela ordem em que foram introduzidos. |
| __p__ | Procura um jogo. |
| __P__ | Procura uma equipa. |
| __r__ | Apaga um jogo. |
| __s__ | Altera a pontuação (_score_) de um jogo. |
| __g__ | Encontra as equipas que venceram mais jogos.
| __x__ | Termina o programa. |

## 2. Especificação do problema

O objetivo do projeto é ter um sistema de gestão da jogos de futebol que permita associar a cada jogo as equipas e o resultado.

Cada jogo e cada equipa é caracterizada por uma string não vazia, com um máximo de 1023
caracteres. Usando `scanf`, a string pode ser lida através de `%[^:\n]`,
i.e. uma string não vazia sem  `:` e `\n`.

Cada jogo é caracterizado por:

* Um _nome_, uma string não vazia, com um máximo de 1023 caracteres (`%[^:\n]`).
* Duas equipas, strings não vazias, com um máximo de 1023 caracteres cada (`%[^:\n]`).
* Um _score_, um par de números inteiros não negativos.

*Nota:* Como os nomes longos são raros, as estruturas de dados utilizadas só deverão alocar a memória necessária para guardar as strings dadas.

## 3. Dados de Entrada

Durante a execução do programa as instruções devem ser lidas do standard input
na forma de um conjunto de linhas iniciadas por um carácter, que se passa a
designar por _comando_, seguido de um número de informações dependente do
comando a executar.

Os comandos disponíveis são descritos de seguida. Cada comando indica uma
determinada acção que se passa a caracterizar em termos de formato de entrada,
formato de saída, e erros. No caso de múltiplos erros para o mesmo comando
deverá retornar apenas o primeiro desses erros.

**Importantante:**
Para simplificar o debug do projecto, no inicio de cada linha do output deverá aparecer o número da linha do comando de input que originou esse output.  
A sigla `NL` vai ser usada no texto seguinte para designar este número.

* __a__ - Adiciona um novo jogo.
  * Formato de entrada: `a nome:equipa1:equipa2:score1:score2`
  * Formato de saída: NADA (excepto erro).
  * Erros:
    * `NL Jogo existente.` no caso de já existir um jogo com esse nome no sistema.
    * `NL Equipa inexistente.` no caso de uma das equipas ou ambas não existirem no sistema.
* __l__ - Lista todos os jogos introduzidos.
  * Formato de entrada: `l`
  * Formato de saída: Uma linha por jogo no formato abaixo

        NL nome-jogo nome-equipa1 nome-equipa2 score1 score2

    Os jogos deverão ser listados pela ordem em que foram introduzidos.
    Caso não exista nenhum jogo no sistema, o comando não imprime nada.
  * Erros: Não aplicável.
* __p__ - Procura um jogo com o nome dado.
  * Formato de entrada: `p nome`
  * Formato de saída: Igual ao formato de saída do comando `l` mas apenas com o jogo `nome`.
  * Erros:
    * `NL Jogo inexistente.` no caso de não existir nenhum jogo com esse nome no sistema.
* __r__ - Apaga um jogo dado um nome.
  * Formato de entrada: `r nome`
  * Formato de saída: NADA (excepto erro).
  * Erros:
    * `NL Jogo inexistente.` no caso de não existir nenhum jogo com esse nome no sistema.
* __s__ - Altera o score de um jogo dado o nome.
  * Formato de entrada: `s nome:score1:score2`
  * Formato de saída: NADA (excepto erro).
  * Erros:
    * `NL Jogo inexistente.` no caso de não existir nenhum jogo com esse nome no sistema.
* __A__ - Adiciona uma nova equipa.
  * Formato de entrada: `A nome`
  * Formato de saída: NADA (excepto erro).
  * Erros:
    * `NL Equipa existente.` no caso de já existir uma equipa com esse nome no sistema.
* __P__ - Procura uma equipa dado um nome.
  * Formato de entrada: `P nome`
  * Formato de saída: `NL nome numero-de-jogos-ganhos`.
  * Erros:
    * `NL Equipa inexistente.` no caso de não existir nenhuma equipa com esse nome no sistema.
* __g__ - Encontra as equipas que ganharam mais jogos e lista por ordem lexicográfica (do nome da equipa).
  * Formato de entrada: `g`
  * Formato de saída:
  
        NL Melhores número-de-jogos-ganhos
        NL * nome-equipa1
        NL * nome-equipa2
        NL * nome-equipa3
        ...
    Caso não exista nenhuma equipa, o comando não imprime nada (nem a palavra `Melhores`).
  * Erros: Não aplicável.

## 4. Dados de Saída

O programa deverá escrever no standard output as respostas aos comandos apresentados no standard input. As respostas são igualmente linhas de texto formatadas conforme definido anteriormente neste enunciado. Tenha em atenção o número de espaços entre elementos do seu output, assim como os espaços no final de cada linha. Procure respeitar escrupulosamente as indicações dadas.


## 5. Compilação do Programa

O compilador a utilizar é o `gcc` com as seguintes opções de compilação: `-Wall -Wextra -Werror -ansi -pedantic`. Para compilar o programa deve executar o seguinte comando:

    $ gcc -Wall -Wextra -Werror -ansi -pedantic -o proj2 *.c

Este comando deve ter como resultado a geração do ficheiro executável `proj2`, caso não haja erros de compilação. __A execução deste comando não deverá escrever qualquer resultado no terminal. Caso a execução deste comando escreva algum resultado no terminal, considera-se que o programa não compilou com sucesso__. Por exemplo, durante a compilação do programa, o compilador não deverá escrever mensagens de aviso (warnings).

__Não poderá ser usada a biblioteca `search.h`__

## 6. Execução do Programa

O programa deve ser executado da forma seguinte:

    $ ./proj2 < test.in > test.myout

Posteriormente poderá comparar o seu output (`*.myout`) com o output previsto (`*.out`) usando o comando `diff`,

    $ diff test.out test.myout
