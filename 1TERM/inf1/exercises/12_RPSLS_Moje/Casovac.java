public class Casovac {
    private int pocetTikov;
    private int maxPocetTikov;
    private boolean jeAktivny;
    private Hra hra;

    public Casovac(Hra h) {
        this.pocetTikov = 0;
        this.maxPocetTikov = 0;
        this.hra = h;
        this.jeAktivny = false;
    }

    public void start(int paMaxPocet) {
        this.maxPocetTikov = paMaxPocet;
        this.pocetTikov = 0;
        this.jeAktivny = true;
    }

    public void tik() {
        if (this.jeAktivny){
            this.pocetTikov++;
            if (this.pocetTikov == this.maxPocetTikov)
                this.stop();
        }
    }

    public void stop() {
        this.jeAktivny = false;
        if (this.hra != null)
            hra.jeCas();
    }
}
