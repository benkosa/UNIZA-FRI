#include "Zajazd.h"

Zajazd::Zajazd(string nazovDestinacie, unsigned int cena, string typDopravy, unsigned int vzdialenost) {
	this->nazovDestinacie = nazovDestinacie;
	this->cena = cena;
	this->typDopravy = typDopravy;
	this->vzdialenost = vzdialenost;
}


ostream& operator<<(ostream& os, const Zajazd& zajazd) {
	os << zajazd.nazovDestinacie << " " << zajazd.cena << " " << zajazd.vzdialenost << " " << zajazd.typDopravy;
	return os;
}
