#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "simulacao.h"
#include "config.h"
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

void mostrar_quadro (int nlin, int ncol, int **quadro)
{
    int x, y;
    for (y = 0; y < nlin; y++)
    {
        for (x = 0; x < ncol; x++)
            printf("| %d |", quadro[y][x]);
            
        printf("\n");
    }
    puts("\n");
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
ppeca_ins adiciona_peca (ppeca_ins lista, int x, int y, int p)
{
    ppeca_ins aux = lista;
    ppeca_ins novo = malloc(sizeof(peca_ins));
    if (novo == NULL)
    {
        printf("Erro ao reservar memoria\n");
        return lista;
    }
    novo->x = x; novo->y = y; novo->p = p;
    novo->prox = NULL;
    if (lista == NULL) return novo;
    while (aux->prox)
        aux = aux -> prox;

    aux ->prox = novo;
    return lista;
}
void mostra_lista (ppeca_ins lista)
{
    while(lista)
    {
        printf("Peca: %d : (%d,%d)\n", lista->p, lista->x, lista->y);
        lista = lista -> prox;
    }
}

void simul(Configuracoes C, int PrimVez){
	int **quadro;
	int erro = 0, i, j, x, y, p, iter,nlin, ncol;
	int satis;
    ppeca_ins lista = NULL; // guarda as pecas instisfeitas

    //FILE *f;
    //f = fopen("pos.txt", "w"); // para poder ler os que estao satisfeitos
	if (PrimVez == 1){	// ConfiguraÁıes STANDARD (se ainda nao tiver sido escolhido uma configuraÁ„o)
		C = inicializ();
		C = Standard(&erro);
		if (erro == 1)
			return;
	}

    nlin = C.DimGrid[0]; ncol = C.DimGrid[1];

	// Criar quadro com base nas configs
    quadro = malloc(nlin * sizeof(int *));
    if (quadro == NULL)
    {
        printf("Nao ha memoria para o quadro");
        exit(0);
    }
    printf("Array de ponteiros criado\n" ); // remover linha
    for (i = 0; i < nlin; i++)
    {
        quadro[i] = malloc(ncol * sizeof(int));
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
            quadro[0][0] = 4; /// retirar estas linhas depois
            quadro[0][1] = 6;
            quadro[1][0] = 5;
            do {
                y = numero_random(0, nlin-1);
                x = numero_random(0, ncol-1);
            } while ((quadro[y])[x] != 0);
            (quadro[y])[x] = j;
        }
    }

    for (iter = 0; iter < 2/*C.NIter*/; iter++) // iteracoes especificadas na configuracao
    {
        mostrar_quadro(nlin, ncol, quadro);

        for (y = 0; y < nlin; y++)
        {
            for (x = 0; x < ncol; x++)
            {
                if ((quadro[y])[x] > 0) // se existir uma peca
                {
                    p = (quadro[y])[x];
                    if (C.TipoViz == 1 && C.TipoFront == 1)
                        satis = viz_neuman_fech(x, y, nlin-1, ncol-1, C.PercSatisf[p-1], quadro);

                    else if (C.TipoViz == 1 && C.TipoFront == 2)
                        satis = viz_neuman_tor(x, y, C.DimGrid[0], C.DimGrid[1], C.PercSatisf[p-1], quadro);

                    else if (C.TipoViz == 2 && C.TipoFront == 1)
                        satis = viz_moore_fech(x, y, C.DimGrid[0], C.DimGrid[1], C.PercSatisf[p-1], quadro);

                    else if (C.TipoViz == 2 && C.TipoFront == 2)
                        satis = viz_moore_tor(x, y, C.DimGrid[0], C.DimGrid[1], C.PercSatisf[p-1], quadro);

                    printf("Peca %d na posicao: (%d,%d) -> satisfacao: %d\n\n",p , x,y, satis);

                    if (satis == 0) // nao estiver satisfeito
                        lista = adiciona_peca(lista, x, y, p);
                }
            }
        }
        // Mexer as pessas instisfeitas
        if (!lista)
        {
            printf("Nao existem pessas instisfeitas!\n");
            break;
        }
        else
        {
            linha();
            mostra_lista(lista);
            
            while (lista -> prox != NULL)
            {
                (quadro[lista->y])[lista->x] = 0;
                do { // movimento aleatorio
                    y = numero_random(0, nlin-1);
                    x = numero_random(0, ncol-1);
                } while ((quadro[y])[x] != 0);
                (quadro[y])[x] = lista->p;

                lista = lista -> prox;
            }
            free(lista);
            linha();
        }
    }
 
	// free arrays
	for (i = 0; i < nlin; i++)
    	free(quadro[i]);
	free(quadro);
}

int menu_simul()
{
    int i = 0;
    do {
        linha();
        printf("1 - Modificar limite de satisfacao\n");
        printf("2 - Modificar tipo de vizinhanca\n");
        printf("3 - Modificar tipo de deslocamento\n");
        printf("4 - Terminar Simulacao\n");
        printf("5 - Continuar simulacao\n");
        printf("Escolha uma Opcao: "); scanf("%d", &i);
    } while (i < 1 || 5 < i);
    return i;
}

void simul_passo(Configuracoes C, int PrimVez)
{
    int **quadro;
    int erro = 0, i, j, x, y, p, iter, m;
    int satis;
    if (PrimVez == 1){  // Configuracoes STANDARD (se ainda nao tiver sido escolhido uma configuraÁao)
        mostra(C); putchar('\n');
        C = Standard(&erro);
        if (erro == 1)
            return;
    }
    mostra(C); putchar('\n');//

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
            do 
            {
                x = numero_random(0, C.DimGrid[0]-1);
                y = numero_random(0, C.DimGrid[1]-1);
            } while ((quadro[x])[y] != 0);
            (quadro[x])[y] = j;
        }
    }

    for (iter = 0; iter < C.NIter; iter ++) // iteracoes especificadas na configuracao
    {
        m = menu_simul();
        if (m == 1)
        {
            if (C.NPop == 2)
            {
                printf("Novo limite de satisfacao para populacao 1: ");
                scanf("%f", &(C.PercSatisf[0]));

                printf("Novo limite de satisfacao para populacao 2: ");
                scanf("%f", &(C.PercSatisf[1]));
            }
            else if (C.NPop == 3)
            {
                printf("Novo limite de satisfacao para populacao 1: ");
                scanf("%f", &(C.PercSatisf[0]));

                printf("Novo limite de satisfacao para populacao 2: ");
                scanf("%f", &(C.PercSatisf[1]));

                printf("Novo limite de satisfacao para populacao 3: ");
                scanf("%f", &(C.PercSatisf[2]));
            }
        }
        else if (m == 2)
        {
            do {
                printf("Tipo de vizinhanca (1:Von Neumann; 2:Moore): ");
                scanf(" %d", &(C.TipoViz));
            } while (C.TipoViz<1 || C.TipoViz>2);        
        }
        else if (m == 3)
        {
            do{
                printf("Deslocamento dos agentes (1:celula mais proxima; 2:aleatorio): ");
                scanf(" %d", &(C.Desloc));
            } while (C.TipoViz<1 || C.TipoViz>2);
        }
        else if (m == 4)
        {
            break;
        }

        mostrar_quadro(C.DimGrid[0], C.DimGrid[1], quadro);

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
    for (i = 0; i < C.DimGrid[1]; i++)
        free(quadro[i]);
    free(quadro);    
}
