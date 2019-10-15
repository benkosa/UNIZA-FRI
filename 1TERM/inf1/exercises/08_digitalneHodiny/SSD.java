
/**
 * Write a description of class SSD here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class SSD {
    /**
     * Constructor for objects of class SSD
     */
    
    private Segment segmentA;
    private Segment segmentB;
    private Segment segmentC;
    private Segment segmentD;
    private Segment segmentE;
    private Segment segmentF;
    private Segment segmentG;
    
    public SSD(int paLHX, int paLHY) {
        // initialise instance variables
        this.segmentA = new Segment(50, 15, 15+paLHX, paLHY);
        this.segmentB = new Segment(15, 50, 65+paLHX, 15+paLHY);
        this.segmentC = new Segment(15, 50, 65+paLHX, 80+paLHY);
        this.segmentD = new Segment(50, 15, 15+paLHX, 100+30+paLHY);
        this.segmentE = new Segment(15, 50, paLHX, 80+paLHY);
        this.segmentF = new Segment(15, 50, paLHX, 15+paLHY);
        this.segmentG = new Segment(50, 15, 15+paLHX, 65+paLHY);
    }
    
    public void rozsvietVsetko() {
        // initialise instance variables
        this.segmentA.rozsviet();
        this.segmentB.rozsviet();
        this.segmentC.rozsviet();
        this.segmentD.rozsviet();
        this.segmentE.rozsviet();
        this.segmentF.rozsviet();
        this.segmentG.rozsviet();
    }
    
    public void zhasniVsetko() {
        // initialise instance variables
        this.segmentA.zhasni();
        this.segmentB.zhasni();
        this.segmentC.zhasni();
        this.segmentD.zhasni();
        this.segmentE.zhasni();
        this.segmentF.zhasni();
        this.segmentG.zhasni();
    }
    
    public void rozsviet1() {
        // initialise instance variables
        this.segmentA.rozsviet();
        this.segmentB.rozsviet();
        this.segmentC.rozsviet();
        this.segmentD.zhasni();
        this.segmentE.zhasni();
        this.segmentF.zhasni();
        this.segmentG.zhasni();
    }
    
        
    private void rozsviet2() {
        // initialise instance variables
        this.segmentA.rozsviet();
        this.segmentB.rozsviet();
        this.segmentC.zhasni();
        this.segmentD.rozsviet();
        this.segmentE.rozsviet();
        this.segmentF.zhasni();
        this.segmentG.rozsviet();
    }    
    private void rozsviet3() {
        // initialise instance variables
        this.segmentA.rozsviet();
        this.segmentB.rozsviet();
        this.segmentC.rozsviet();
        this.segmentD.rozsviet();
        this.segmentE.zhasni();
        this.segmentF.zhasni();
        this.segmentG.rozsviet();
    }    
    private void rozsviet4() {
        // initialise instance variables
        this.segmentA.zhasni();
        this.segmentB.zhasni();
        this.segmentC.rozsviet();
        this.segmentD.zhasni();
        this.segmentE.rozsviet();
        this.segmentF.rozsviet();
        this.segmentG.rozsviet();
    }    
    private void rozsviet5() {
        // initialise instance variables
        this.segmentA.rozsviet();
        this.segmentB.zhasni();
        this.segmentC.rozsviet();
        this.segmentD.rozsviet();
        this.segmentE.zhasni();
        this.segmentF.rozsviet();
        this.segmentG.rozsviet();
    }    
    private void rozsviet6() {
        // initialise instance variables
        this.segmentA.zhasni();
        this.segmentB.zhasni();
        this.segmentC.rozsviet();
        this.segmentD.rozsviet();
        this.segmentE.rozsviet();
        this.segmentF.rozsviet();
        this.segmentG.rozsviet();
    }    
    private void rozsviet7() {
        // initialise instance variables
        this.segmentA.rozsviet();
        this.segmentB.rozsviet();
        this.segmentC.zhasni();
        this.segmentD.zhasni();
        this.segmentE.rozsviet();
        this.segmentF.zhasni();
        this.segmentG.rozsviet();
    }    
    private void rozsviet8() {
        // initialise instance variables
        this.rozsvietVsetko();
    }    
    private void rozsviet9() {
        // initialise instance variables
        this.segmentA.rozsviet();
        this.segmentB.rozsviet();
        this.segmentC.rozsviet();
        this.segmentD.zhasni();
        this.segmentE.zhasni();
        this.segmentF.rozsviet();
        this.segmentG.rozsviet();
    }    
    private void rozsviet0() {
        // initialise instance variables
        this.rozsvietVsetko();
        this.segmentG.zhasni();
    }    
    private void rozsvietA() {
        // initialise instance variables
        this.segmentA.rozsviet();
        this.segmentB.rozsviet();
        this.segmentC.rozsviet();
        this.segmentD.zhasni();
        this.segmentE.rozsviet();
        this.segmentF.rozsviet();
        this.segmentG.rozsviet();
    }    
    private void rozsvietP() {
        // initialise instance variables
        this.segmentA.rozsviet();
        this.segmentB.rozsviet();
        this.segmentC.zhasni();
        this.segmentD.zhasni();
        this.segmentE.rozsviet();
        this.segmentF.zhasni();
        this.segmentG.rozsviet();
    }
    public void zobraz(int cislo) {
        switch(cislo){
            case 0: this.rozsviet0(); break;
            case 1: this.rozsviet1(); break;
            case 2: this.rozsviet2(); break;
            case 3: this.rozsviet3(); break;
            case 4: this.rozsviet4(); break;
            case 5: this.rozsviet5(); break;
            case 6: this.rozsviet6(); break;
            case 7: this.rozsviet7(); break;
            case 8: this.rozsviet8(); break;
            case 9: this.rozsviet9(); break;
            default: this.zhasniVsetko();
        }
        
    }
}
