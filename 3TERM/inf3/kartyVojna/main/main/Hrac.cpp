#include "Hrac.h"

Hrac::Hrac(int cisloHraca) {
	this->cisloHraca = cisloHraca;
}

void Hrac::pridajKartu(Karta& karta) {
	this->karty[this->zapisanychKariet++] = &karta;
}

void Hrac::pridajVyhratuKartu(Karta& karta) {
	this->vyhrateKarty[this->vyhratychKariet++] = &karta;
}

int Hrac::getPocetVyhratch() {
	return this->vyhratychKariet;
}

void Hrac::vypis() {
	for (int i = 0; i < this->zapisanychKariet; i++) {
		this->karty[i]->vypis();
	}
}

bool Hrac::mamKartu(int cislo, char znak) {
	for (int i = 0; i < vyhratychKariet; i++) {
		if (this->vyhrateKarty[i]->somKarta(cislo, znak))
			return true;
	}
	return false;
}

Karta& Hrac::getPosledna() {
	return *this->karty[this->zapisanychKariet - 1];
}

void Hrac::zmazPoslednu() {
	this->karty[--this->zapisanychKariet] = nullptr;
}

Hrac::~Hrac() {
	//jednotlive karty sa mazu v hre
	delete[] this->karty;
	delete[] this->vyhrateKarty;
}
