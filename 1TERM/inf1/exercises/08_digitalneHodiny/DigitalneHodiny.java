public class DigitalneHodiny {
    private CiselnyDisplej hodiny;
    private CiselnyDisplej minuty;
    private CiselnyDisplej sekundy;
    
    private CiselnyDisplej den;
    private CiselnyDisplej mesiac;
    private CiselnyDisplej rok1;
    private CiselnyDisplej rok2;
    
    private int pocetTikov;
    private HodinovyStroj stroj;
    
    public DigitalneHodiny() {
        this.hodiny = new CiselnyDisplej(24, 20, 20);
        this.minuty = new CiselnyDisplej(60, 340, 20);
        this.sekundy = new CiselnyDisplej(60, 660, 20);
        
        this.mesiac = new CiselnyDisplej(12, 340, 340);
        this.den = new CiselnyDisplej(this.getMaxPocetDniMesiaca(), 20, 340);
        this.rok1 = new CiselnyDisplej(99, 660, 340);
        this.rok2 = new CiselnyDisplej(99, 880, 340);
        
        this.pocetTikov = 0;
        this.stroj = null;
 
    }
    
    public void start(){
        this.stroj = new HodinovyStroj(this);
        this.setCas(23,59,55,31,12,2019);
        this.zobrazAktualnyDatum();
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
    
    public void zobrazAktualnyDatum() {        
        this.den.zobraz();
        this.mesiac.zobraz();
        this.rok1.zobraz();
        this.rok2.zobraz();
    }
    
    public void setCas(int hodina, int minuta, int sekunda, int den, int mesiac, int rok) {
        this.hodiny.setHodnota(hodina);
        this.minuty.setHodnota(minuta);
        this.sekundy.setHodnota(sekunda);
        
        this.mesiac.setHodnotaDatum(mesiac);
        
        this.den.setHronaHranica(this.getMaxPocetDniMesiaca());
        this.den.setHodnotaDatum(den);
        
        this.rok1.setHodnotaDatum(rok/100);
        this.rok2.setHodnotaDatum(rok%100);
    }
    
    private int getRok(){
        return this.rok1.getHodnota() * 100 + this.rok2.getHodnota();
    }
    
    private boolean jePriestupny(){
        int rok = this.getRok();
        return (rok % 4 == 0) && ((rok % 100 != 0) || (rok % 400 == 0));
    }
     
    private int getMaxPocetDniMesiaca(){
        switch (this.mesiac.getHodnota()){
            case 4:
            case 6:
            case 9:
            case 11:
                return 30;
            case 2:
                //je priestupny
                if(this.jePriestupny())
                    return 29;
                    
                return 28;
            default: 
                return 31;
        }
    }
    
    public void setZajtra(){
         int rok = getRok();
        
         this.den.setHodnota(this.den.getHodnota() + 1);
          
         //ak pretiekol den
         if(this.den.getHodnota() == 1){
             this.mesiac.setHodnota(this.mesiac.getHodnota() + 1);
             //prepocita hornu hranicu pre den
             this.den.setHronaHranica(this.getMaxPocetDniMesiaca());
             
             //ak pretiekol mesiac
             if(this.mesiac.getHodnota() == 1){
                 rok++;
                 this.rok1.setHodnota(rok/100);
                 this.rok2.setHodnota(rok%100);
             }
        }
         
    }
    
    
    
    public void tik() {
        int rok = getRok();
        
        if(++this.pocetTikov == 4){
            this.pocetTikov = 0;
            this.sekundy.krok();
            if(this.sekundy.getHodnota() == 3) this.stop();
            if (this.sekundy.getHodnota() == 0) {
                this.minuty.krok();
                if (this.minuty.getHodnota() == 0)
                    this.hodiny.krok();
                    if(this.hodiny.getHodnota() == 0){
                        this.den.krok();
                        if (this.den.getHodnota() == 1){
                            this.mesiac.krok();
                            this.den.setHronaHranica(this.getMaxPocetDniMesiaca());
                            if (this.mesiac.getHodnota() == 1){
                                 rok++;
                                 this.rok1.setHodnota(rok/100);
                                 this.rok2.setHodnota(rok%100);
                             }
                        }
                        this.zobrazAktualnyDatum();
                    }
            }
            
            this.zobrazAktualnyCas();
        }
    }
    
    public void pridajPriestupnuSekundu(){
        this.sekundy.priestupnaSekunda();
    }
}
