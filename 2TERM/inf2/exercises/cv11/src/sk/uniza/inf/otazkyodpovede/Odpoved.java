package sk.uniza.inf.otazkyodpovede;

public class Odpoved {
    
    private String text;
    
    private boolean jeSpravna;

    public Odpoved(String text, boolean jeSpravna) {
        this.text = text;
        this.jeSpravna = jeSpravna;
    }

    public String getText() {
        return text;
    }

    public boolean isSpravna() {
        return jeSpravna;
    }
}
