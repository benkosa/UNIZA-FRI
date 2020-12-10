#pragma once
#include "Student.h"
#include <iostream>
#include <sstream>
#include <fstream>
class ZoznamStudentov {
private:
	Student** zoznam;
	int pocetStudentov;
	int zapisany = 0;
	int getZnamka(string znamka);
public: 
	ZoznamStudentov(int pocetStudentov);
	void pridajStudenta(string line);
	void vypis();

	void zapis();

	void sort();
	void swap(Student& a, Student& b);

	~ZoznamStudentov();
};

