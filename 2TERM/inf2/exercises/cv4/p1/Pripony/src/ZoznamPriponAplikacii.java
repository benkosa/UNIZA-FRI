import java.util.HashMap; // import the HashMap class

/**
 *
 * @author kosa11
 */
public class ZoznamPriponAplikacii {
    private HashMap<String, String> pripony;

    public ZoznamPriponAplikacii() {
        this.pripony = new HashMap<String, String>();
    }
    
    public void registruj(String pripona, String aplikacia) {
        this.pripony.put(pripona, aplikacia);
    }
    
    public void odRegistruj(String pripona) {
        this.pripony.remove(pripona);
    }
    
    public String getAplikacia(String pripona) {
        return this.pripony.get(pripona);
    }
    
    public String getAplikaciaPodlaNazvuSuboru(String cestaKsuboru) {
        int id = cestaKsuboru.lastIndexOf(".") + 1;
        if(id >= 0) return cestaKsuboru.substring(id);
        
        return null;
    }
}
