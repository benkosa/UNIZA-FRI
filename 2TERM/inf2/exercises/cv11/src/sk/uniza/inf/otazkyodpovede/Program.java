package sk.uniza.inf.otazkyodpovede;

import java.io.FileNotFoundException;
import java.io.IOException;

public class Program {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        try {
            Test test = new Test();
            test.nacitajOtazky("DatabazaOtazok.txt");
            //test.nacitajOtazkyBinarne("DatabazaOtazok2.bin");
            
            Otazka otazka = new Otazka("Ktory predmet je najlepsi?");
            otazka.pridajOdpoved(new Odpoved("Telesna vychova", true));
            otazka.pridajOdpoved(new Odpoved("Informatika 2", true));
            otazka.pridajOdpoved(new Odpoved("Algoritmicka teoria grafov", true));
            otazka.pridajOdpoved(new Odpoved("Ani jedna odpoved nie je spravna", false));
            test.pridajOtazku(otazka);        
            
            test.ulozOtazky("DatabazaOtazok2.txt");
            test.ulozOtazkyBinarne("DatabazaOtazok2.bin");
            
            test.spusti();
        } catch (FileNotFoundException ex) {
            System.err.println("Subor neexistuje!");
        } catch (IOException ex) {
            System.err.println("Nastala vstupno - vystupna chyba: " + ex.getMessage());;
        }
            
//        try {
//            BufferedReader citac = new BufferedReader(new FileReader("DatabazaOtazok.txt"));
//            String riadok;
//            if ((riadok = citac.readLine()) != null) {
//                if (riadok.startsWith(Character.toString((char) 65279))) {
//                    riadok = riadok.substring(1);
//                }
//
//                do {
//                    if (riadok.startsWith(">")) {
//                        System.out.println(riadok);
//                    }
//                } while ((riadok = citac.readLine()) != null);
//            }
//
//            citac.close();
//        } catch (FileNotFoundException ex) {
//            System.err.println("Subor neexistuje!");
//        } catch (IOException ex) {
//            System.err.println("Nastala vstupno - vystupna chyba: " + ex.getMessage());;
//        }

    }

}
