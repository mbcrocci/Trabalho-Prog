#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "config.h"



void linha()
{
    int i;
    for (i = 0; i < 60; i++)
        putchar('_');
    puts("\n");
}

Configuracoes Read_Config(char nomefic[15], int *erro) //ler configuaraÁoes pre-defindas e presonalizadas nos ficheiros
{
	Configuracoes C;
	FILE *f;
	f = fopen(nomefic, "r");
	if (f!= NULL){
		fscanf(f, " DIM: %d %d", &(C.DimGrid[0]), &(C.DimGrid[1]));//[^DIM:]
		fscanf(f, " POPS: %d", &(C.NPop));//[^POPS:]
		fscanf(f, " DIM_POP: %d", &(C.DimPop));
		fscanf(f, " VIZ: %d", &(C.TipoViz));
		fscanf(f, " FRONTEIRA: %d", &(C.TipoFront));
		C.PercSatisf = malloc(sizeof(float)*C.NPop);	//Se Numero de PopulaÁoes for 2 entao existem 2 percentagens de satisfaÁao
		if (C.NPop == 2)
			fscanf(f, " K: %f %f", &(C.PercSatisf[0]), &(C.PercSatisf[1]));

		else //Se nao... entao existem 3 percentagens fe satisfaÁao
			fscanf(f, " K: %f %f %f", &(C.PercSatisf[0]), &(C.PercSatisf[1]), &(C.PercSatisf[2]));

		fscanf(f, " MOVE: %d", &(C.Desloc));
		fscanf(f, " NUM_ITER: %d", &(C.NIter));
		fclose(f);
	}
	else{
		puts("Erro no acesso ao ficheiro!");
		*erro = 1;
	}
	return C;
}

Configuracoes Choose_Config() //Escolher qual a configuraÁ„o a utilizar na simulaÁ„o 
{
	int r, falha = 0;
	Configuracoes C;
	char rc;
	do{
		linha();
		do{
			printf("Qual e a configuracao que quer utilizar? [1, 2, 3 ou 4(Config. pessoal)]: "); scanf(" %d", &r);
		} while (r<1 || r>4);

		if (r == 1)
			C = Read_Config("config1.txt", &falha);

		else if (r == 2)
			C = Read_Config("config2.txt", &falha);
		
		else if (r == 3)
			C = Read_Config("config3.txt", &falha);

		else 
			C = Read_Config("configpes.txt", &falha);
			
		
		if (falha == 1)
		{
			printf("\nPretende escolher outra configuracao? (s ou n): "); scanf(" %c", &rc);
		}
		else
			rc = 'n';

		falha = 0;
	} while (rc == 's' || rc == 'S');
	return C;
}

void See_Config(Configuracoes C) //Mostrar conteudo dos 3 ficheiros de texto com as configuraÁoes pre-definidas
{
	int v, falha = 0;
	char r;
	do{
		linha();
		do{
			printf("Qual e a configuracao que quer visualizar? [1, 2, 3 ou 4(Config. pessoal)]: "); scanf(" %d", &v);
		} while (v < 1 || v > 4);
		if (v == 1)
		{ 
			C = Read_Config("config1.txt", &falha); 
			if (falha != 1)
				puts("\nConfiguracao 1:");
		}
		else if (v == 2)
		{ 
			C = Read_Config("config2.txt", &falha); 
			if (falha != 1)
				puts("\nConfiguracao 2:");
		}
		else if (v == 3)
		{ 
			C = Read_Config("config3.txt", &falha); 
			if (falha != 1)
				puts("\nConfiguracao 3:");
		}
		else
		{ 
			C = Read_Config("configpes.txt", &falha); 
			if (falha != 1)
				puts("\nConfiguracao Pessoal:");		
		}

		if (falha!=1)
		{
			printf("DIM: %d %d\n", C.DimGrid[0], C.DimGrid[1]);
			printf("POPS: %d\n", C.NPop);
			printf("DIM_POP: %d\n", C.DimPop);
			printf("VIZ: %d\n", C.TipoViz);
			printf("FRONTEIRA: %d\n", C.TipoFront);
			if (C.NPop == 2) 
				printf("K: %f %f\n", C.PercSatisf[0], C.PercSatisf[1]);
			else 
				printf("K: %f %f %f\n", C.PercSatisf[0], C.PercSatisf[1], C.PercSatisf[2]);

			printf("MOVE: %d\n", C.Desloc);
			printf("NUM_ITER: %d\n", C.NIter);
		}
		falha = 0;
		printf("\nPretende visualizar mais alguma configuracao? (s ou n): "); scanf(" %c", &r);
	} while (r == 's' || r == 'S');
}

void Save_Config(Configuracoes C) //guardar configuraÁıes pessoais num novo ficheiro("configpes.txt")
{
	FILE *f;
	if ((f = fopen("configpes.txt", "w")) == NULL)
	{ 
		puts("Erro no acesso ao ficheiro!"); 
		return; 
	}
	else
	{
		fprintf(f, "DIM: %d %d\n", C.DimGrid[0], C.DimGrid[1]);
		fprintf(f, "POPS: %d\n", C.NPop);
		fprintf(f, "DIM_POP: %d\n", C.DimPop);
		fprintf(f, "VIZ: %d\n", C.TipoViz);
		fprintf(f, "FRONTEIRA: %d\n", C.TipoFront);
		if (C.NPop == 2) 
			fprintf(f, "K: %f %f\n", C.PercSatisf[0], C.PercSatisf[1]);
		else 
			fprintf(f, "K: %f %f %f\n", C.PercSatisf[0], C.PercSatisf[1], C.PercSatisf[2]);

		fprintf(f, "MOVE: %d\n", C.Desloc);
		fprintf(f, "NUM_ITER: %d\n", C.NIter);
		fclose(f);
	}
}

Configuracoes Obter_PersonalConfig()
{
	linha();
	char r;
	Configuracoes C;
	//pedir dados das configuraÁıes e preencher estrutura
	do{
		printf("Dimensao do ambiente (Numero_Linhas Numero_Colunas): "); 
		scanf(" %d %d", &(C.DimGrid[0]), &(C.DimGrid[1]));
	} while ((C.DimGrid[0]<MIN_LIN || C.DimGrid[0]>MAX_LIN) 
		|| (C.DimGrid[1]<MIN_COL || C.DimGrid[1]>MAX_COL));

	do{
		printf("Numero de populacoes (2 -(X,0) ou 3 -(X, 0, H)): "); 
		scanf(" %d", &(C.NPop));
	} while (C.NPop<2 || C.NPop>3);

	do{
		printf("Numero de agentes em cada populacao: "); 
		scanf(" %d", &(C.DimPop));	//Deve garantir-se que a percentagem total de cÈlulas ocupadas varia entre 50 % e 70 % do total;
	} while ((C.NPop*C.DimPop*100) / (C.DimGrid[0] * C.DimGrid[1])<PERC_MIN
		|| (C.NPop*C.DimPop*100) / (C.DimGrid[0] * C.DimGrid[1])>PERC_MAX);
	//	(p->NPop * p->DimPop * N100) / (p->DimGrid[Z] * p->DimGrid[N1]) => calcula a percentagem total de cÈlulas ocupadas 

	do{
		printf("Tipo de vizinhanca (1:Von Neumann; 2:Moore): "); 
		scanf(" %d", &(C.TipoViz));
	} while (C.TipoViz<1 || C.TipoViz>2);

	do{
		printf("Tipo de Fronteira (1:Fechada; 2:Toroidal): "); 
		scanf(" %d", &(C.TipoFront));
	} while (C.TipoFront<1 || C.TipoFront>2);

	//Pode existir uma ˙nica percentagem para todas as populaÁıes ou uma percentagem especÌfica para cada tipo de agente;
	C.PercSatisf = malloc(sizeof(float)*C.NPop);	
	//as percentagens tem de ser MAIORES que 1% e MENORES que 100%
	if (C.NPop == 2) //Se Numero de PopulaÁoes for 2 entao existem 2 percentagens de satisfaÁao
	{
		do{
			printf("Percentagem de satisfacao para cada populacao: ");
			scanf(" %f %f", &(C.PercSatisf[0]), &(C.PercSatisf[1]));
		} while ((C.PercSatisf[0]<1 || C.PercSatisf[0]>100)
			|| (C.PercSatisf[1]<1 || C.PercSatisf[1]>100));
	}
	else //Se nao... entao existem 3 percentagens de satisfaÁao
	{
		do{
			printf("Percentagem de satisfacao para cada populacao: ");
			scanf(" %f %f %f", &(C.PercSatisf[0]), &(C.PercSatisf[1]), &(C.PercSatisf[2]));
		} while ((C.PercSatisf[0]<1 || C.PercSatisf[0]>100)
			|| (C.PercSatisf[1]<1 || C.PercSatisf[1]>100)
			||(C.PercSatisf[2]<1||C.PercSatisf[2]>100));
	}
	do{
		printf("Deslocamento dos agentes (1:celula mais proxima; 2:aleatorio): "); 
		scanf(" %d", &(C.Desloc));
	} while (C.TipoViz<1 || C.TipoViz>2);

	do{
		printf("Numero maximo de iteracoes: "); 
		scanf(" %d", &(C.NIter));
	} while (C.NIter < 1);

	//guardar configuraÁıes
	linha();
	printf("\nPretende guardar estas configuracoes para utilizacao frequente? (s ou n): "); scanf(" %c", &r);
	if (r == 's' || r == 'S') 
		Save_Config(C);
	return C;
}

Configuracoes inicializ()
{
	Configuracoes c;
	c.DimGrid[0] = 0;
	c.DimGrid[1] = 0;
	c.NPop = 0;
	c.DimPop = 0;
	c.TipoViz = 0;
	c.TipoFront = 0;
	c.PercSatisf = malloc(sizeof(float));
	c.PercSatisf[0] = 0;
	c.PercSatisf[1] = 0;
	c.Desloc = 0;
	c.NIter = 0;
	return c;
}

Configuracoes Config()
{
	int x;
	Configuracoes C = inicializ();
	do{
		do{	//MenuConfig()
			linha();
			puts("1 - Escolher Configuracoes Pre-definidas");
			puts("2 - Visualizar Configuracoes Pre-definidas");
			puts("3 - Personalizar Configuracoes");
			puts("4 - Voltar Atras");
			printf("Escolha uma Opcao: "); scanf(" %d", &x); 
			if (x <1 || x >4)
				puts("Erro na escolha da opcao!");
		} while (x <1 || x >4);

		switch (x)
		{
		case 1: C = Choose_Config(); break;
		case 2: See_Config(C); break;
		case 3: C = Obter_PersonalConfig(); break;
		default:
			break;
		}
	} while (x != 4);
	return C;
}