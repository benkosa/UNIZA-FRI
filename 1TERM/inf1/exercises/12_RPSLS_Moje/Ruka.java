public class Ruka {
    private int aktGesto;
    private Obrazok obrGesto;

    public Ruka() {
        this.obrGesto = new Obrazok("pics\\rock.png");
        this.obrGesto.zmenPolohu(200, 200);
        this.setGesto(0);
    }

    public Ruka(int suradnicaX, int suradnicaY, int cisloGesta) {
        this.obrGesto = new Obrazok("pics\\rock.png");
        this.obrGesto.zmenPolohu(suradnicaX, suradnicaY);
        this.setGesto(cisloGesta);       
    }

    public int getGesto() {
        return this.aktGesto;
    } 

    public void setGesto(int cislo) {
        if (cislo < 0)
            this.aktGesto = 4;
        else if (cislo > 4)  
            this.aktGesto = 0;
        else
            this.aktGesto = cislo;

        this.ukazGesto();
    }

    public void ukazGesto() {
        switch (this.aktGesto) {
            case 0: 
                this.obrGesto.zmenObrazok("pics\\rock.png");
                break;
            case 1: 
                this.obrGesto.zmenObrazok("pics\\paper.png");
                break; 
            case 2: 
                this.obrGesto.zmenObrazok("pics\\scissors.png");
                break; 
            case 3: 
                this.obrGesto.zmenObrazok("pics\\lizard.png");
                break; 
            default: 
                this.obrGesto.zmenObrazok("pics\\Spock.png");       
        }  
        
        this.obrGesto.zobraz(); 
    }

    public String dajNazovGesta() {
        switch (this.aktGesto) {
            case 0: return "Rock";
            case 1: return "Paper";
            case 2: return "Scissors";
            case 3: return "Lizard";
            default: return "Spock";       
        } 
    }

    public void posunHore() {
        this.obrGesto.posunHore();
    }

    public void posunDole() {
        this.obrGesto.posunDole();
    }

    public void posunVpravo() {
        this.setGesto(this.getGesto() + 1);
    }

    public void posunVlavo() {
        this.setGesto(this.getGesto() - 1);
    }
}
