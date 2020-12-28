#pragma once
#include "Student.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

class Container {
private:
	Student** zoznam;
	int pocetStudentov;
	int zapisany = 0;


public:
	void pridajStudenta(string line);

	Container(int pocetStudentov);

	void vypis();

	void sort();
	void swap(Student& a, Student& b);


	~Container();

};

