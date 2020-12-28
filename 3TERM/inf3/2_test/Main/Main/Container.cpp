#include "Container.h"

void Container::pridajStudenta(string line) {
    string word;
    stringstream ss(line);

    float priemer = 0;
    string meno;
    string priezvsko;

    int i = 0;

    do {
        ss >> word;
        switch (i) {
        case 0:
            meno = word;
            break;
        case 1:
            priezvsko = word;
            break;
        case 2:
            priemer = stof(word);
            break;
        }
        i++;
        
    } while (!ss.eof());
    this->zoznam[this->zapisany++] = new Student(meno, priezvsko, priemer);
}

void Container::sort() {
    //sort podla priemeru
    for (int i = 0; i < pocetStudentov; i++) {
        int swaps = 0;	//ak sa nevykonal swap pole je zoradene
        for (int j = 0; j < pocetStudentov - i - 1; j++) {
            if (zoznam[j]->getPriemer() > zoznam[j + 1]->getPriemer()) {
                swap(*zoznam[j], *zoznam[j + 1]);
                swaps = 1;
            }
        }
        if (!swaps)
            break;
    }
}

//https://www.geeksforgeeks.org/pointers-vs-references-cpp/
//https://www.geeksforgeeks.org/passing-by-pointer-vs-passing-by-reference-in-c/
void Container::swap(Student& a, Student& b) {
    Student tmp = a;
    a = b;
    b = tmp;
}

Container::Container(int pocetStudentov) {
    this->pocetStudentov = pocetStudentov;
    this->zoznam = new Student * [pocetStudentov];
}

void Container::vypis() {
    this->sort();
    for (int i = 0; i < this->pocetStudentov; i++) {
        this->zoznam[i]->vypis();
    }
}


Container::~Container() {
    for (int i = 0; i < this->pocetStudentov; i++) {
        delete this->zoznam[i];
    }
    delete[] zoznam;
}
