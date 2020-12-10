// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include "Team.h"
#include "Hra.h"
#include <time.h>


int main(int argc, char* argv[]) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    if (argc != 2) {
        std::cout << "povinny jeden argument - nazov vstupneho suboru\n";
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    char* nazovSuboru = argv[1];

    const int DLZKA = 255;
    char* riadok = new char[DLZKA];

    FILE* fp = fopen(nazovSuboru, "r");
    if (fp == NULL) {
        std::cout << "Chyba pri otvarani suboru\n";
        exit(EXIT_FAILURE);
    }

    Hra *hra = new Hra;
        
    //naciatnie suboru
    while ((fgets(riadok, DLZKA, fp)) != NULL) {
        hra->pridaj(riadok);
    }

    //hra->vypisPoradie();
    hra->spustitHru();
    std::cout << "////////////////////////////////////////////\n";
    hra->vypisPoradie();

    fclose(fp);
    delete[] riadok;
    delete hra;
    return 0;
}