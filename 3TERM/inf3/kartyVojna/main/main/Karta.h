#pragma once
#include <iostream>

class Karta {
private:
	int cislo;
	char znak;
public:
	Karta();
	Karta(int cislo, char znak);
	Karta(const Karta& other);
	Karta& operator=(const Karta& other);

	friend bool operator<(const Karta& a, const Karta& b);

	int getCislo();
	char getZnak();

	bool somKarta(int cislo, char znak);

	void vypis();

};

