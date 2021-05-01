// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Adresa.h"
#include "Zajazd.h"
#include "CestovnaKancelaria.h"
using namespace std;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Adresa adr("Rene", "Novak", "Ruzova", 248, "010 01", "Zilina");
	std::cout << adr << endl;

    string line;

    CestovnaKancelaria* cestovnaKancelaria = new CestovnaKancelaria;

    //parsovanie suboru
    ifstream infile("Zajazdy.txt");
    while (getline(infile, line)) {
        string word;
        stringstream ss(line);
        string nazovDestinacie;
        int cena = 0;
        string typDopravy;
        int vzdialenost = 0;
        int i = 0;
        do {
            ss >> word;
            switch (i) {
            case 0:
                nazovDestinacie = word;
                break;
            case 1:
                cena = stoi(word);
                break;
            case 2:
                typDopravy = word;
                break;
            case 3:
                vzdialenost = stoi(word);
                break;
            }
            i++;
        } while (!ss.eof());
        Zajazd* zajazd = new Zajazd(nazovDestinacie, cena, typDopravy, vzdialenost);
        cestovnaKancelaria->pridaj(*zajazd);
    }

    cestovnaKancelaria->vypis();
    cestovnaKancelaria->zapis();

    string mystr;
    std::cout << "\nZadaj cenu: ";
    getline(cin, mystr);
    int cena = 0;
    try {
        cena = stoi(mystr);
    }
    catch(std::exception const& e) {
        cout << mystr << " nieje int\n";
        delete cestovnaKancelaria;
        return 1;
    }
    if (mystr.length())
        cestovnaKancelaria->vypisMensieAko(cena);

    delete cestovnaKancelaria;
	return 0;
}
