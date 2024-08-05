//-----------------------------------------------------------------------------
// Dictionary.h
// Header file for Dictionary ADT based on a Binary Search Tree. Includes a
// built in iterator called current that can perform a smallest-to-largest
// (forward) or a largest-to-smallest (reverse) iteration over all keys.
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>

#ifndef DICTIONARY_H_INCLUDE_
#define DICTIONARY_H_INCLUDE_


// Exported types -------------------------------------------------------------
typedef std::string keyType;  // must be comparable using <, <=, >, >=, ==, !=
typedef int         valType;

class Dictionary{

private:

   // private Node struct
   struct Node{
      // Node fields
      keyType key;
      valType val;
      Node* parent;
      Node* left;
      Node* right;
      // Node constructor
      Node(keyType k, valType v);
   };

   // Dictionary fields
   Node* nil;
   Node* root;
   Node* current;
   int   num_pairs;

   // Helper Functions (Optional) ---------------------------------------------
   /*
    * tree_copy()
    * For an empty "this" tree it will insert all the nodes in the 
    * tree rooted at R
    */
   void tree_copy(Node *R);

   /*
    * search_r()
    * Returns a reference to the pointer that either points to the 
    * existing node or should point to a node with key k if nil 
    * Also sets the parent of the found node in P 
    */
   Node*& search_r(Node*& R, keyType k, Node*& P) const;
   
   /* 
    * search()
    * same as search_r() but no reference 
    */
   Node* search(Node *R, keyType k) const;


   // pretty prints the tree for debug
   // std::string pretty_tree() const; 
   
   /*
    * findMin()
    * returns a reference to the node with the smallest key for the 
    * subtree rooted at R 
    */
   Node*& findMin(Node*& R) const;

   /*
    * findMax()
    * same as findMin() but for the largest key 
    */
   Node*& findMax(Node*& R) const;

public:

   // Class Constructors & Destructors ----------------------------------------
   
   // Creates new Dictionary in the empty state. 
   Dictionary();

   // Copy constructor.
   Dictionary(const Dictionary& D);

   // Destructor
   ~Dictionary();


   // Access functions --------------------------------------------------------

   // size()
   // Returns the size of this Dictionary.
   int size() const;

   // contains()
   // Returns true if there exists a pair such that key==k, and returns false
   // otherwise.
   bool contains(keyType k) const;

   // getValue()
   // Returns a reference to the value corresponding to key k.
   // Pre: contains(k)
   valType& getValue(keyType k) const;

   // hasCurrent()
   // Returns true if the current iterator is defined, and returns false 
   // otherwise.
   bool hasCurrent() const;

   // currentKey()
   // Returns the current key.
   // Pre: hasCurrent() 
   keyType currentKey() const;

   // currentVal()
   // Returns a reference to the current value.
   // Pre: hasCurrent()
   valType& currentVal() const;


   // Manipulation procedures -------------------------------------------------

   // clear()
   // Resets this Dictionary to the empty state, containing no pairs.
   void clear();

   // setValue()
   // If a pair with key==k exists, overwrites the corresponding value with v, 
   // otherwise inserts the new pair (k, v).
   void setValue(keyType k, valType v);

   // remove()
   // Deletes the pair for which key==k. If that pair is current, then current
   // becomes undefined.
   // Pre: contains(k).
   void remove(keyType k);

   // begin()
   // If non-empty, places current iterator at the first (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
   void begin();

   // end()
   // If non-empty, places current iterator at the last (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
   void end();

   // next()
   // If the current iterator is not at the last pair, advances current 
   // to the next pair (as defined by the order operator < on keys). If 
   // the current iterator is at the last pair, makes current undefined.
   // Pre: hasCurrent()
   void next();

   // prev()
   // If the current iterator is not at the first pair, moves current to  
   // the previous pair (as defined by the order operator < on keys). If 
   // the current iterator is at the first pair, makes current undefined.
   // Pre: hasCurrent()
   void prev();


   // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this Dictionary. Consecutive (key, value)
   // pairs are separated by a newline "\n" character, and the items key and value 
   // are separated by the sequence space-colon-space " : ". The pairs are arranged 
   // in order, as defined by the order operator <.
   std::string to_string() const;

   // pre_string()
   // Returns a string consisting of all keys in this Dictionary. Consecutive
   // keys are separated by newline "\n" characters. The key order is given
   // by a pre-order tree walk.
   std::string pre_string() const;

   // equals()
   // Returns true if and only if this Dictionary contains the same (key, value)
   // pairs as Dictionary D.
   bool equals(const Dictionary& D) const;


   // Overloaded Operators ----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of Dictionary D into stream, as defined by
   // member function to_string().
   friend std::ostream& operator<<( std::ostream& stream, Dictionary& D );

   // operator==()
   // Returns true if and only if Dictionary A equals Dictionary B, as defined
   // by member function equals(). 
   friend bool operator==( const Dictionary& A, const Dictionary& B );

   // operator=()
   // Overwrites the state of this Dictionary with state of D, and returns a
   // reference to this Dictionary.
   Dictionary& operator=( const Dictionary& D );

};


#endif
