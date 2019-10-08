/**
 * Trieda Student predstavuje studenta. Obsahuje jeho meno, osobne cislo
 * a prospech.
 */
public class Student {
    // meno studenta (Priezvisko, Meno)
    private String celeMeno;
    // osobne cislo studenta
    private String osobneCislo;
    // doteraz ziskane kredity
    private int kredity;

    /**
     * Vytvor noveho studenta so zadanym menom (Priezvisko, Meno) a osobnym cislom.
     * Nastavi jeho pocet kreditov na nulu.
     */
    public Student(String celeMeno, String osobneCislo) {
        this.celeMeno = celeMeno;
        this.osobneCislo = osobneCislo;
        this.kredity = 0;
    }

    /**
     * Vrat cele meno (Priezvisko, Meno)
     */
    public String getCeleMeno() {
        return this.celeMeno;
    }

    /**
     * Vrat osobne cislo
     */
    public String getOsobneCislo() {
        return this.osobneCislo;
    }

    /**
     * Pridaj studentovi zadany pocet kreditov
     */
    public void pridajKredity(int ziskaneKredity) {
        this.kredity += ziskaneKredity;
    }

    /**
     * Vrat pocet ziskanych kreditov.
     */
    public int getKredity() {
        return this.kredity;
    }

    /**
     * Vypocitaj a vrat prihlasovacie meno studenta
     */
    public String getPrihlasovacieMeno() {
        return this.celeMeno.substring(0, 4)
            + this.osobneCislo.substring(0, 3);
    }
}
