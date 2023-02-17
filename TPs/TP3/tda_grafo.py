import random


class Grafo:
    def __init__(self):
        self.vertices = {}

    def agregar_vertice(self, v):
        self.vertices[v] = {}

    def agregar_arista(self, v, w, peso=1):
        if v not in self.vertices:
            return None
        if w not in self.vertices:
            return None

        self.vertices[v][w] = peso
        self.vertices[w][v] = peso

    def borrar_vertice(self, v):
        if v not in self.vertices:
            return None

        self.vertices.pop(v)
        for vertice in self.vertices:
            vertice.pop(v)

    def borrar_arista(self, v, w):
        if v not in self.vertices:
            return None
        if w not in self.vertices:
            return None

        self.vertices[v].pop(w)
        self.vertices[w].pop(v)

    def estan_unidos(self, v, w):
        if v not in self.vertices:
            return False
        if w not in self.vertices:
            return False
        if self.vertices[v].get(w):
            return True
        return False

    def peso_arista(self, v, w):
        if v not in self.vertices:
            return None
        if w not in self.vertices:
            return None
        if w not in self.vertices[v]:
            return None
        return self.vertices[v].get(w)

    def obtener_vertices(self):
        lista_vertices = []
        for v in self.vertices:
            lista_vertices.append(v)
        return lista_vertices

    def vertice_aleatorio(self):
        return random.choice(list(self.vertices.keys()))

    def adyacentes(self, v):
        lista_adyacentes = []
        if v not in self.vertices:
            return None
        for w in self.vertices[v].keys():
            lista_adyacentes.append(w)
        return lista_adyacentes
