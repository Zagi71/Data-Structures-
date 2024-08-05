# Programming Assignment 5
This Assignment contains the implementation of a List ADT and a Shuffle program.

## Files

- `List.h`: Header file for List ADT. List is a double ended queue with a vertical cursor standing between elements.
- `List.cpp`: Implementation of the List ADT.
- `ListTest.cpp`: Contains tests for the List ADT.
- `Shuffle.cpp`: A program that, for a positive integer input `n`, lists down the number of Riffle Shuffles needed for a permutation to return back to itself.
- `Makefile`: Used to compile and run the programs.

## Usage

### Shuffle
The program `Shuffle.c` for a positive integer input `n` will list down the number of Riffle Shuffles needed to for a permutation return back to itself.

Usage: 
```
$ make
$ ./Shuffle <n>
```
where <n> is a positve integer

## List ADT
The file `List.h` provides the class and method declarations. 
To compile and run the tests for the List ADT: 
```
$ make ListTest
$ ./ListTest
```