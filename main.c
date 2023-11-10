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
  GRAFO *g = criaGrafo(15);

  criaAresta(g, 0, 1, 0);
  criaAresta(g, 0, 2, 0);
  criaAresta(g, 1, 3, 0);
  criaAresta(g, 1, 4, 0);
  criaAresta(g, 1, 5, 0);
  criaAresta(g, 3, 6, 0);
  criaAresta(g, 3, 7, 0);
  criaAresta(g, 5, 8, 0);
  criaAresta(g, 5, 9, 0);
  criaAresta(g, 7, 10, 0);
  criaAresta(g, 7, 11, 0);
  criaAresta(g, 7, 12, 0);
  criaAresta(g, 9, 13, 0);
  criaAresta(g, 9, 14, 0);

  imprime(g);
  printf("\n");

  int *vis = (int *)malloc(g->vertices * sizeof(int));

  // Define o vertice de partida
  int vertice = 0;

  // Busca em largura
  printf("Busca em largura a partir do vertice %d:\n", vertice);
  buscaLargura(g, vertice, vis);
  free(vis);

  GRAFO *g2 = criaGrafo(15);

  criaAresta(g2, 0, 1, 0);
  criaAresta(g2, 1, 2, 0);
  criaAresta(g2, 1, 4, 0);
  criaAresta(g2, 2, 3, 0);
  criaAresta(g2, 2, 4, 0);
  criaAresta(g2, 2, 9, 0);
  criaAresta(g2, 3, 4, 0);
  criaAresta(g2, 4, 5, 0);
  criaAresta(g2, 4, 6, 0);
  criaAresta(g2, 4, 7, 0);
  criaAresta(g2, 5, 6, 0);
  criaAresta(g2, 7, 8, 0);
  criaAresta(g2, 7, 9, 0);

  imprime(g2);

  // Busca em profundidade
  printf("\n");
  buscaProfundidade(g2, vertice);

  return 0;
}