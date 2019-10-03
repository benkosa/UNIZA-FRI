
/**
 * Write a description of class Osoba here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Osoba
{
    // instance variables - replace the example below with your own
    private String meno;
    private String priezvisko;
    private int rokNarodenia;
    private boolean narokNaVlakyZadarmo;
    

    /**
     * Constructor for objects of class Osoba
     */
    public Osoba(String meno, String priezvisko, int rokNarodenia, boolean narokNaVlakyZadarmo)
    {
        // initialise instance variables
        this.meno = meno;
        this.priezvisko = priezvisko;
        this.rokNarodenia = rokNarodenia;
        this.narokNaVlakyZadarmo = narokNaVlakyZadarmo;
    }
    
    public String getMenoApriezvisko(){
        return meno + " " + priezvisko;
    }
    
    
    public int getVek (){
        return 2019 - this.rokNarodenia;
    }
    
    
    public boolean getNarokNaVlakyZadarmo(){
        return this.narokNaVlakyZadarmo;
    }
    
    
    public void vypisInfo(){
        System.out.println( this.meno + " " + this.priezvisko + "\nNarodeny/a: " + (2019 - this.rokNarodenia) + "\nVlaky zadarmo: " + this.narokNaVlakyZadarmo);
    }
}
