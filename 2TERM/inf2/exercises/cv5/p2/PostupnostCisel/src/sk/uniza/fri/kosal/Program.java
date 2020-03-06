package sk.uniza.fri.kosal;

/**
 *
 * @author kosa11
 */
public class Program {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        GeneratorPostupnostiParnychCisiel generator = new GeneratorPostupnostiParnychCisiel();
        vygenerujCisla(generator);
        System.out.println("********************************************");
        
        GeneratorPostupnostiMocninyDva generatorMocniny = new GeneratorPostupnostiMocninyDva();
        vygenerujCisla(generatorMocniny);
        System.out.println("********************************************");
        
        GeneratorPostupnostiNeparnychCisel generatorNeparne = new GeneratorPostupnostiNeparnychCisel();
        vygenerujCisla(generatorNeparne);
    }

    private static void vygenerujCisla(IGenerator generator) {
        for (int i = 0; i < 5; i++) {
            int cislo = generator.getNasledujuceCislo();
            System.out.println(cislo);
        }
        generator.reset();
        for (int i = 0; i < 10; i++) {
            int cislo = generator.getNasledujuceCislo();
            System.out.println(cislo);
        }
    }
}
