#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "Uzol.h"
#include "Zoznam.h"

using namespace std;

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    string line;
    ifstream infile("vstup.txt");
    Zoznam* zoznam = new Zoznam();

    while (getline(infile, line)) {
        Uzol* uzol = new Uzol(line.c_str());
        zoznam->pridaj(*uzol);
    }

    zoznam->vypis();
    zoznam->zapis();

    string mystr;
    std::cout << "Zadaj zacinajuce pismeno: ";
    getline(cin, mystr);
    if(mystr.length())
        zoznam->vypisZacinajucePismenom(mystr[0]);

    delete zoznam;
}
