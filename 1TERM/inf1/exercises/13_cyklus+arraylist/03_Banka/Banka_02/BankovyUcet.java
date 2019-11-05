public class BankovyUcet{
    private int zostatok;
    private Banka aBanka;

    public BankovyUcet(){
        this.zostatok = 0;
        this.aBanka = null;
    }

    public Banka getBanka(){
        return this.aBanka;
    }

    public int getZostatok(){
        return this.zostatok;
    }

    public boolean Vklad(int suma){
        if (suma > 0){
            this.zostatok += suma; // this.zostatok = this.zostatok + suma;
            if (this.aBanka != null)
                this.aBanka.setSuma(this.aBanka.getSuma() + suma);
            return true;
        }
        else
            return false;
    }

    public boolean Vyber(int suma){
        if ((suma > 0) && (suma <= this.zostatok)){
            this.zostatok -= suma;
            if (this.aBanka != null)
                this.aBanka.setSuma(this.aBanka.getSuma() - suma);
            return true;
        }
        else
            return false;
    }

    public void setBanka(Banka novaBanka){
        if (novaBanka != null)
            this.aBanka = novaBanka;
    }
}
