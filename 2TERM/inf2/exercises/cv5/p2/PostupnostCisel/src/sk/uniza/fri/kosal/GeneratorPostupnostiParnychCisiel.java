/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sk.uniza.fri.kosal;

/**
 *
 * @author kosa11
 */
class GeneratorPostupnostiParnychCisiel implements iGenerator {
    private int cislo;

    public GeneratorPostupnostiParnychCisiel() {
        this.cislo = -2;
    }
    
    @Override
    public int getNasledujuceCislo() {
        return this.cislo+=2;
    }
    
    @Override
    public void reset() {
        this.cislo = -2;
    }
}
