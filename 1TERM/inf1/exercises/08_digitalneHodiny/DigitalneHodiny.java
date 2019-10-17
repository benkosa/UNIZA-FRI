public class DigitalneHodiny {
    private CiselnyDisplej hodiny;
    private CiselnyDisplej minuty;
    private CiselnyDisplej sekundy;
    private int pocetTikov;
    private HodinovyStroj stroj;
    
    public DigitalneHodiny() {
        this.hodiny = new CiselnyDisplej(24, 20, 20);
        this.minuty = new CiselnyDisplej(60, 340, 20);
        this.sekundy = new CiselnyDisplej(60, 660, 20);        
        this.pocetTikov = 0;
        this.stroj = null;

    }
    
    public void start(){
        this.stroj = new HodinovyStroj(this);
    }
    
    public void stop(){
        this.stroj.setHodiny(null);
        this.stroj = null;
    }
    
    // metoda zobrazAktCas
    public void zobrazAktualnyCas() {
        this.hodiny.zobraz();
        this.minuty.zobraz();
        this.sekundy.zobraz();
    }
    
    public void setCas(int hodina, int minuta, int sekunda) {
        this.hodiny.setHodnota(hodina);
        this.minuty.setHodnota(minuta);
        this.sekundy.setHodnota(sekunda);
    }
    
    public void tik() {
        if(++this.pocetTikov == 4){
            this.pocetTikov = 0;
            this.sekundy.krok();
            if (this.sekundy.getHodnota() == 0) {
                this.minuty.krok();
                if (this.minuty.getHodnota() == 0)
                    this.hodiny.krok();
            }
            
            this.zobrazAktualnyCas();
        }
    }
    
    public void pridajPriestupnuSekundu(){
        this.sekundy.priestupnaSekunda();
    }
}
