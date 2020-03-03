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
class GeneratorPostupnostiParnychCisiel {
    private int cislo;
    private int cisloMocnina;

    public GeneratorPostupnostiParnychCisiel() {
        this.cislo = -2;
        this.cisloMocnina = 1;
    }
    
    public int getNasledujuceCislo() {
        return this.cislo+=2;
    }
    
    public int getNasledujuceCisloMocnina() {
        int cislo = this.cisloMocnina;
        this.cisloMocnina*=2;
        return cislo;
    }

    public void reset() {
        this.cislo = -2;
        this.cisloMocnina = 1;
    }
    
}
