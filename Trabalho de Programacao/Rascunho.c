/*
2 ERROS	- Nao Esta a Atribuir Valores as Variaveis da Estrutura
		- Falta a condiçao ao pedir a 3ª percentagem de Satisfaçao
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define Z 0
#define N1 1
#define N2 2
#define N3 3
#define N4 4
#define N5 5

#define MIN_LIN 8
#define MIN_COL 15
#define MAx_LIN 15
#define MAX_COL 30

#define N50 50
#define N70 70
#define N100 100

void linha();	//Header_MenuPrincipal.h
typedef struct{	//Header_Configuracoes.h
	int DimGrid[N2];
	int NPop, DimPop, TipoViz, TipoFront, Desloc, NIter;
	int PercSatisf[N3];
}Configuracoes;	//ERRO: nao esta a atribuir valores as variaveis
/*				EX:
DimGrid		DIM: 8 15		Dimensão do ambiente (Linhas, Colunas)
NPop		POPS: 2			Número de populações (X,0) ou (X, 0, H)
DimPop		DIM_POP: 40		Número de agentes em cada população
VTipoViz	VIZ: 1			Tipo de vizinhança (1:Von Neumann; 2:Moore)
TipoFront	FRONTEIRA: 1	Tipo de fronteira (1:Fechada; 2:Toroidal)
PercSatisf	K: 50 50		Percentagem/Limite de satisfação para cada população
Desloc		MOVE: 1			Deslocamento dos agentes (1:célula mais próxima; 2:aleatório)
NIter		NUM_ITER: 50	Número máximo de iterações
*/

//Configuracoes.c
void Read_Config(char nomefic[N15]) //ler configuaraçoes pre-defindas e presonalizadas nos ficheiros
{
	Configuracoes conf, *p=&conf;
	FILE *f, **F = &f; 
	f = fopen(nomefic, "r");
    
	if (f == NULL)
    {
        puts("Erro no acesso ao ficheiro!");
        return;
    }
    
	else
    {
		fscanf(f, " %d %d", &(p->DimGrid[Z]), &(p->DimGrid[N1]));
		fscanf(f, " %d", &(p->NPop));
		fscanf(f, " %d", &(p->DimPop));
		fscanf(f, " %d", &(p->TipoViz));
		fscanf(f, " %d", &(p->TipoFront));
		if (p->NPop == 2)
            fscanf(f, " %d %d", &(p->PercSatisf[Z]), &(p->PercSatisf[N1]));
		else
            fscanf(f, " %d %d %d", &(p->PercSatisf[Z]), &(p->PercSatisf[N1]),&(p->PercSatisf[N2]));
        
		fscanf(f, " %d", &(p->Desloc));
		fscanf(f, " %d", &(p->NIter));
		fclose(f);
	}
}

void Choose_Config()
{	//Escolher qual a configuração a utilizar na simulação
	int c;
	linha();
	do{
		printf("Qual e a configuracao que quer utilizar? (1,2,3 ou 4[Configuracao pessoal]): "); scanf(" %d", &c);
	} while (c<1 || 4<c);
    
	if (c == 1)
        Read_Config("config1.txt");
    
	else if (c == 2)
        Read_Config("config2.txt");
    
    else if (c == 3)
        Read_Config("config3.txt");
			
    else
        Read_Config("configpes.txt");
		
}

void See_Config() //Mostrar conteudo dos 3 ficheiros de texto com as configuraçoes pre-definidas
{
    int c; char r;
	Configuracoes conf, *p = &conf;
	linha();
	do{
		do{
			printf("Qual e a configuracao que quer visualizar? (1,2,3 ou 4[Configuracao pessoal]): "); scanf(" %d", &c);
		} while (c < 1 || 4 < c);
        
		if (c == 1)
        {
            Read_Config("config1.txt");
            puts("Configuracao 1:");
        }
		else if (c == 2)
        {
            Read_Config("config2.txt");
            puts("Configuracao 2:");
        }
        else if (c == 3)
        {
            Read_Config("config3.txt");
            puts("Configuracao 3:");
        }
        else
        {
            Read_Config("configpes.txt");
            puts("Configuracao Pessoal:");
		}
        
		printf("DIM: %d %d\n", p->DimGrid[Z], p->DimGrid[N1]);
		printf("POPS: %d\n", p->NPop);
		printf("DIM_POP: %d\n", p->DimPop);
		printf("VIZ: %d\n", p->TipoViz);
		printf("FRONTEIRA: %d\n", p->TipoFront);
		if (p->NPop == 2)
            printf("K: %d %d\n", p->PercSatisf[Z], p->PercSatisf[N1]);
		else
            printf("K: %d %d %d\n", p->PercSatisf[Z], p->PercSatisf[N1], p->PercSatisf[N2]);
        
		printf("MOVE: %d\n", p->Desloc);
		printf("NUM_ITER: %d\n", p->NIter);
		printf("\nPretende visualizar mais alguma configuracao? (s ou n): "); scanf(" %c", &r);
	} while (r == 's' || r == 'S');
}

void Save_Config() //guardar configurações pessoais num novo ficheiro("configpes.txt")
{
	Configuracoes conf, *p = &conf;
	FILE *f, **F = &f;
	f = fopen("configpes.txt", "w");
	if (f == NULL)
    {
        puts("Erro no acesso ao ficheiro!");
        return;
    }
    
	else
    {
		fprintf(f, "DIM: %d %d\n", p->DimGrid[Z], p->DimGrid[N1]);
		fprintf(f, "POPS: %d\n", p->NPop);
		fprintf(f, "DIM_POP: %d\n", p->DimPop);
		fprintf(f, "VIZ: %d\n", p->TipoViz);
		fprintf(f, "FRONTEIRA: %d\n", p->TipoFront);
        
		if (p->NPop == 2)
            fprintf(f, "K: %d %d\n", p->PercSatisf[Z], p->PercSatisf[N1]);
		else
            fprintf(f, "K: %d %d %d\n", p->PercSatisf[Z], p->PercSatisf[N1], p->PercSatisf[N2]);
        
		fprintf(f, "MOVE: %d\n", p->Desloc);
		fprintf(f, "NUM_ITER: %d\n", p->NIter);
		fclose(f);
	}
}

void Obter_PersonalConfig()
{
	linha();
	char c;
	Configuracoes conf, *p = &conf;
	//pedir dados das configurações e preencher estrutura

	do{
		printf("Dimensao do ambiente (Numero_Linhas Numero_Colunas): "); scanf(" %d %d", &(p->DimGrid[Z]), &(p->DimGrid[N1]));
	} while ((p->DimGrid[Z]<N8 || p->DimGrid[Z]>N15) || (p->DimGrid[N1]<N15 || p->DimGrid[N1]>N30));
    
	do{
		printf("Numero de populacoes (2 -(X,0) ou 3 -(X, 0, H)): "); scanf(" %d", &(p->NPop));
	} while (p->NPop<N2 || p->NPop>N3);
    
	do{
		printf("Numero de agentes em cada populacao: "); scanf(" %d", &(p->DimPop));	//Deve garantir-se que a percentagem total de células ocupadas varia entre 50 % e 70 % do total;
	} while ((p->NPop*p->DimPop*N100) / (p->DimGrid[Z] * p->DimGrid[N1])<N50 || (p->NPop*p->DimPop*N100) / (p->DimGrid[Z] * p->DimGrid[N1])>N70);
	//	(p->NPop * p->DimPop * N100) / (p->DimGrid[Z] * p->DimGrid[N1]) => calcula a percentagem total de células ocupadas
    
	do{
		printf("Tipo de vizinhanca (1:Von Neumann; 2:Moore): "); scanf(" %d", &(p->TipoViz));
	} while (p->TipoViz<N1 || p->TipoViz>N2);
    
	do{
		printf("Tipo de Fronteira (1:Fechada; 2:Toroidal): "); scanf(" %d", &(p->TipoFront));
	} while (p->TipoFront<N1 || p->TipoFront>N2);
    
	do{
		printf("Percentagem de satisfacao para cada populacao: ");
		//Pode existir uma única percentagem para todas as populações ou uma percentagem específica para cada tipo de agente;
		if (p->NPop == 2)
            scanf(" %d %d", &(p->PercSatisf[Z]), &(p->PercSatisf[N1]));
		else
            scanf(" %d %d %d", &(p->PercSatisf[Z]), &(p->PercSatisf[N1]), &(p->PercSatisf[N2]));
	} while ((p->PercSatisf[Z]<N1 || p->PercSatisf[Z]>N100) || (p->PercSatisf[N1]<N1 || p->PercSatisf[N1]>N100));//as percentagens tem de ser MAIORES que 1% e MENORES que 100%
	//	=> FALTA A CONDIÇAO DA 3ª PERCETAGEM	<=

	do{
		printf("Deslocamento dos agentes (1:celula mais proxima; 2:aleatorio): "); scanf(" %d", &(p->Desloc));
	} while (p->TipoViz<N1 || p->TipoViz>N2);
    
	do{
		printf("Numero maximo de iteracoes: "); scanf(" %d", &(p->NIter));
	} while (p->NIter < N1);

	//guardar configurações
	linha();
	do{
		printf("\nPretende guardar estas configuracoes para utilizacao frequente? (s ou n): "); scanf(" %c", &c);
	} while ((c != 's' && c != 'S') && (c != 'n' && c != 'N'));
    
	if (c == 's' || c == 'S')
        Save_Config();
}

void Config()
{
	int x;
	do{
		do{	//MenuConfig()
			linha();
			puts("1 - Escolher Configuracoes Pre-definidas");
			puts("2 - Visualizar Configuracoes Pre-definidas");
			puts("3 - Personalizar Configuracoes");
			puts("4 - Voltar Atras");
			printf("Escolha uma Opcao: "); scanf(" %d", &x); if (x <N1 || x >N4) puts("Erro na escolha da opcao!");
		} while (x <N1 || x >N4);

		switch (x)
		{
		case 1: Choose_Config(); break;
		case 2: See_Config(); break;
		case 3: Obter_PersonalConfig(); break;
		default:
			break;
		}
	} while (x != N4);
}

//Simulacao.c

//Menu_Principao.c
void linha()
{
	int i;
	for (i = 0; i < 60; i++)
		putchar('_');
	puts("\n");
}

int MenuPrincipal()
{
	int i;
	linha();
	do{
		puts("1 - Configuracoes");
		puts("2 - Simulacao");
		puts("3 - Guardar Informacao");
		puts("4 - Recuperar Informacao");
		puts("5 - Terminar");
		printf("Escolha uma Opcao: "); scanf(" %d", &i); if (i <N1 || i >N5) puts("Erro na escolha da opcao!");
	} while (i <N1 || i >N5);
	return i;
}

int main()
{
	int i;
	do{
		i = MenuPrincipal();
		switch (i){
		case 1: Config(); break;
		//case 2: break; //chamada a funçao da simulaçao do "quadro"
		//case 3: Save_Info(); break; //falta funçao para guardar informaçao da simulaçao
		//case 4: Recover_Info(); break; //falta funçao para recuperar informaçao da simulaçao

		default:
			break;
		}
	} while (i != 5);
    
    return 0;
}