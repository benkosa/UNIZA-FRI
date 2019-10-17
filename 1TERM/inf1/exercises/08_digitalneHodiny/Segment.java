public class Segment {
    private Obdlznik aObdlznik;
    
    public Segment(int paDlzkaSegmentu, int paHrubkaSegmentu, 
                   int paPoziciaX, int paPoziciaY) {
        this.aObdlznik = new Obdlznik();
        this.aObdlznik.zmenPolohu(paPoziciaX, paPoziciaY);
        this.aObdlznik.zmenStrany(paDlzkaSegmentu, paHrubkaSegmentu);
    }
    
    public void rozsviet() {
        this.aObdlznik.zobraz();
    }
    
    public void zhasni() {
        this.aObdlznik.skry();
    }
}

