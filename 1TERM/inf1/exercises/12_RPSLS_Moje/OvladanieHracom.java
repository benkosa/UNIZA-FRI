public class OvladanieHracom {
    private Ruka ruka;

    public OvladanieHracom() {
        this.ruka = new Ruka(100, 200, 0);
    }

    public Ruka getRuka() {
        return this.ruka;
    }

    public void posunHore() {
        this.ruka.posunHore();
    }

    public void posunDole() {
        this.ruka.posunDole();
    }

    public void posunVpravo() {
        this.ruka.posunVpravo();
    }

    public void posunVlavo() {
        this.ruka.posunVlavo();
    }
}
