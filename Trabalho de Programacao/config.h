#ifndef CONFIG_H_
#define CONFIG_H_

#define MIN_LIN 8
#define MAX_LIN 15
#define MIN_COL 15
#define MAX_COL 30
#define PERC_MIN 50
#define PERC_MAX 70


typedef struct{	
	int DimGrid[2];
	int NPop, DimPop, TipoViz, TipoFront, Desloc, NIter;
	float *PercSatisf;
} Configuracoes;
/*				EX:
DimGrid		DIM: 8 15		Dimens„o do ambiente (Linhas, Colunas)
NPop		POPS: 2			N˙mero de populaÁıes (X,0) ou (X, 0, H)
DimPop		DIM_POP: 40		N˙mero de agentes em cada populaÁ„o
VTipoViz	VIZ: 1			Tipo de vizinhanÁa (1:Von Neumann; 2:Moore)
TipoFront	FRONTEIRA: 1	Tipo de fronteira (1:Fechada; 2:Toroidal)
PercSatisf	K: 50 50		Percentagem/Limite de satisfaÁ„o para cada populaÁ„o
Desloc		MOVE: 1			Deslocamento dos agentes (1:cÈlula mais prÛxima; 2:aleatÛrio)
NIter		NUM_ITER: 50	N˙mero m·ximo de iteraÁıes
*/

void linha();

Configuracoes Read_Config(char nomefic[15], int *erro);

Configuracoes Choose_Config();

void See_Config(Configuracoes C);

void Save_Config(Configuracoes C);

Configuracoes Obter_PersonalConfig();

Configuracoes inicializ();

Configuracoes Config();

#endif