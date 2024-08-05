#include <iostream>
#include "Dictionary.h"

int main() {
    Dictionary D;
    D.setValue("D", 'D');
    D.setValue("B", 'B');
    D.setValue("A", 'A');
    D.setValue("C", 'C');
    D.setValue("T", 'T');
    D.setValue("U", 'U');
    D.setValue("Y", 'Y');
    D.setValue("W", 'Y');
    D.setValue("H", 'H');
    D.setValue("G", 'G');
    D.setValue("E", 'E');
    D.setValue("P", 'P');
    D.setValue("R", 'R');
    D.setValue("Q", 'Q');
    D.setValue("S", 'S');
    D.setValue("J", 'J');
    D.setValue("I", 'I');
    D.setValue("L", 'L');
    D.setValue("N", 'N');
    D.setValue("M", 'M');
    D.setValue("O", 'O');
    std::cout << D.to_string() << std::endl;
    D.remove("I");
    std::cout << D.to_string() << std::endl;
    D.remove("H");
    std::cout << D.to_string() << std::endl;
    D.remove("D");
    std::cout << D.to_string() << std::endl;
    D.remove("U");
    std::cout << D.to_string() << std::endl;
    D.remove("N");
    std::cout << D.to_string() << std::endl;

    Dictionary E;
    E.setValue("F", 1);
    E.setValue("B", 2);
    E.setValue("H", 3);
    std::cout << E.to_string() << std::endl;
    E.remove("F");
    std::cout << E.to_string() << std::endl;
    E.remove("B");
    std::cout << E.to_string() << std::endl;
    E.remove("H");
    std::cout << E.to_string() << std::endl;

    std::cout << D.to_string() << std::endl;
    std::cout << D.pre_string() << std::endl;

    for(D.begin(); D.hasCurrent(); D.next()) {
        std::cout << D.currentKey() << ',' << D.currentVal() << '\n';
    }
    std::cout << std::endl;
    for(D.end(); D.hasCurrent(); D.prev()) {
        std::cout << D.currentKey() << ',' << D.currentVal() << '\n';
    }

    Dictionary F = D;
    std::cout << F << std::endl;
    std::cout << D << std::endl;
    if (F==D) std::cout << "F equals D\n";
    else std::cout << "F does not equal D\n";
    F.remove("C");
    std::cout << F << std::endl;
    std::cout << D << std::endl;
    if (F==D) std::cout << "F equals D\n";
    else std::cout << "F does not equal D\n";

    D.clear();
    std::cout << D.to_string() << std::endl;
}
