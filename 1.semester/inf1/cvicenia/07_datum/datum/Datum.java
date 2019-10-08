
/**
 * Write a description of class Datum here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Datum {
    /**
     * Constructor for objects of class Datum
     */
    public int den;
    public int mesiac;
    public int rok;
    
    public Datum() {
        this.rok = 2019;
        this.mesiac = 1;
        this.den = 1;
        
    }
    
    public int getDen(){
        return this.den;
    }
    
    public int getMesiac(){
        return this.mesiac;
    }
    
    public int getRok(){
        return this.rok;
    }
    
    public void setRok(int rok){
        if (rok >= 1900)
            this.den = den;
        else
            this.den = 1900;
    }
    
    public void setMesiac(int mesiac){
        if (mesiac >= 1 && mesiac <= 12)
            this.mesiac = mesiac;
        else
            this.mesiac = 1;
    }
    
    public void setDen(int den){
        switch (this.mesiac){
            case 1:
            case 3:
            case 5:
            case 6:
            case 7:
            case 10:
            case 12:
                if (den >= 0 && den <= 31)
                    this.den = den;
                return;
            case 4:
            case 8:
            case 9:
            case 11:
                if (den >= 0 && den <= 30)
                    this.den = den;
                return;
            case 2:
                //je priestupny
                if((this.rok % 4 == 0) && ((this.rok % 100 != 0) || (this.rok % 400 == 0)))
                    if (den >= 0 && den <= 29)
                        this.den = den;
                else
                    if (den >= 0 && den <= 28)
                        this.den = den;
                return;
        
        }
        this.den = 1;
    }
}
