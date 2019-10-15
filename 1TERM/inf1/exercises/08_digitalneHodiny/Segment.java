
/**
 * Write a description of class Segment here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Segment {
    private Obdlznik aObdlznik;
    
    /**
     * Constructor for objects of class Segment
     */
    public Segment(int dlzkaSegmentu, int hrubkaSegmentu, int poziciaX, int poziciaY) {
        // initialise instance variables
        this.aObdlznik = new Obdlznik();
        this.aObdlznik.zmenPolohu(poziciaX, poziciaY);
        this.aObdlznik.zmenStrany(dlzkaSegmentu, hrubkaSegmentu);
    }
    
    public void rozsviet(){
        this.aObdlznik.zobraz();
    }
    
    public void zhasni(){
        this.aObdlznik.skry();
    }
}
