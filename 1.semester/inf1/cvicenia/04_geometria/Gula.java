
/**
 * Write a description of class Gula here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Gula {
    
    private double polomer;
    /**
     * Constructor for objects of class Gula
     */
    public Gula() {
        this.polomer = 10.5;// initialise instance variables
    }
    
    public Gula(double polomer){
        this.polomer = polomer;
    }
    
    public double getPolomer(){
        return this.polomer;
    }
    
    private double setPolomer(){
        return this.polomer;
    }
    
    public double countObjem(){
        return (4/3)*3.14*this.getPolomer()*this.getPolomer()*this.getPolomer();
        
    }
        
    public void vypisInfo(){
        System.out.println(this + "\nPolomer: " + this.getPolomer() + "cm\n");
    }
    
}
