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
public class Stolicka implements IPredmet {
    private String nazov;
    private boolean jeOtocena;
    
    public Stolicka() {
        this.nazov = "stolicka";
        this.jeOtocena = false;
    }
    @Override
    public String getNazov() {
        return nazov;
    }
    
    public void otoc() {
        this.jeOtocena = true;
    } 
    
}
