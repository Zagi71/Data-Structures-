#include "List.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

void shuffle(List& D) {
    const int len = D.length();
    List E = D;
    D.moveFront();
    E.moveFront();
    for(int i = 0; i < len/2; i++) E.moveNext();
    for(; E.position() < len; E.moveNext()) {
        D.insertBefore(E.peekNext());
        D.moveNext();
    }
    D.moveBack();
    for(; D.length() != len;) {
        D.eraseBefore();
    }
}

int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Please provide an argument (Shuffe <n>)\n";
        exit(EXIT_FAILURE);
    }
    const int n = std::stoi(std::string(argv[1]));
    if (n < 1) {
        std::cerr << "Argument should be a positive integer\n";
        exit(EXIT_FAILURE);
    }
    
    auto in_order = [](List &list) -> bool {
        list.moveFront();
        for(int i = 0; i < list.length(); i++) {
            if (list.peekNext() != i) return false;
            list.moveNext();
        }
        return true;
    };

    std::cout << std::left 
        << std::setw(16)<< "deck size" << std::setfill(' '); 
    std::cout << std::left 
         << "shuffle count"<< '\n';
    std::cout << std::setw(0) << std::string(30,'-') << '\n';

    List l;
    for(int i = 1; i <= n; i++) {
        unsigned int count = 1;
        l.moveBack();
        l.insertBefore(i-1);
        shuffle(l);
        for(;!in_order(l);) {
            shuffle(l);
            count++;
        }

        std::cout << std::left 
            << ' ' << std::setw(15) << i << std::setfill(' '); 
        std::cout << std::left 
            << std::setw(0) << ' ' <<  count << '\n'; 
    }
    return EXIT_SUCCESS;
} 
