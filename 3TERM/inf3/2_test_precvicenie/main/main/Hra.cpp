#include "Hra.h"
#include <random>
#include <time.h>
#include <iostream>

void Hra::zapas(Team* team0, Team* team1) {
	int golyT0 = rand() % 11;
	int golyT1 = rand() % 11;
	//remiza
	if (golyT0 == golyT1) {
		team0->pripocitajBody(1, golyT0, golyT1);
		team1->pripocitajBody(1, golyT1, golyT0);
		std::cout << team0->getNazov() << " : " << team1->getNazov() << " " << golyT0 << ':' << golyT1 << "\n";
	//vyhral T1
	} else if (golyT0 < golyT1) {
		team1->pripocitajBody(2, golyT1, golyT0);
		team0->pripocitajBody(0, golyT0, golyT1);
		std::cout << team1->getNazov() << " : " << team0->getNazov() << " " << golyT1 << ':' << golyT0 << "\n";
	//vyhral T0
	} else {
		team0->pripocitajBody(2, golyT0, golyT1);
		team1->pripocitajBody(0, golyT1, golyT0);
		std::cout << team0->getNazov() << " : " << team1->getNazov() << " " << golyT0 << ':' << golyT1 << "\n";
	}
}

void Hra::zoradHry() {
	//sort podla poctu golov
	for (int i = 0; i < pocetTeamov; i++) {
		int swaps = 0;	//ak sa nevykonal swap pole je zoradene
		for (int j = 0; j < pocetTeamov - i - 1; j++) {
			if (poleTeamov[j]->getBody() < poleTeamov[j + 1]->getBody()) {
				swap(*poleTeamov[j], *poleTeamov[j + 1]);
				swaps = 1;
			}
		}
		if (!swaps)
			break; 
	}
	//sort podla strelenych golov
	for (int i = 0; i < pocetTeamov; i++) {
		int swaps = 0;
		for (int j = 0; j < pocetTeamov - i - 1; j++) {
			//ak sa rovna pocet bodov
			if (poleTeamov[j]->getBody() == poleTeamov[j + 1]->getBody()) {
				//triedi podla strelenych golov
				if (poleTeamov[j]->getStrelene() < poleTeamov[j + 1]->getStrelene()) {
					swap(*poleTeamov[j], *poleTeamov[j + 1]);
					swaps = 1;
				}
			}
		}
		if (!swaps)
			break;
	}
}
//https://www.geeksforgeeks.org/pointers-vs-references-cpp/
//https://www.geeksforgeeks.org/passing-by-pointer-vs-passing-by-reference-in-c/
void Hra::swap(Team& a, Team& b) {
	Team tmp = a;
	a = b;
	b = tmp;
}


Hra::Hra() {}

void Hra::pridaj(char* nazovTeamu) {
	this->poleTeamov[pocetTeamov++] = new Team(nazovTeamu);
}

void Hra::vypisPoradie() {
	zoradHry();
	for (int i = 0; i < this->pocetTeamov; i++) {
		this->poleTeamov[i]->vypis();
	}
}

void Hra::spustitHru() {
	for (int i = 0; i < this->pocetTeamov; i++) {
		for (int j = i+1; j < this->pocetTeamov; j++) {
			this->zapas(&*this->poleTeamov[i], &*this->poleTeamov[j]);
		}
	}
}

Hra::~Hra() {
	for (int i = 0; i < this->pocetTeamov; i++) {
		delete this->poleTeamov[i];
	}
	delete[] poleTeamov;
}
