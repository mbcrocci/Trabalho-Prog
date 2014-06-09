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
        {
            /*if (quadro[y][x] == 1)
                printf("| X |");

            else if (quadro[y][x] == 2)
                printf("| O |");

            else if (quadro[y][x] == 0)
                printf("|   |");
            */
            printf("| %d |", quadro[y][x]);
        }
            
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


int menu_simul()
{
    int i = 0;
    do {
        linha();
        printf("1 - Modificar limite de satisfacao\n");
        printf("2 - Modificar tipo de vizinhanca\n");
        printf("3 - Modificar tipo de deslocamento\n");
        printf("4 - Continuar simulacao\n");
        printf("5 - Terminar a simulacao e guardar dados para continuar depois\n");
        printf("6 - Terminar Simulacao\n");
        printf("Escolha uma Opcao: "); scanf("%d", &i);
    } while (i < 1 || 6 < i);
    return i;
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

void simul(Configuracoes C, int PrimVez, int passo) {
	int **quadro;
	int erro = 0, i, j, x, y, p, m, iter, nlin, ncol, satis;
    int num_peca_ins_X = 0, num_peca_ins_O = 0, num_peca_ins_H = 0;
    int num_desloc_X = 0, num_desloc_O = 0, num_desloc_H = 0;

    ppeca_ins lista = NULL; // guarda as pecas instisfeitas
    FILE *rel = fopen("rel.txt", "w");

    if (rel == NULL) printf("Impossivel criar relatorio");

	if (PrimVez == 1){	// ConfiguraÁıes STANDARD (se ainda nao tiver sido escolhido uma configuraÁ„o)
		C = inicializ();
		C = Standard(&erro);
		if (erro == 1)
			return;
	}

    nlin = C.DimGrid[0]; ncol = C.DimGrid[1];
    mostra(C);

	// Criar quadro com base nas configs
    quadro = malloc(nlin * sizeof(int *));
    if (quadro == NULL)
    {
        printf("Nao ha memoria para o quadro");
        exit(0);
    }

    for (i = 0; i < nlin; i++)
    {
        quadro[i] = malloc(ncol * sizeof(int));
        if (quadro[i] == NULL)
        {
            printf("Nao ha memoria para o quadro");
            exit(1);
        }
    } 

    // preencher quandro aleatoriamente
    for (j = 1; j <= C.NPop; j++) // por cada tipo de populacao
    {
        for (i = 0; i < C.DimPop; i++) // percorrer a dimensao da populacao
        {
            do {
                y = numero_random(0, nlin-1);
                x = numero_random(0, ncol-1);
            } while ((quadro[y])[x] != 0);
            (quadro[y])[x] = j;
        }
    }

    // Configuracao para relatorio
    fprintf(rel, "CONFIGURACOES\n");
    fprintf(rel, "DIM: %d %d\n", C.DimGrid[0], C.DimGrid[1]);
    fprintf(rel, "POPS: %d\n", C.NPop);
    fprintf(rel, "DIM_POP: %d\n", C.DimPop);
    fprintf(rel, "VIZ: %d\n", C.TipoViz);
    fprintf(rel, "FRONTEIRA: %d\n", C.TipoFront);
    if (C.NPop == 2)
        fprintf(rel, "K: %2.0f %2.0f\n", C.PercSatisf[0], C.PercSatisf[1]);
    else
        fprintf(rel, "K: %2.0f %2.0f %2.0f\n", C.PercSatisf[0], C.PercSatisf[1], C.PercSatisf[2]);
    fprintf(rel, "MOVE: %d\n", C.Desloc);
    fprintf(rel, "NUM_ITER: %d\n\n\n", C.NIter);


    for (iter = 0; iter < C.NIter; iter++) // iteracoes
    {
        // por tudo sobre numero de satisfeitos ou delocamentos a zero para nova iteracao
        num_peca_ins_X = 0; num_peca_ins_O = 0; num_peca_ins_H = 0;
        num_desloc_X = 0; num_desloc_O = 0; num_desloc_H = 0;
        if (passo == 1)
        {
            m = menu_simul();
            fprintf(rel, "Alteracoes:\n");
            if (m == 1)
            {
                if (C.NPop == 2)
                {
                    printf("Novo limite de satisfacao para populacao X: ");
                    scanf("%f", &(C.PercSatisf[0]));

                    printf("Novo limite de satisfacao para populacao O: ");
                    scanf("%f", &(C.PercSatisf[1]));

                    fprintf(rel, "Novo limite de satisfacao populacao X: %f\n", C.PercSatisf[0]);
                    fprintf(rel, "Novo limite de satisfacao populacao O: %f\n", C.PercSatisf[1]);
                }
                else if (C.NPop == 3)
                {
                    printf("Novo limite de satisfacao para populacao 1: ");
                    scanf("%f", &(C.PercSatisf[0]));

                    printf("Novo limite de satisfacao para populacao 2: ");
                    scanf("%f", &(C.PercSatisf[1]));

                    printf("Novo limite de satisfacao para populacao 3: ");
                    scanf("%f", &(C.PercSatisf[2]));

                    fprintf(rel, "Novo limite de satisfacao populacao X: %f\n", C.PercSatisf[0]);
                    fprintf(rel, "Novo limite de satisfacao populacao O: %f\n", C.PercSatisf[1]);
                    fprintf(rel, "Novo limite de satisfacao populacao H: %f\n", C.PercSatisf[2]);
                }
            }
            else if (m == 2)
            {
                do {
                    printf("Tipo de vizinhanca (1:Von Neumann; 2:Moore): ");
                    scanf(" %d", &(C.TipoViz));
                } while (C.TipoViz<1 || C.TipoViz>2);
                fprintf(rel, "Novo tipo de vizinhanca: %d\n", C.TipoViz);     
            }
            else if (m == 3)
            {
                do{
                    printf("Deslocamento dos agentes (1:celula mais proxima; 2:aleatorio): ");
                    scanf(" %d", &(C.Desloc));
                } while (C.TipoViz<1 || C.TipoViz>2);
                fprintf(rel, "Novo tipo de deslocamento: %d\n", C.Desloc);
            }
            else if (m == 5)
            {
                break;
            }
        }

        if (passo == 0) espera(1); // sequencial 
        mostrar_quadro(nlin, ncol, quadro);

        for (y = 0; y < nlin; y++)
        {
            for (x = 0; x < ncol; x++)
            {
                if ((quadro[y])[x] > 0) // se existir uma peca
                {
                    // Diferentes tipos de vizinhanca e fronteira
                    p = (quadro[y])[x];
                    if (C.TipoViz == 1 && C.TipoFront == 1)
                        satis = viz_neuman_fech(x, y, nlin-1, ncol-1, C.PercSatisf[quadro[y][x]-1], quadro);

                    else if (C.TipoViz == 1 && C.TipoFront == 2)
                        satis = viz_neuman_tor(x, y, nlin-1, ncol-1, C.PercSatisf[quadro[y][x]-1], quadro);

                    else if (C.TipoViz == 2 && C.TipoFront == 1)
                        satis = viz_moore_fech(x, y, nlin-1, ncol-1, C.PercSatisf[quadro[y][x]-1], quadro);

                    else if (C.TipoViz == 2 && C.TipoFront == 2)
                        satis = viz_moore_tor(x, y, nlin-1, ncol-1, C.PercSatisf[quadro[y][x]-1], quadro);

                    if (satis == 0) // nao estiver satisfeito
                    {
                        lista = adiciona_peca(lista, x, y, quadro[y][x]);
                        if (quadro[y][x] == 1)
                            num_peca_ins_X++;

                        if (quadro[y][x] == 2)
                            num_peca_ins_O++;

                        if (quadro[y][x] == 3)
                            num_peca_ins_H++;
                    }
                }
            }
        }

        fprintf(rel, "\n\nIteracao %d:\n", iter+1);
        fprintf(rel, "Percentagem de pecas X instisfeitas: %f\n", (num_peca_ins_X * 100.0) / C.DimPop);
        fprintf(rel, "Percentagem de pecas O instisfeitas: %f\n", (num_peca_ins_O * 100.0) / C.DimPop);
        if (C.NPop == 3)
            fprintf(rel, "Percentagem de pecas H instisfeitas: %f\n", (num_peca_ins_H * 100.0) / C.DimPop);

        fprintf(rel, "\n\n\n");

        // Se ja nao houver pessas instisfeitas
        if (num_peca_ins_X == 0 && num_peca_ins_O == 0 && num_peca_ins_H == 0)
        {
            printf("Ja nao existem pessas instisfeitas!\n");
            break;
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
            
            if (C.Desloc == 1)
            {
                while (lista -> prox != NULL)
                {
                    (quadro[lista->y])[lista->x] = 0; // por o lugar da peca instisfeita vazio

                    // ver todos os lugares a volta da peca, no sentido horario
                    // O primeiro lugar que encontrar e onde mete a peca guardada na lista

                    if (lista->y == 0) // primeira linha
                    {
                        if (lista->x == 0) // primeira peca
                        {
                            if ((quadro[lista->y])[(lista->x)+1] == 0)
                                (quadro[lista->y])[(lista->x)+1] = lista->p; 

                            else if ((quadro[(lista->y)+1])[(lista->x)+1] == 0 )
                                (quadro[(lista->y)+1])[(lista->x)+1] = lista->p;

                            else if ((quadro[(lista->y)+1])[lista->x] == 0 )
                                (quadro[(lista->y)+1])[(lista->x)] = lista->p;
                        }
                        
                        else if (lista -> x == ncol - 1) // ultima peca da primeira linha
                        {
                            if ((quadro[(lista->y)+1])[(lista->x)] == 0)
                                (quadro[(lista->y)+1])[(lista->x)]  = lista->p;

                            else if ((quadro[(lista->y)+1])[(lista->x)-1] == 0 )
                                (quadro[(lista->y)+1])[(lista->x)-1] = lista->p;

                            else if ((quadro[(lista->y)])[(lista->x)-1] == 0 )
                                (quadro[(lista->y)])[(lista->x)-1] = lista->p;
                        }
                        
                        else
                        {
                            if ((quadro[(lista->y)])[(lista->x)+1] == 0 )
                                (quadro[(lista->y)])[(lista->x)+1] = lista->p;

                            else if ((quadro[(lista->y)+1])[(lista->x)+1] == 0 )
                                (quadro[(lista->y)+1])[(lista->x)+1] = lista->p;

                            else if ((quadro[(lista->y)+1])[(lista->x)] == 0 )
                                (quadro[(lista->y)+1])[(lista->x)] = lista->p;

                            else if ((quadro[(lista->y)+1])[(lista->x)-1] == 0 )
                                (quadro[(lista->y)+1])[(lista->x)-1] = lista->p;

                            else if ((quadro[(lista->y)])[(lista->x)-1] == 0 )
                                (quadro[(lista->y)])[(lista->x)-1] = lista->p;
                        }
                    }
                    
                    else if (lista -> y == nlin - 1) // ultima linha
                    {
                        if (lista -> x == 0) // primeira peca
                        {
                            if ((quadro[(lista->y)])[(lista->x)+1] == 0 )
                                (quadro[(lista->y)])[(lista->x)+1] = lista -> p;

                            else if ((quadro[(lista->y)-1])[(lista->x)] == 0 )
                                (quadro[(lista->y)-1])[(lista->x)] = lista -> p;

                            else if ((quadro[(lista->y)-1])[(lista->x)+1] == 0 )
                                (quadro[(lista->y)-1])[(lista->x)+1] = lista -> p;
                        }
                        
                        else if (lista -> x == ncol - 1) // ultima peca
                        {
                            if ((quadro[(lista->y)])[(lista->x)-1] == 0 )
                                (quadro[(lista->y)])[(lista->x)-1] = lista -> p;

                            else if ((quadro[(lista->y)-1])[(lista->x)-1] == 0 )
                                (quadro[(lista->y)-1])[(lista->x)-1] = lista -> p;

                            else if ((quadro[(lista->y)-1])[(lista->x)] == 0 )
                                (quadro[(lista->y)-1])[(lista->x)] = lista -> p;
                        }
                        
                        else
                        {
                            if ((quadro[(lista->y)])[(lista->x)+1] == 0 )
                                (quadro[(lista->y)])[(lista->x)+1] = lista -> p;

                            else if ((quadro[(lista->y)])[(lista->x)-1] == 0 )
                                (quadro[(lista->y)])[(lista->x)-1] = lista -> p;

                            else if ((quadro[(lista->y)-1])[(lista->x)-1] == 0 )
                                (quadro[(lista->y)-1])[(lista->x)-1] = lista -> p;

                            else if ((quadro[(lista->y)-1])[(lista->x)] == 0 )
                                (quadro[(lista->y)-1])[(lista->x)] = lista -> p;

                            else if ((quadro[(lista->y)-1])[(lista->x)+1] == 0)
                                (quadro[(lista->y)-1])[(lista->x)+1] = lista -> p;
                        }
                    }
                    else if (lista -> x == 0) // primeira coluna
                    {
                        if ((quadro[(lista->y)])[(lista->x)+1] == 0 )
                            (quadro[(lista->y)])[(lista->x)+1]  = lista -> p;

                        else if ((quadro[(lista->y)+1])[(lista->x)+1] == 0 )
                            (quadro[(lista->y)+1])[(lista->x)+1] = lista -> p;

                        else if ((quadro[(lista->y)+1])[(lista->x)] == 0 )
                            (quadro[(lista->y)+1])[(lista->x)] = lista -> p;

                        else if ((quadro[(lista->y)-1])[(lista->x)] == 0 )
                            (quadro[(lista->y)-1])[(lista->x)] = lista -> p;

                        else if ((quadro[(lista->y)-1])[(lista->x)+1] == 0)
                            (quadro[(lista->y)-1])[(lista->x)+1] = lista -> p;
                    }
                    
                    else if (lista -> x == ncol - 1) // ultima coluna
                    {
                        if ((quadro[(lista->y)+1])[(lista->x)] == 0 )
                            (quadro[(lista->y)+1])[(lista->x)] = lista -> p;

                        else if ((quadro[(lista->y)+1])[(lista->x)-1] == 0 )
                            (quadro[(lista->y)+1])[(lista->x)-1] = lista -> p;

                        else if ((quadro[(lista->y)])[(lista->x)-1] == 0 )
                            (quadro[(lista->y)])[(lista->x)-1] = lista -> p;

                        else if ((quadro[(lista->y)-1])[(lista->x)-1] == 0 )
                            (quadro[(lista->y)-1])[(lista->x)-1] = lista -> p;

                        else if ((quadro[(lista->y)-1])[(lista->x)] == 0)
                            (quadro[(lista->y)-1])[(lista->x)] = lista -> p;
                    }
                    
                    else // resto das pecas
                    {
                        if ((quadro[(lista->y)])[(lista->x)+1] == 0 )
                            (quadro[(lista->y)])[(lista->x)+1] = lista -> p;

                        else if ((quadro[(lista->y)+1])[(lista->x)+1] == 0 )
                            (quadro[(lista->y)+1])[(lista->x)+1] = lista -> p;

                        else if ((quadro[(lista->y)+1])[(lista->x)] == 0 )
                            (quadro[(lista->y)+1])[(lista->x)] = lista -> p;

                        else if ((quadro[(lista->y)+1])[(lista->x)-1] == 0 )
                            (quadro[(lista->y)+1])[(lista->x)-1] = p;

                        else if ((quadro[(lista->y)])[(lista->x)-1] == 0 )
                            (quadro[(lista->y)])[(lista->x)-1] = lista -> p;

                        else if ((quadro[(lista->y)-1])[(lista->x)-1] == 0 )
                            (quadro[(lista->y)-1])[(lista->x)-1] = lista -> p;

                        else if ((quadro[(lista->y)-1])[(lista->x)] == 0 )
                            (quadro[(lista->y)-1])[(lista->x)] = lista -> p;

                        else if ((quadro[(lista->y)-1])[(lista->x)+1] == 0)
                            (quadro[(lista->y)-1])[(lista->x)+1] = lista -> p;
                    }
                    // aumentar o numero de deslocamentos para cada tipo de peca
                    if (lista -> p == 1)
                        num_desloc_X++;

                    else if (lista -> p == 2)
                        num_desloc_O++;

                    else if (lista -> p == 3)
                        num_desloc_H++;

                    lista = lista -> prox;
                }
            }
            else if (C.Desloc == 2) // movimento aleatorio
            {
                while (lista -> prox != NULL)
                {
                    (quadro[lista->y])[lista->x] = 0;
                    do { 
                        y = numero_random(0, nlin-1);
                        x = numero_random(0, ncol-1);
                    } while ((quadro[y])[x] != 0);
                    (quadro[y])[x] = lista->p;

                    if (lista -> p == 1)
                        num_desloc_X++;

                    else if (lista -> p == 2)
                        num_desloc_O++;

                    else if (lista -> p == 3)
                        num_desloc_H++;

                    lista = lista -> prox;
                }
            }
        }
        fprintf(rel, "Deslocamentos:\n");
        fprintf(rel, "Numero de deslocamentos pecas X: %d\n", num_desloc_X);
        fprintf(rel, "Numero de deslocamentos pecas O: %d\n", num_desloc_O);

        if (C.NPop == 3)
            fprintf(rel, "Numero de deslocamentos pecas H:\n");
    } // fim do loop iteracao
 

	// free tudo o que for alocado
	for (i = 0; i < nlin; i++)
    	free(quadro[i]);
	free(quadro);
    free(lista);
    fclose(rel);
}