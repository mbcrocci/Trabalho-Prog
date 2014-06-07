#ifndef VIZ_H_
#define VIZ_H_

int check (int x, int y, int **quadro, int p);
int viz_neuman_fech (int x, int y, int lin, int col, float per, int **quadro);
int viz_moore_fech  (int x, int y, int lin, int col, float per, int **quadro);
int viz_neuman_tor  (int x, int y, int lin, int col, float per, int **quadro);
int viz_moore_tor   (int x, int y, int lin, int col, float per, int **quadro);


#endif