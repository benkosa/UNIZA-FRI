
public class Program {

    public static void main(String[] args) {
     
        String[] farby = { "biela", "cierna", "cervena" };
        
        Program.vypisPoleRetazcovCezForeachCyklus(farby);
        System.out.println();
        
        Program.vypisPoleRetazcovCezForCyklus(farby);
        System.out.println();
        
        Program.vypisPoleRetazcovCezWhileCyklus(farby);
        System.out.println();
        
        int cislo1 = Program.vratCisloVRozsahuCezDoWhile(100, 200);
        System.out.println();
        
        int cislo2 = Program.vratCisloVRozsahuCezWhile(100, 200);
    }
    
    private static void vypisPoleRetazcovCezForeachCyklus(String[] poleRetazcov) {
        // TODO: Vypiste obsah pola cez foreach cyklus
    }
    
    private static void vypisPoleRetazcovCezForCyklus(String[] poleRetazcov) {
        // TODO: Vypiste obsah pola cez foreach cyklus
    }
    
    private static void vypisPoleRetazcovCezWhileCyklus(String[] poleRetazcov) {
        // TODO: Vypiste obsah pola cez foreach cyklus
    }
    
    private static int vratCisloVRozsahuCezDoWhile(int minimum, int maximum) {
        // TODO: Vypiste na standardny vystup retazec "Zadajte cislo v rozsahu <%d, %d>: "
        // a vypytajte si od pouzivatela zo standardneho vstupu cislo, ktore bude 
        // v rozsahu minimum a maximum. Ak zadane cislo bude mimo hranic, znova
        // zobrazte retazec a vypytajte si cislo. Toto sa bude opakovat 
        // az dovtedy, kym pouzivatel nezada cislo v pozadovanom rozsahu.
        // Ulohu rieste pomocou do-while cyklu
        
        return 0;
    }
    
     private static int vratCisloVRozsahuCezWhile(int minimum, int maximum) {
        // TODO: Vypiste na standardny vystup retazec "Zadajte cislo v rozsahu <%d, %d>: "
        // a vypytajte si od pouzivatela zo standardneho vstupu cislo, ktore bude 
        // v rozsahu minimum a maximum. Ak zadane cislo bude mimo hranic, znova
        // zobrazte retazec a vypytajte si cislo. Toto sa bude opakovat 
        // az dovtedy, kym pouzivatel nezada cislo v pozadovanom rozsahu.
        // Ulohu rieste pomocou while cyklu
        
        return 0;
    }
    
}
