package sk.uniza.inf.otazkyodpovede;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class Test {

    private final ArrayList<Otazka> otazky = new ArrayList<>();
    
    public void pridajOtazku(Otazka otazka) {
        this.otazky.add(otazka);
    }
    
    public void ulozOtazky(String nazovSuboru) throws FileNotFoundException {
        // Zapisovanie do textoveho suboru
        try (PrintWriter zapisovac = new PrintWriter(nazovSuboru)) {
            for (Otazka otazka : this.otazky) {
                
                if (otazka.getPocetOdpovedi() < 2) {
                    continue;
                }
                
                zapisovac.println(">" + otazka.getText());
                
                for (int i = 0; i < otazka.getPocetOdpovedi(); i++) {
                    Odpoved odpoved = otazka.getOdpoved(i);
                    if (odpoved.isSpravna()) {
                        zapisovac.print("*");
                    }
                    
                    zapisovac.println(odpoved.getText());
                }
            }
        
        }
    }
    
    public void nacitajOtazky(String nazovSuboru) throws FileNotFoundException, IOException {
        // Nacitanie z textoveho suboru:
        BufferedReader citac = new BufferedReader(new FileReader(nazovSuboru));
        String riadok = citac.readLine();
        if (riadok != null) {
            if (riadok.startsWith(Character.toString((char) 65279))) {
                riadok = riadok.substring(1);
            }

            Otazka otazka = null;
            do {
                if (riadok.startsWith(">")) {
                    otazka = new Otazka(riadok.substring(1));
                    this.otazky.add(otazka);
                } else {
                    boolean jeSpravna;
                    if (riadok.startsWith("*")) {
                        jeSpravna = true;
                        riadok = riadok.substring(1);
                    } else {
                        jeSpravna = false;
                    }
                    
                    if (otazka != null) {
                        Odpoved odpoved = new Odpoved(riadok, jeSpravna);
                        otazka.pridajOdpoved(odpoved);
                    } else {
                        System.err.println("Varovanie: v subore sa nenachadza otazka na prvom riadku!");
                    }                   
                }
                
                riadok = citac.readLine();
            } while (riadok != null);
        }

        citac.close();
    }
    
    public void ulozOtazkyBinarne(String nazovBinarnehoSuboru) throws FileNotFoundException, IOException {
        final int verzia = 1;
        
        try (DataOutputStream zapisovac = new DataOutputStream(new FileOutputStream(nazovBinarnehoSuboru))) {
            // Zapiseme cislo verzie suboru - ak by sme v buducnosti zmenili format, vieme nacitat subor 
            zapisovac.writeInt(verzia);
            
            // Zapiseme pocet otazok, aby sme ich pri nacitani vedeli vsetky nacitat
            zapisovac.writeInt(this.otazky.size());
            for (Otazka otazka : this.otazky) {
                // Zapiseme text otazky a pocet odpovedi, aby sme ich pri nacitani vedeli vsetky nacitat
                zapisovac.writeUTF(otazka.getText());
                zapisovac.writeInt(otazka.getPocetOdpovedi());
                for (int i = 0; i < otazka.getPocetOdpovedi(); i++) {
                    // Zapiseme text odpovede a informaciu, ci je spravna
                    Odpoved odpoved = otazka.getOdpoved(i);
                    zapisovac.writeUTF(odpoved.getText());
                    zapisovac.writeBoolean(odpoved.isSpravna());
                }
            }            
        }        
    }
    
     public void nacitajOtazkyBinarne(String nazovBinarnehoSuboru) throws FileNotFoundException, IOException {
        try (DataInputStream citac = new DataInputStream(new FileInputStream(nazovBinarnehoSuboru))) {
             // Precitame cislo verzie suboru
            int verzia = citac.readInt();
            
            if (verzia == 1) {
                // Precitame pocet otazok a potom kazdu otazku samostatne
                int pocetOtazok = citac.readInt();
                for (int i = 0; i < pocetOtazok; i++) {
                    String textOtazky = citac.readUTF();
                    int pocetOdpovedi = citac.readInt();
                    Otazka otazka = new Otazka(textOtazky);
                    this.pridajOtazku(otazka);
                    
                    for (int j = 0; j < pocetOdpovedi; j++) {
                        // Precitame text odpovede a informaciu, ci je spravna
                        String textOdpovede = citac.readUTF();
                        boolean jeSpravna = citac.readBoolean();
                        Odpoved odpoved = new Odpoved(textOdpovede, jeSpravna);
                        otazka.pridajOdpoved(odpoved);
                    }
                }
            }
        }        
    }    

    public void spusti() {
        Scanner skener = new Scanner(System.in);
                
        int pocetOtazok = 0;
        int pocetSpravnychOdpovedi = 0;
        long zaciatokTestu = System.nanoTime();
        
        for (Otazka otazka : this.otazky) {
            
            if (otazka.getPocetOdpovedi() == 0) {
                continue;
            }
            
            pocetOtazok++;
            
            otazka.vypis();            
            
            boolean jeOdpovedPouzivatelaChybna;
            do {
                //try { 
                System.out.print("Vasa odpoved: ");
                if (!skener.hasNextInt()) {
                    jeOdpovedPouzivatelaChybna = true;
                    System.out.println("Chybne zadana hodnota. Zadajte iba cislo od 1 do " + otazka.getPocetOdpovedi());
                    skener.nextLine();
                    continue;
                }

                int odpovedPouzivatela = skener.nextInt();
                // Precitame znak noveho riadka - \n (stlaceny Enter na klavesnici) - inak to robi problemy s nextInt
                skener.nextLine();

                Odpoved odpoved = otazka.getOdpoved(odpovedPouzivatela - 1);
                if (odpoved == null) {
                    jeOdpovedPouzivatelaChybna = true;
                    System.out.println("Zle zadane cislo.");
                    continue;
                }

                if (odpoved.isSpravna()) {
                    System.out.println("Spravna odpoved :)");
                    pocetSpravnychOdpovedi++;
                } else {
                    System.out.println("Nespravna odpoved :(");
                }

                System.out.println();

                jeOdpovedPouzivatelaChybna = false;
//                }  catch (InputMismatchException ex) {
//                    jeOdpovedPouzivatelaChybna = true;
//                    System.out.println("Chybne zadana hodnota. Zadajte cislo od 1 do " + otazka.getPocetOdpovedi());
//                    skener.nextLine();
//                }
            } while (jeOdpovedPouzivatelaChybna);
        }
        
        long koniecTestu = System.nanoTime();
        
        double celkovyCasTestuVSekundach = (koniecTestu - zaciatokTestu) / 1e9; // TimeUnit.NANOSECONDS.toSeconds(koniecTestu - zaciatokTestu)

        System.out.println("Pocet spravnych odpovedi: " + pocetSpravnychOdpovedi + " z " + pocetOtazok);
        double uspesnost = pocetOtazok > 0 ? pocetSpravnychOdpovedi * 100.0 / pocetOtazok : 0;
        System.out.println("Celkova uspesnost testu: " + String.format("%.2f", uspesnost) + " %");
        System.out.println("Celkovy cas testu: " + String.format("%.2f s.", celkovyCasTestuVSekundach));
    }
    
}
