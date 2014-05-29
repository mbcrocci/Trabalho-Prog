//
//  main.c
//  Trabalho de Programacao
//
//  Created by Maurizio Crocci on 29/05/14.
//
//


#include <stdio.h>

#define MIN_LIN 8
#define MAX_LIN 15

#define MIN_COL 15
#define MAX_COL 30

struct pessa {
    char posicao[2];
    int satisfeito;
};

int main()
{
    /* 
        CONFIGURCOES (esta tudo comentado para testar mais facilmente)
     */
    
    int lin=0, col=0;
    /*
    while ( lin < 8 || 15 < lin || col < 15 || 30 < col)
    {
        printf("Introduza as dimesoes do ambiente: ");
        scanf("%d %d", &lin, &col);
    }
    */
    
    lin = 8; col =15;
    int quadro[lin][col];
    
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
    
    int fronteira = 1 // desenvolver a toroidal depois
    
    // satisfacao ...
    
    int tipo_desloc = 1 // pedir ao utilizador depois
    
    int num_iter = 10 // pedir ao utilizador depois
    
    
    
    
    
    
    
    return 0;
}