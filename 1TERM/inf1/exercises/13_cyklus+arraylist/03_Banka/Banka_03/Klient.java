import java.util.ArrayList;

public class Klient{
    private String aMeno;
    private String aPriezvisko;
    private ArrayList<BankovyUcet> mojeUcty;

    public Klient(){
        this.aMeno = "Marek";
        this.aPriezvisko = "Kvet";
        this.mojeUcty = new ArrayList<BankovyUcet>();
    }

    public String getMeno(){
        return this.aMeno;
    }

    public String getPriezvisko(){
        return this.aPriezvisko;
    }

    public String toString(){
        return this.aMeno + " " + this.aPriezvisko;
    }

    public void setMeno(String noveMeno){
        if (!noveMeno.equals(""))
            this.aMeno = noveMeno;
        else
            this.aMeno = "Nezname meno";
    }

    public void setPriezvisko(String novePriezvisko){
        if (!novePriezvisko.equals(""))
            this.aPriezvisko = novePriezvisko;
        else
            this.aPriezvisko = "Nezname priezvisko";
    }

    public void zriadSiUcetVbanke(Banka b){
        if (b != null){
            BankovyUcet vytvorenyUcet = b.vytvorNovyUcet(this);
            this.mojeUcty.add(vytvorenyUcet);
            System.out.println("Bol vytvoreny ucet s cislom " + vytvorenyUcet.getCisloUctu());
        }
    }

    private BankovyUcet najdiUcet(String paCisloUctu){
        if (this.mojeUcty == null){
            System.out.println("Klient nema ziadne ucty!");    
            return null;
        }
        else{
            BankovyUcet hladanyUcet = null;
            for(BankovyUcet u: this.mojeUcty){
                if (u.getCisloUctu().equals(paCisloUctu)){
                    hladanyUcet = u;
                    break;
                }
            }

            if (hladanyUcet == null)
                System.out.println("Nenasiel sa ucet s cislom " + paCisloUctu);
            return hladanyUcet;
        }
    }

    public void vypisStavUctu(String paCisloUctu){
        BankovyUcet hladanyUcet = this.najdiUcet(paCisloUctu);
        if (hladanyUcet != null)
            System.out.println("Aktualny stav uctu: " + paCisloUctu + " je " + hladanyUcet.getZostatok());
    }

    public void vypisMajetokKlienta(){
        if (this.mojeUcty == null)
            System.out.println("Klient nema ziadne ucty!");          
        else{
            int celkovyMajetok = 0;
            for(BankovyUcet u: this.mojeUcty){
                celkovyMajetok += u.getZostatok();
                this.vypisStavUctu(u.getCisloUctu());
            }
            System.out.println("Celkovy majetok klienta: " + celkovyMajetok);
        }
    }

    public void vlozNaUcet(String cu, int s){
        BankovyUcet hladanyUcet = this.najdiUcet(cu);
        if (hladanyUcet != null){
            if (hladanyUcet.Vklad(s))
                System.out.println("Transakcia uspesna.");
            else
                System.out.println("Transakcia neuspesna.");
        }
    }

    public void vyberZUctu(String cu, int s, String pin){
        BankovyUcet hladanyUcet = this.najdiUcet(cu);
        if (hladanyUcet != null){
            if (hladanyUcet.Vyber(s, pin))
                System.out.println("Transakcia uspesna.");
            else
                System.out.println("Transakcia neuspesna.");
        }
    }

    public void vytlacVypisUctu(String cu){
        BankovyUcet hladanyUcet = this.najdiUcet(cu);
        if (hladanyUcet != null)
            hladanyUcet.vypisZuctu();
    }

    public void prevedZuctuNaUcet(String odkial, String kam, int sum, String pin){
        BankovyUcet hladanyUcet = this.najdiUcet(odkial);
        if (hladanyUcet != null){
            if (hladanyUcet.prevodNaInyUcet(sum, kam, pin))
                System.out.println("Prevod uspesny.");
            else
                System.out.println("Prevod neuspesny.");
        }
    }

    public void zistiPINkodSvojhoUctu(String cu){
        BankovyUcet hladanyUcet = this.najdiUcet(cu);
        if (hladanyUcet != null)
            System.out.println("Ucet s cislom " + cu + " ma PIN " + hladanyUcet.getPIN());
    }

    public void zmenPINkodSvojhoUctu(String cu, String stary, String novy){
        BankovyUcet hladanyUcet = this.najdiUcet(cu);
        if (hladanyUcet != null){
            if (hladanyUcet.setHeslo(stary, novy))
                System.out.println("Heslo bolo zmenene.");
            else
                System.out.println("Heslo nebolo zmenene!");
        }  
    }
}
