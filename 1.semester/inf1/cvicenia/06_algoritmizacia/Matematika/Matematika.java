
/**
 * Write a description of class Matematika here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Matematika {
    /**
     * Constructor for objects of class Matematika
     */
    public double atributA;
    public double atributB;
    public double atributC;
    
    public Matematika() {
        this.atributA = 1;
        this.atributB = 2;
        this.atributC = 3;
    }
    
    public Matematika(double atributA, double atributB, double atributC) {
        setAtributA(atributA);
        setAtributB(atributB);
        this.atributC = atributC;
    }
    
    public double getAtributA(){
        return this.atributA;
    }
    
    public double getAtributB(){
        return this.atributB;
    }
    
    public void setAtributA(double atributA){
        if(atributA > 0)
            this.atributA = atributA;
        else
            this.atributA = 1;
            
    }
    
    public void setAtributB(double atributB){
        if(atributB > 0)
            this.atributB = atributB;
        else
            this.atributB = 1;
    }
    
    public void vypis(){
        System.out.println(this.atributA + " \n" + this.atributB + " \n" + this.atributC);
    }
    
    public void vypisMax(){
        if(this.atributA > this.atributB)
            System.out.println(this.atributA);
        else
            System.out.println(this.atributB);
    }
    
    public double najdiMax(double atributA, double atributB) {
        if(atributA > atributB)
            return atributA;
            
        return atributB;
    }
    
    public void vypisMax3(){
        System.out.println(najdiMax(najdiMax(this.atributA, this.atributB), this.atributC));
    }
    
    public void swap(){
        double tmp = this.atributA;
        this.atributA = this.atributB;
        this.atributB = tmp;
        
    }
   
    
}
