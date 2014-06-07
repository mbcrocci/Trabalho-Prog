#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "simulacao.h"
#include "config.h"
#include "quadro.h"
#include "random.h"
#include "viz.h"

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

void simul(Configuracoes C, int PrimVez){
	int **quadro;
	int erro = 0, i, j, x, y, p;
	int satis;
	if (PrimVez == 1){	// ConfiguraÁıes STANDARD (se ainda nao tiver sido escolhido uma configuraÁ„o)
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
    printf("Array de ponteiros criado\n" );
    for (i = 0; i < C.DimGrid[0]; i++)
    {
        quadro[i] = malloc(C.DimGrid[1] * sizeof(int));
        if (quadro[i] == NULL)
        {
            printf("Nao ha memoria para o quadro");
            exit(1);
        }
    }
    printf("resto de arrays criados\n");

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


    // 1 iteracao do quadro
    for (i = 0; i < C.DimGrid[0]; i++)
    {
        for (j = 1; j < C.DimGrid[1]; j++)
        {
            if ((quadro[i])[j] > 0) // se existir uma peca
            {
                p = (quadro[x])[y];
                if (C.TipoViz == 1 && C.TipoFront == 1)
                    satis = viz_neuman_fech(x, y, C.DimGrid[0], C.DimGrid[1], C.PercSatisf[p-1], quadro);

                else if (C.TipoViz == 1 && C.TipoFront == 2)
                    satis = viz_neuman_tor(x, y, C.DimGrid[0], C.DimGrid[1], C.PercSatisf[p-1], quadro);

                else if (C.TipoViz == 2 && C.TipoFront == 1)
                    satis = viz_moore_fech(x, y, C.DimGrid[0], C.DimGrid[1], C.PercSatisf[p-1], quadro);

                else if (C.TipoViz == 2 && C.TipoFront == 2)
                    satis = viz_moore_tor(x, y, C.DimGrid[0], C.DimGrid[1], C.PercSatisf[p-1], quadro);

                printf("Pessa na posicao: (%d,%d) -> satisfacao: %d\n", i,j, satis);
            }
        }
    }
 
	// free arrays
	for (i = 0; i < C.DimGrid[0]; i++)
    	free(quadro[i]);
	free(quadro);
}
