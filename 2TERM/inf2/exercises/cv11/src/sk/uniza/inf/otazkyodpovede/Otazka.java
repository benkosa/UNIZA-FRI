package sk.uniza.inf.otazkyodpovede;

import java.util.ArrayList;

public class Otazka {
    
    private final String text;

    private final ArrayList<Odpoved> odpovede; 

    public Otazka(String text) {
        this.text = text;
        this.odpovede = new ArrayList<>();
    }
    
    public void pridajOdpoved(Odpoved odpoved) {
        this.odpovede.add(odpoved);
    }
    
    public void vypis() {
        System.out.println(this.text);
//        for (int i = 0; i < this.odpovede.size(); i++) {
//            System.out.println( (i+1) + ". " + this.odpovede.get(i));
//        }
        
        int cislo = 1;
        for (Odpoved odpoved : this.odpovede) {
            System.out.println(cislo + ". " + odpoved.getText());
            cislo++;
        }
    }

    public String getText() {
        return this.text;
    }
    
    public int getPocetOdpovedi() {
        return this.odpovede.size();
    }

    public Odpoved getOdpoved(int index) {
        if (index < 0 || index >= this.odpovede.size()) {
            return null;
        }
        
        return this.odpovede.get(index);
    }
    
}
