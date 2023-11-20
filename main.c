#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "listaAdj.h"
#define true 1
#define false 0
typedef int bool;
typedef int TIPOPESO;

typedef struct adjacencia
{
  int vertice;
  TIPOPESO peso;
  struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice
{
  ADJACENCIA *cab;
} VERTICE;

typedef struct grafo
{
  int vertices;
  int arestas;
  VERTICE *adj;
} GRAFO;

GRAFO2 *criaGrafo2(int v)
{
  int i, j;

  GRAFO2 *g = (GRAFO2 *)malloc(sizeof(GRAFO2));
  g->vertices = v;
  g->arestas = 0;

  // Aloca a matriz de adjacência
  g->adj = (int **)malloc(v * sizeof(int *));
  for (i = 0; i < v; i++)
  {
    g->adj[i] = (int *)malloc(v * sizeof(int));
    for (j = 0; j < v; j++)
    {
      g->adj[i][j] = 0; // Inicializa todas as entradas como 0
    }
  }

  return g;
}

GRAFO *criaGrafo(int v)
{
  int i;

  GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
  g->vertices = v;
  g->arestas = 0;
  g->adj = (VERTICE *)malloc(v * sizeof(VERTICE));

  for (i = 0; i < v; i++)
  {
    g->adj[i].cab = NULL;
  }

  return (g);
}

ADJACENCIA *criaAdj(int v, int peso)
{
  ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
  temp->vertice = v;
  temp->peso = peso;
  temp->prox = NULL;
  return (temp);
}

bool criaAresta2(GRAFO2 *gr, int vi, int vf, TIPOPESO p)
{
  if (!gr)
    return false;
  if ((vf < 0) || (vf >= gr->vertices))
    return false;
  if ((vi < 0) || (vi >= gr->vertices))
    return false;

  gr->adj[vi][vf] = p;
  gr->arestas++;

  return true;
}

bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p)
{
  if (!gr)
    return (false);
  if ((vf < 0) || (vf >= gr->vertices))
    return (false);
  if ((vi < 0) || (vi >= gr->vertices))
    return (false);

  ADJACENCIA *novo = criaAdj(vf, p);

  novo->prox = gr->adj[vi].cab;
  gr->adj[vi].cab = novo;
  gr->arestas++;

  return (true);
}

void buscaLargura(GRAFO *gr, int ini, int *vis)
{
  int i, vert, nv, cont = 1, *fila, IF = 0, FF = 0;

  for (i = 0; i < gr->vertices; i++)
  {
    vis[i] = 0;
  }

  nv = gr->vertices;
  fila = (int *)malloc(nv * sizeof(int));
  FF++;
  fila[FF] = ini;
  vis[ini] = cont;

  while (IF != FF)
  {
    IF = (IF + 1) % nv;
    vert = fila[IF];
    cont++;
    printf("Visitando vertice %d\n", vert);

    ADJACENCIA *p = gr->adj[vert].cab;
    while (p != NULL)
    {
      if (vis[p->vertice] == 0)
      {
        FF = (FF + 1) % nv;
        fila[FF] = p->vertice;
        vis[p->vertice] = cont;
        printf("Enfileirando vertice adjacente %d\n", p->vertice);
      }
      p = p->prox;
    }
  }

  free(fila);
}

void dfsRecursivo(GRAFO *gr, int vertice, int *visitado)
{
  ADJACENCIA *p = gr->adj[vertice].cab;
  visitado[vertice] = 1;

  printf("Visitando vertice %d\n", vertice);

  while (p != NULL)
  {
    int adjacente = p->vertice;
    if (!visitado[adjacente])
    {
      dfsRecursivo(gr, adjacente, visitado);
    }
    p = p->prox;
  }
}

void buscaProfundidade(GRAFO *gr, int verticeInicial)
{
  int *visitado = (int *)malloc(gr->vertices * sizeof(int));
  int i;

  for (i = 0; i < gr->vertices; i++)
  {
    visitado[i] = 0;
  }

  printf("Busca em profundidade a partir do vertice %d:\n", verticeInicial);
  dfsRecursivo(gr, verticeInicial, visitado);

  free(visitado);
}

void inicializaDijkstra(GRAFO *grafo, int origem, int *distancia, int *anterior, bool *visitado)
{
  int i;
  for (i = 0; i < grafo->vertices; i++)
  {
    distancia[i] = 300000;
    anterior[i] = -1;
    visitado[i] = false;
  }

  distancia[origem] = 0;
}

int encontraVerticeMinimo(int *distancia, bool *visitado, int vertices)
{
  int minimo = 300000, minimoIndice = -1;
  int i;
  for (i = 0; i < vertices; i++)
  {
    if (!visitado[i] && distancia[i] < minimo)
    {
      minimo = distancia[i];
      minimoIndice = i;
    }
  }
  return minimoIndice;
}

void relaxaVizinhos(GRAFO *grafo, int u, int *distancia, int *anterior)
{
  ADJACENCIA *atual = grafo->adj[u].cab;

  while (atual != NULL)
  {
    int v = atual->vertice;
    int pesoUV = atual->peso;

    if (distancia[u] != 300000 && distancia[u] + pesoUV < distancia[v])
    {
      distancia[v] = distancia[u] + pesoUV;
      anterior[v] = u;
    }

    atual = atual->prox;
  }
}

void imprimeCaminho(int *anterior, int destino)
{
  if (anterior[destino] != -1)
  {
    imprimeCaminho(anterior, anterior[destino]);
    printf("-> %d ", destino);
  }
  else
  {
    printf("%d ", destino);
  }
}

void caminhoMaisCurto2(GRAFO2 *grafo, int origem, int destino)
{
  int *distancia = (int *)malloc(grafo->vertices * sizeof(int));
  int *anterior = (int *)malloc(grafo->vertices * sizeof(int));
  bool *visitado = (bool *)malloc(grafo->vertices * sizeof(bool));

  // Inicialização
  for (int i = 0; i < grafo->vertices; i++)
  {
    distancia[i] = INT_MAX;
    anterior[i] = -1;
    visitado[i] = false;
  }

  distancia[origem] = 0;

  // Encontrar o caminho mais curto
  for (int count = 0; count < grafo->vertices - 1; count++)
  {
    int u = -1;

    // Escolher o vértice de menor distância não visitado
    for (int i = 0; i < grafo->vertices; i++)
    {
      if (!visitado[i] && (u == -1 || distancia[i] < distancia[u]))
        u = i;
    }

    visitado[u] = true;

    // Relaxar vizinhos
    for (int v = 0; v < grafo->vertices; v++)
    {
      if (!visitado[v] && grafo->adj[u][v] && distancia[u] != INT_MAX &&
          distancia[u] + grafo->adj[u][v] < distancia[v])
      {
        distancia[v] = distancia[u] + grafo->adj[u][v];
        anterior[v] = u;
      }
    }
  }

  // Imprimir o caminho mais curto
  printf("Caminho mais curto de %d para %d: ", origem, destino);
  int atual = destino;
  while (atual != -1)
  {
    printf("%d ", atual);
    atual = anterior[atual];
  }
  printf("\n");

  free(distancia);
  free(anterior);
  free(visitado);
}

// void imprimeGrafo2(GRAFO2 g)
// {
//   int i;

//   printf("\nVertices: %d. Arestas: %d. \n", g->v, g->a);
//   for (i = 0; i < g->v; i++)
//   {
//     printf("Vertice %d: ", i);

//     No *p = g->A[i];
//     while (p != NULL)
//     {
//       printf("%d ", p->vertice);
//       p = p->prox;
//     }
//     printf("\n");
//   }
// }

void imprime(GRAFO *gr)
{
  printf("Vertices: %d. Arestas: %d. \n", gr->vertices, gr->arestas);
  int i;
  int somaPeso = 0;
  for (i = 0; i < gr->vertices; i++)
  {
    printf("v%d: ", i);
    ADJACENCIA *ad = gr->adj[i].cab;
    while (ad)
    {
      printf("v%d(%d) ", ad->vertice, ad->peso);
      somaPeso = somaPeso + ad->peso;
      ad = ad->prox;
    }
    printf("\n");
  }
  printf("Soma pesos: %d\n", somaPeso);
}

int main()
{
  int V = 6;
  GRAFO2 *grafo = criaGrafo2(V);

  // Preencher a matriz de adjacência
  grafo->adj = (int *[]){(int[]){0, 1, 4, 0, 0, 0}, (int[]){1, 0, 4, 2, 7, 0}, (int[]){4, 4, 0, 3, 5, 0}, (int[]){0, 2, 3, 0, 4, 6}, (int[]){0, 7, 5, 4, 0, 7}, (int[]){0, 0, 0, 6, 7, 0}};

  for (int i = 0; i < V; i++)
  {
    for (int j = 0; j < V; j++)
    {
      if (grafo->adj[i][j] != 0)
      {
        criaAresta2(grafo, i, j, grafo->adj[i][j]);
      }
    }
  }

  caminhoMaisCurto2(grafo, 0, 4);

  // Liberar memória
  for (int i = 0; i < V; i++)
  {
    free(grafo->adj[i]);
  }
  free(grafo->adj);
  free(grafo);

  return 0;
}