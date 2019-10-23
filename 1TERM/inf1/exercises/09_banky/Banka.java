public class Banka {
    private String aNazovBanky;

    public Banka() {
        this.setNazovBanky("FRI banka");
    }
        
    public String getNazovBanky(){
        return this.aNazovBanky;
    }

    public void setNazovBanky(String novyNazov){
        if (!novyNazov.equals(""))
            this.aNazovBanky = novyNazov;
        else
            this.aNazovBanky = "Neznama banka";
    }
   
}
