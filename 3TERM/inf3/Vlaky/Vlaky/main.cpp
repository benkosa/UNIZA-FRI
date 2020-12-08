#include "main.h"

#include <iostream>
#include <fstream>
#include <string>
#include "Vlak.h"
#include "Stanice.h"

using namespace std;

int main() {

	string line;

    int counter = 0;



	ifstream myfile("Source.txt");
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            counter++;
        }
        myfile.close();
    }

    else cout << "Unable to open file";


    Vlak* vlaky = (Vlak*)malloc(sizeof(Vlak) * counter);

    Stanica* stanice = (Stanica*)malloc(sizeof(Stanica) * counter);

    ifstream myfile2("Source.txt");
    if (myfile2.is_open()) {
        while (getline(myfile2, line)) {

            

            // Returns first token 
            char* line2 = new char[line.length() + 1];
            strcpy(line2, line.c_str());

            char* token = strtok(line2, " ");

            cout << token << '\n';


            // Keep printing tokens while one of the 
            // delimiters present in str[]. 
            //while (token != NULL) {
            //    printf("%s\n", token);
            //    token = strtok(NULL, " ");
            //}
        }
        myfile2.close();
    }

    else cout << "Unable to open file";

    return 0;

}
