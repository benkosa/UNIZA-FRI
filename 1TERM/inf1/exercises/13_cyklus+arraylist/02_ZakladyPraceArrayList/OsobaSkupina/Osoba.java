public class Osoba {
    private String meno;
    private String priezvisko;

    public Osoba(String noveMeno, String novePriezvisko) {
        this.meno = noveMeno;
        this.priezvisko = novePriezvisko;
    }
    
    public String getMeno() {
        return this.meno;
    }
    
    public String getPriezvisko() {
        return this.priezvisko;
    }
    
    public String toString() {
        return this.meno + " " + this.priezvisko;
    }
}
