public class Banka {
    private String nazovBanky;

    public Banka() {
        this.setNazovBanky("FRI banka");
    }
        
    public String getNazovBanky(){
        return this.nazovBanky;
    }

    public void setNazovBanky(String novyNazov){
        if (!novyNazov.equals(""))
            this.nazovBanky = novyNazov;
        else
            this.nazovBanky = "Neznama banka";
    }
}
