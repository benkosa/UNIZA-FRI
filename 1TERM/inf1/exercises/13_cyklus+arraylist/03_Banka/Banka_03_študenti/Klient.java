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

    public String getMeno() {
        return this.aMeno;
    }

    public String getPriezvisko() {
        return this.aPriezvisko;
    }

    public String toString() {
        return this.aMeno + " " + this.aPriezvisko;
    }

    public void setMeno(String noveMeno) {
        if (!noveMeno.equals(""))
            this.aMeno = noveMeno;
        else
            this.aMeno = "Nezname meno";
    }

    public void setPriezvisko(String novePriezvisko) {
        if (!novePriezvisko.equals(""))
            this.aPriezvisko = novePriezvisko;
        else
            this.aPriezvisko = "Nezname priezvisko";
    }

    public void zriadSiUcetVbanke(Banka b) {
        // Doplnit!
    }

    private BankovyUcet najdiUcet(String paCisloUctu) {
        // Doplnit!
        return null;
    }

    public void vypisStavUctu(String paCisloUctu) {
        // Doplnit!
    }

    public void vypisMajetokKlienta() {
        // Doplnit!
    }

    public void vlozNaUcet(String cu, int s) {
        // Doplnit!
    }

    public void vyberZUctu(String cu, int s, String pin) {
        // Doplnit!
    }

    public void vytlacVypisUctu(String cu) {
        // Doplnit!
    }

    public void prevedZuctuNaUcet(String odkial, String kam, int sum, String pin) {
        // Doplnit!
    }

    public void zistiPINkodSvojhoUctu(String cu) {
        // Doplnit!
    }

    public void zmenPINkodSvojhoUctu(String cu, String stary, String novy) {
        // Doplnit!
    }
}
