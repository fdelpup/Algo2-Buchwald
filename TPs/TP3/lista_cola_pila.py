class _Nodo:
    def __init__(self, dato, prox=None):
        self.dato = dato
        self.prox = prox


class ListaEnlazada:
    def __init__(self):
        self.prim = None

    def append(self, dato):
        nuevo = _Nodo(dato)
        act = self.prim
        if act is None:
            self.prim = nuevo
            return
        while act.prox:
            act = act.prox
        act.prox = nuevo

    def __str__(self):
        L = []
        act = self.prim
        while act:
            L.append(str(act.dato))
            act = act.prox
        return f'[{", ".join(L)}]'

    def __len__(self):
        n = 0
        act = self.prim
        while act is not None:
            n += 1
            act = act.prox
        return n

    def insert(self, i, dato):
        nuevo = _Nodo(dato)
        act = self.prim
        if not act or i < 0:
            raise IndexError("")
        if i == 0:
            self.prim = _Nodo(dato)
        while i > 1 and act.prox:
            act = act.prox
            i -= 1
        if not act.prox:
            raise IndexError("")
        nuevo.prox = act.prox
        act.prox = nuevo


class Cola:
    def __init__(self):
        # invariante:
        # si la cola está vacía => frente = ultimo = None
        # si la cola no está vacía => frente != None y ult != None
        self.frente = None
        self.ultimo = None

    def encolar(self, dato):
        nuevo = _Nodo(dato)
        if self.ultimo is None:
            self.frente = nuevo
        else:
            self.ultimo.prox = nuevo
        self.ultimo = nuevo

    def desencolar(self):
        """
        Desencola un elemento y lo devuelve.
        Pre: la cola no puede estar vacía.
        """
        dato = self.frente.dato
        self.frente = self.frente.prox
        if self.frente is None:
            self.ultimo = None
        return dato

    def esta_vacia(self):
        return self.frente is None

    def ver_frente(self):
        """Pre: la cola no es vacía"""
        return self.frente.dato


class Pila:
    def __init__(self):
        self.tope = None

    def apilar(self, dato):
        self.tope = _Nodo(dato, self.tope)

    def desapilar(self):
        dato = self.tope.dato
        self.tope = self.tope.prox
        return dato

    def ver_tope(self):
        return self.tope.dato

    def esta_vacia(self):
        return self.tope is None
