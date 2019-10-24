
/**
 * 2-ciferny displej
 */
public class CiselnyDisplej {
    private int hornaHranica;
    private int hodnota;
    private SSD lavySSD;
    private SSD pravySSD;
    
    private int povodnaHronaHranica;
    
    public CiselnyDisplej(int hornaHranica, int surX, int surY) {
        this.hornaHranica = hornaHranica;
        this.povodnaHronaHranica = hornaHranica;
        this.hodnota = 0;
        
        this.lavySSD = new SSD(surX, surY);
        this.pravySSD = new SSD(surX+110, surY);
    }
    
    public void zobraz() {
        this.lavySSD.zobraz(this.hodnota / 10);
        this.pravySSD.zobraz(this.hodnota % 10);
    }
    
    public int getHodnota() {
        return this.hodnota;
    }
    
    public int getHornaHranica() {
        return this.hornaHranica;
    }
    
    public void setHodnota(int hodnota) {
        if ((hodnota >= 0) && (hodnota < this.hornaHranica))
            this.hodnota = hodnota;
    }
    
    public void setHodnotaDatum(int hodnota) {
        if ((hodnota >= 0) && (hodnota <= this.hornaHranica))
            this.hodnota = hodnota;
    }
    
    public void setHronaHranica(int hornaHranica){
        this.hornaHranica = hornaHranica;
    }
    
    public String getHodnotaAkoRetazec() {
        if(this.hodnota < 10) {
            return "0" + this.hodnota;
        } else {
            return "" + this.hodnota;
        }
    }
    
    public void krok() {
        this.hodnota = (this.hodnota - 1) % this.hornaHranica;
        if(this.hodnota == 0)
            this.hornaHranica = this.povodnaHronaHranica;
    }
    
    public void krokZobraz() {
        this.krok();
        this.zobraz();
    }
    
    public void priestupnaSekunda(){
        this.hornaHranica++;
    }
}
