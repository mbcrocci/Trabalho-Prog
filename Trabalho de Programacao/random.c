//
//  random.c
//  Trabalho de Programacao
//
//  Created by Maurizio Crocci on 02/06/14.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "random.h"

// Inicializacao do gerador de numeros aleatorios
// Deve ser chamada apenas uma vez no inicio da execucao do programa
void init_gerador_random(void)
{
	srand((unsigned)time(NULL));
}


// Devolve um numero inteiro aleatorio entre min e max
int numero_random(int min, int max)
{
	return min + rand() % (max-min+1);
}


// Devolve um numero real aleatorio distribuido uniformemente no intervalo [0, 1]
/* double uniforme_01()
{
	return rand()/(double)RAND_MAX;
}*/