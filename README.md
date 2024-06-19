# ippd-project-bucket-sort

## Projeto da disciplina Introdução à Programação Paralela e Distribuída
Professor: Alexandro Baldassin
Alunos: Ian Passos e Anael Porto

## Objetivo

O projeto tem como objetivo praticar os conceitos de programação paralela aprendidos durante o semestre, a partir da escolha de um ou mais algoritmos que devem ser paralelizados. Neste caso, o algoritmo de ordenação Bucket Sort foi escolhido, e a implementação do código foi feita em C, utilizando a interface OpenMP.

## OpenMP

OpenMP é uma API para programação multi-processo de memória compartilhada. Ela permite acrescentar simultaneidade aos programas escritos em C sobre a base do modelo de execução fork-join. Ela é construída a partir de um conjunto de diretivas ao compilador, rotinas e variáveis de ambiente que influenciam o comportamento do programa no tempo de execução. O OpenMP é um modelo facilmente escalável que possui uma interface simples, sendo assim uma ótima escolha para o desenvolvimento deste projeto.

Esta biblioteca utiliza diretivas chamadas de pragmas para criar threads e dividir o trabalho de um bloco de código entre elas.

## Bucket Sort

O Bucket Sort é um algoritmo de ordenação que envolve dividir elementos do vetor de entrada em grupos, ou baldes. Esses baldes são formados através da distribuição uniformizada dos elemenetos. Após a divisão em baldes, cada balde será responsável por ordenar os valores dentro dele, utilizando outro algoritmo de ordenação qualquer. Posteriormente, os baldes são unidos de forma ordenada em um único objeto. Neste caso, os baldes serão ordenados através do Insertion Sort, que é um algoritmo muito eficiente para listas com tamanhos menores, que será o caso dos baldes. O Bucket Sort possui complexidade O(n) para vetores com valores uniformemente distribuídos.

## Passo a Passo do Bucket Sort

Passo 1 - Criação de um array, onde cada posição representa um balde

![image](https://github.com/IanPassos/ippd-project-bucket-sort/assets/86252440/b5dcd877-9b11-4aa9-bc72-aaa77b02f587)

Passo 2 - Inserir os elementos em cada balde de acordo com o seu valor. Neste exemplo, cada elemento é multiplicado por 10, e inserido no bucket de acordo com o valor inteiro do resultado

![image](https://github.com/IanPassos/ippd-project-bucket-sort/assets/86252440/3e3c9138-d083-4111-abdc-246d54b53081)

Passo 3 - Ordenar cada balde com o algoritmo de ordenação desejado

![image](https://github.com/IanPassos/ippd-project-bucket-sort/assets/86252440/1c6e3635-300f-465e-85b7-3d23d782e0b4)

Passo 4 - Juntar os baldes em um único vetor em ordem 

![image](https://github.com/IanPassos/ippd-project-bucket-sort/assets/86252440/0dfa341c-689c-4e12-9f51-2756c3105db6)

## Paralelização do Bucket Sort

A ideia de paralelizar este algoritmo é permitir que ele seja executado da forma mais rápida e eficiente possível para vetores de tamanhos elevados.

Para isso, threads foram criadas dentro da função bucketSort. Os laços paralelizados foram: Ordenação dos baldes com Insertion Sort e junção dos baldes em um único vetor.

Para calcular o tempo que o algoritmo demora para executar, foram utilizadas variáveis de tempo do OpenMP.

## Referências

[GeeksForGeeks Bucket Sort](https://www.geeksforgeeks.org/bucket-sort-2)

[OpenMP](https://www.openmp.org/)

[GitHub Parallelized Bucket Sort](https://github.com/adricarda/parallel-Bucket-Sort)
