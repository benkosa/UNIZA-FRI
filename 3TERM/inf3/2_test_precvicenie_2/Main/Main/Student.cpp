
#include "Student.h"

Student::Student() {}

Student::Student(string meno, string priezvisko, string pohlavie, int pocetA, float priemer, int pocetZnamok) {
	this->meno = meno;
	this->priezvisko = priezvisko;
	this->pocetA = pocetA;
	this->priemer = priemer;
	this->pohlavie = pohlavie;
	this->pocetZnamok = pocetZnamok;
}

Student::Student(const Student& other) {
	this->meno = other.meno;
	this->priezvisko = other.priezvisko;
	this->pocetA = other.pocetA;
	this->priemer = other.priemer;
	this->pohlavie = other.pohlavie;
	this->pocetZnamok = other.pocetZnamok;
}

Student& Student::operator=(const Student& other) {
	if (this == &other) return *this;

	//Student::~Student();

	this->meno = other.meno;
	this->priezvisko = other.priezvisko;
	this->pocetA = other.pocetA;
	this->priemer = other.priemer;
	this->pohlavie = other.pohlavie;
	this->pocetZnamok = other.pocetZnamok;

	return *this;
}



void Student::vypis() {
	std::cout << this->meno << " " << this->priezvisko << " " << this->priemer << "\n";
}

string Student::zapis() {
	return pocetA + " " + meno + " " + priezvisko + "\n";
}

int Student::getPocetA() {
	return this->pocetA;
}

float Student::getPriemer() {
	return this->priemer;
}
