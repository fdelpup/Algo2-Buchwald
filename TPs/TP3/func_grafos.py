from heapq import heapify, heappush, heappop
import tda_grafo as Grafo
from lista_cola_pila import Cola


def obtener_aristas(grafo):
    aristas = {}
    visitados = set()
    for v in grafo:
        for w in grafo.adyacentes(v):
            if w not in visitados:
                aristas.append((v, w))
                visitados.add(w)
    return visitados


def BFS(grafo, origen):
    visitados = set()
    padres = {}
    orden = {}
    padres[origen] = None
    orden[origen] = 0
    visitados.add(origen)
    cola = Cola()
    cola.encolar(origen)
    while not cola.esta_vacia():
        v = cola.desencolar()
        for w in grafo.adyacentes(v):
            if w not in visitados:
                padres[w] = v
                orden[w] = orden[v] + 1
                visitados.add(w)
                cola.encolar(w)
    return padres, orden


def _DFS(grafo, v, visitados, padres, orden):
    for w in grafo.adyacentes(v):
        if w not in visitados:
            visitados.add(w)
            padres[w] = v

            orden[w] = orden[v] + 1
            _DFS(grafo, w, visitados, padres, orden)


def DFS(grafo, origen):
    padres = {}
    orden = {}
    visitados = set()
    padres[origen] = None

    orden[origen] = 0
    visitados.add(origen)
    _DFS(grafo, origen, visitados, padres, orden)
    return padres, orden


def dijkstra(grafo, origen):
    dist = {}
    padre = {}
    for v in grafo.obtener_vertices():
        dist[v] = float("inf")
    dist[origen] = 0
    padre[origen] = None
    heap = []
    heapify(heap)
    heappush(heap, (0, origen))
    while heap:
        v = heappop(heap)[1]
        for w in grafo.adyacentes(v):
            dist_por_aca = dist[v] + grafo.peso_arista(v, w)
            if dist_por_aca < dist[w]:
                dist[w] = dist[v] + grafo.peso_arista(v, w)
                padre[w] = v
                heappush(heap, (dist[w], w))
    return padre, dist


grafo = Grafo.Grafo()

grafo.agregar_vertice(1)
grafo.agregar_vertice(2)
grafo.agregar_vertice(3)
grafo.agregar_vertice(4)
grafo.agregar_arista(1, 2)
grafo.agregar_arista(2, 3)
grafo.agregar_arista(2, 4)
grafo.agregar_arista(3, 4)


print(grafo.adyacentes(1))
print(grafo.obtener_vertices())
print(grafo.vertice_aleatorio())
print(dijkstra(grafo, 1))
print(BFS(grafo, 1))
print(DFS(grafo, 2))
