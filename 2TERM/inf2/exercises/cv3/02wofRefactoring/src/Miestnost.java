/**
 * Trieda Miestnost realizuje jednu miestnost/priestor v celom priestore hry.
 * Kazda "miestnost" je z inymi miestnostami spojena vychodmi. 
 * Vychody z miestnosti su oznacovane svetovymi stranami sever, vychod, juh
 * a zapad. Pre kazdy vychod si miestnost pamata odkaz na susednu miestnost
 * alebo null, ak tym smerom vychod nema.
 *
 * @author  Michael Kolling, David J. Barnes
 * @version 2006.03.30
 * @author  lokalizacia: Lubomir Sadlon, Jan Janech
 * @version 2012.02.21
 */
public class Miestnost {
    private String popisMiestnosti;
    private Miestnost severnyVychod;
    private Miestnost juznyVychod;
    private Miestnost vychodnyVychod;
    private Miestnost zapadnyVychod;

    /**
     * Vytvori miestnost popis ktorej je v parametrom.
     * Po vytvoreni miestnost nema ziadne vychody. Popis miesnost strucne 
     * charakterizuje.
     * 
     * @param popis text popisu miestnosti.
     */
    public Miestnost(String popis) {
        this.popisMiestnosti = popis;
    }

    /**
     * Nastavi vychody z miestnosti. Kazdy vychod je urceny bud odkazom 
     * na miestnost alebo hodnotou null, ak vychod tym smerom neexistuje.
     * 
     * @param sever miestnost smerom na sever.
     * @param vychod miestnost smerom na vychod.
     * @param juh miestnost smerom na juh.
     * @param zapad miestnost smerom na zapad.
     */
    public void nastavVychody(Miestnost sever, Miestnost vychod, Miestnost juh, Miestnost zapad) {
        if (sever != null) {
            this.severnyVychod = sever;
        }
        if (vychod != null) {
            this.vychodnyVychod = vychod;
        }
        if (juh != null) {
            this.juznyVychod = juh;
        }
        if (zapad != null) {
            this.zapadnyVychod = zapad;
        }
    }

    public Miestnost getVychod(String smer) {
        switch (smer) {
            case "sever":
                return this.severnyVychod;
            case "vychod":
                return this.vychodnyVychod;
            case "juh":
                return this.juznyVychod;
            case "zapad":
                return this.zapadnyVychod;
            default:
                return null;
        }
    }

    /**
     * @return textovy popis miestnosti.
     */
    public String getPopis() {
        return this.popisMiestnosti;
    }
    
    public String getPopisVychodov() {
        StringBuilder vychody = new StringBuilder("Vychody:");
        if (this.severnyVychod != null) {
            vychody.append(" sever");
        }
        if (this.vychodnyVychod != null) {
            vychody.append(" vychod");
        }
        if (this.juznyVychod != null) {
            vychody.append(" juh");
        }
        if (this.zapadnyVychod != null) {
            vychody.append(" zapad");
        }
        return vychody.toString();
    }

    public void vypisInfo() {
        System.out.println(this.getPopis());
        System.out.println(this.getPopisVychodov());
    }
}
