#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define INF 999999

typedef struct bloco {
    int id;
    struct bloco *proxlinha, *proxcoluna;
    int dist;
    char tipo;
} no;

typedef struct {
    no *cabecalho;
} MatrizEsparsa;

void criar (MatrizEsparsa *M);

void inserir_no (MatrizEsparsa *M, int *id);

int checar_aresta (no *aresta, int escolha);

void inserir_aresta (MatrizEsparsa *M, int *id1, int *id2);

int analisarGrau(MatrizEsparsa *M, int *ide);

void grauVizinhos(MatrizEsparsa *M, int *ide);

int eVizinho(MatrizEsparsa *M, int ide, int ide2);

void coeficiente(MatrizEsparsa *M, int *ide);

int setardist(MatrizEsparsa *M, no *aux, int distatual);

void grau_hierarquico_rec(MatrizEsparsa *M, int ide, int distatual);

void grau_hierarquico(MatrizEsparsa *M, int ide);
