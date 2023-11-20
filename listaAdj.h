typedef struct no No;
struct no
{
  int vertice;
  No *prox;
};

typedef struct grafo2
{
  int vertices;
  int arestas;
  int **adj; // Matriz de adjacência
} GRAFO2;