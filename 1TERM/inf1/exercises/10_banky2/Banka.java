public class Banka{
    private String aNazovBanky;
    private int celkovaSuma;

    public Banka(){
        this.setNazovBanky("FRI banka");
        celkovaSuma = 0;
    }

    public void setSuma(int s){
        celkovaSuma = s;
    }

    public int getSuma(){
        return this.celkovaSuma;
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
