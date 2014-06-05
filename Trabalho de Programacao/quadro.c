// Inicializacao do gerador de numeros aleatorios
// Deve ser chamada apenas uma vez no inicio da execucao do programa
/*
#include <stdlib.h>
#include <time.h>
void init_gerador_random(void)
{
    srand((unsigned)time(NULL));
}

// Devolve um numero inteiro aleatorio entre min e max
int numero_random(int min, int max)
{
    return min + rand() % (max-min+1);
} */

#include <stdio.h>
#include "quadro.h"
#include "random.h"


int check (int x, int y, int **quadro)
{
    if (quadro[x][y] > 0) // se a posicao tiver alguma pessa
        return 0;
    else
        return 1;
}

int vizinhancas (int x, int y, int lin, int col, int **quadro) // E melhor por noutro ficheiro
{
    /* 
     Recebe as coordenadas (x, y) de uma posicao e o quadro mais as suas dimensoes
     Baseado nas coordenadas ve as pessas a volta e decide se esta satisfeita
     Devolve 1 se estiver ou 0 se nao
     */
    
    
    if (y == 0) // primeira linha
    {
        if (x == 0) // primeira pessa
        {
            if (check(x+1, y, quadro)
                + check(x, y+1, quadro)
                + check(x+1, y+1, quadro)
                == 3)
                return 1;
        }
        
        else if (x == lin) // ultima pessa da primeira linha
        {
            if (check(x-1, y, quadro)
                + check(x, y+1, quadro)
                + check(x-1, y+1, quadro)
                == 3)
                return 1;
        }
        
        else
        {
            if (check(x-1, y, quadro)
                + check(x+1, y, quadro)
                + check(x-1, y+1, quadro)
                + check(x, y+1, quadro)
                + check(x+1, y+1, quadro)
                == 5) return 1;
        }
    }
    
    else if (y == lin) // ultima linha
    {
        if (x == 0) // primeira pessa
        {
            if (check(x, y-1, quadro)
                + check(x+1, y-1, quadro)
                + check(x+1, y, quadro)
                == 3) return 1;
        }
        
        else if (x == lin) // ultima pessa
        {
            if (check(x, y-1, quadro)
                + check(x-1, y-1, quadro)
                + check(x-1, y, quadro)
                == 3) return 1;
        }
        
        else
        {
            if (check(x-1, y-1, quadro)
                + check(x, y-1, quadro)
                + check(x+1, y-1, quadro)
                + check(x-1, y, quadro)
                + check(x+1, y, quadro)
                == 5) return 1;
        }
    }
    else if (x == 0) // primeira coluna
    {
        if (check(x, y-1, quadro)
            + check(x+1, y-1, quadro)
            + check(x+1, y, quadro)
            + check(x, y+1, quadro)
            + check(x+1, y+1, quadro)
            == 5) return 1;
    }
    
    else if (x == col) // ultima coluna
    {
        if (check(x, y-1, quadro)
            + check(x-1, y-1, quadro)
            + check(x-1, y, quadro)
            + check(x-1, y+1, quadro)
            + check(x, y+1, quadro)
            == 5) return 1;
    }
    
    else // resto das pessas
    {
        if (check(x-1, y-1, quadro)
            + check(x, y-1, quadro)
            + check(x+1, y+1, quadro)
            + check(x-1, y, quadro)
            + check(x+1, y, quadro)
            + check(x-1, y+1, quadro)
            + check(x, y+1, quadro)
            + check(x+1, y+1, quadro)
            == 8) return 1;
    }
    return 0;
}
void mostrar_quadro (int lin, int col, int **quadro)
{
    int i, j;
    for (i = 0; i < lin; i++)
    {
        for (j = 0; j < col; j++)
            printf("| %d |", quadro[i][j]);
            
        printf("\n");
    }
}

void preencher_quandro(int **quadro, int lin, int col, int dim_pops, int num_pops)
{
    int x, y, i, j, pessa;

    // preencher tudo com zeros que representa sitio vazio
    for (i = 0; i < lin; i++)
        for (j = 0; j < col; j++)
            (quadro[i])[j] = 0;


    for (j = 1; j <= num_pops; j++)
    {
        for (i = 0; i < dim_pops; i++)
        {
            do 
            {
                x = numero_random(0, lin-1);
                y = numero_random(0, col-1);
            } while ((quadro[x])[y] != 0);
            (quadro[x])[y] = j;
        }
    }
}