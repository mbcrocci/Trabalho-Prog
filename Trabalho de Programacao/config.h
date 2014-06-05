#ifndef CONFIG_H_
#define CONFIG_H_

typedef struct{	//Header_Configuracoes.h
	int DimGrid[2];
	int NPop, DimPop, TipoViz, TipoFront, *PercSatisf, Desloc, NIter;
} Configuracoes;

Configuracoes Read_Config(char nomefic[15], int *erro);

Configuracoes Choose_Config();

void See_Config(Configuracoes C);

void Save_Config(Configuracoes C);

Configuracoes Obter_PersonalConfig();

Configuracoes inicializ();

Configuracoes Config();

#endif