#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "BigInteger.h"

int main (int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "You need 2 arguments:\n"
                     "Usage: Arithmetic <input file> <output file>\n";
        return EXIT_FAILURE;
    }

    std::fstream infs(argv[1], std::ios_base::in);
    std::string num;
    std::getline(infs, num);
    BigInteger A(num);
    std::getline(infs, num);
    std::getline(infs, num);
    BigInteger B(num);
    infs.close();

    std::fstream outfs(argv[2], std::ios_base::out);

    outfs << A << '\n' << '\n';
    outfs << B << '\n' << '\n';
    outfs << A+B << '\n' << '\n';
    outfs << A-B << '\n' << '\n';
    outfs << A-A << '\n' << '\n';
    outfs << 3*A - 2*B << '\n' << '\n';
    outfs << A*B << '\n' << '\n';
    outfs << A*A << '\n' << '\n';
    outfs << B*B << '\n' << '\n';
    outfs << 9*(A*A*A*A) + 16*(B*B*B*B*B) << '\n' << '\n';

    outfs.close();

    return EXIT_SUCCESS;
}   
