#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main() {
    // Test newGraph() and getOrder()
    Graph G = newGraph(5);
    printf("Order: %d\n", getOrder(G)); // Expected output: 5

    // Test addEdge() and getSize()
    addEdge(G, 1, 2);
    addEdge(G, 2, 3);
    addEdge(G, 3, 4);
    addEdge(G, 4, 5);
    printf("Size: %d\n", getSize(G)); // Expected output: 8

    // Test BFS(), getParent(), and getDist()
    BFS(G, 1);
    printf("Parent of 5: %d\n", getParent(G, 5)); // Expected output: 4
    printf("Distance to 5: %d\n", getDist(G, 5)); // Expected output: 3

    // Test getPath()
    List L = newList();
    getPath(L, G, 5);
    printf("Path to 5: ");
    printList(stdout, L); // Expected output: 1 2 3 4 5
    printf("\n");

    // Test makeNull() and printGraph()
    makeNull(G);
    printf("Size after makeNull(): %d\n", getSize(G)); // Expected output: 0
    printf("Graph:\n");
    printGraph(stdout, G); // Expected output: an empty graph

    // Test freeGraph()
    freeGraph(&G);
    printf("Graph freed\n");


    return 0;
}
