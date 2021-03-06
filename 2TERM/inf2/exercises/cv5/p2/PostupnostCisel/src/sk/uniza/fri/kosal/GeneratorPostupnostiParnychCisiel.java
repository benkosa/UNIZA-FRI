package sk.uniza.fri.kosal;

/**
 *
 * @author kosa11
 */
class GeneratorPostupnostiParnychCisiel implements IGenerator {
    private int cislo;

    GeneratorPostupnostiParnychCisiel() {
        this.cislo = -2;
    }
    
    @Override
    public int getNasledujuceCislo() {
        this.cislo += 2;
        return this.cislo;
    }
    
    @Override
    public void reset() {
        this.cislo = -2;
    }
}
