#pragma once
#include "Karta.h"
class Hrac {
private:
	int cisloHraca;
	int pocetKariet = 32;
	int zapisanychKariet = 0;
	int vyhratychKariet = 0;
	Karta** karty = new Karta*[pocetKariet];
	Karta** vyhrateKarty = new Karta * [pocetKariet];
public:
	Hrac(int cisloHraca);

	void pridajKartu(Karta& karta);
	void pridajVyhratuKartu(Karta& karta);

	int getPocetVyhratch();

	void vypis();

	bool mamKartu(int cislo, char znak);

	Karta& getPosledna();

	void zmazPoslednu();

	~Hrac();
};

