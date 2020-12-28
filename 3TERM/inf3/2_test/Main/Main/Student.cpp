#include "Student.h"

Student::Student(string meno, string priezvisko, float priemer) {
	this->meno = meno;
	this->priemer = priemer;
	this->priezvisko = priezvisko;
}

float Student::getPriemer() {
	return this->priemer;
}

Student::Student(const Student& other) {
	this->meno = other.meno;
	this->priezvisko = other.priezvisko;
	this->priemer = other.priemer;
}

Student& Student::operator=(const Student& other) {
	if (this == &other) return *this;

	this->meno = other.meno;
	this->priezvisko = other.priezvisko;
	this->priemer = other.priemer;

	return *this;
}

void Student::vypis() {
	std::cout << this->meno << " " << this->priezvisko << " " << this->priemer << "\n";
}
