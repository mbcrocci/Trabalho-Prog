#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "simulacao.h"


int MenuPrincipal(){
    int x;
    do{
        linha();
        puts("1 - Configuracoes");
        puts("2 - Simulacao Sequencial");
        puts("3 - Simulacao Passo a Passo");
        puts("4 - Recuperar Informacao");
        puts("5 - Terminar");
        printf("Escolha uma Opcao: ");
        scanf(" %d", &x); 
        if (x <1 || x >5) 
            puts("Erro na escolha da opcao!");
    } while (x <1 || x >5);
    return x;
}

int main(){
    int i, FirstTime = 1;
    Configuracoes Conf;
    do{
        i = MenuPrincipal();
        switch (i){
        case 1: Conf = config(&FirstTime); break;
        case 2: if (FirstTime == 1) // Se a funcao simul() for chamada antes das configuracoes serem escolhidas 
                        Conf = inicializ(); //incializaÁ„o da estrutura - poe tudo a zeros
                    simul(Conf, FirstTime, 0); 
                    break;  //chamada a funÁao da simulaÁao do "quadro" (main), 0 zero indique que e sequencial
                    
        case 3: if (FirstTime == 1) // Se a funcao simul() for chamada antes das configuracoes serem escolhidas 
                        Conf = inicializ(); //incializaÁ„o da estrutura - poe tudo a zeros
                    simul(Conf, FirstTime, 1);
                    break;

        // case 4: recover_info(&Conf); break; //falta funÁao para recuperar informaÁao da simulaÁao
            
        default:
            break;
        }
    } while (i != 5);
    free(Conf.PercSatisf);
    return 0;
}