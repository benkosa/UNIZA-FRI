#include "Karta.h"

Karta::Karta() {}

Karta::Karta(int cislo, char znak) {
	this->cislo = cislo;
	this->znak = znak;
}

Karta::Karta(const Karta& other) {
	if (!other.cislo) return;

	this->cislo = other.cislo;
	this->znak = other.znak;
}

Karta& Karta::operator=(const Karta& other) {
	if (this == &other) return *this;

	if (!other.cislo) return *this;

	this->cislo = other.cislo;
	this->znak = other.znak;

	return *this;
}

int Karta::getCislo() {
	return this->cislo;
}

char Karta::getZnak() {
	return this->znak;
}

bool Karta::somKarta(int cislo, char znak) {
	return (this->cislo == cislo && this->znak == znak);
}

void Karta::vypis() {
	std::cout << this->cislo << "-" << this->znak << " ";
}

bool operator<(const Karta& a, const Karta& b) {

	if (a.cislo == b.cislo)
		return a.znak > b.znak;

	return a.cislo < b.cislo;
}
