#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "config.h"
#include "simulacao.h"

void linha(){
    int i;
    for (i = 0; i < 60; i++)
        putchar('_');
    puts("\n");
}

int MenuPrincipal(){
    int x;
    do{
        linha();
        puts("1 - Configuracoes");
        puts("2 - Simulacao Sequencial");
        puts("3 - Siulacao Sem Interropcao");
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
    int i, firstTime = 1;
    int *first = &firstTime;
    Configuracoes Conf;
    do{
        i = MenuPrincipal();
        switch (i){
        case 1: Conf = config(first); break;
        case 2: simul(Conf, first); break;  //chamada a funÁao da simulaÁao do "quadro" (main)
        case 3: simul_passo(Conf, first); break;
            //case 3: Save_Info(); break; //falta funÁao para guardar informaÁao da simulaÁao
            //case 4: Recover_Info(); break; //falta funÁao para recuperar informaÁao da simulaÁao
            default:
                break;
        }
    } while (i != 5);
    return 0;
}