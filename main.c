#include <stdio.h>
#include <stdlib.h>
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

Grafo2 criaGrafo2(int v)
{
  int i;
  Grafo2 g = malloc(sizeof *g);
  g->v = v;
  g->a = 0;
  g->A = malloc(v * sizeof(No *));
  for (i = 0; i < v; i++)
  {
    g->A[i] = NULL;
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

void criaAresta2(Grafo2 g, int vi, int vf)
{
  No *p;

  for (p = g->A[vi]; p != NULL; p = p->prox)
  {
    if (p->vertice == vf)
    {
      return;
    }
  }
  p = malloc(sizeof(No));
  p->vertice = vf;
  p->prox = g->A[vi];
  g->A[vi] = p;
  g->a++;
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

void caminhoMaisCurto2(GRAFO *grafo, int origem, int destino)
{
  int *distancia = (int *)malloc(grafo->vertices * sizeof(int));
  int *anterior = (int *)malloc(grafo->vertices * sizeof(int));
  bool *visitado = (bool *)malloc(grafo->vertices * sizeof(bool));

  inicializaDijkstra(grafo, origem, distancia, anterior, visitado);

  int i;
  for (i = 0; i < grafo->vertices - 1; i++)
  {
    int u = encontraVerticeMinimo(distancia, visitado, grafo->vertices);
    visitado[u] = true;

    relaxaVizinhos(grafo, u, distancia, anterior);
  }

  printf("Caminho mais curto de %d para %d: ", origem, destino);
  imprimeCaminho(anterior, destino);
  printf("\n");

  free(distancia);
  free(anterior);
  free(visitado);
}

void imprimeGrafo2(Grafo2 g)
{
  int i;

  printf("\nVertices: %d. Arestas: %d. \n", g->v, g->a);
  for (i = 0; i < g->v; i++)
  {
    printf("Vertice %d: ", i);

    No *p = g->A[i];
    while (p != NULL)
    {
      printf("%d ", p->vertice);
      p = p->prox;
    }
    printf("\n");
  }
}

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
  GRAFO *g = criaGrafo(5);

  criaAresta(g, 0, 1, 3);
  criaAresta(g, 0, 2, 2);
  criaAresta(g, 1, 2, 1);
  criaAresta(g, 1, 3, 5);
  criaAresta(g, 2, 3, 3);
  criaAresta(g, 2, 4, 6);
  criaAresta(g, 3, 4, 4);

  imprime(g);
  caminhoMaisCurto2(g, 0, 4);

  return 0;
}