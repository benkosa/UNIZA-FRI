/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package evidenciastrudentov;

/**
 *
 * @author kosa11
 */
public class EvidenciaStrudentov {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Skupina skupina = new Skupina("5ZY01A");

        skupina.pridajStudenta(new Student("123456", "Stefan", "Toth"));
        skupina.pridajStudenta(new Student("100001", "Jan", "Mrkvicka"));
        skupina.pridajStudenta(new Student("100001", "Frantisek", "Paprika"));

        System.out.println("Vypis studentov zo skupiny " + skupina.getCislo());
        skupina.vypisStudentov();
        System.out.println("");
        
        skupina.odoberStudenta("123456");
        System.out.println("Vypis po odobrati studenta:");
        skupina.vypisStudentov();
    }
    
}
