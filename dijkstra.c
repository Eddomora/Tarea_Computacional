#include "dijkstra.h"

void dijkstra(int G_escogido[MAX][MAX], int n, int nodo_inicio, int nodo_final)
{
    int dist[MAX], pred[MAX], visitado[MAX];

    // 1. Inicialización
    for (int i = 0; i < n; ++i)
    {
        dist[i] = INFINITO;
        pred[i] = -1;
        visitado[i] = 0;
    }
    dist[nodo_inicio] = 0;

    // 2. Bucle principal de Dijkstra
    for (int step = 0; step < n; ++step)
    {
        int u = -1;
        int best = INFINITO;
        for (int i = 0; i < n; ++i)
        {
            if (!visitado[i] && dist[i] < best)
            {
                best = dist[i];
                u = i;
            }
        }

        if (u == -1)
            break; // No quedan nodos alcanzables

        visitado[u] = 1;
        if (u == nodo_final)
            break; // Corte temprano: alcanzamos el destino

        for (int v = 0; v < n; ++v)
        {
            // Verificamos si hay una arista (peso > 0) y si el destino no ha sido visitado
            if (!visitado[v] && G_escogido[u][v] != 0)
            {
                int w = G_escogido[u][v];
                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    pred[v] = u;
                }
            }
        }
    }

    // 3. Resultado y reconstrucción del camino
    if (dist[nodo_final] >= INFINITO / 2) // Usar INFINITO/2 para evitar desbordamiento
    {
        printf("\nNo existe un camino entre '%c' y '%c'.\n", index_a_char(nodo_inicio), index_a_char(nodo_final));
        return;
    }

    // reconstruir camino
    int path[MAX], len = 0;
    for (int cur = nodo_final; cur != -1; cur = pred[cur])
    {
        path[len] = cur;
        len++;
        if (cur == nodo_inicio)
            break;
    }

    printf("\nLa distancia mas corta de '%c' a '%c' es: %d\n", index_a_char(nodo_inicio), index_a_char(nodo_final), dist[nodo_final]);

    printf("El camino es: ");

    for (int i = len - 1; i >= 0; --i)
    {
        printf("%c", index_a_char(path[i]));
        if (i)
            printf(" -> ");
    }
    printf("\n");
}