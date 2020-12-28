#pragma once
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
class Student {
private:
	string meno;
	string priezvisko;
	float priemer;
public:
	void vypis();

	Student(const Student& other);
	Student& operator=(const Student& other);

	Student(string meno, string priezvisko, float priemer);

	float getPriemer();
};

