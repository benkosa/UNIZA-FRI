#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "ZoznamStudentov.h"

using namespace std;

int main(int argc, char* argv[]) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    if (argc != 2) {
        std::cout << "povinny jeden argument - nazov vstupneho suboru\n";
        exit(EXIT_FAILURE);
    }

    string line, word;
    ifstream infile(argv[1]);
    int countStudents = 0;

    while (getline(infile, line)) countStudents++;

    ZoznamStudentov* zoznam = new ZoznamStudentov(countStudents);
    
    ifstream infile2(argv[1]);
    while (getline(infile2, line)) {
        zoznam->pridajStudenta(line);
    }

    zoznam->vypis();

    zoznam->zapis();

    delete zoznam;

    return 0;
}

