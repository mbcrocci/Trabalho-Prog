//
//  main.c
//  Trabalho de Programacao
//
//  Created by Maurizio Crocci on 29/05/14.
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


int check (int x, int y, int quadro[8][15])
{
    if (quadro[x][y] > 0) // se a posicao tiver alguma pessa
        return 0;
    else
        return 1;
}

int vizinhancas (int x, int y, int lin, int col, int quadro[lin][col]) // E melhor por noutro ficheiro
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
void mostrar_quadro (int lin, int col, int quadro[lin][col])
{
    int i, j;
    for (i = 0; i < lin; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("| %d |", quadro[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    /* 
        CONFIGURCOES (esta tudo comentado para testar mais facilmente)
     */
    int i, j, satis;
    int lin=8, col=15;
    /*
    while ( lin < 8 || 15 < lin || col < 15 || 30 < col) // os numeros sao os limites
    {
        printf("Introduza as dimesoes do ambiente: ");
        scanf("%d %d", &lin, &col);
    }
    */
    
    int num_pops=2; // 2 ou 3
    int tipo_viz = 1; // 1 ou 2
    int fronteira = 1; // desenvolver a toroidal depois
    // satisfacao
    int tipo_desloc = 1;// pedir ao utilizador depois
    int num_iter = 10;// pedir ao utilizador depois
    
    int quadro[lin][col];
    init_gerador_random();
    
    // preencher o quadro (nao verifica as percentagens de pessas)
    for (i = 0; i < lin; i++) {
        for (j = 0; j < col; j++) {
            quadro[i][j] = numero_random(0, 2);
        }
    }
    
    mostrar_quadro(lin, col, quadro);
    
    // 1 iteracao do quadro
    for (i = 0; i < lin; i++)
    {
        for (j = 1; j < col; j++)
        {
            if (quadro[i][j] == 1)
            {
                satis = vizinhancas(i, j, lin, col, quadro);
                printf("Pessa na posicao: (%d,%d) -> satisfacao: %d\n", i,j, satis);
            }
        }
    }
    
    return 0;
}