#include "Team.h"
#include <memory>
#include <iostream>

Team::Team() {}

Team::Team(char* nazov) {
	if (!nazov) return;

	const int DLZKA_NAZVU = strlen(nazov);
	this->nazov = new char[DLZKA_NAZVU + 1];
	memcpy(this->nazov, nazov, DLZKA_NAZVU + 1);
	this->nazov[DLZKA_NAZVU-1] = 0;
}

void Team::vypis() {
	std::cout << nazov << ": " << streleneGoly << " | " << dostaneGoly << " | " << body << "\n";
}

void Team::pripocitajBody(int body, int streleneGoly, int dostaneGoly) {
	this->body += body;
	this->streleneGoly += streleneGoly;
	this->dostaneGoly += dostaneGoly;
}

char* Team::getNazov() {
	return this->nazov;
}

int Team::getBody() {
	return this->body;
}

int Team::getStrelene() {
	return this->streleneGoly;
}

Team::~Team() {
	//delete[] this->nazov;
}


	