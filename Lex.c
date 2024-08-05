// Include necessary header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

int main(int argc, char *argv[]) {
    // Check command line arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }

    // Open the input file
    FILE *in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        return 1;
    }

    // Count the number of lines in the input file
    int n = 0;
    char line[100];
    while (fgets(line, 100, in) != NULL) {
        n++;
    }

    // Create a string array and read the lines from the input file
    char **lines = malloc(n * sizeof(char *));
    rewind(in);
    int i = 0;
    while (fgets(line, 100, in) != NULL) {
        lines[i] = malloc(100 * sizeof(char));
        strcpy(lines[i], line);
        i++;
    }
    fclose(in);

    // Create an empty List for storing the indices
    List indices = newList();

    // Insert the indices into the List in a sorted order
    // Insert the indices into the List in a sorted order
    for (i = 0; i < n; i++) {
        if (length(indices) == 0) {
            append(indices, i);
        } else {
            moveFront(indices);
            while (index(indices) >= 0 && strcmp(lines[i], lines[get(indices)]) >= 0) {
                moveNext(indices);
            }
            if (index(indices) >= 0) {
                insertBefore(indices, i);
            } else {
                append(indices, i);
            }
        }
    }


    // Open the output file
    FILE *out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        return 1;
    }

    // Print the strings in a sorted order to the output file
    // also check if same alphabetical order , add next line and print it
    
    // Print the strings in a sorted order to the output file
    // also check if same alphabetical order , add next line and print it
    char *prevLine = NULL;
    for (moveFront(indices); index(indices) >= 0; moveNext(indices)) {
        // add new line if same alphabetical order
        if (prevLine != NULL && strcmp(lines[get(indices)], prevLine) == 0) {
            fprintf(out, "\n");
        }
        prevLine = lines[get(indices)];
        fprintf(out, "%s", prevLine);
    }

    // Close the output file
    fclose(out);

    // Free the memory
    for (i = 0; i < n; i++) {
        free(lines[i]);
    }
    free(lines);
    freeList(&indices);

    return 0;
}