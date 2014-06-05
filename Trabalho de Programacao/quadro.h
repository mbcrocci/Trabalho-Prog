#ifndef QUADRO_H_
#define QUADRO_H_

int check (int x, int y, int **quadro);
int vizinhancas (int x, int y, int lin, int col, int **quadro);
void mostrar_quadro (int lin, int col, int **quadro);
void preencher_quandro(int **quadro, int lin, int col, int dim_pops, int num_pops);

#endif