public class Transakcia {
    private String typ;
    private int ciastka;

    public Transakcia(String t, int s) {
        this.typ = t;
        this.ciastka = s;
    }

    public String getTyp(){
        return this.typ;
    }

    public int getCiastka(){
        return this.ciastka;
    }

    public String toString(){
        return this.typ + ": " + this.ciastka;
    }
}