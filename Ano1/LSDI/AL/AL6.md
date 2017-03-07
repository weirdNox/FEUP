---
title:  LSDI - AL 6
author: Gonçalo Santos
geometry: margin=1in
---

a) `.text` é uma diretiva que indica o início do segmento de código do programa
b) Como estamos a usar o modo de memória compacto, o código máquina começa no endereço `0x00000000`
c) Essa instrução é a quinta. É então a instrução `beq $t0, $zero, escreve`
d) O código da instrução é `0x2108ffff`
e) O código da instrução é `0x09000003`
f) O *assembler* converteu `escreve` em `0x00000006` porque a label `escreve` está a um offset de 6 instruções (6 é o valor pedido) da instrução seguinte
g) `0x00000000`
h) O armazenamento de dados começa no endereço `0x00002000`
i) O vetor V começa no endereço `0x00002004`
j) O vetor V ocupa $4\times7 = 28$ bytes em memória
k) O valor `0xfffffff6` é -10 em complemento para 2, que é o quinto elemento do vetor
l) Ocupa os endereços de `0x0000201c` (inclusivé) a `0x00002020` (exclusivé)
m) Fica na posição `0x0000201c`
n) `$0` fica a conter o valor do endereço do primeiro elemento de V
o) O endereço correspondente a `escreve` é `0x0000002c`, e o seu conteúdo correponde a uma instrução do programa
p) A instrução `addi $v0, $zero, 1` coloca o valor 1 no registo `$v0`, que depois é usado pela instrução syscall para se saber qual é o serviço pretendido. Neste caso, indica que o serviço é o 'print integer'
q) É executada 2 vezes
r) O resultado é 50
s) O resultado passa a ser 21
t) O programa passa a indicar qual é o menor elemento do vetor
