#include <stdio.h>
#include <stdlib.h>

int vsetkyRovnake(int kocka1, int kocka2, int kocka3) {
	if (kocka1 == kocka2 && kocka3 == kocka2) {
		return kocka1 * 100;
	}

	return 0;
}

void sort(int* kocka1, int* kocka2, int* kocka3) {
	int tmp = 0;
	for (int i = 0; i < 3; i++) {

		if (*kocka1 > *kocka2) {
			tmp = *kocka1;
			*kocka1 = *kocka2;
			*kocka2 = tmp;
		}

		if (*kocka2 > *kocka3) {
			tmp = *kocka2;
			*kocka2 = *kocka3;
			*kocka3 = tmp;
		}
	}

	return;
}

int suZaSebou(int kocka1, int kocka2, int kocka3) {

	sort(&kocka1, &kocka2, &kocka3);

	if ((kocka1 + 2) == (kocka2 + 1) && kocka3 == (kocka2 + 1)) {
		return (kocka1 + kocka2 +kocka3) * 100;
	}

	return 0;
}

int hra() {
	

	int kocka1 = rand() % 6 + 1;
	int kocka2 = rand() % 6 + 1;
	int kocka3 = rand() % 6 + 1;

	printf("%d, %d, %d\n", kocka1, kocka2, kocka3);

	int body = vsetkyRovnake(kocka1, kocka2, kocka3);
	body += suZaSebou(kocka1, kocka2, kocka3);

	printf("%d\n", body);

	return body;
}

struct Hrac {
	int body;
	int vyhrateKola;
	int bodyAktualneKolo;
};

void hracConstruct(struct Hrac* hrac, int body, int vyhrateKola, int bodyAktualneKolo) {
	hrac -> body = body;
	hrac -> vyhrateKola = vyhrateKola;
	hrac -> bodyAktualneKolo = bodyAktualneKolo;
}


int main(int argc, const char* argv[])
{

	srand(time(NULL));

	struct Hrac hrac1;
	struct Hrac hrac2;

	hracConstruct(&hrac1, 0, 0, 0);

	hracConstruct(&hrac2, 0, 0, 0);

	int body = 0;
	
	for (int i = 0; i < 10; i++) {

		hrac1.bodyAktualneKolo = hra();
		hrac1.body += hrac1.bodyAktualneKolo;

		hrac2.bodyAktualneKolo = hra();
		hrac2.body += hrac2.bodyAktualneKolo;
		
		//hrac 2 vyhral
		if (hrac1.bodyAktualneKolo < hrac2.bodyAktualneKolo) {
			hrac2.vyhrateKola++;
			printf("body hrac2 %d\n", hrac2.vyhrateKola);
		//remiza
		}else if (hrac1.bodyAktualneKolo == hrac2.bodyAktualneKolo) {
		//hrac 2 vyhral
			printf("remiza\n");
		} else {
			hrac1.vyhrateKola++;
			printf("body hrac1 %d\n", hrac1.vyhrateKola);

		}
	}



	if (hrac2.vyhrateKola > hrac1.vyhrateKola) {
		printf("vyhral hrac2");
	}
	if (hrac2.vyhrateKola == hrac1.vyhrateKola) {
		printf("remiza");
	}
	if (hrac2.vyhrateKola < hrac1.vyhrateKola) {
		printf("vyhral hrac1");
	}

	

	return 0;
}