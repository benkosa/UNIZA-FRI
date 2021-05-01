#pragma once
#include "Hrac.h"

//#include <iostream>
//#include <sstream>
#include <fstream>
//#include <iostream>
#include <stdio.h>

using namespace std;
class Hra {
private:
	Hrac* hrac1 = new Hrac(1);
	Hrac* hrac2 = new Hrac(2);
	Karta** balicek = new Karta * [32];
	int zapisane = 0;
public:

	Hra();

	void generujKarty();

	void zamiesaj();

	void rozdajKarty();

	void spustiHru();

	void zistiVitza();

	void swap(Karta& a, Karta& b);

	void vypis();

	void najdiVlastnika(int cislo, char znak);

	~Hra();
};

