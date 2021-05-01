#pragma once
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include "Zajazd.h"
using namespace std;
class CestovnaKancelaria {
private:
	Zajazd* start = nullptr;
public:
	void pridaj(Zajazd& uzol);

	void vypis();

	void zapis();

	void vypisMensieAko(int cena);

	~CestovnaKancelaria();

};

