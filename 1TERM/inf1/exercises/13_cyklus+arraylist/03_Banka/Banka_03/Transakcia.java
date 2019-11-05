import java.util.Date;
import java.text.SimpleDateFormat;

public class Transakcia {
    private String typ;
    private int ciastka;
    private Date datum;

    public Transakcia(String t, int s) {
        this.typ = t;
        this.ciastka = s;
        this.datum = new Date();
    }

    public String getTyp(){
        return this.typ;
    }

    public int getCiastka(){
        return this.ciastka;
    }

    public String toString(){
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd.MM.yyyy HH:mm:ss");
        return dateFormat.format(datum) + " - " + this.typ + ": " + this.ciastka;
    }
}