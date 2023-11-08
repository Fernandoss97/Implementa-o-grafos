typedef struct no No;
struct no
{
  int vertice;
  No *prox;
};

typedef struct grafo2
{
  No **A;
  int v;
  int a;
} *Grafo2;
