#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[]) {
    //pocet argumentov
    if (argc == 1) {
        printf("Chybny pocet argumentov");
        return 1;
    }

    srand(time(NULL));

    //nazov suboru z argumentu
    char* nazovSuboru = argv[1];

    FILE* subor = nazovSuboru;
    int bufferDlzka = 255;
    char buffer[255];

    subor = fopen(nazovSuboru, "r");

    //prve nacitanie suboru, zistenie poctu riadkov
    char* pocetRiadkov = fgets(buffer, bufferDlzka, subor);

    //prebod stringu na int
    int pocerRiadkovInt = atoi(pocetRiadkov);
    //generovanie nahodneho cisla, ohraniecnie pomocou modulo
    int randCislo = rand() % pocerRiadkovInt;

    printf("nazov suboru: %s\n", nazovSuboru);
    printf("nahodne cislo: %d\n", randCislo);
    printf("pocet riadkov: %d\n", pocerRiadkovInt);

    //nacitanie ostatnych riadkov
    for (int i = 0; i < pocerRiadkovInt; i++) {
        //nacitanie cleho riadku
        fgets(buffer, bufferDlzka, subor);

        //prevod string na int
        int cislo = atoi(buffer);

        if(cislo > randCislo)
            printf("%d\n", cislo);
    }

    fclose(subor);
}