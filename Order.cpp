#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include "Dictionary.h"

int main (int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Missing Input File Argument\n"
                     "Usage: ./Order <input file> <output file>\n";
        return EXIT_FAILURE;
    }
    
    std::fstream infs(argv[1], std::ios_base::in);
    
    std::string key;
    unsigned int line_no = 1;
    Dictionary D;
    for(; std::getline(infs, key); line_no++) {
        D.setValue(key, line_no);
    }

    std::fstream outfs(argv[2], std::ios_base::out);

    outfs << D << '\n';
    outfs << D.pre_string() << '\n';

    infs.close();
    outfs.close();

    return EXIT_SUCCESS;
}
