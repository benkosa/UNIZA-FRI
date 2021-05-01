#pragma once
#include <string>
#include <iostream>

using namespace std;

class Adresa {
private:
	string aMeno;
	string aPriezvisko;
	string aUlica;
	unsigned int aCislo;
	string aPSC;
	string aObec;
public:
	Adresa(const char* meno, const char* priezvisko, const char* ulica, unsigned cislo, const char* psc, const  char* obec)
		: aMeno(meno), aPriezvisko(priezvisko), aUlica(ulica), aCislo(cislo), aPSC(psc), aObec(obec) {}

	friend ostream& operator<<(ostream& os, const Adresa& dt) {
		os << dt.aMeno << " " << dt.aPriezvisko << "\n" << dt.aUlica << " " << dt.aCislo << "\n" << dt.aPSC << " " << dt.aObec << "\n";
		return os;
	}
};
