#include <stdio.h>
#include <stdlib.h>


void naplneniePolaRandom(int* pole, int pocetRiadkov) {
    pole[0] = rand() % pocetRiadkov;
    pole[1] = rand() % pocetRiadkov;
    pole[2] = rand() % pocetRiadkov;
}

int najdiMaxmimum(int* subor, int* randomIndex) {
    int max = subor[randomIndex[0]];

    if (max < subor[randomIndex[1]])
        max = subor[randomIndex[1]];

    if (max < subor[randomIndex[2]])
        max = subor[randomIndex[2]];

    return max;
}

void vypisVystup(int* subor, int* randomIndex, int pocetRiadkov, int max) {
    printf("Vstup: ");
    for (int i = 0; i < pocetRiadkov; i++) {
        printf("%d ", subor[i]);
    }
    printf("\n");

    printf("Generovane indexy: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", randomIndex[i]);
    }
    printf("\n");

    printf("Najvacisie cislo je: %d\n", max);
}


int main(int argc, const char* argv[]) {
    if (argc != 2) {
        printf("Chybny pocet argumentov");
        return 1;
    }

    srand(time(NULL));

    //ziskanie nazvu suboru z arguemtnu
    char* nazovSuboru = argv[1];

    FILE* subor = fopen(nazovSuboru, "r");
    const int DLZKA = 255;
    char riadok[255];

    if (subor == NULL) {
        printf("Chyba pri otvarani suboru");
        return 1;
    }

    //prevod stringu na int
    int pocetRiadkov = atoi(fgets(riadok, DLZKA, subor));

    // pole random cisel
    int* randCisla = (int*)malloc(3 * sizeof(int));
    if (randCisla == NULL) {
        printf("Chyba pri alokovani pamate");
        return 1;
    }
    naplneniePolaRandom(randCisla, pocetRiadkov);

    // pole na ulozenie suboru
    int* pole = (int*)malloc(pocetRiadkov * sizeof(int));
    if (pole == NULL) {
        printf("Chyba pri alokovani pamate"); 
        return 1;
    }

    // citanie suboru
    for (int i = 0; i < pocetRiadkov; i++) {
        fgets(riadok, DLZKA, subor);
        //vlozenie riadku do pola ako integer
        pole[i] = atoi(riadok);
    }

    int max = najdiMaxmimum(pole, randCisla);

    vypisVystup(pole, randCisla, pocetRiadkov, max);
    
    //uvolnenie pamate
    free(pole);
    free(randCisla);
    fclose(subor);

    return 0;
}