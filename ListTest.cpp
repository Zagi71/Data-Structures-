#include <cstdio>
#include <iostream>
#include <ostream>
#include "List.h"



int main() {
    List l;
    l.insertBefore(1);
    l.insertBefore(2);
    l.insertBefore(3);
    std::cout << l << std::endl;
    
    // Equality Tests:
    std::cout << "Equality Tests ...\n";
    List l2;
    std::cout << l2 << " == " << l << " -> "
        << l2.equals(l) << std::endl;
    std::cout << l << " == " << l2 << " -> "
        << l2.equals(l) << std::endl;
    l2.insertBefore(1);
    std::cout << l2 << " == " << l << " -> "
        << l2.equals(l) << std::endl;
    std::cout << l << " == " << l2 << " -> "
        << l2.equals(l) << std::endl;
    l2.insertBefore(2);
    l2.insertBefore(3);
    std::cout << l2 << " == " << l << " -> "
        << l2.equals(l) << std::endl;
    std::cout << l << " == " << l2 << " -> "
        << l2.equals(l) << std::endl;
    std::cout << std::endl;
    
    // Find Tests
    std::cout << "Find Tests ...\n";
    auto test_findNext = [&](List&l, ListElement x) {
        int pos = l.findNext(x);
        if (pos < 0) std::cout << x <<" not found\n";
        else std::cout << x << " found, cursor pos " << pos << std::endl;
    };
    List l3;
    l3.insertBefore(1);
    l3.insertBefore(2);
    l3.insertBefore(3);
    l3.insertBefore(5);
    l3.insertBefore(8);
    l3.insertBefore(2);
    l3.insertBefore(3);
    l3.moveFront();
    std::cout << l3 << std::endl;
    test_findNext(l3, 8);
    test_findNext(l3, 3);
    l3.moveFront();
    test_findNext(l3, 8);
    test_findNext(l3, 1);
    l3.moveFront();
    test_findNext(l3, 1);
    test_findNext(l3, 2);
    test_findNext(l3, 2);
    std::cout << std::endl;

    // Cleanup Test 
    std::cout << "Cleanup Test ...\n";
    l3.insertBefore(11);
    std::cout << l3 << std::endl;
    l3.moveFront();
    for(int i = 0; i < 6; i++) l3.moveNext();
    printf("Cursor: %d, Before: %d, After: %d\n",
           l3.position(), l3.peekPrev(), l3.peekNext());
    l3.cleanup();
    std::cout << l3 << std::endl;
    printf("Cursor: %d, Before: %d, After: %d\n",
           l3.position(), l3.peekPrev(), l3.peekNext());
    std::cout << std::endl;

    // Concat Test
    std::cout << "Concat Test ...\n";
    std::cout << l3 << " ++ " << l2 << std::endl;
    List l4 = l3.concat(l2);
    std::cout << l4 << std::endl;
    std::cout << std::endl;

    // Clear Test 
    std::cout << "Clear Test ...\n";
    std::cout << l4 << std::endl;
    l4.clear();
    std::cout << l4 << std::endl;
    printf("Cursor: %d, Length: %d\n", 
           l4.position(), l4.length());
    std::cout << std::endl;

    // Copy/Assign Test 
    std::cout << "Copy/Assign Test ...\n";
    List l5 = l3;
    l5.insertBefore(13);
    std::cout << l5 << std::endl;
    l5.moveNext();
    l5.moveNext();
    List l6;
    l6 = l5;
    std::cout << l6 << std::endl;
    printf("Cursor: %d, Before: %d, After: %d\n",
           l5.position(), l5.peekPrev(), l5.peekNext());
    printf("Cursor: %d, Before: %d, After: %d\n",
           l6.position(), l6.peekPrev(), l6.peekNext());
    std::cout << std::endl;

    return 0;
}
