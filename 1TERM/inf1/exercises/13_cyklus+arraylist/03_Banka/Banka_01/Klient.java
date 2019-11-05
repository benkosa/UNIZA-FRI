public class Klient{
    private String aMeno;
    private String aPriezvisko;
    private Banka aBanka;

    public Klient(){
        this.aMeno = "Marek";
        this.aPriezvisko = "Kvet";
        this.aBanka = null;
    }

    public Klient(String paMeno, String paPriezvisko){
        this.aMeno = paMeno;
        this.aPriezvisko = paPriezvisko;
        this.aBanka = null;
    }
        
    public String getMeno(){
        return this.aMeno;
    }

    public String getPriezvisko(){
        return this.aPriezvisko;
    }

    public Banka getBanka(){
        return this.aBanka; 
    }

    public void setMeno(String noveMeno){
        if (!noveMeno.equals(""))
            this.aMeno = noveMeno;
        else
            this.aMeno = "Nezname meno";
    }

    public void setPriezvisko(String novePriezvisko){
        if (!novePriezvisko.equals(""))
            this.aPriezvisko = novePriezvisko;
        else
            this.aPriezvisko = "Nezname priezvisko";
    }

    public void vypisNazovSvojejBanky(){
        if (this.aBanka == null)
            System.out.println("Nemam banku!");
        else 
            System.out.println(this.aBanka.getNazovBanky());
    }

    public void setBanka(Banka novaBanka){
        if (novaBanka != null)
            this.aBanka = novaBanka;
    }
}
