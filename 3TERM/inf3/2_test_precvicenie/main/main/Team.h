#pragma once
class Team {
private:
	char* nazov = nullptr;
	int body = 0;
	int streleneGoly = 0;
	int dostaneGoly = 0;

public:
	Team();
	Team(char* nazov);
	Team(const Team& other);
	Team& operator=(const Team& other);

	void vypis();

	void pripocitajBody(int body, int streleneGoly, int dostaneGoly);

	char* getNazov();

	int getBody();

	int getStrelene();

	~Team();
};




