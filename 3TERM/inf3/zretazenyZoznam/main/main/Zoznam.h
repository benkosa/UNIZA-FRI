#pragma once
#include "Uzol.h"
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
class Zoznam {
private:
	Uzol* start = nullptr;
public:
	void pridaj(Uzol& uzol);

	void vypis();

	void zapis();

	void vypisZacinajucePismenom(char pismeno);

	~Zoznam();

};

