#pragma once
#include <string>
#include <iostream>
#include <string>
using namespace std;
class Zajazd {
private:
	string nazovDestinacie;
	unsigned int cena = 0;
	string typDopravy;
	unsigned int vzdialenost = 0;

	Zajazd* dalsi = nullptr;
public:
	Zajazd() {};
	Zajazd(string nazovDestinacie, unsigned int cena, string typDopravy, unsigned int vzdialenost);

	Zajazd* getDalsi() { return this->dalsi; };

	void setDalsi(Zajazd& dalsi) { this->dalsi = &dalsi; };

	int getCena() { return this->cena;  };


	friend ostream& operator<<(ostream& os, const Zajazd& zajazd);
};

