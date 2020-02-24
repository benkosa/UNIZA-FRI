import java.util.Scanner; 
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
    //ctrl + prejst na premennu ma hodi na deklaraciu
    public static void main(String[] args) {
        // TODO code application logic here
        Cislo cislo = new Cislo(123);
        System.out.println(cislo);
        
        cislo.setHodnota(3.14);
        System.out.println(cislo);
        
        Scanner in = new Scanner(System.in); 
        System.out.print("Zadaj cislo: ");
        cislo.setHodnota(in.nextDouble());
        System.out.println(cislo);
        
        cislo.vypisNasobilku();
    
        
    }
    
}
