#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 26
#define INFINITY 999999999

// ---------- Utilidades letra <-> índice ----------
int char_to_index(char c)
{
    return tolower((unsigned char)c) - 'a';
}
char index_to_char(int i)
{

int char_to_index(char c) {
    return tolower((unsigned char)c) - 'a';
}
char index_to_char(int i) {
    return (char)('a' + i);
}

// ---------- Helpers de la matriz ----------
void clear_graph(int G[MAX][MAX])
{
    memset(G, 0, sizeof(int) * MAX * MAX);
}
void copy_graph(int dst[MAX][MAX], int src[MAX][MAX])
{
    memcpy(dst, src, sizeof(int) * MAX * MAX);
}

// ---------- Orientaciones determinísticas 1..4 ----------
void orient_edge_by_mode(int u, int v, int mode, int *from, int *to)
{
    // Normalizamos u<v para reglas estables
    int lo = u < v ? u : v;
    int hi = u < v ? v : u;
    switch (mode)
    {
    case 1: // menor -> mayor
        *from = lo;
        *to = hi;
        break;
    case 2: // mayor -> menor
        *from = hi;
        *to = lo;
        break;
    case 3: // paridad de (lo+hi): si par lo->hi; si impar hi->lo
        if (((lo + hi) % 2) == 0)
        {
            *from = lo;
            *to = hi;
        }
        else
        {
            *from = hi;
            *to = lo;
        }
        break;
    case 4: // paridad de lo: si lo par lo->hi; si impar hi->lo
        if ((lo % 2) == 0)
        {
            *from = lo;
            *to = hi;
        }
        else
        {
            *from = hi;
            *to = lo;
        }
        break;
    default:
        *from = lo;
        *to = hi;
        break;
    }
}

// A partir de una matriz no dirigida base, crea una versión dirigida según modo 1..4
void build_oriented_from_undirected(int base[MAX][MAX], int n, int mode, int outG[MAX][MAX])
{
    clear_graph(outG);
    for (int u = 0; u < n; ++u)
    {
        for (int v = u + 1; v < n; ++v)
        {
            if (base[u][v] != 0)
            {
                int from, to;
                orient_edge_by_mode(u, v, mode, &from, &to);
                outG[from][to] = 1; // peso = 1
            }
        }
    }
}

// ---------- Dijkstra (matriz, pesos=1) con corte temprano y manejo "sin camino" ----------
void dijkstra(int G[MAX][MAX], int n, int start_node, int end_node)
{
    int dist[MAX], pred[MAX], visited[MAX];
    for (int i = 0; i < n; ++i)
    {
        dist[i] = INFINITY;
        pred[i] = -1;
        visited[i] = 0;
    }
    dist[start_node] = 0;

    for (int step = 0; step < n; ++step)
    {
        int u = -1, best = INFINITY;
        for (int i = 0; i < n; ++i)
        {
            if (!visited[i] && dist[i] < best)
            {
                best = dist[i];
                u = i;
            }
        }
        if (u == -1)
            break; // no quedan alcanzables
        visited[u] = 1;
        if (u == end_node)
            break; // corte temprano: ya alcanzamos destino

        for (int v = 0; v < n; ++v)
        {
            if (!visited[v] && G[u][v] != 0)
            {              // arista u->v
                int w = 1; // pesos unitarios
                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    pred[v] = u;
                }
            }
        }
    }

    if (dist[end_node] >= INFINITY / 2)
    {
        printf("\nNo existe un camino entre '%c' y '%c'.\n",
               index_to_char(start_node), index_to_char(end_node));
        return;
    }

    // reconstruir camino
    int path[MAX], len = 0;
    for (int cur = end_node; cur != -1; cur = pred[cur])
    {
        path[len++] = cur;
        if (cur == start_node)
            break;
    }

    printf("\nLa distancia mas corta de '%c' a '%c' es: %d\n",
           index_to_char(start_node), index_to_char(end_node), dist[end_node]);
    printf("El camino es: ");
    for (int i = len - 1; i >= 0; --i)
    {
        printf("%c", index_to_char(path[i]));
        if (i)
            printf(" -> ");
    }
    printf("\n");
}

int main(void)
{
    // Matrices base (no dirigidas) de cada grafo
    int graph_tree[MAX][MAX], graph_planar[MAX][MAX], graph_eulerian[MAX][MAX];
    clear_graph(graph_tree);
    clear_graph(graph_planar);
    clear_graph(graph_eulerian);

    // --- Árbol (12 vértices: a-l) ---
    // E = {ab, ac, bd, dh, di, ce, cf, cg, gl, fj, fk}
    char tree_edges[][2] = {
        {'a', 'b'}, {'a', 'c'}, {'b', 'd'}, {'d', 'h'}, {'d', 'i'}, {'c', 'e'}, {'c', 'f'}, {'c', 'g'}, {'g', 'l'}, {'f', 'j'}, {'f', 'k'}};
    for (int i = 0; i < 11; ++i)
    {
        int u = char_to_index(tree_edges[i][0]);
        int v = char_to_index(tree_edges[i][1]);
        graph_tree[u][v] = graph_tree[v][u] = 1;
    }

    // --- Grafo Planar (9 vértices: a-i) ---
    // E = {ab, ah, bh, bd, bc, cd, di, df, de, ef, fi, fh, fg, gh}
    char planar_edges[][2] = {
        {'a', 'b'}, {'a', 'h'}, {'b', 'h'}, {'b', 'd'}, {'b', 'c'}, {'c', 'd'}, {'d', 'i'}, {'d', 'f'}, {'d', 'e'}, {'e', 'f'}, {'f', 'i'}, {'f', 'h'}, {'f', 'g'}, {'g', 'h'}};
    for (int i = 0; i < 14; ++i)
    {
        int u = char_to_index(planar_edges[i][0]);
        int v = char_to_index(planar_edges[i][1]);
        graph_planar[u][v] = graph_planar[v][u] = 1;
    }

    // --- Grafo Euleriano (10 vértices: a-j) ---
    // E = {ab, ah, bc, bj, bh, cj, cd, ce, dj, di, de, ej, ei, ef, eg, fi, fh, fg, gi, gh, hi, hj, ij}
    char eulerian_edges[][2] = {
        {'a', 'b'}, {'a', 'h'}, {'b', 'c'}, {'b', 'j'}, {'b', 'h'}, {'c', 'j'}, {'c', 'd'}, {'c', 'e'}, {'d', 'j'}, {'d', 'i'}, {'d', 'e'}, {'e', 'j'}, {'e', 'i'}, {'e', 'f'}, {'e', 'g'}, {'f', 'i'}, {'f', 'h'}, {'f', 'g'}, {'g', 'i'}, {'g', 'h'}, {'h', 'i'}, {'h', 'j'}, {'i', 'j'}};
    for (int i = 0; i < 23; ++i)
    {
        int u = char_to_index(eulerian_edges[i][0]);
        int v = char_to_index(eulerian_edges[i][1]);
        graph_eulerian[u][v] = graph_eulerian[v][u] = 1;
    }

    // --- Interfaz de usuario ---
    int choice, directed = 0, orient_mode = 1;
    int selected_graph[MAX][MAX], working_graph[MAX][MAX];
    int num_vertices = 0;
    char start_char, end_char;
    int start_node, end_node;

    printf("Seleccione el grafo a utilizar:\n");
    printf("1. Arbol (vertices a-l)\n");
    printf("2. Grafo Planar (vertices a-i)\n");
    printf("3. Grafo Euleriano (vertices a-j)\n");
    printf("Ingrese su eleccion: ");
    if (scanf("%d", &choice) != 1)
        return 1;

    switch (choice)
    {
    case 1:
        num_vertices = 12;
        copy_graph(selected_graph, graph_tree);
        break;
    case 2:
        num_vertices = 9;
        copy_graph(selected_graph, graph_planar);
        break;
    case 3:
        num_vertices = 10;
        copy_graph(selected_graph, graph_eulerian);
        break;
    default:
        printf("Eleccion invalida.\n");
        return 1;
    }

    printf("¿Dirigido? 0=No, 1=Si: ");
    if (scanf("%d", &directed) != 1)
        return 1;
    if (directed)
    {
        printf("Elija orientacion (1..4): ");
        if (scanf("%d", &orient_mode) != 1)
            return 1;
        if (orient_mode < 1 || orient_mode > 4)
            orient_mode = 1;
        build_oriented_from_undirected(selected_graph, num_vertices, orient_mode, working_graph);
    }
    else
    {
        copy_graph(working_graph, selected_graph);
    }

    printf("Ingrese el vertice inicial: ");
    scanf(" %c", &start_char);
    printf("Ingrese el vertice final: ");
    scanf(" %c", &end_char);

    start_node = char_to_index(start_char);
    end_node = char_to_index(end_char);

    if (start_node < 0 || start_node >= num_vertices ||
        end_node < 0 || end_node >= num_vertices)
    {
        printf("Vertices fuera de rango para el grafo elegido.\n");
        return 1;
    }

    printf("\nEjecutando Dijkstra en grafo %s con %d vertices. Origen=%c, Destino=%c\n",
           directed ? "DIRIGIDO" : "NO DIRIGIDO",
           num_vertices, index_to_char(start_node), index_to_char(end_node));

    dijkstra(working_graph, num_vertices, start_node, end_node);
    return 0;
}
