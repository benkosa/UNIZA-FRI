import java.util.ArrayList;

public class Skupina {
    private ArrayList<Osoba> zoznam;

    public Skupina() {
        this.zoznam = new ArrayList<Osoba>();
    }

    public void pridajOsobu(Osoba paOsoba) {
        this.zoznam.add(paOsoba);
    }

    public void pridajOsobu(String noveMeno, String novePriezvisko) {
        this.zoznam.add(new Osoba(noveMeno, novePriezvisko));
    }

    public boolean jeClenomSkupiny(Osoba paOsoba) {
        return this.zoznam.contains(paOsoba);
    }

    public int getPocetClenovSkupiny() {
        return this.zoznam.size();
    }

    
    
    
    
    public void vypisClenovSkupiny() {
        if (this.zoznam == null)
            System.out.println("Zoznam neexistuje!");
        else {
            if (this.zoznam.isEmpty())
                System.out.println("Zoznam je prazdny!");
            else {
                
                // Vypis osob cez cyklus foreach
                for(Osoba o: this.zoznam) {
                    System.out.println(o);
                }

                // Vypis osob cez cyklus while
                int i = 0;
                while(i < this.zoznam.size()) {
                    System.out.println(this.zoznam.get(i));
                    i++;
                }
                
                // Vypis osob cez cyklus for
                for(int index = 0; index < this.zoznam.size(); index++)    
                    System.out.println(this.zoznam.get(index));
            }
        }
    }
    
    public void odstranClenaSkupiny(int paPoradie) {
        if ((paPoradie >= 0) && (paPoradie < this.zoznam.size()))
            this.zoznam.remove(paPoradie);   
    }

    public void odstranClenaSkupiny(Osoba paOsoba) {
        this.zoznam.remove(paOsoba);
    }

    public void zrusSkupinu() {          
        this.zoznam.clear();    
    }
}
