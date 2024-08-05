#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"
#include "List.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define INF -1
#define NIL 0


Graph newGraph(int n){
    Graph G = malloc(sizeof(struct GraphObj));
    assert(G != NULL);
    G->adj = calloc(n+1, sizeof(List));
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->distance = calloc(n+1, sizeof(int));
    G->order = n;
    G->size = 0;
    G->source = NIL;
    for (int i = 1; i <= n; i++) {
        G->adj[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    return G;
}

void freeGraph(Graph* pG){
    if (pG == NULL || *pG == NULL) {
        return;
    }
    for (int i = 1; i <= (*pG)->order; i++) {
        freeList(&((*pG)->adj[i]));
    }
    free((*pG)->adj);
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->distance);
    free(*pG);
    *pG = NULL;
}

int getOrder(Graph G){
    if (G == NULL) {
        return -1;
    }
    return G->order;
}

int getSize(Graph G){
    if (G == NULL) {
        return -1;
    }
    return G->size;
}

int getSource(Graph G){
    if (G == NULL) {
        return NIL;
    }
    return G->source;
}

int getParent(Graph G, int u){
    if (G == NULL) {
        return NIL;
    }
    if (u < 1 || u > getOrder(G)) {
        return NIL;
    }
    return G->parent[u];
}

int getDist(Graph G, int u){
    if (G == NULL) {
        return INF;
    }
    if (u < 1 || u > getOrder(G)) {
        return INF;
    }
    return G->distance[u];
}

void getPath(List L, Graph G, int u){
    if (G == NULL) {
        return;
    }
    if (u < 1 || u > getOrder(G)) {
        return;
    }
    if (getSource(G) == NIL) {
        return;
    }
    if (u == getSource(G)) {
        append(L, u);
        return;
    }
    if (G->parent[u] == NIL) {
        append(L, NIL);
        return;
    }
    getPath(L, G, G->parent[u]);
    append(L, u);
}

void makeNull(Graph G){
    if (G == NULL) {
        return;
    }
    for (int i = 1; i <= getOrder(G); i++) {
        clear(G->adj[i]);
    }
    G->size = 0;
}


void addEdge(Graph G, int u, int v){
    if (G == NULL) {
        return;
    }
    if (u < 1 || u > getOrder(G)) {
        return;
    }
    if (v < 1 || v > getOrder(G)) {
        return;
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
}

void addArc(Graph G, int u, int v){
    if (G == NULL) {
        return;
    }
    
    if (u < 1 || u > getOrder(G)) {
        return;
    }
    if (v < 1 || v > getOrder(G)) {
        return;
    }
    List L = G->adj[u];
    moveFront(L);
    while (index(L) != -1 && v > get(L)) {
        moveNext(L);
    }
    if (index(L) == -1) {
        append(L, v);
    } else {
        insertBefore(L, v);
    }
    G->size++;


}

void BFS(Graph G, int s){
    if (G == NULL) {
        return;
    }
    if (s < 1 || s > getOrder(G)) {
        return;
    }
    for (int i = 1; i <= getOrder(G); i++) {
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->distance[i] = INF;
        
    }
    G->source = s;
    G->color[s] = GRAY;
    G->distance[s] = 0;
    List Q = newList();
    append(Q, s);
    while (length(Q) > 0) {
        int u = front(Q);
        deleteFront(Q);
        List L = G->adj[u];
        moveFront(L);
        while (index(L) != -1) {
            // printf("TES");
            int v = get(L);
            if (G->color[v] == WHITE) {
                G->color[v] = GRAY;
                G->distance[v] = G->distance[u] + 1;
                G->parent[v] = u;
                append(Q, v);
            }
            moveNext(L);
            
        }
        G->color[u] = BLACK;
    }
    freeList(&Q);
    // Q = NULL;
}

void printGraph(FILE* out, Graph G){
    if (G == NULL) {
        return;
    }
    for (int i = 1; i <= getOrder(G); i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
    }
}