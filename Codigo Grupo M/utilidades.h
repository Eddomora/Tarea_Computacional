#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_VERT 50
#define MAX_ARISTAS 100
#define TAM_ARISTA 2
#define MAX 26
#define INFINITO 9999999

struct grafo
{
    char vertices[MAX_VERT];
    char aristas[MAX_ARISTAS][TAM_ARISTA];
};

int char_a_index(char c);
char index_a_char(int i);
void creacion_grafico(int g_adyacencia[MAX][MAX], struct grafo graf);
int verificar(char letra, struct grafo G);

#endif