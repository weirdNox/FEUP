#---------------------------------------------------------------------
# LSDI 2016/17 - FEUP
# Lab 7 (Dez. 2016) - parte II (operações com 2 vetores)
# Ver. 2.3
#---------------------------------------------------------------------

	.data
Nmax:	.word	100
N:      .word	10
array1:	.word   0 : 100
array2:	.word   0 : 100
strSumV:.asciiz "Sequência soma = "
strPint:.asciiz "Produto interno = "
strMaxM:.asciiz "Maior média = "
strNigs:.asciiz "Nº de elementos comuns = "
space:	.asciiz " "
crlf:	.asciiz "\n"

	.text
main:   li  $v0, 40	# set seed
	li  $a0, 0
	syscall

loop:   jal menu
	bne $v0, 1, main1
	jal readN
	j   loop

main1:  bne $v0, 2, main2
	jal fillV1
	jal printV1
	j   main

main2:  bne $v0, 3, main3
	jal fillV2
	jal printV2
	j   main

main3:  bne $v0, 4, main4
	jal printV1
	j   main

main4:  bne $v0, 5, main5
	la  $a0, N
	lw  $a0, ($a0)
	la  $a1, array1
	la  $a2, array2

	jal sumV

	jal printV1

	j   main

main5:  bne $v0, 6, main6
	la  $a0, N
	lw  $a0, ($a0)
	la  $a1, array1
	la  $a2, array2

	jal prodInt

	move $a0, $v0
	la  $v0, strPint
	jal result

	j   main

main6:  bne $v0, 7, main7
	la  $a0, N
	lw  $a0, ($a0)
	la  $a1, array1
	la  $a2, array2

	jal maxMed

	move $a0, $v0
	la  $v0, strMaxM
	jal result

	j   main

main7:  bne $v0, 8, main9    # v2
	la  $a0, N
	lw  $a0, ($a0)
	la  $a1, array1
	la  $a2, array2

	jal com

	move $a0, $v0
	la  $v0, strNigs
	jal result

	j   main


main9:  beq $v0, 0, main10
	jal err
	j   main

main10: li  $v0, 10
	syscall

#===================================================================================================
	.data
menu0:	.asciiz	"-------------------------------- MENU v2 ------------------------------------\n"
menu1:	.asciiz	"  Sequência: 1-Dimensão  2-Preenche S1      3-Preenche S2  4-Imprimir S1\n"
menu2:	.asciiz	"  Operações: 5-Soma      6-Produto interno  7-Maior média  8-Elementos iguais\n"
menu3:	.asciiz	"                                                           0-Terminar\n"
menu4:	.asciiz	"Introduza a sua opção: "
#===================================================================================================

	.text
menu:   li  $v0, 4
	la  $a0, menu0
	syscall
	la  $a0, menu1
	syscall
	la  $a0, menu2
	syscall
	la  $a0, menu3
	syscall
	la  $a0, menu4
	syscall

	li  $v0, 5
	syscall

	jr  $ra

#---------------------------------------------------------------------
	.data
askN:	.asciiz	"Introduza o número de elementos das sequências: "
	.text
readN:  li  $v0, 4
	la  $a0, askN
	syscall

	li  $v0, 5
	syscall
	sw  $v0, N

	jr  $ra

#---------------------------------------------------------------------

result: move $t0, $a0
	move $a0, $v0
	li   $v0, 4
	syscall

	li   $v0, 1
	move $a0, $t0
	syscall

	li   $v0, 4
	la   $a0, crlf
	syscall

	jr   $ra

#---------------------------------------------------------------------
	.data
strB1:	.asciiz "º elemento da sequência 1 = "
	.text
fillV1: la   $t2, array1
	la   $t0, N
	lw   $t0, ($t0)
	li   $t1, 0
fill2:  beq  $t0, $t1, fill1
	addi $t1, $t1, 1
	li   $v0, 1
	move $a0, $t1
	syscall

	li   $v0, 4
	la   $a0, strB1
	syscall

	li   $v0, 5
	syscall
	sw   $v0, ($t2)

	addi $t2, $t2, 4

	j    fill2

fill1:  jr   $ra

#---------------------------------------------------------------------
	.data
strB2:	.asciiz "º elemento da sequência 2 = "
	.text
fillV2: la   $t2, array2
	la   $t0, N
	lw   $t0, ($t0)
	li   $t1, 0
fill4:  beq  $t0, $t1, fill3
	addi $t1, $t1, 1
	li   $v0, 1
	move $a0, $t1
	syscall

	li   $v0, 4
	la   $a0, strB2
	syscall

	li   $v0, 5
	syscall
	sw   $v0, ($t2)

	addi $t2, $t2, 4

	j    fill4

fill3:  jr   $ra


#---------------------------------------------------------------------
	.data
strA1:	.asciiz "Sequência 1 = "
	.text
printV1:li  $v0, 4
	la  $a0, strA1
	syscall

	la  $t2, array1

	la  $t0, N
	lw  $t0, ($t0)
	li  $t1, 0
print2: beq $t0, $t1, print1
	li  $v0, 1
	lw  $a0, ($t2)
	syscall

	li  $v0, 4
	la  $a0, space
	syscall

	addi $t2, $t2, 4
	addi $t1, $t1, 1

	j    print2

print1: li  $v0, 4
	la  $a0, crlf
	syscall

	jr  $ra

#---------------------------------------------------------------------
	.data
strA2:	.asciiz "Sequência 2 = "
	.text
printV2:li  $v0, 4
	la  $a0, strA2
	syscall

	la  $t2, array2

	la  $t0, N
	lw  $t0, ($t0)
	li  $t1, 0
print4: beq $t0, $t1, print3
	li  $v0, 1
	lw  $a0, ($t2)
	syscall

	li  $v0, 4
	la  $a0, space
	syscall

	addi $t2, $t2, 4
	addi $t1, $t1, 1

	j    print4

print3: li  $v0, 4
	la  $a0, crlf
	syscall

	jr  $ra

#---------------------------------------------------------------------

	.data
errStr:	.asciiz "Opção inválida!\n"
	.text
err:    li  $v0, 4
	la  $a0, errStr
	syscall

	jr  $ra

#---------------------------------------------------------------------
# sumV - calcula a soma (vetorial) de duas sequências
#
# Argumentos:
#	$a0 - dimensão das sequências
#	$a1 - endereço base da sequência 1
#	$a2 - endereço base da sequência 2
# Valor retornado
#	nenhum: após a operação, $a1 tem o endereço base da sequência
#               resultante (a sequência 1 original é perdida)
#---------------------------------------------------------------------

sumV:
    move $t0, $a1 # $t0: iterator 1
    move $t1, $a2 # $t1: iterator 2
    move $t2, $a0 # $t2: count
sumV_loop:
    beqz $t2, sumV_end
    lw $t3, ($t0)
    lw $t4, ($t1)
    add $t3, $t3, $t4
    sw $t3, ($t0)
    addi $t0, $t0, 4
    addi $t1, $t1, 4
    addi $t2, $t2, -1
    j sumV_loop

sumV_end:
	jr  $ra    # para retornar ao programa que chamou esta rotina


#---------------------------------------------------------------------
# prodInt - calcula o produto interno de dois vetores (sequências)
#
# Argumentos:
#	$a0 - dimensão das sequências
#	$a1 - endereço base da sequência 1
#	$a2 - endereço base da sequência 2
# Valor retornado
#	$v0 - produto interno
#---------------------------------------------------------------------

prodInt:
    move $t0, $a1 # $t0: iterator 1
    move $t1, $a2 # $t1: iterator 2
    move $t2, $a0 # $t2: count
    xor $v0, $v0, $v0
prodInt_loop:
    beqz $t2, prodInt_end
    lw $t3, ($t0)
    lw $t4, ($t1)
    mul $t3, $t3, $t4
    add $v0, $v0, $t3
    addi $t0, $t0, 4
    addi $t1, $t1, 4
    addi $t2, $t2, -1
    j prodInt_loop
prodInt_end:
	jr $ra

#---------------------------------------------------------------------
# sum - calcula o somatório dos elementos de uma sequência
#
# Argumentos:
#	$a0 - dimensão da
#	$a1 - endereço base da sequência
# Valor retornado
#	$v0 - somatório
#---------------------------------------------------------------------

sum:
    move $t0, $a1 # $t0: iterator
    move $t1, $a0 # $t1: counter
    xor $v0, $v0, $v0
sum_loop:
    beqz $t1, sum_end
    lw $t3, ($t0)
    add $v0, $v0, $t3
    addi $t0, $t0, 4
    addi $t1, $t1, -1
    j sum_loop
sum_end:
    jr  $ra


#---------------------------------------------------------------------
# avg - calcula a média aritmética dos elementos de uma sequência
#
# Argumentos:
#	$a0 - dimensão da sequência
#	$a1 - endereço base da sequência
# Valor retornado
#	$v0 - média
# Nota: A média deverá ser arredondada para o inteiro mais próximo
#---------------------------------------------------------------------

avg:
    addi $sp, $sp, -4
    sw $ra, 0($sp) # Save return addr

    jal sum # $v0: sum
    div $v0, $a0
    mflo $v0 # $v0: result
    mfhi $t0 # $t0: remainder
    abs $t0, $t0
    sll $t0, $t0, 1 # $t0: |remainder|*2
    blt $t0, $a0, avg_end
    bltz $v0, avg_neg
    addi $v0, $v0, 1 # result = result + 1
    j avg_end
avg_neg:
    addi $v0, $v0, -1 # result = result - 1
avg_end:
    lw $ra, 0($sp) # Restore return addr
    addi $sp, $sp, 4
	jr $ra

#---------------------------------------------------------------------
# maxMed - calcula a média das sequências e determina a maior das duas
#
# Argumentos:
#	$a0 - dimensão das sequências
#	$a1 - endereço base da sequência 1
#	$a2 - endereço base da sequência 2
# Valor retornado
#	$v0 - valor da maior média
#---------------------------------------------------------------------

maxMed:
    addi $sp, $sp, -20
    sw $ra, 12($sp)
    sw $a0,  8($sp)
    sw $a1,  4($sp)
    sw $a2,  0($sp)

    jal avg
    sw $v0, 16($sp) # store avg 1

    move $a1, $a2
    jal avg # $v0: avg 2
    lw $t0, 16($sp) # $t0: restore avg 1

    blt $t0, $v0, maxMed_next
    move $v0, $t0

maxMed_next:
    lw $ra, 12($sp)
    lw $a0,  8($sp)
    lw $a1,  4($sp)
    lw $a2,  0($sp)
    addi $sp, $sp, 20
	jr $ra


#---------------------------------------------------------------------
# com - determina o número de elementos comuns às sequências
#
# Argumentos:
#	$a0 - dimensão das sequências
#	$a1 - endereço base da sequência 1
#	$a2 - endereço base da sequência 2
# Valor retornado
#	$v0 - número de elementos
#---------------------------------------------------------------------

com:
    addi $sp, $sp, -32
    sw $s3, 28($sp)
    sw $s2, 24($sp)
    sw $s1, 20($sp)
    sw $s0, 16($sp)
    sw $a0, 12($sp)
    sw $a1,  8($sp)
    sw $a2,  4($sp)
    sw $ra,   ($sp)

    move $s0, $a0 # $s0: counter
    move $s1, $a1 # $s1: iterator
    xor $s2, $s2, $s2 # $s2: number of verified
    xor $s3, $s3, $s3 # $s3: result
com_loop:
    beqz $s0, com_end
    lw $a2, ($s1) # $a2: test value
    # Check if it was counted before
    move $a0, $s2
    lw $a1, 8($sp)
    jal array_contains_num
    bnez $v0, com_next
    # Not counted before, check if common
    lw $a0, 12($sp)
    lw $a1, 4($sp)
    jal array_contains_num
    add $s3, $s3, $v0
com_next:
    addi $s0, $s0, -1
    addi $s1, $s1, 4
    addi $s2, $s2, 1
    j com_loop
com_end:
    move $v0, $s3
    lw $s3, 28($sp)
    lw $s2, 24($sp)
    lw $s1, 20($sp)
    lw $s0, 16($sp)
    lw $a0, 12($sp)
    lw $a1,  8($sp)
    lw $a2,  4($sp)
    lw $ra,   ($sp)
    addi $sp, $sp, 32
	jr $ra

#---------------------------------------------------------------------
# array_contains_num - returns if number is in array
#
# Args:
#   $a0 - dimension
#   $a1 - base array address
#   $a2 - number
# Return:
#   $v0 - 1 if it contains, else 0
#---------------------------------------------------------------------
array_contains_num:
    move $t0, $a0
    move $t1, $a1
array_contains_num_loop:
    beqz $t0, array_contains_num_end
    lw $t2, ($t1) # $t2: value
    bne $a2, $t2, array_contains_num_next
    addi $v0, $zero, 1
    jr $ra
array_contains_num_next:
    addi $t0, $t0, -1
    addi $t1, $t1, 4
    j array_contains_num_loop
array_contains_num_end:
    xor $v0, $v0, $v0
    jr $ra

#---------------------------------------------------------------------
