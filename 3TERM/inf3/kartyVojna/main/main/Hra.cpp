#include "Hra.h"

Hra::Hra() {}

void Hra::generujKarty() {
	for (int i = 1; i < 9; i++) {
		for (char j = 'A'; j < 'E'; j++) {
			//std::cout << i << j << "\n";
			this->balicek[zapisane++] = new Karta(i, j);
		}
	}
}

void Hra::zamiesaj() {
	for (int i = 0; i < this->zapisane; i++) {
		int i1 = rand() % this->zapisane;
		int i2 = rand() % this->zapisane;

		swap(*this->balicek[i1], *this->balicek[i2]);
	}
}

void Hra::rozdajKarty() {
	for (int i = 0; i < this->zapisane; i++) {
		if (i % 2) {
			this->hrac1->pridajKartu(*this->balicek[i]);
		} else {
			this->hrac2->pridajKartu(*this->balicek[i]);
		}
	}
}

void Hra::spustiHru() {
	std::cout << "ZACALA HRA\n";
	for (int i = 0; i < this->zapisane/2; i++) {
		//berie hrac 2
		if (this->hrac1->getPosledna() < this->hrac2->getPosledna()) {
			//vypis
			this->hrac1->getPosledna().vypis();
			this->hrac2->getPosledna().vypis();
			std::cout << " 2 \n";
			//pridanie kariet
			this->hrac2->pridajVyhratuKartu(this->hrac1->getPosledna());
			this->hrac2->pridajVyhratuKartu(this->hrac2->getPosledna());
			//zmazanie kariet
			this->hrac1->zmazPoslednu();
			this->hrac2->zmazPoslednu();
		//berie hrac 1
		} else {
			//vypis
			this->hrac1->getPosledna().vypis();
			this->hrac2->getPosledna().vypis();
			std::cout << " 1 \n";
			//pridanie kariet
			this->hrac1->pridajVyhratuKartu(this->hrac1->getPosledna());
			this->hrac1->pridajVyhratuKartu(this->hrac2->getPosledna());
			//zmazanie kariet
			this->hrac1->zmazPoslednu();
			this->hrac2->zmazPoslednu();
		}
	}
}

void Hra::zistiVitza() {
	std::cout << "Vyhodnotenie" << "\n";
	std::cout << hrac1->getPocetVyhratch() << ":" << hrac2->getPocetVyhratch() << "\n";
	//remiza
	if (hrac1->getPocetVyhratch() == hrac2->getPocetVyhratch()) {
		if (hrac1->mamKartu(1, 'A'))
			std::cout << "Vyhral hrac 1 po remize" << "\n";
		else
			std::cout << "Vyhral hrac 2 po remize" << "\n";
	//vyhral hrac 2
	} else if (hrac1->getPocetVyhratch() < hrac2->getPocetVyhratch()) {
		std::cout << "Vyhral hrac 2" << "\n";
	//vyhral hrac 1
	} else {
		std::cout << "Vyhral hrac 1" << "\n";
	}

	//zapis do suboru
	ofstream myfile("vystup.txt");
	if (myfile.is_open()) {
		myfile << "1: " << hrac1->getPocetVyhratch() << "\n";
		myfile << "2: " << hrac2->getPocetVyhratch() << "\n";
	} else std::cout << "Unable to open file";

	myfile.close();
}

void Hra::swap(Karta& a, Karta& b) {
	Karta tmp = a;
	a = b;
	b = tmp;
}

void Hra::vypis() {
	std::cout << "balicek" << "\n";
	for (int i = 0; i < this->zapisane; i++) {
		this->balicek[i]->vypis();
	}
	std::cout << "hrac1" << "\n";
	this->hrac1->vypis();
	std::cout << "hrac2" << "\n";
	this->hrac2->vypis();
}

void Hra::najdiVlastnika(int cislo, char znak) {
	if (hrac1->mamKartu(cislo, znak))
		std::cout << "vlastni hrac 1" << "\n";
	else if (hrac2->mamKartu(cislo, znak))
		std::cout << "vlastni hrac 2" << "\n";
	else {
		std::cout << "Karta neexistuje" << "\n";
	}
}


Hra::~Hra() {
	for (int i = 0; i < this->zapisane; i++) {
		delete this->balicek[i];
	}
	delete[] this->balicek;
	delete this->hrac1;
	delete this->hrac2;
}
