public class Osoba {
    private String aMeno;
    private String aPriezvisko;

    public Osoba(String paMeno, String paPriezvisko) {
        this.aMeno = paMeno;
        this.aPriezvisko = paPriezvisko;
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
}
