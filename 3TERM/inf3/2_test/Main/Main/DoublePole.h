#pragma once

template <class T>
class DoublePole {
private:
    double** aData = nullptr;
public:
    DoublePole() : aData(new double* [100]) {
        for (int i = 0; i < 100; i++) {
            aData[i] = new double(0.0);
        }
    }

    DoublePole(const DoublePole& other);
    DoublePole& operator=(const DoublePole& other);

    ~DoublePole();
};

