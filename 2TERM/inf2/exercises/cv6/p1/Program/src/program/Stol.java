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
public class Stol implements IPredmet {
    private String nazov;
    
    public Stol() {
        this.nazov = "stol";
    }
    
    @Override
    public String getNazov() {
        return nazov;
    }
    
    
    
}
