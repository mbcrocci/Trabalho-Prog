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
double uniforme_01()
{
	return rand()/(double)RAND_MAX;
}



int rmain()
{
	int i;
	
	init_gerador_random();
	
	printf("\nValores inteiros aleatorios entre 10 e 100: ");
	for(i=0; i<10; i++)
		printf("%d\t", numero_random(10, 100));
	
	
	printf("\n\nValores reais entre 0 e 1: ");
	for(i=0; i<10; i++)
		printf("%.3lf\t", uniforme_01());
	printf("\n\n");
	return 0;
	
}