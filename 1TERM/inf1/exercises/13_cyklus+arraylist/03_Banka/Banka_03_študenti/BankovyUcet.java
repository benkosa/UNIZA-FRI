import java.util.ArrayList;

public class BankovyUcet{
    private int zostatok;
    private String cisloUctu;
    private String PIN;
    private Banka aBanka;
    private ArrayList<Transakcia> pohybyNaUcte;
    private Klient majitel;

    public BankovyUcet(String paCisloUctu, Banka b, Klient k){
        this.zostatok = 0;
        this.cisloUctu = paCisloUctu;
        this.aBanka = b;
        this.pohybyNaUcte = new ArrayList<Transakcia>();
        this.majitel = k;
        this.PIN = "0000";
    }

    public int getZostatok(){
        return this.zostatok;
    }

    public String getCisloUctu(){
        return this.cisloUctu;
    }

    public Banka getBanka(){
        return this.aBanka;
    }

    public Klient getKlient(){
        return this.majitel;
    }

    public boolean Vklad(int suma){
        if (suma > 0){
            this.zostatok += suma;
            this.pohybyNaUcte.add(new Transakcia("Vklad", suma));
            return true;
        }
        else
            return false;
    }

    public boolean Vyber(int suma, String heslo){
        if (suma > 0 && suma <= this.zostatok){
            if (overHeslo(heslo)){
                this.zostatok -= suma;
                this.pohybyNaUcte.add(new Transakcia("Vyber", suma));
                return true;
            }
            else 
                return false;
        }
        else
            return false;
    }

    public boolean prevodNaInyUcet(int suma, String ciel, String heslo){
        if (suma <= this.zostatok){
            // Mozme presuvat na iny ucet
            // Skontrolujeme, ci v banke existuje cielovy ucet
            if (this.aBanka == null){
                System.out.println("Neexistuje banka pre tento ucet!");
                return false;
            }
            else {
                BankovyUcet cielovyUcet = null;
                ArrayList<BankovyUcet> ucty = this.aBanka.vratZoznamUctov();
                for(BankovyUcet ucet: ucty)
                    if (ucet.getCisloUctu().equals(ciel))
                        cielovyUcet = ucet;

                if(cielovyUcet == null){
                    System.out.println("Nenasiel sa cielovy ucet!");
                    return false;
                }
                else {
                    if (this.Vyber(suma, heslo) && cielovyUcet.Vklad(suma)){
                        System.out.println("Transakcia uspesna!");
                        return true;
                    }
                    else {
                        System.out.println("Nastala ina chyba!");
                        return false;
                    }                   
                }
            }
        }
        else {
            // Nedostatocna hotovost na ucte
            System.out.println("Na ucte nie je dostatocna suma!");
            return false;
        }
    }

    public void vypisZuctu(){
        // Doplnit!
        System.out.println("Aktualny zostatok na ucte: " + this.getZostatok());
    }

    public String getPIN(){
        return PIN;
    }

    public boolean setHeslo(String stareHeslo, String noveHeslo) {
        // 1. Nove heslo nesmie byt null
        if (noveHeslo == null)
            return false;

        // 2. Nove heslo musi byt aspon 4-miestne cislo (PIN kod)
        // (v opacnom pripade ho nezmeni)
        boolean jeNoveHesloOK = true;
        if (noveHeslo.length() < 4)
            jeNoveHesloOK = false;
        else {
            for (int i = 0; i < noveHeslo.length(); i++)
            {
                if (!Character.isDigit(noveHeslo.charAt(i))) {
                    jeNoveHesloOK = false;
                    break;
                }
            }

            if (jeNoveHesloOK){
                if (overHeslo(stareHeslo))
                    this.PIN = noveHeslo;
                else
                    jeNoveHesloOK = false;
            }
        }

        return jeNoveHesloOK;
    }

    public boolean overHeslo(String h) {
        // Doplnit!
        return this.PIN.equals(h);
    }
}
