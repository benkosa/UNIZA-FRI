#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "Container.h"

using namespace std;

int main (int argc, char* argv[]) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    if (argc != 2) {
        std::cout << "povinny jeden argument - nazov vstupneho suboru\n";
        exit(EXIT_FAILURE);
    }

    string line;
    ifstream infile(argv[1]);
    int countStudents = 0;

    while (getline(infile, line)) countStudents++;

    Container* zoznam = new Container(countStudents);

    ifstream infile2(argv[1]);
    while (getline(infile2, line)) {
        zoznam->pridajStudenta(line);
    }

    zoznam->vypis();

    infile.close();
    infile2.close();

    delete zoznam;

}

