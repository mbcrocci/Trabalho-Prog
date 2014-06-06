#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "quadro.h"
#include "random.h"

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
        printf("Escolha uma Opcao: "); scanf(" %d", &i);
        if (i <1 || i >5)
            puts("Erro na escolha da opcao!");
    } while (i <1 || i >5);
    return i;
}

void simul(Configuracoes C)
{
    int **quadro;
    int erro = 0, i, j;
    int satis;
    char resp;
    // ConfiguraÁıes STANDARD (se ainda nao tiver sido escolhido uma configuraÁ„o)
    C = Read_Config("config1.txt", &erro);
    if (erro == 1)
    {
        puts("\nErro ao definir configuracoes standard!");
        printf("Quer definir outras configuraÁoes? (s, n): ");
        scanf(" %c", &resp);
        if (resp == 's' || resp == 'S')
            Config();
    }
    else 
    {
        printf("C.DimGrid[0] -> %d \nC.DimGrid[1] -> %d", C.DimGrid[0], C.DimGrid[1]);
        criar_quadro(quadro, C.DimGrid[0], C.DimGrid[1]);
        preencher_quandro(quadro, C.DimGrid[0], C.DimGrid[1], C.DimPop, C.NPop);
        mostrar_quadro(C.DimGrid[0], C.DimGrid[1], quadro);

        // 1 iteracao do quadro
        for (i = 0; i < C.DimGrid[0]; i++)
        {
            for (j = 1; j < C.DimGrid[1]; j++)
            {
                if (quadro[i][j] == 1)
                {
                    satis = vizinhancas(i, j, C.DimGrid[0], C.DimGrid[1], quadro);
                    printf("Pessa na posicao: (%d,%d) -> satisfacao: %d\n", i,j, satis);
                }
            }
        }
    }
    
}

int main()
{
    
    int i, j, satis;
    Configuracoes Conf;

    init_gerador_random();

    do{
        i = MenuPrincipal();
        switch (i)
        {
            case 1: Conf = Config(); break;
            case 2: simul(Conf); break; //chamada a funÁao da simulaÁao do "quadro" (main)
            //case 3: Save_Info(); break; //falta funÁao para guardar informaÁao da simulaÁao
            //case 4: Recover_Info(); break; //falta funÁao para recuperar informaÁao da simulaÁao

            default:
                break;
        }
    } while (i != 5);
    return 0;
}