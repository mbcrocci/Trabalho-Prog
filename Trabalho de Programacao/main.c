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
        puts("3 - Simulacao Sem Interropcao");
        puts("4 - Guardar Informacao");
        puts("5 - Recuperar Informacao");
        puts("6 - Terminar");
        printf("Escolha uma Opcao: ");
        scanf(" %d", &x); 
        if (x <1 || x >6) 
            puts("Erro na escolha da opcao!");
    } while (x <1 || x >6);
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
                    simul(Conf, FirstTime);
                    break;  //chamada a funÁao da simulaÁao do "quadro" (main)
        case 3: if (FirstTime == 1) // Se a funcao simul_passo() for chamada antes das configuracoes serem escolhidas 
                        Conf = inicializ(); //incializaÁ„o da estrutura - poe tudo a zeros
                    simul_passo(Conf, FirstTime);
                    break;
        //case 3: Save_Info(); break; //falta funÁao para guardar informaÁao da simulaÁao
        //case 4: Recover_Info(); break; //falta funÁao para recuperar informaÁao da simulaÁao
            default:
                break;
        }
    } while (i != 6);
    free(Conf.PercSatisf);
    return 0;
}