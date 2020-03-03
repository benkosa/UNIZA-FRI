/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author kosa11
 */
public class Program {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        ZoznamPriponAplikacii zoznam = new ZoznamPriponAplikacii();
        
        zoznam.registruj("txt", "notepad.txt");
        zoznam.registruj("css", "style.css");
        
        System.out.println(zoznam.getAplikacia("txt"));
        System.out.println(zoznam.getAplikacia("css"));
        
        String cesta = "sdfsdsdfs/sdf/sdfsdf/sdf/s.css";
        
        System.out.println(zoznam.getAplikaciaPodlaNazvuSuboru(cesta));
    }
    
}
