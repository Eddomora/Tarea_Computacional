#include "caminos.h"

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


static void crear_orientacion(int g_adyacencia[MAX][MAX], struct grafo graf, int modo)
{
    for (int i = 0; i < MAX_ARISTAS; ++i)
    {
        // Si el primer char es nulo, significa que llegamos al final 
        // de las aristas definidas en la inicialización del struct.
        if (graf.aristas[i][0] == '\0')
        {
            break;
        }

        // Obtenemos los índices numéricos (0='a', 1='b', ...)
        int u = char_a_index(graf.aristas[i][0]);
        int v = char_a_index(graf.aristas[i][1]);

        // Normalizamos: 'lo' siempre es el índice menor, 'hi' el mayor
        int lo = (u < v) ? u : v;
        int hi = (u < v) ? v : u;

        int from, to; // Variables para guardar el origen (from) y destino (to)

        switch (modo)
        {
        case 1: // ASCENDENTE (lo -> hi)
            from = lo;
            to = hi;
            break;

        case 2: // DESCENDENTE (hi -> lo)
            from = hi;
            to = lo;
            break;

        case 3: // PARIDAD DE LA SUMA
            if ((lo + hi) % 2 == 0) // Si (lo + hi) es par
            {
                from = lo;
                to = hi;
            }
            else // Si (lo + hi) es impar
            {
                from = hi;
                to = lo;
            }
            break;

        case 4: // PARIDAD DEL MENOR
            if (lo % 2 == 0) // Si lo es par
            {
                from = lo;
                to = hi;
            }
            else // Si lo es impar
            {
                from = hi;
                to = lo;
            }
            break;
        
        default: // Modo por defecto (ascendente)
            from = lo;
            to = hi;
            break;
        }

        //el peso 1 a la arista dirigida
        g_adyacencia[from][to] = 1;
    }
}

void orientacion1(int g_adyacencia[MAX][MAX], struct grafo graf)
{
    crear_orientacion(g_adyacencia, graf, 1);
}

void orientacion2(int g_adyacencia[MAX][MAX], struct grafo graf)
{
    crear_orientacion(g_adyacencia, graf, 2);
}


void orientacion3(int g_adyacencia[MAX][MAX], struct grafo graf)
{
    crear_orientacion(g_adyacencia, graf, 3);
}

void orientacion4(int g_adyacencia[MAX][MAX], struct grafo graf)
{
    crear_orientacion(g_adyacencia, graf, 4);
}