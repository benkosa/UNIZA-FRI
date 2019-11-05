import java.util.ArrayList;

public class Skupina {
    // Atributom triedy bude zoznam osob (objektov typu Osoba)
    private ArrayList<Osoba> zoznamOsob;

    public Skupina() {
        this.zoznamOsob = new ArrayList<Osoba>();     
    }

    public void pridajOsobu(Osoba paOsoba) {
        this.zoznamOsob.add(paOsoba);
    }

    public void pridajOsobu(String noveMeno, String novePriezvisko) {
        // Pouzitie anonymneho objektu
        this.zoznamOsob.add(new Osoba(noveMeno, novePriezvisko));
    }

    public boolean jeClenomSkupiny(Osoba paOsoba) {
        // Takto NIE:
        //if (this.zoznamOsob.contains(paOsoba)) // alebo este horsie: if (this.zoznamOsob.contains(paOsoba) == true)
        //    return true;
        //else
        //    return false;

        return this.zoznamOsob.contains(paOsoba);
    }

    public int getPocetClenovSkupiny() {
        return this.zoznamOsob.size();
    }

    public void vypisClenovSkupiny() {
        if (this.zoznamOsob == null)
            System.out.println("Zoznam neexistuje!");
        else {
            if (this.zoznamOsob.isEmpty())
                System.out.println("Zoznam je prazdny!");
            
            //if (this.zoznamOsob.size() == 0)
            //    System.out.println("Zoznam je prazdny!");
            else {
                for(Osoba o: this.zoznamOsob) {
                    System.out.println(o);
                }
            }
        }
    }

    public void odstranClenaSkupiny(int paPoradie) {
        if ((paPoradie >= 0) && (paPoradie < this.zoznamOsob.size()))
            this.zoznamOsob.remove(paPoradie);   
    }

    public void odstranClenaSkupiny(Osoba paOsoba) {
        this.zoznamOsob.remove(paOsoba);
    }

    public void zrusSkupinu() {
        // Rozobrat so studentami, ktora moznost je spravna a preco !!!
        
        // V cykle foreach sa struktura (ArrayList) menit nemoze !!!
        //for(Osoba o: this.zoznamOsob)
        //    zoznamOsob.remove(o);
               
        //while (this.zoznamOsob.size() > 0)
        //    this.zoznamOsob.remove(0);
            
        this.zoznamOsob.clear();    
    }
}
