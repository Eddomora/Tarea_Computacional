#include "utilidades.h"

int char_a_index(char c)
{
    return tolower((unsigned char)c) - 'a';
}
char index_a_char(int i)
{
    return (char)('a' + i);
}

void creacion_grafico(int g_adyacencia[MAX][MAX], struct grafo graf)
{
    for (int i = 0; i < 11; ++i)
    {
        int u = char_a_index(graf.aristas[i][0]);
        int v = char_a_index(graf.aristas[i][1]);
        g_adyacencia[u][v] = g_adyacencia[v][u] = 1;
    }
}

int verificar(char letra, struct grafo G)
{
    for (int i = 0; i < strlen(G.vertices); i++)
    {
        if (G.vertices[i] == letra)
        {

            return 1;
        }
    }
    return 0;
}
