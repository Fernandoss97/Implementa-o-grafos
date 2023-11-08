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
  if ((vi < 0) || (vf >= gr->vertices))
    return (false);

  ADJACENCIA *novo = criaAdj(vf, p);

  novo->prox = gr->adj[vi].cab;
  gr->adj[vi].cab = novo;
  gr->arestas++;

  return (true);
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
  GRAFO *g = criaGrafo(6);

  criaAresta(g, 1, 1, 2);
  criaAresta(g, 1, 3, 5);
  criaAresta(g, 2, 4, 3);
  criaAresta(g, 2, 5, 4);
  criaAresta(g, 3, 2, 2);
  criaAresta(g, 3, 4, 3);
  criaAresta(g, 4, 5, 1);
  imprime(g);

  printf("\nLista adj\n");

  Grafo2 g2 = criaGrafo2(5);
  criaAresta2(g2, 1, 1);
  criaAresta2(g2, 1, 3);
  criaAresta2(g2, 2, 4);
  criaAresta2(g2, 2, 5);
  criaAresta2(g2, 3, 2);
  criaAresta2(g2, 3, 4);
  criaAresta2(g2, 4, 5);
  imprimeGrafo2(g2);

  return 0;
}