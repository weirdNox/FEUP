#---------------------------------------------------------------------
# LSDI 2016/17 - FEUP
# Lab 7 (Dez. 2016) - parte I (operações com 1 vetor)
# Ver. 2.3
#---------------------------------------------------------------------

	.data
Nmax:	.word	100
N:      .word	10
array:	.word   0 : 100
strSum: .asciiz "Somatório = "
strAvg: .asciiz "Média = "
strMinL:.asciiz "Nº de mínimos locais = "
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
	jal fill
	jal print
	j   main

main2:  bne $v0, 3, main3
	jal rnd
	jal print
	j   main

main3:  bne $v0, 4, main4
	jal print
	j   main

main4:  bne $v0, 5, main5
	la  $a0, N
	lw  $a0, ($a0)
	la  $a1, array

	jal sum

	move $a0, $v0
	la  $v0, strSum
	jal result

	j   main

main5:  bne $v0, 6, main6
	la  $a0, N
	lw  $a0, ($a0)
	la  $a1, array

	jal avg

	move $a0, $v0
	la  $v0, strAvg
	jal result

	j   main

main6:  bne $v0, 7, main7
	la  $a0, N
	lw  $a0, ($a0)
	la  $a1, array

	jal minL

	move $a0, $v0
	la  $v0, strMinL
	jal result

	j   main

main7:  bne $v0, 8, main8
	la  $a0, N
	lw  $a0, ($a0)
	la  $a1, array

	jal inv    # Não imprime resultado

	j   main

main8:  beq $v0, 0, main10
	jal err
	j   main

main10:  li  $v0, 10
	syscall

#==========================================================================================
	.data
menu0:	.asciiz	"-------------------------------- MENU ---------------------------------\n"
menu1:	.asciiz	"  Sequência: 1-Dimensão     2-Preencher    3-Aleatório       4-Imprimir\n"
menu2:	.asciiz	"  Operações: 5-Somatório    6-Média        7-Mínimos locais  8-Inverter\n"
menu3:	.asciiz	"                                                             0-Terminar\n"
menu4:	.asciiz	"Introduza a sua opção: "
#==========================================================================================

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
askN:	.asciiz	"Introduza o número de elementos da sequência: "
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
strB:	.asciiz "º elemento da sequência = "
	.text
fill:   la   $t2, array
	la   $t0, N
	lw   $t0, ($t0)
	li   $t1, 0
fill2:  beq  $t0, $t1, fill1
	addi $t1, $t1, 1
	li   $v0, 1
	move $a0, $t1
	syscall

	li   $v0, 4
	la   $a0, strB
	syscall

	li   $v0, 5
	syscall
	sw   $v0, ($t2)

	addi $t2, $t2, 4

	j    fill2

fill1:  jr   $ra

#---------------------------------------------------------------------

rnd:    la  $t2, array
	la  $t0, N
	lw  $t0, ($t0)
	li  $t1, 0

rnd2:   beq $t0, $t1, rnd1
	li  $v0, 42
	li  $a0, 0
	li  $a1, 100
	syscall

	sw  $a0, ($t2)

	addi $t2, $t2, 4
	addi $t1, $t1, 1

	j    rnd2

rnd1:   jr   $ra

#---------------------------------------------------------------------
	.data
strA:	.asciiz "Sequência = "
	.text
print:  li  $v0, 4
	la  $a0, strA
	syscall

	la  $t2, array

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
errStr:	.asciiz "Opção inválida!\n"
	.text
err:    li  $v0, 4
	la  $a0, errStr
	syscall

	jr  $ra

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
# minL - determina o número de mínimos locais de uma sequência
#
# Argumentos:
#	$a0 - dimensão da sequência
#	$a1 - endereço base da sequência
# Valor retornado
#	$v0 - número de mínimos locais
#---------------------------------------------------------------------

minL:
    addi $t0, $a1, 4 # $t0: iterator (excluding first)
    addi $t1, $a0, -2 # $t1: counter (excluding first and second)
    xor $v0, $v0, $v0
minL_loop:
    beqz $t1, minL_end
    lw $t2,   ($t0) # $t2: Current value
    lw $t3, -4($t0) # $t3: Prev value
    lw $t4,  4($t0) # $t4: Next value
    slt $t3, $t2, $t3 # curr < prev?
    slt $t4, $t2, $t4 # curr < next?
    and $t3, $t3, $t4
    beqz $t3, minL_next
    addi $v0, $v0, 1
minL_next:
    addi $t0, $t0, 4
    addi $t1, $t1, -1
    j minL_loop
minL_end:
    jr $ra


#---------------------------------------------------------------------
# inv - inverte a ordem dos elementos de uma sequência
#
# Argumentos:
#	$a0 - dimensão da sequência
#	$a1 - endereço base da sequência
# Valor retornado
#	nenhum (após a operação, $a1 tem o endereço base da sequência modificada)
#---------------------------------------------------------------------

inv:
    move $t0, $a1 # $t0: head
    sll $t1, $a0, 2
    add $t1, $t1, $t0
    addi $t1, $t1, -4 # $t1: tail
inv_loop: bge $t0, $t1, inv_end
    lw $t2, ($t0)
    lw $t3, ($t1)
    sw $t2, ($t1)
    sw $t3, ($t0)
    addi $t0, $t0, 4
    addi $t1, $t1, -4
    j inv_loop
inv_end: jr $ra

#---------------------------------------------------------------------
