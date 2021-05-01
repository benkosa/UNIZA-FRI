#include "Zoznam.h"

void Zoznam::pridaj(Uzol& uzol) {
	//prazdny zoznam
	if (this->start == nullptr) {
		this->start = &uzol;
		return;
	}
	

	//na starte je mensie slovo ako to co chceme pridat
	//pridavama na zaciatok zoznamu
	if (strcmp(this->start->getSlovo(), uzol.getSlovo()) > 0) {
		uzol.setDalsi(*this->start);
		this->start = &uzol;
		return;
	}


	Uzol* aktualny = this->start;

	//opakujeme az pokial dalsie nieje null
	while (aktualny->getDalsi() != nullptr) {
		//ak ja dalsi vacsi ako novy uzol
		if (strcmp(aktualny->getDalsi()->getSlovo(), uzol.getSlovo()) > 0) {
			//do pridavaneho uzla nastavime dalsi(vacsi) ako dalsi aktualneho
			uzol.setDalsi(*aktualny->getDalsi());
			//v aktualnom zmenime dalsi na pridavany
			aktualny->setDalsi(uzol);
			return;
		}
		aktualny = aktualny->getDalsi();
	}
	//dalsi je null tj. pridavame na koniec zoznamu
	aktualny->setDalsi(uzol);
}

void Zoznam::vypis() {
	Uzol* dalsi = this->start;

	while (dalsi != nullptr) {
		cout << dalsi->getSlovo() << "\n";
		dalsi = dalsi->getDalsi();
	}
}

void Zoznam::zapis() {
	ofstream myfile("vystup.txt");
	if (myfile.is_open()) {

		Uzol* dalsi = this->start;

		while (dalsi != nullptr) {
			myfile << dalsi->getSlovo() << "\n";
			dalsi = dalsi->getDalsi();
		}
	} else cout << "Unable to open file";
}

void Zoznam::vypisZacinajucePismenom(char pismeno) {
	Uzol* dalsi = this->start;

	int counter = 0;

	while (dalsi != nullptr) {
		if (dalsi->getSlovo()[0] == pismeno) {
			cout << dalsi->getSlovo() << "\n";
			counter++;
		}
		dalsi = dalsi->getDalsi();
	}

	if(!counter)
		cout << "ziadne slovo nezacina na: "<< pismeno << "\n";
}



Zoznam::~Zoznam() {
	Uzol* predosli = this->start;
	Uzol* dalsi = predosli->getDalsi();
	delete predosli;

	while (dalsi != nullptr) {
		predosli = dalsi;
		dalsi = predosli->getDalsi();
		delete predosli;
	}
}
