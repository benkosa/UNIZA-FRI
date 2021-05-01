#pragma once
#include <cstring>
#pragma warning(disable:4996)
class Uzol {
private:
	char* slovo = nullptr;
	int dlzka = 0;

	Uzol* dalsi = nullptr;
public:
	Uzol();
	Uzol(const char* slovo);

	Uzol* getDalsi();

	void setDalsi(Uzol& dalsi);

	char* getSlovo();

	~Uzol();

};

