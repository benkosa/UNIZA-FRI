#pragma once
#include "Team.h"
class Hra {
private:
	int alokovane = 6;
	int pocetTeamov = 0;
	Team** poleTeamov = new Team*[alokovane];

	void zapas(Team* team0, Team* team1);

	void zoradHry();

	void swap(Team& a, Team& b);

public:
	Hra();

	void pridaj(char* nazovTeamu);

	void vypisPoradie();

	void spustitHru();

	~Hra();
};

