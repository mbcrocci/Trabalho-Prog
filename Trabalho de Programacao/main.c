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
        puts("2 - Simulacao");
        puts("3 - Guardar Informacao");
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
    int i, firstTime = 1;
    Configuracoes Conf;
    do{
        i = MenuPrincipal();
        switch (i){
        case 1: Conf = config(firstTime); break;
        case 2: simul(Conf, firstTime); break;  //chamada a funÁao da simulaÁao do "quadro" (main)
            //case 3: Save_Info(); break; //falta funÁao para guardar informaÁao da simulaÁao
            //case 4: Recover_Info(); break; //falta funÁao para recuperar informaÁao da simulaÁao
            default:
                break;
        }
    } while (i != 5);
    return 0;
}