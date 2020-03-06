package sk.uniza.fri.kosal;

/**
 *
 * @author kosa11
 */
class GeneratorPostupnostiNeparnychCisel implements IGenerator {
    private int cislo;
    
    GeneratorPostupnostiNeparnychCisel() {
        this.cislo = -1;
    }

    @Override
    public int getNasledujuceCislo() {
        this.cislo += 2;
        return this.cislo;
    }

    @Override
    public void reset() {
        this.cislo = -1;
    }
    
}
