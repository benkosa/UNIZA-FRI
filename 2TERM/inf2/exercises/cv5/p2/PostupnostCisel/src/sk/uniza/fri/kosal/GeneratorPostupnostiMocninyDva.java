package sk.uniza.fri.kosal;

/**
 *
 * @author kosa11
 */
class GeneratorPostupnostiMocninyDva implements iGenerator {
    private int cislo;

    public GeneratorPostupnostiMocninyDva() {
        this.cislo = 1;
    }
    
    @Override
    public int getNasledujuceCislo() {
        int predosleCislo = this.cislo;
        this.cislo*=2;
        return predosleCislo;
    }
    
    @Override
    public void reset() {
        cislo = 1;
    }
    
}
