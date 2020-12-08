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
		int swaps = 0;         //flag to detect any swap is there or not
		for (int j = 0; j < pocetTeamov - i - 1; j++) {
			if (poleTeamov[j].getBody() < poleTeamov[j + 1].getBody()) {       //when the current item is bigger than next
				swap(poleTeamov[j], poleTeamov[j + 1]);
				swaps = 1;    //set swap flag
			}
		}
		if (!swaps)
			break;       // No swap in this pass, so array is sorted
	}
	//sor podla strelenych golov
	for (int i = 0; i < pocetTeamov; i++) {
		int swaps = 0;         //flag to detect any swap is there or not
		for (int j = 0; j < pocetTeamov - i - 1; j++) {
			if (poleTeamov[j].getBody() == poleTeamov[j + 1].getBody()) {     //when the current item is bigger than next
				if (poleTeamov[j].getStrelene() < poleTeamov[j + 1].getStrelene()) {       //when the current item is bigger than next
					swap(poleTeamov[j], poleTeamov[j + 1]);
					swaps = 1;    //set swap flag
				}
			}

		}
		if (!swaps)
			break;       // No swap in this pass, so array is sorted
	}
}

void Hra::swap(Team& a, Team& b) {
	Team temp;
	temp = a;
	a = b;
	b = temp;
}


Hra::Hra() {}

void Hra::pridaj(char* nazovTeamu) {
	this->poleTeamov[pocetTeamov++] = *new Team(nazovTeamu);
}

void Hra::vypisPoradie() {
	zoradHry();
	for (int i = 0; i < this->pocetTeamov; i++) {
		this->poleTeamov[i].vypis();
	}
}

void Hra::spustitHru() {
	for (int i = 0; i < this->pocetTeamov; i++) {
		for (int j = i+1; j < this->pocetTeamov; j++) {
			this->zapas(&this->poleTeamov[i], &this->poleTeamov[j]);
		}
	}
}

Hra::~Hra() {
	delete[] poleTeamov;
}
