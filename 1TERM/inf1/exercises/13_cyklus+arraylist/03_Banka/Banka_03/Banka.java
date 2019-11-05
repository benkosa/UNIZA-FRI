import java.util.ArrayList;
import java.util.Random;

public class Banka{
    private String aNazovBanky;
    private ArrayList<BankovyUcet> zoznamUctov;

    public Banka(){
        this.setNazovBanky("FRI banka");
        this.zoznamUctov = new ArrayList<BankovyUcet>();
    }    

    public int getCelkovaSuma(){
        if (this.zoznamUctov == null)
            return 0;
        else{
            int celkovaSuma = 0;
            for (BankovyUcet bu: zoznamUctov){ 
                celkovaSuma += bu.getZostatok();
            }
            return celkovaSuma;
        }
    }

    public String getNazovBanky(){
        return this.aNazovBanky;
    }

    public ArrayList<BankovyUcet> vratZoznamUctov(){
        return this.zoznamUctov;
    }    

    public void setNazovBanky(String novyNazov){
        if (!novyNazov.equals(""))
            this.aNazovBanky = novyNazov;
        else
            this.aNazovBanky = "Neznama banka";
    }

    public BankovyUcet vytvorNovyUcet(Klient paKlient){
        // Vygenerivanie noveho IBAN cisla uctu
        String noveCislo = "SK";
        Random generator = new Random();
        for (int i = 0; i < 10; i++)
            noveCislo += generator.nextInt(10);
            // Metoda nextInt(10) vygeneruje nahodne cele cislo z intervalu <0, 10), teda 0-9

        // Zalozenie noveho uctu a pridanie do zoznamu uctov danej banky    
        // Tu sa pouzitie anonymneho objektu nehodi, nakolko ucet musim vratit cey return
        BankovyUcet novy = new BankovyUcet(noveCislo, this, paKlient);
        zoznamUctov.add(novy);
        return novy;
    }

    public void vypisCislaVsetkychUctov(){
        if (this.zoznamUctov.isEmpty())
            System.out.println("Banka nema ziadny ucet!");
        else{
            for(BankovyUcet bu: this.zoznamUctov)
                System.out.println(bu.getCisloUctu());
        }       
    }

    public void vypisZoznamKlientovBezDuplicit(){
        if (zoznamUctov != null){

            // Vo vypise klientov chceme potlacit duplicity
            ArrayList<Klient> zoznamKlientov = new ArrayList<Klient>();
            Klient k;
            for(BankovyUcet bu: this.zoznamUctov){
                k = bu.getKlient();
                if (k != null){
                    if (!zoznamKlientov.contains(k))
                        zoznamKlientov.add(k);
                }
            }

            // Vypis zoznamu klientov
            if (zoznamKlientov.isEmpty())
                System.out.println("Banka nema ziadneho klienta!");
            else{
                System.out.println("Zoznam klientov:");
                for(Klient kl: zoznamKlientov){
                    System.out.println(kl);
                }
            }
        }
        else
            System.out.println("Zoznam uctov neexistuje!");
    }
}
