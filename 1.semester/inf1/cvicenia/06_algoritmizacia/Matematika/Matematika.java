
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
    
    public Matematika() {
        this.atributA = 1;
        this.atributB = 2;
    }
    
    public Matematika(double atributA, double atributB) {
        this.atributA = atributA;
        this.atributB = atributB;
    }
    
    public double getAtributA(){
        return this.atributA;
    }
    
    public double getAtributB(){
        return this.atributB;
    }
    
    public void setAtributA(double atributA){
        this.atributA = atributA;
    }
    
    public void setAtributB(double atributB){
        this.atributB = atributB;
    }
    
}
