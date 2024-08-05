#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_
#include <stdio.h>
#include <stdbool.h>

//----------------------------------------------------
// List.h
// Header file for List ADT
// ---------------------------------------------------

// List ADT Specifications
// Your list module for this project will be a bi-directional queue that includes a "cursor" to be used for iteration.

// The List ADT represents a bi-directional queue. The queue is represented as a doubly linked list with a cursor. The cursor always points at an element, and operations are performed on the element pointed to by the cursor. The cursor is undefined initially and "points to" NULL. The List ADT contains a constructor and destructor, as well as functions for manipulating the cursor and the queue. The queue is made up of nodes, each with a "data" field and pointers to the next and previous nodes. The data field can be of any type. The List ADT also contains a function to print the list to a file (see below).


// The underlying data structure for the List ADT will be a doubly linked list. The file List.c should therefore contain a private (non-exported) struct called NodeObj and a pointer to that struct called Node. 

// The struct NodeObj should contain fields for an int (the data), and two Node references (the previous and next Nodes, respectively.) 

extern struct  NodeObj
{
    /* data */
    int data;
    struct NodeObj *next;
    struct NodeObj *prev;

} NodeObj;
typedef struct NodeObj *NodePtr;

// The struct ListObj should contain fields for a Node reference (the front Node), a Node reference (the back Node), a Node reference (the cursor Node), and an int (the length of the List), index of the cursor element.

extern struct ListObj
{
    /* data */
    struct NodeObj *head;
    struct NodeObj *tail;
    struct NodeObj *cursor;
    int index_cursor; // undefined == -1
    int length;
      
} ListObj;

typedef struct ListObj *List;




// Constructors-Destructors --------------------------

/**
 * @brief Creates a new list
 * 
 * @return	List		returns a new empty List.
 */
List newList(void);


/**
 * @brief Frees the space taken up by the list
 * 
 * @param	*pL		A pointer to the List to deallocate.
 * 				The pointer should be set to NULL!
 */
void freeList(List *pL);





// Access functions ----------------------------------

/**
 * @brief Gets the length of a list
 * 
 * @param	L	The list for which the length should be returned.
 * @return	int	The length of the list, or -1 if error
 */
int length( List L );

/**
 * @brief Get the index of cursor element 
 * 
 * @param	L	The list to get the data from
 * @return	int    The index of the cursor element, or -1 if error
 */
int index(List L);

/*
* @brief Returns the front element of L. Pre: length()>0
*
* @param L The list to get the front element from
*
* @return void* The front element of L. Pre: length()>0
*/
int front(List L);

/*
* @brief Returns the back element of L. Pre: length()>0
*
* @param L The list to get the back element from
*
* @return void* The back element of L. Pre: length()>0
*/

int back(List L);

/*
* @brief Returns cursor element of L. Pre: length()>0, index()>=0
*
* @param L The list to get the cursor element from
*
* @return void* The cursor element of L. Pre: length()>0, index()>=0
*/

int get(List L);


/**
 * @brief Returns true iff Lists A and B are in same
 * state, and returns false otherwise.
 * 
 * @param	A	The first list to compare
 * @param	B	The second list to compare
 * @return	bool	True if the lists are equal, False otherwise
 */
bool equals(List A, List B);




/**
 * @brief Retrieves the data from the entry at the specified index.
 *
 * @param L The list to retrieve the entry from.
 * @param i The index of the entry to retrieve. The 1st element has index 0.
 * @return void* The data that was stored in that entry. Returns NULL if the entry does not exist.
 */
void *getList( List L, int i );


// Manipulation functions ----------------------------

// Resets L to its original empty state.
void clear(List L); 

// Overwrites the cursor element’s data with x.
 // Pre: length()>0, index()>=0
void set(List L, int x); 

 // If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.
void moveFront(List L); 

// If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.
void moveBack(List L); 

// If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing
void movePrev(List L); 

// If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing
void moveNext(List L); 

// Insert new element into L. If L is non-empty,
 // insertion takes place before front element.
void prepend(List L, int x);

// Insert new element into L. If L is non-empty,
 // insertion takes place after back element.
void append(List L, int x);

// Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertBefore(List L, int x); 

// Insert new element after cursor.
 // Pre: length()>0, index()>=0
void insertAfter(List L, int x);

// Delete the front element. Pre: length()>0
void deleteFront(List L);

// Delete the back element. Pre: length()>0
void deleteBack(List L);

// Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0
void delete(List L);


// Other operations -----------------------------------------------------------
void printList(FILE* out, List L); // Prints to the file pointed to by out, a
 // string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
List copyList(List L); // Returns a new List representing the same integer
 // sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.

// Returns a new List which is the concatenation of
 // A and B. The cursor in the new List is undefined,
 // regardless of the states of the cursors in A and B.
 // The states of A and B are unchanged.
List concatList(List A, List B); 
#endif