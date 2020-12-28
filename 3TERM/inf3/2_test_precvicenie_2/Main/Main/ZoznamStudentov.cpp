#include "ZoznamStudentov.h"


int ZoznamStudentov::getZnamka(string znamka) {
    if (znamka == "A") return 1;
    if (znamka == "B") return 2;
    if (znamka == "C") return 3;
    if (znamka == "D") return 4;
    if (znamka == "E") return 5;

    cout << znamka << "chyba\n";

    return 0;
}

ZoznamStudentov::ZoznamStudentov(int pocetStudentov) {
	this->pocetStudentov = pocetStudentov;
	this->zoznam = new Student* [pocetStudentov];
}

void ZoznamStudentov::pridajStudenta(string line) {
    string word;
    stringstream ss(line);
    int pocetA = 0;
    int pocetZnamok = 0;
    float suma = 0;
    string meno;
    string priezvsko;
    string pohlavie;

    int i = 0;

    ss >> word;
    while (!ss.eof()) {
        switch (i) {
        case 0:
            meno = word;
            break;
        case 1:
            priezvsko = word;
            break;
        case 2:
            pohlavie = word;
            break;
        default:
            if (word == "A")
                pocetA++;
            pocetZnamok++;
            suma += getZnamka(word);
            break;
        }
        i++;
        ss >> word;
    } 

    if (i < 3)
        return;
    this->zoznam[this->zapisany++] = new Student(meno, priezvsko, pohlavie, pocetA, suma/pocetZnamok, pocetZnamok);
}

void ZoznamStudentov::sort() {
    //sort podla priemeru
    for (int i = 0; i < pocetStudentov; i++) {
        int swaps = 0;	//ak sa nevykonal swap pole je zoradene
        for (int j = 0; j < pocetStudentov - i - 1; j++) {
            if (zoznam[j]->getPriemer() < zoznam[j + 1]->getPriemer()) {
                swap(*zoznam[j], *zoznam[j + 1]);
                swaps = 1;
            }
        }
        if (!swaps)
            break;
    }
}

void ZoznamStudentov::swap(Student& a, Student& b) {
    Student tmp = a;
    a = b;
    b = tmp;
}

void ZoznamStudentov::vypis() {
    this->sort();
    for (int i = 0; i < this->pocetStudentov; i++) {
       this->zoznam[i]->vypis();
    }
}

void ZoznamStudentov::zapis() {
    ofstream myfile("vystup.txt");
    if (myfile.is_open()) {
        for (int i = 0; i < this->pocetStudentov; i++) {
            if (this->zoznam[i]->getPocetA()) {
                myfile << " " << this->zoznam[i]->getPocetA() << this->zoznam[i]->zapis();
            }
        }
    } else cout << "Unable to open file";
}

ZoznamStudentov::~ZoznamStudentov() {
    for (int i = 0; i < this->pocetStudentov; i++) {
        delete this->zoznam[i];
    }
    delete[] zoznam;
}


