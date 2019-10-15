
/**
 * Write a description of class CiselnyDisplay here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class CiselnyDisplay {
    /**
     * Constructor for objects of class CiselnyDisplay
     */
    private int hornaHranica;
    private int hodnota;
    private SSD lavySegment;
    private SSD pravySegment;
    public CiselnyDisplay(int hornaHranica, int x, int y) {
        // initialise instance variables
        this.hornaHranica = hornaHranica;
        this.hodnota = 0;
        this.lavySegment = new SSD(x, y);
        this.pravySegment = new SSD(x, y);
    }
    
    public void zobraz(){
        this.lavySegment.zobraz(this.hodnota/10);
        this.lavySegment.zobraz(this.hodnota%10);
    }
    
    public int getHodnota(){
        return this.hodnota;
    }
    
    public void setHodnota(int hodnota){
        if(this.)
    }
    
    public String getHodnotaAkoString(){
        if(this.hodnota < 10)
            return "0" + this.hodnota;
        
        return "" + this.hodnota;
    }
    
    public void krok(){}
}
