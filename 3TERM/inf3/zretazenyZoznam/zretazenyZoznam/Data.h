#pragma once

typedef int HODNOTA_TYP;
const HODNOTA_TYP NEPLATNA_HODNOTA = 0;

class Uzol{
private: 
	HODNOTA_TYP aCislo = NEPLATNA_HODNOTA;
	Uzol* aNasledovnik = nullptr;
public:
	Uzol(int pCislo, Uzol* pNasledovnik) {
		this->aCislo = pCislo;
		aNasledovnik = pNasledovnik;
	}

	HODNOTA_TYP Cislo() {
		return aCislo;
	}

	void Nasledovnik(Uzol)
};

