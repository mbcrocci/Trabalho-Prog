#include <stdio.h>
#include <stdlib.h>
#include "quadro.h"
#include "random.h"

void mostrar_quadro (int lin, int col, int **quadro)
{
    int i, j;
    for (i = 0; i < lin; i++)
    {
        for (j = 0; j < col; j++)
            printf("| %d |", quadro[i][j]);
            
        printf("\n");
    }
    puts("\n");
}

void preencher_quandro(int lin, int col, int dim_pops, int num_pops, int **quadro)
{
    int x, y, i, j, pessa;
    printf("inicio do preencher");

    // preencher tudo com zeros que representa sitio vazio
    for (i = 0; i < col; i++)
        for (j = 0; j < lin; j++)
            quadro[i][j] = 0;

    printf("tudo com zeros\n");
    mostrar_quadro(lin, col, quadro);


    for (j = 1; j <= num_pops; j++)
    {
        for (i = 0; i < dim_pops; i++)
        {
            do 
            {
                x = numero_random(0, lin-1);
                y = numero_random(0, col-1);
                printf("%d, %d", x, y);
            } while ((quadro[x])[y] != 0);
            (quadro[x])[y] = j;
            printf("%d, %d", x, y);
        }
    }
}

void criar_quadro(int **quadro, int lin, int col)
{
    int i;

    quadro = malloc(lin * sizeof(int *));
    if (quadro == NULL)
    {
        printf("Nao ha memoria para o quadro");
        exit(0);
    }
    printf("Array de ponteiros criado\n" );
    for (i = 0; i < lin; i++)
    {
        quadro[i] = malloc(col * sizeof(int));
        if (quadro[i] == NULL)
        {
            printf("Nao ha memoria para o quadro");
            exit(1);
        }
    }
    printf("resto de arrays criados\n");
}