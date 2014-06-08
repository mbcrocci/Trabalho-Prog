#define _CRT_SECURE_NO_WARNINGS
//#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "simulacao.h"
#include "config.h"
#include "quadro.h"
#include "random.h"
#include "viz.h"

void espera(int seg) // Funcao fornecida no enunciado
{
    time_t inicio = time(NULL);
    long int i;
    do{
        for(i=0; i<100000; i++)
            ;
    }while(difftime(time(NULL), inicio) < seg);
}

Configuracoes Standard(int *falha){
	Configuracoes Conf;
	int erro = 0, FirstTime = 1;
	char resp;
	Conf = Read_Config("config1.txt", &erro);
	if (erro == 1){
		puts("\nErro ao definir configuracoes standard!");
		printf("Quer definir outras configuraÁoes? (s, n): ");
		scanf(" %c", &resp);
		if (resp == 's' || resp == 'S')
			Conf = config(&FirstTime);
		else
			*falha = erro;
	}
	return Conf;
}

void simul(Configuracoes C, int *PrimVez){
	int **quadro;
	int erro = 0, i, j, x, y, p, iter;
	int satis;
    FILE *f;
    f = fopen("pos.txt", "w"); // para poder ler os que estao satisfeitos
	if (*PrimVez == 1){	// ConfiguraÁıes STANDARD (se ainda nao tiver sido escolhido uma configuraÁ„o)
		C = inicializ();
		C = Standard(&erro);
		if (erro == 1)
			return;
	}

	// Criar quadro com base nas configs
    quadro = malloc(C.DimGrid[1] * sizeof(int *));
    if (quadro == NULL)
    {
        printf("Nao ha memoria para o quadro");
        exit(0);
    }
    printf("Array de ponteiros criado\n" ); // remover linha
    for (i = 0; i < C.DimGrid[1]; i++)
    {
        quadro[i] = malloc(C.DimGrid[1] * sizeof(int));
        if (quadro[i] == NULL)
        {
            printf("Nao ha memoria para o quadro");
            exit(1);
        }
    }
    printf("resto de arrays criados\n"); // remover linha

    //preencher_quandro( lin, col, 40, 2, quadro);
    for (j = 1; j <= C.NPop; j++)
    {
        for (i = 0; i < C.DimPop; i++)
        {
            quadro[0][0] = 4;
            quadro[0][1] = 5;
            quadro[1][0] = 6;
            do {
                x = numero_random(0, C.DimGrid[0]-1);
                y = numero_random(0, C.DimGrid[1]-1);
            } while ((quadro[x])[y] != 0);
            (quadro[x])[y] = j;
        }
    }

    for (iter = 0; iter < C.NIter; iter++) // iteracoes especificadas na configuracao
    {
        mostrar_quadro(C.DimGrid[0], C.DimGrid[1], quadro);

        // #pragma omp parallel for
        for (i = 0; i < C.DimGrid[0]; i++)
        {
            for (j = 0; j < C.DimGrid[1]; j++)
            {
                if ((quadro[i])[j] > 0) // se existir uma peca
                {
                    p = (quadro[i])[j];
                    if (C.TipoViz == 1 && C.TipoFront == 1)
                        satis = viz_neuman_fech(i, j, C.DimGrid[0]-1, C.DimGrid[1]-1, C.PercSatisf[p-1], quadro);

                    else if (C.TipoViz == 1 && C.TipoFront == 2)
                        satis = viz_neuman_tor(i, j, C.DimGrid[0], C.DimGrid[1], C.PercSatisf[p-1], quadro);

                    else if (C.TipoViz == 2 && C.TipoFront == 1)
                        satis = viz_moore_fech(i, j, C.DimGrid[0], C.DimGrid[1], C.PercSatisf[p-1], quadro);

                    else if (C.TipoViz == 2 && C.TipoFront == 2)
                        satis = viz_moore_tor(i, j, C.DimGrid[0], C.DimGrid[1], C.PercSatisf[p-1], quadro);

                    printf("Peca na posicao: (%d,%d) -> satisfacao: %d\n", i,j, satis);

                    /*if (satis == 0) // nao estiver satisfeito
                    {
                        (quadro[i])[j] = 0;
                        if (C.Desloc == 1)
                        {
                            continue;
                        }

                        else if (C.Desloc == 2)
                        {
                            do { // movimento aleatorio
                                x = numero_random(0, C.DimGrid[0]-1);
                                y = numero_random(0, C.DimGrid[1]-1);
                            } while ((quadro[x])[y] != 0);
                            (quadro[x])[y] = p;
                        }
                    }*/
                }
            }
            espera(1);
        }

    }
 
	// free arrays
	for (i = 0; i < C.DimGrid[0]; i++)
    	free(quadro[i]);
	free(quadro);
}

int menu_simul()
{
    int i;
    do {
        printf("1 - Modificar limite de satisfacao");
        printf("2 - Modificar tipo de vizinhanca");
        printf("3 - Modificar tipo de deslocamento");
        printf("4 - Continuar simulacao");
    } while (i < 1 || i > 4);
    return i;
}

void simul_passo(Configuracoes C, int *PrimVez)
{
    int **quadro;
    int erro = 0, i, j, x, y, p, iter;
    int satis;
    if (*PrimVez == 1){ // ConfiguraÁıes STANDARD (se ainda nao tiver sido escolhido uma configuraÁ„o)
        C = inicializ();
        C = Standard(&erro);
        if (erro == 1)
            return;
    }

    // Criar quadro com base nas configs
    quadro = malloc(C.DimGrid[0] * sizeof(int *));
    if (quadro == NULL)
    {
        printf("Nao ha memoria para o quadro");
        exit(0);
    }
    printf("Array de ponteiros criado\n" ); // remover linha
    for (i = 0; i < C.DimGrid[0]; i++)
    {
        quadro[i] = malloc(C.DimGrid[1] * sizeof(int));
        if (quadro[i] == NULL)
        {
            printf("Nao ha memoria para o quadro");
            exit(1);
        }
    }
    printf("resto de arrays criados\n"); // remover linha

    //preencher_quandro( lin, col, 40, 2, quadro);
    for (j = 1; j <= C.NPop; j++)
    {
        for (i = 0; i < C.DimPop; i++)
        {
            do 
            {
                x = numero_random(0, C.DimGrid[0]-1);
                y = numero_random(0, C.DimGrid[1]-1);
            } while ((quadro[x])[y] != 0);
            (quadro[x])[y] = j;
        }
    }

    mostrar_quadro(C.DimGrid[0], C.DimGrid[1], quadro);


    for (iter = 0; iter < C.NIter; iter ++) // iteracoes especificadas na configuracao
    {

        for (i = 0; i < C.DimGrid[0]; i++)
        {
            for (j = 0; j < C.DimGrid[1]; j++)
            {
                if ((quadro[i])[j] > 0) // se existir uma peca
                {
                    p = (quadro[i])[j]; // p vai ser igual a 1, 2 ou 3 consoante a pessa;
                    if (C.TipoViz == 1 && C.TipoFront == 1)
                        satis = viz_neuman_fech(i, j, C.DimGrid[0], C.DimGrid[1], C.PercSatisf[p-1], quadro);

                    else if (C.TipoViz == 1 && C.TipoFront == 2)
                        satis = viz_neuman_tor(i, j, C.DimGrid[0], C.DimGrid[1], C.PercSatisf[p-1], quadro);

                    else if (C.TipoViz == 2 && C.TipoFront == 1)
                        satis = viz_moore_fech(i, j, C.DimGrid[0], C.DimGrid[1], C.PercSatisf[p-1], quadro);

                    else if (C.TipoViz == 2 && C.TipoFront == 2)
                        satis = viz_moore_tor(i, j, C.DimGrid[0], C.DimGrid[1], C.PercSatisf[p-1], quadro);

                    printf("Pessa na posicao: (%d,%d) -> satisfacao: %d\n", i,j, satis);

                    if (satis == 0) // nao estiver satisfeito
                    {
                        (quadro[i])[j] = 0;
                        do // movimento aleatorio
                        {
                            x = numero_random(0, C.DimGrid[0]-1);
                            y = numero_random(0, C.DimGrid[1]-1);
                        } while ((quadro[x])[y] != 0);
                        (quadro[x])[y] = p; 
                    }
                }
            }
        }

    }
 
    // free arrays
    for (i = 0; i < C.DimGrid[0]; i++)
        free(quadro[i]);
    free(quadro);    
}
