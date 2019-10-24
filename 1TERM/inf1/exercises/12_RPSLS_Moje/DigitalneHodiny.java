public class DigitalneHodiny {
    private CiselnyDisplej sekundy;    

    
    private int pocetTikov;
    private HodinovyStroj stroj;
    
    private int zaciatocnyCas;
    
    public DigitalneHodiny() {

        this.sekundy = new CiselnyDisplej(15, 20, 20);
        
        this.zaciatocnyCas = 0;
        
        this.pocetTikov = 0;
        this.stroj = null;
 
    }
    
    public void start(int cas){
        this.stroj = new HodinovyStroj(this);
        this.setCas(cas);
    }
    
    public void stop(){
        this.stroj.setHodiny(null);
        this.stroj = null;
        
    }
    
    // metoda zobrazAktCas
    public void zobrazAktualnyCas() {
        this.sekundy.zobraz();
    }
    

    
    public void setCas(int sekunda) {

        this.sekundy.setHodnota(sekunda);
        
    }


     
    
    
    
    public void tik() {        
        if(++this.pocetTikov == 4){
            this.pocetTikov = 0;
            this.sekundy.krok();
            if(this.sekundy.getHodnota() == 0) this.stop();
            
            
            this.zobrazAktualnyCas();
        }
    }
   
}
