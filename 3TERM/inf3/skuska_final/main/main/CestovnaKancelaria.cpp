#include "CestovnaKancelaria.h"

void CestovnaKancelaria::pridaj(Zajazd& uzol) {
	//prazdny zoznam
	if (this->start == nullptr) {
		this->start = &uzol;
		return;
	}


	//na starte je mensie slovo ako to co chceme pridat
	//pridavama na zaciatok zoznamu
	if (this->start->getCena() > uzol.getCena()) {
		uzol.setDalsi(*this->start);
		this->start = &uzol;
		return;
	}


	Zajazd* aktualny = this->start;

	//opakujeme az pokial dalsie nieje null
	while (aktualny->getDalsi() != nullptr) {
		//ak ja dalsi vacsi ako novy uzol
		if (aktualny->getDalsi()->getCena() > uzol.getCena()) {
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

void CestovnaKancelaria::vypis() {
	Zajazd* dalsi = this->start;

	while (dalsi != nullptr) {
		cout << *dalsi << "\n";
		dalsi = dalsi->getDalsi();
	}
}

void CestovnaKancelaria::zapis() {
	ofstream myfile("Zajazd.txt");
	if (myfile.is_open()) {

		Zajazd* dalsi = this->start;

		while (dalsi != nullptr) {
			myfile << *dalsi << "\n";
			dalsi = dalsi->getDalsi();
		}
	} else cout << "Nepodarilo sa otvorit subor\n";
}

void CestovnaKancelaria::vypisMensieAko(int cena) {
	Zajazd* dalsi = this->start;

	int counter = 0;

	while (dalsi != nullptr) {
		if (dalsi->getCena() < cena) {
			cout << *dalsi << "\n";
			counter++;
		}
		dalsi = dalsi->getDalsi();
	}

	if (!counter)
		cout << "ziadny zajazd nema nizsiu cenu ako: " << cena << "\n";
}

CestovnaKancelaria::~CestovnaKancelaria() {
	Zajazd* predosli = this->start;
	Zajazd* dalsi = predosli->getDalsi();
	delete predosli;

	while (dalsi != nullptr) {
		predosli = dalsi;
		dalsi = predosli->getDalsi();
		delete predosli;
	}
}
