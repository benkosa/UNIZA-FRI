public class Klient{
    private String aMeno;
    private String aPriezvisko;
    private BankovyUcet ucet;

    public Klient(){
        this.aMeno = "Marek";
        this.aPriezvisko = "Kvet";
        this.ucet = new BankovyUcet(); // vztah kompozicie (kazda osoba ma svoj ucet)
    }

    public String getMeno(){
        return this.aMeno;
    }

    public String getPriezvisko(){
        return this.aPriezvisko;
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
        if (this.ucet != null){
            Banka b = this.ucet.getBanka();
            if (b == null)
                System.out.println("Nemam banku!");
            else 
                System.out.println(b.getNazovBanky());
        }
        else
            System.out.println("Nemam ucet!");
    }

    public void setBanka(Banka novaBanka){
        if (novaBanka != null){
            if (this.ucet != null)
                this.ucet.setBanka(novaBanka);
            else
                System.out.println("Nemam ucet!");
        }
    }

    public void vlozNaUcet(int s){
        if (this.ucet == null)
            System.out.println("Nemam ucet!");
        else{
            if (this.ucet.Vklad(s))
                System.out.println("Transakcia uspesna.");
            else
                System.out.println("Transakcia neuspesna.");
        }
    }

    public void vyberZUctu(int s){
        if (this.ucet == null)
            System.out.println("Nemam ucet!");
        else{
            if (this.ucet.Vyber(s))
                System.out.println("Transakcia uspesna.");
            else
                System.out.println("Transakcia neuspesna.");
        }
    }

    public void vypisStavUctu(){
        if (this.ucet == null)
            System.out.println("Nemam ucet!");
        else
            System.out.println(this.ucet.getZostatok());
    }

    public void zrusUcet(){
        if (this.ucet == null)
            System.out.println("Nemam ucet!");
        else{
            Banka b = this.ucet.getBanka();
            if (b != null)
                b.setSuma(b.getSuma() - this.ucet.getZostatok());
            this.ucet = null;
        }
    }
}
