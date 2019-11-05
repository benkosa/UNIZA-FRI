public class PrvaUloha {
    // Trieda nema ziadne atributy, nepotrebuje ich.
    
    public PrvaUloha(){
        // Pokial trieda nema atributy, konstruktor moze zostat przdny, nic netreba inicializovat.
        // V takomto pripade sluzi konstruktor len na vytvaranie instancii tried.
    }

    // 1. uloha: Vytvorte metodu, ktora vypocita a vrati ciferny sucet cisla, ktore preberie ako parameter.
    // Metodu upravte tak, aby pracovala aj so zapornym vstupom.
        
    public int vypocitajCifernySucet(int vstup){ 
        // 1. Vstupny parameter si ulozim do lokalnej premennej.
        // Kedze sa tato hodnota bude v priebehu vypoctu menit,
        // oplati sa mat pristup aj k povodnej hodnote.
        int cislo = vstup;
        
        // 2. Odstranim znamienko. Ak je na vstupe zaporne cislo,
        // do lokalnej premennej vlozim opacne cislo, teda bez znamienka minus.
        if (cislo < 0)
            cislo = -cislo;

        // 3. Teraz mam zarucene, ze v lokalnej premennej budem mat nezaporne cislo, 
        // teoreticky aj nulu.
            
        // 4. Teraz mozem zacat pocitat ciferny sucet cisla. Ako?
        // Pokial bude cislo obsahovat este nejaku cislicu, pripocitam ju k cifernemu suctu
        // a z povodneho cisla ju odstranim. Kedze neviem, ake velke je povodne cislo (kolko ma cifier),
        // budem pracovat z pravej strany. Teda, ak mam na vstupe cislo 123456, postupne budem dostavat
        // cifry 6, 5, 4, 3, 2, 1. Ako? Delenie 10 a zvysok po deleni 10.
        int cifSucet = 0;    
        while (cislo > 0) {
            cifSucet += cislo % 10;
            cislo = cislo / 10;        
        }

        // 5. Na obrazovku vypisem povodne cislo, ktore vstupilo do metody cez parameter,
        // a jeho ciferny sucet.
        System.out.println("Ciferny sucet cisla " + vstup + " je " + cifSucet + ".");   
        
        // 6. Vratim vysledok vypoctu cez navratovu hodnotu.
        return cifSucet;
    }

    // 2. uloha: Vytvorte metodu, ktora vypocita, vypise a vrati cislo s opacnym poradim cifier.
    // Metoda musi pracovat BEZ KONVERZIE NA RETAZEC !!!
    // Upravte metodu tak, aby zachovala znamienko vstupneho parametra. Teda, ak na vstupe zadam
    // 12345, na vystupe ocakavam 54321, ale pokial zadam -123456, na vystupe chcem -654321.
    public int vypocitajCisloSopacnymPoradimCifier(int vstup){
        // Doplnit !!!
        return 0;
    }    
}
