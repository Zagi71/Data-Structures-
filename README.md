## Programming Assignemt 1: Lex

This project consists of a main program, Lex.c, and a List Abstract Data Type (ADT) module contained in List.h and List.c. The List ADT module exports its services to the client module Lex.c.

## Files
Lex.c: This is the main program for the project. It uses the services of the List ADT module.
List.h: This is the header file for the List ADT. It contains the declarations of the List operations.
List.c: This is the implementation file for the List ADT. It contains the definitions of the List operations.

## Usage
Lex.c takes two command line arguments: the names of an input file and an output file, respectively.

### Run Lex.c

```
  make Lex
./Lex input.txt output.txt
```

### Run ListTest

```
  make ListTest
./ListTest
```

### Run Valgrind

```
make 
valgrind Lex input_file output_file
```

## txt
List ADT Operations
The List ADT operations are specified in detail in List.h and List.c.