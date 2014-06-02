//
//  main.c
//  Trabalho de Programacao
//
//  Created by Maurizio Crocci on 29/05/14.
//
//


#include <stdio.h>
// #include "random.c" usar algumas das funcoes para gerar as posicoes da peca

struct pessa { // nao sei se vai ser preciso
    char posicao[2];
    int satisfeito;
};

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

    int quadro[lin][col];
    // encher o quadro de zeros
    for (i = 0; i < col; i++) {
        for (j = 0; j < lin; j++) {
            if (i == 5 && j == 7)
                quadro[i][j] = 1;
            
            else
                quadro[i][j] = 0;
        }
    }
    
    int num_pops=2;
    /*
    printf("Introduza o numro de populacoes (2 ou 3): ");
    scanf(" %d", &num_pops);
    */
    
    int tipo_viz = 1;
    /*
     printf("Introduzao o tipo de vizinhaca (1 ou 2): ");
     scanf(" %d", *tipo_viz);
     */
    
    int fronteira = 1; // desenvolver a toroidal depois
    
    // satisfacao ...
    
    int tipo_desloc = 1;// pedir ao utilizador depois
    
    int num_iter = 10;// pedir ao utilizador depois
    
    

    // 1 iteracao do quadro
    for (i = 0; i < col; i++)
    {
        for (j = 1; j < lin; j++)
        {
            satis = vizinhancas(i, j, lin, col, quadro);
            printf("Pessa na posicao: (%d,%d) -> satisfacao: %d", i,j, satis);
        }
    }
    
    
    
    
    
    
    
    return 0;
}