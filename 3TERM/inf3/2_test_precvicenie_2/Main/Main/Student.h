#pragma once
#include <string>
#include <iostream>
using namespace std;

class Student {
private:
	string meno;
	string priezvisko;
	string pohlavie;
	int pocetA = 0;
	int pocetZnamok = 0;
	float priemer = 0;
public:
	Student();
	Student(string meno, string priezvisko, string pohlavie, int pocetA, float priemer, int pocetZnamok);

	Student(const Student& other);
	Student& operator=(const Student& other);

	void vypis();
	string zapis();
	int getPocetA();
	float getPriemer();
};

