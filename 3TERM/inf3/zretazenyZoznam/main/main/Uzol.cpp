#include "Uzol.h"

Uzol::Uzol() {}

Uzol::Uzol(const char* slovo) {
	this->dlzka = strlen(slovo);
	this->slovo = new char[this->dlzka + 1];
	strcpy(this->slovo, slovo);
}

Uzol* Uzol::getDalsi() {
	return this->dalsi;
}

void Uzol::setDalsi(Uzol& dalsi) {
	this->dalsi = &dalsi;
}

char* Uzol::getSlovo() {
	return this->slovo;
}

Uzol::~Uzol() {
	//dalsi uzol sa maze v zozname
	delete this->slovo;
}
