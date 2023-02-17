
typedef struct nodo nodo_t;
struct nodo {
    void* dato;         // Apunta al dato almacenado
    nodo_t* prox_nodo;  // Apunta al prox nodo
};

nodo_t* crear_nodo(void* dato);