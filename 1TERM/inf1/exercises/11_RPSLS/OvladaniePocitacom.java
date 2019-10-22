import java.util.Random;

public class OvladaniePocitacom {
    private Ruka ruka;
    private Random generator;

    public OvladaniePocitacom() {
        this.ruka = new Ruka(200, 200, 0);
        this.generator = new Random();
    }

    public Ruka getRuka() {
        return this.ruka;
    }

    public void tik() {
        this.ruka.setGesto(generator.nextInt(5));
    }
}
