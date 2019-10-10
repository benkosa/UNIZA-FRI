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
    private int den;
    private int mesiac;
    private int rok;
    
    public Datum() {
        this.rok = 2019;
        this.mesiac = 10;
        this.den = 10;
        
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
            this.rok = rok;
        else
            this.rok = 1900;
    }
    
    public void setMesiac(int mesiac){
        if (mesiac >= 1 && mesiac <= 12)
            this.mesiac = mesiac;
        else
            this.mesiac = 1;
    }
    
    private boolean jePriestupny(){
        return (this.rok % 4 == 0) && ((this.rok % 100 != 0) || (this.rok % 400 == 0));
    }
    
    private int getMaxPocetDniMesiaca(){
        switch (this.mesiac){
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
    
    public void setDen(int den){
        this.den = 1;
        
        if (den >= 1 && den <= this.getMaxPocetDniMesiaca())
            this.den = den;
    }
    
    public int getPocetDniOdZaciatkuRoka(){
        
        int count = this.den;
        switch(this.mesiac){
            case 12: if(this.mesiac != 12)count += 31;
            case 11: if(this.mesiac != 11)count += 30;
            case 10: if(this.mesiac != 10)count += 31;
            case 9: if(this.mesiac != 9)count += 30;
            case 8: if(this.mesiac != 8)count += 31;
            case 7: if(this.mesiac != 7)count += 31;
            case 6: if(this.mesiac != 6)count += 30;
            case 5: if(this.mesiac != 5)count += 31;
            case 4: if(this.mesiac != 4)count += 30;
            case 3: if(this.mesiac != 3)count += 31;
            case 2:
                if(this.jePriestupny()){
                    if(this.mesiac != 2)count += 29;
                }else{    
                    if(this.mesiac != 2)count += 28;
                }
            case 1: if(this.mesiac != 1)count += 31;
        } 
        
        return count;        
    }
   

    
    public Datum getZajtra(){
         Datum datumZajtra = new Datum();
         
         datumZajtra.setRok(this.rok);
         datumZajtra.setMesiac(this.mesiac);
         datumZajtra.setDen(++this.den);
         
         if(datumZajtra.den == 1)
            datumZajtra.setMesiac(++this.mesiac);
         
         if(datumZajtra.mesiac == 1)
            datumZajtra.setRok(++this.rok);
         
         System.out.println(datumZajtra.den + "." + datumZajtra.mesiac + "." + datumZajtra.rok+"\n");
         return datumZajtra;
    }
}
