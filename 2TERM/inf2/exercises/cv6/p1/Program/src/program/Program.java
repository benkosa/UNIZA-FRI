/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package program;

/**
 *
 * @author kosa11
 */
public class Program {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        ZoznamPredmetov zoznam = new ZoznamPredmetov();
        
        zoznam.pridajPredmet(new Stol());
        zoznam.pridajPredmet(new Stolicka(), false);
        zoznam.pridajPredmet(new Stolicka(), false);
        zoznam.pridajPredmet(new Stolicka(), false);
        zoznam.pridajPredmet(new VseobecnyPredmet(), "projektor");
    }
    
}
