/** 7-segmentovy displej s privatnymi metodami
 * metoda - odpoved objektu na spravu zvonka
 *  Segmenty:
 *   ---a---
 *  |       |
 *  f       b
 *  |       |
 *   ---g---
 *  |       |
 *  e       c
 *  |       |
 *   ---d---
 */
public class SSD {
    private Segment aSegmentA;
    private Segment aSegmentB;
    private Segment aSegmentC;
    private Segment aSegmentD;
    private Segment aSegmentE;
    private Segment aSegmentF;
    private Segment aSegmentG;
    
    public SSD(int paLHX, int paLHY) {
        this.aSegmentA = new Segment(50, 15, 15+paLHX, paLHY);
        this.aSegmentB = new Segment(15, 50, 65+paLHX, 15+paLHY);
        this.aSegmentC = new Segment(15, 50, 65+paLHX, 80+paLHY);
        this.aSegmentD = new Segment(50, 15, 15+paLHX, 100+30+paLHY);
        this.aSegmentE = new Segment(15, 50, paLHX, 80+paLHY);
        this.aSegmentF = new Segment(15, 50, paLHX, 15+paLHY);
        this.aSegmentG = new Segment(50, 15, 15+paLHX, 65+paLHY);
    }
    
    private void zobrazVsetko() {
        this.aSegmentA.rozsviet();
        this.aSegmentB.rozsviet();
        this.aSegmentC.rozsviet();
        this.aSegmentD.rozsviet();
        this.aSegmentE.rozsviet();
        this.aSegmentF.rozsviet();
        this.aSegmentG.rozsviet();
    }
    private void zhasniVsetko() {
        this.aSegmentA.zhasni();
        this.aSegmentB.zhasni();
        this.aSegmentC.zhasni();
        this.aSegmentD.zhasni();
        this.aSegmentE.zhasni();
        this.aSegmentF.zhasni();
        this.aSegmentG.zhasni();        
    }
    // CISLA
    private void zobraz0() {
        this.aSegmentA.rozsviet();
        this.aSegmentB.rozsviet();
        this.aSegmentC.rozsviet();
        this.aSegmentD.rozsviet();
        this.aSegmentE.rozsviet();
        this.aSegmentF.rozsviet();
        this.aSegmentG.zhasni();
    }
    private void zobraz1() {
        this.aSegmentA.zhasni();
        this.aSegmentB.rozsviet();
        this.aSegmentC.rozsviet();
        this.aSegmentD.zhasni();
        this.aSegmentE.zhasni();
        this.aSegmentF.zhasni();
        this.aSegmentG.zhasni();
    }
    private void zobraz2() {
        this.aSegmentA.rozsviet();
        this.aSegmentB.rozsviet();
        this.aSegmentC.zhasni();
        this.aSegmentD.rozsviet();
        this.aSegmentE.rozsviet();
        this.aSegmentF.zhasni();
        this.aSegmentG.rozsviet();
    }
    private void zobraz3() {
        this.aSegmentA.rozsviet();
        this.aSegmentB.rozsviet();
        this.aSegmentC.rozsviet();
        this.aSegmentD.rozsviet();
        this.aSegmentE.zhasni();
        this.aSegmentF.zhasni();
        this.aSegmentG.rozsviet();
    }
    private void zobraz4() {
        this.aSegmentA.zhasni();
        this.aSegmentB.rozsviet();
        this.aSegmentC.rozsviet();
        this.aSegmentD.zhasni();
        this.aSegmentE.zhasni();
        this.aSegmentF.rozsviet();
        this.aSegmentG.rozsviet();
    }
    private void zobraz5() {
        this.aSegmentA.rozsviet();
        this.aSegmentB.zhasni();
        this.aSegmentC.rozsviet();
        this.aSegmentD.rozsviet();
        this.aSegmentE.zhasni();
        this.aSegmentF.rozsviet();
        this.aSegmentG.rozsviet();
    }
    private void zobraz6() {
        this.aSegmentA.rozsviet();
        this.aSegmentB.zhasni();
        this.aSegmentC.rozsviet();
        this.aSegmentD.rozsviet();
        this.aSegmentE.rozsviet();
        this.aSegmentF.rozsviet();
        this.aSegmentG.rozsviet();
    }
    private void zobraz7() {
        this.aSegmentA.rozsviet();
        this.aSegmentB.rozsviet();
        this.aSegmentC.rozsviet();
        this.aSegmentD.zhasni();
        this.aSegmentE.zhasni();
        this.aSegmentF.zhasni();
        this.aSegmentG.zhasni();
    }
    private void zobraz8() {
        this.zobrazVsetko();
    }
    private void zobraz9() {
        this.aSegmentA.rozsviet();
        this.aSegmentB.rozsviet();
        this.aSegmentC.rozsviet();
        this.aSegmentD.zhasni();
        this.aSegmentE.zhasni();
        this.aSegmentF.rozsviet();
        this.aSegmentG.rozsviet();
    }
    public void zobrazA() {
        this.aSegmentA.rozsviet();
        this.aSegmentB.rozsviet();
        this.aSegmentC.rozsviet();
        this.aSegmentD.zhasni();
        this.aSegmentE.rozsviet();
        this.aSegmentF.rozsviet();
        this.aSegmentG.rozsviet();
    }
    public void zobrazP() {
        this.aSegmentA.rozsviet();
        this.aSegmentB.rozsviet();
        this.aSegmentC.zhasni();
        this.aSegmentD.zhasni();
        this.aSegmentE.rozsviet();
        this.aSegmentF.rozsviet();
        this.aSegmentG.rozsviet();
    }
    
    public void zobraz(int cislo) {
        switch(cislo) {
            case 0: this.zobraz0();
                break;
            case 1: this.zobraz1();
                break;
            case 2: this.zobraz2();
                break;
            case 3: this.zobraz3();
                break;
            case 4: this.zobraz4();
                break;
            case 5: this.zobraz5();
                break;
            case 6: this.zobraz6();
                break;
            case 7: this.zobraz7();
                break;
            case 8: this.zobraz8();
                break;
            case 9: this.zobraz9();
                break;
            default: this.zhasniVsetko();
                
            }
        }
}
