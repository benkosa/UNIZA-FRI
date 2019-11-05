import java.util.ArrayList;
import java.util.Random;

public class Banka{
    private String aNazovBanky;
    private ArrayList<BankovyUcet> zoznamUctov;

    public Banka(){
        this.setNazovBanky("Tatra banka");
        this.zoznamUctov = new ArrayList<BankovyUcet>();
    }    

    public int getCelkovaSuma(){
        if (this.zoznamUctov == null)
            return 0;
        else {
            int celkovaSuma = 0;
            for (BankovyUcet bu: this.zoznamUctov) { 
                celkovaSuma += bu.getZostatok();
            }
            return celkovaSuma;
        }
    }

    public String getNazovBanky() {
        return this.aNazovBanky;
    }

    public ArrayList<BankovyUcet> vratZoznamUctov() {
        return this.zoznamUctov;
    }    

    public void setNazovBanky(String novyNazov) {
        if (!novyNazov.equals(""))
            this.aNazovBanky = novyNazov;
        else
            this.aNazovBanky = "Neznama banka";
    }

    public BankovyUcet vytvorNovyUcet(Klient paKlient) {
        // Doplnit!
        return null;
    }

    public void vypisCislaVsetkychUctov() {
        // Doplnit!
    }

    public void vypisZoznamKlientovBezDuplicit() {
        // Doplnit!
    }
}
