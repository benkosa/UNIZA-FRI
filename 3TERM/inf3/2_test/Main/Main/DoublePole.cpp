#include "DoublePole.h"

template <class T>
DoublePole<T>::~DoublePole() {
    for (int i = 0; i < 100; i++) {
        delete this->aData[i];
    }
    delete[] aData;
	aData = nullptr;
}

template <class T>
DoublePole<T>::DoublePole(const DoublePole& other) {
	if (!this->aData) return;
	this->aData = other.aData;
}

template <class T>
DoublePole<T>& DoublePole<T>::operator=(const DoublePole& other) {
	if (this == &other) return *this;

	DoublePole::~DoublePole();

	this->aData = other.aData;

	return *this;
}
