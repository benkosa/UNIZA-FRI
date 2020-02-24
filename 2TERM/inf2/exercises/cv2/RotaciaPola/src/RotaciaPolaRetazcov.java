
public class RotaciaPolaRetazcov {
    
    private String[] poleRetazcov;

    public RotaciaPolaRetazcov() {
        this.poleRetazcov = null;
    }
    
    public RotaciaPolaRetazcov(String[] poleRetazcov) {
        this.poleRetazcov = poleRetazcov;
    }
    
    public String[] getPoleRetazcov() {
        return poleRetazcov;
    }

    public void setPoleRetazcov(String[] poleRetazcov) {
        this.poleRetazcov = poleRetazcov;
    }
    
    public void posunVpravo() {
        if (this.poleRetazcov == null) {
            return;
        }

        // Vytvorime nove pole, do ktoreho skopirujeme stare prvky posunute 
        // o jednu poziciu vpravo
        String[] novePoleRetazcov = new String[this.poleRetazcov.length];
        for (int i = 0; i < this.poleRetazcov.length - 1; i++) {
            novePoleRetazcov[i+1] = this.poleRetazcov[i];
        }
        novePoleRetazcov[0] = this.poleRetazcov[this.poleRetazcov.length - 1];
        this.poleRetazcov = novePoleRetazcov;
    }
    
    public void posunVpravo(int pocetPosunuti) {
        pocetPosunuti = pocetPosunuti % this.poleRetazcov.length;
        
        for (int i = 0; i < pocetPosunuti; i++) {
            this.posunVpravo();
        }
    }
    
}
