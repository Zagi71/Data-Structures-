#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define INF -1
#define NIL 0

int main(int argc, char* argv[]) {
    FILE *in, *out;
    int n, u, v, source, destination;
    List path = newList();
    Graph G = NULL;

    // check command line for correct number of arguments
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // read in the number of vertices
    fscanf(in, "%d", &n);
    G = newGraph(n);

    // read in the edges
    while (fscanf(in, "%d %d", &u, &v) == 2) {
        if (u == 0 && v == 0) {
            break;
        }
        addEdge(G, u, v);
    }

    // print adjacency list representation of G
    printGraph(out, G);
    fprintf(out, "\n");

    // While loop to read in pairs of vertices to run BFS on
    while (fscanf(in, "%d %d", &source, &destination) == 2) {
        if (source == 0 && destination == 0) {
            break;
        }
        
        BFS(G, source);
        getPath(path, G, destination);
        if (getDist(G, destination) == INF) {
            fprintf(out, "The distance from %d to %d is infinity\n", source, destination);
            fprintf(out, "No %d-%d path exists\n", source, destination);
        } else {
            fprintf(out, "The distance from %d to %d is %d\n", source, destination, getDist(G, destination));
            fprintf(out, "A shortest %d-%d path is: ", source, destination);
            printList(out, path);
            fprintf(out, "\n");
        }
        fprintf(out, "\n");
        clear(path);
    
    }

   

    freeList(&path);
    freeGraph(&G);
 
 // close files
    fclose(in);
    fclose(out);
    return(0);
}