#include "viz.h"
#include <stdio.h>

int check (int x, int y, int **quadro, int p)
{
    printf("checking (%d,%d)\n",x,y);
    if (((quadro[y])[x] == p) || ((quadro[y])[x] == 0)) // se a posicao tiver alguma peca
        return 1;
    else
        return 0;
}

int viz_neuman_fech (int x, int y, int lin, int col, float per, int **quadro)
{
    int p = (quadro[y])[x]; // peca
    if (y == 0) // primeira linha
    {
        if (x == 0) // primeira peca
        {
            printf("primeira pessa\n" );
            if (check(x+1, y, quadro, p)
                + check(x, y+1, quadro, p)
                >= (2 * per)/100) return 1;
        }
        else if (x == col) // ultima peca da primeira linha
        {
            if (check(x-1, y, quadro, p)
                + check(x, y+1, quadro, p)
                >= (2*per)/100) return 1;
        }
        else 
        {
            if (check(x-1, y, quadro, p)
                + check(x+1, y, quadro, p)
                + check(x, y+1, quadro, p)
                >= (3*per)/100) return 1;
        }
    }
    else if (y == lin) // ultima linha
    {
        if (x == 0)
        {
            if (check(x+1, y, quadro, p)
                + check(x, y-1, quadro, p)
                >= (2*per)/100) return 1;
        }
        else if (x == col)
        {
            if (check(x-1, y, quadro, p)
                + check(x, y-1, quadro, p)
                >= (2*per)/100) return 1;
        }
        else
        {
            if(check(x-1, y, quadro, p)
                + check(x+1, y, quadro, p)
                + check(x, y-1, quadro, p)
                >= (3*per)/100) return 1;
        }
    }
    else if (x == 0) // primeira coluna
    {
        if (check(x+1, y, quadro, p)
            + check(x, y-1, quadro, p)
            + check(x, y+1, quadro, p)
            >= (3*per)/100) return 1;
    }
    else if (x == col) // ultima coluna
    {
        if (check(x-1, y, quadro, p)
            + check(x, y-1, quadro, p)
            + check(x, y+1, quadro, p)
            >= (3*per)/100) return 1;
    }
    else 
    {
        if (check(x-1, y, quadro, p)
            + check(x+1, y, quadro, p)
            + check(x, y-1, quadro, p)
            + check(x, y+1, quadro, p)
            >= (4*per)/100) return 1;
    }
    return 0;
}

int viz_moore_fech (int x, int y, int lin, int col, float per, int **quadro)
{
    /* 
     Recebe as coordenadas (x, y) de uma posicao e o quadro mais as suas dimensoes
     Baseado nas coordenadas ve as pecas a volta e decide se esta satisfeita
     Devolve 1 se estiver ou 0 se nao
     */
    int p = (quadro[x])[y]; // peca
    
    if (y == 0) // primeira linha
    {
        if (x == 0) // primeira peca
        {
            if (check(x+1, y, quadro, p)
                + check(x, y+1, quadro, p)
                + check(x+1, y+1, quadro, p)
                >= (3*per)/100)
                return 1;
        }
        
        else if (x == col) // ultima peca da primeira linha
        {
            if (check(x-1, y, quadro, p)
                + check(x, y+1, quadro, p)
                + check(x-1, y+1, quadro, p)
                >= (3*per)/100)
                return 1;
        }
        
        else
        {
            if (check(x-1, y, quadro, p)
                + check(x+1, y, quadro, p)
                + check(x-1, y+1, quadro, p)
                + check(x, y+1, quadro, p)
                + check(x+1, y+1, quadro, p)
                >= (5*per)/100) return 1;
        }
    }
    
    else if (y == lin) // ultima linha
    {
        if (x == 0) // primeira peca
        {
            if (check(x, y-1, quadro, p)
                + check(x+1, y-1, quadro, p)
                + check(x+1, y, quadro, p)
                >= (3*per)/100) return 1;
        }
        
        else if (x == col) // ultima peca
        {
            if (check(x, y-1, quadro, p)
                + check(x-1, y-1, quadro, p)
                + check(x-1, y, quadro, p)
                >= (3*per)/100) return 1;
        }
        
        else
        {
            if (check(x-1, y-1, quadro, p)
                + check(x, y-1, quadro, p)
                + check(x+1, y-1, quadro, p)
                + check(x-1, y, quadro, p)
                + check(x+1, y, quadro, p)
                >= (5*per)/100) return 1;
        }
    }
    else if (x == 0) // primeira coluna
    {
        if (check(x, y-1, quadro, p)
            + check(x+1, y-1, quadro, p)
            + check(x+1, y, quadro, p)
            + check(x, y+1, quadro, p)
            + check(x+1, y+1, quadro, p)
            >= (5*per)/100) return 1;
    }
    
    else if (x == col) // ultima coluna
    {
        if (check(x, y-1, quadro, p)
            + check(x-1, y-1, quadro, p)
            + check(x-1, y, quadro, p)
            + check(x-1, y+1, quadro, p)
            + check(x, y+1, quadro, p)
            >= (5*per)/100) return 1;
    }
    
    else // resto das pecas
    {
        if (check(x-1, y-1, quadro, p)
            + check(x, y-1, quadro, p)
            + check(x+1, y+1, quadro, p)
            + check(x-1, y, quadro, p)
            + check(x+1, y, quadro, p)
            + check(x-1, y+1, quadro, p)
            + check(x, y+1, quadro, p)
            + check(x+1, y+1, quadro, p)
            >= (8*per)/100) return 1;
    }
    return 0;
}

// TOROIDAL


int viz_neuman_tor (int x, int y, int lin, int col, float per, int **quadro)
{
    int p = (quadro[x])[y]; // peca

    if (y == 0) // primeira linha
    {
        if (x == 0) // primeira peca
        {
            if (check(x+1, y, quadro, p)
                + check(x, y+1, quadro, p)
                + check(x+col, y, quadro, p)
                + check(x, y+lin, quadro, p)
                >= (4*per)/100) return 1;
        }
        else if (x == col) // ultima peca da primeira linha
        {
            if (check(x-1, y, quadro, p)
                + check(x, y+1, quadro, p)
                + check(x-col, y, quadro, p)
                + check(x, y+lin, quadro, p)
                >= (4*per)/100) return 1;
        }
        else 
        {
            if (check(x-1, y, quadro, p)
                + check(x+1, y, quadro, p)
                + check(x, y+1, quadro, p)
                + check(x, y+lin, quadro, p)
                >= (4*per)/100) return 1;
        }
    }
    else if (y == lin) // ultima linha
    {
        if (x == 0) // primeira peca 
        {
            if (check(x+1, y, quadro, p)
                + check(x+col, y, quadro, p)
                + check(x, y-1, quadro, p)
                + check(x, y-lin, quadro, p)
                >= (4*per)/100) return 1;
        }
        else if (x == col)
        {
            if (check(x-1, y, quadro, p)
                + check(x-col, y, quadro, p)
                + check(x, y-1, quadro, p)
                + check(x, y-lin, quadro, p)
                >= (4*per)/100) return 1;
        }
        else
        {
            if(check(x-1, y, quadro, p)
                + check(x+1, y, quadro, p)
                + check(x, y-1, quadro, p)
                + check(x, y-lin, quadro, p)
                >= (4*per)/100) return 1;
        }
    }
    else if (x == 0) // primeira coluna
    {
        if (check(x+1, y, quadro, p)
            + check(x+col, y, quadro, p)
            + check(x, y-1, quadro, p)
            + check(x, y+1, quadro, p)
            >= (4*per)/100) return 1;
    }
    else if (x == col) // ultima coluna
    {
        if (check(x-1, y, quadro, p)
            + check(x-col, y, quadro, p)
            + check(x, y-1, quadro, p)
            + check(x, y+1, quadro, p)
            >= (4*per)/100) return 1;
    }
    else 
    {
        if (check(x-1, y, quadro, p)
            + check(x+1, y, quadro, p)
            + check(x, y-1, quadro, p)
            + check(x, y+1, quadro, p)
            >= (4*per)/100) return 1;
    }
    return 0;
}

int viz_moore_tor (int x, int y, int lin, int col, float per, int **quadro)
{
    /* 
     Recebe as coordenadas (x, y) de uma posicao e o quadro mais as suas dimensoes
     Baseado nas coordenadas ve as pecas a volta e decide se esta satisfeita
     Devolve 1 se estiver ou 0 se nao
     */
    
    int p = (quadro[x])[y]; // peca

    if (y == 0) // primeira linha
    {
        if (x == 0) // primeira peca
        {
            if (check(x+1, y, quadro, p)
                + check(x, y+1, quadro, p)
                + check(x+1, y+1, quadro, p)
                + check(x, y+lin, quadro, p)
                + check(x+1, y+lin, quadro, p)
                + check(x+col, y, quadro, p)
                + check(x+col, y+1, quadro, p)
                + check(x+col, y+lin, quadro, p)
              >= (8*per)/100)
                return 1;
        }
        
        else if (x == col) // ultima peca da primeira linha
        {
            if (check(x-1, y, quadro, p)
                + check(x-1, y+1, quadro, p)
                + check(x, y+1, quadro, p)
                + check(x-col, y, quadro, p)
                + check(x-col, y+1, quadro, p)
                + check(x-1, y+lin, quadro, p)
                + check(x, y+lin, quadro, p)
                + check(x-col, y+lin, quadro, p)
              >= (8*per)/100)
                return 1;
        }
        
        else
        {
            if (check(x-1, y, quadro, p)
                + check(x+1, y, quadro, p)
                + check(x-1, y+1, quadro, p)
                + check(x, y+1, quadro, p)
                + check(x+1, y+1, quadro, p)
                + check(x, y+lin, quadro, p)
                + check(x-1, y+lin, quadro, p)
                + check(x+1, y+lin, quadro, p)
              >= (8*per)/100) return 1;
        }
    }
    
    else if (y == lin) // ultima linha
    {
        if (x == 0) // primeira peca
        {
            if (check(x, y-1, quadro, p)
                + check(x+1, y-1, quadro, p)
                + check(x+1, y, quadro, p)
                + check(x+col, y, quadro, p)
                + check(x+col, y-1, quadro, p)
                + check(x, y-lin, quadro, p)
                + check(x+1, y-lin, quadro, p)
                + check(x+col, y-lin, quadro, p)
              >= (8*per)/100) return 1;
        }
        
        else if (x == col) // ultima peca
        {
            if (check(x, y-1, quadro, p)
                + check(x-1, y-1, quadro, p)
                + check(x-1, y, quadro, p)
                + check(x-col, y, quadro, p)
                + check(x-col, y-1, quadro, p)
                + check(x-1, y-lin, quadro, p)
                + check(x, y-lin, quadro, p)
                + check(x-col, y-lin, quadro, p)
              >= (8*per)/100) return 1;
        }
        
        else
        {
            if (check(x-1, y-1, quadro, p)
                + check(x, y-1, quadro, p)
                + check(x+1, y-1, quadro, p)
                + check(x-1, y, quadro, p)
                + check(x+1, y, quadro, p)
                + check(x-1, y-lin, quadro, p)
                + check(x, y-lin, quadro, p)
                + check(x+ 1, y-lin, quadro, p)
              >= (8*per)/100) return 1;
        }
    }
    else if (x == 0) // primeira coluna
    {
        if (check(x, y-1, quadro, p)
            + check(x+1, y-1, quadro, p)
            + check(x+1, y, quadro, p)
            + check(x, y+1, quadro, p)
            + check(x+1, y+1, quadro, p)
            + check(x+col, y-1, quadro, p)
            + check(x+col, y, quadro, p)
            + check(x+col, y+1, quadro, p)
          >= (8*per)/100) return 1;
    }
    
    else if (x == col) // ultima coluna
    {
        if (check(x, y-1, quadro, p)
            + check(x-1, y-1, quadro, p)
            + check(x-1, y, quadro, p)
            + check(x-1, y+1, quadro, p)
            + check(x, y+1, quadro, p)
            + check(x-col, y-1, quadro, p)
            + check(x-col, y, quadro, p)
            + check(x-col, y+1, quadro, p)
          >= (8*per)/100) return 1;
    }
    
    else // resto das pecas
    {
        if (check(x-1, y-1, quadro, p)
            + check(x, y-1, quadro, p)
            + check(x+1, y+1, quadro, p)
            + check(x-1, y, quadro, p)
            + check(x+1, y, quadro, p)
            + check(x-1, y+1, quadro, p)
            + check(x, y+1, quadro, p)
            + check(x+1, y+1, quadro, p)
          >= (8*per)/100) return 1;
    }
    return 0;
}