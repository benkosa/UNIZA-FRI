// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include "Karta.h"
#include "Hrac.h"
#include "Hra.h"
#include <time.h>
#include <iostream>
#include <string>

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    srand(time(NULL));

    Hra* hra = new Hra();

    hra->generujKarty();
    hra->zamiesaj();
    hra->rozdajKarty();

    hra->spustiHru();

    hra->zistiVitza();

    string mystr;
    std::cout << "Zadaj kartu napriklad 1A: ";
    getline(cin, mystr);
    hra->najdiVlastnika(mystr[0]-48, mystr[1]);
    delete hra;
}
