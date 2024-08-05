#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cctype>
#include "Dictionary.h"

static __inline__ char lower(char c) {
    return c + ('a'-'A');
}

static void string_lower(std::string& s) {
    for(char& c: s) {
        if (c >= 'A' && c <= 'Z') c = lower(c);
    }
}

int main (int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Missing Input File Argument\n"
                     "Usage: ./WordFrequency <input file> <output file>\n";
        return EXIT_FAILURE;
    }

    std::fstream infs(argv[1], std::ios_base::in);

    std::string line, token;
    const std::string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    Dictionary D;
    for(; std::getline(infs, line);) {
        size_t len = line.length();
        size_t begin = std::min(line.find_first_not_of(delim, 0), len);
        size_t end = std::min(line.find_first_of(delim, begin), len);
        token = line.substr(begin, end-begin);
        
        while(token != "") {
            string_lower(token);
            if (D.contains(token)) {
                valType count = D.getValue(token);
                D.setValue(token, count+1);
            } else {
                D.setValue(token, 1);
            }
            begin = std::min(line.find_first_not_of(delim, end+1), len);
            end = std::min(line.find_first_of(delim, begin), len);
            token = line.substr(begin, end-begin);
        }
    }

    std::fstream outfs(argv[2], std::ios_base::out);
    outfs << D << '\n';

    infs.close();
    outfs.close();

    return EXIT_SUCCESS;
}
