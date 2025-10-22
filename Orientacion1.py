def orientacion1(grafo, inicio, fin):
    visitado = {v: False for v in grafo} #ir guardando los vertices ya visitados. asi no se repiten. False: no visitado, True:visitado
    previo = {v: None for v in grafo} #guarda del vertice que vienes, asi se va construyendo el camino 

    cola = [inicio]
    visitado[inicio] = True

    while cola:
        u = cola.pop() #popleft: elimina y devuelve el primer elemento (el que entro primero(izquierda)).
        if u == fin:
            break
        for v in grafo[u]:
            if not visitado[v]:
                visitado[v] = True
                previo[v] = u
                cola.append(v)

    # Reconstruir camino
    camino = []
    actual = fin
    while actual is not None:
        camino.append(actual)
        actual = previo[actual]
    camino.reverse()

    if camino[0] != inicio:
        print(f"No hay camino dirigido desde {inicio} hasta {fin}.")
        return None

    # Crear orientacion dirigida
    orientado = {v: [] for v in grafo}
    for i in range(len(camino) - 1):
        u, v = camino[i], camino[i + 1]
        orientado[u].append(v)  # direcci0n u → v

    print(f"\nOrientacion 1 (camino {inicio} → {fin}):")
    print(" → ".join(camino))
    print("\nAristas dirigidas:")
    for u in orientado:
        for v in orientado[u]:
            print(f"{u} → {v}")

    return orientado 