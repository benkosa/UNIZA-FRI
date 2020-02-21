/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author kosa11
 */
public class Cislo {
    private double hodnota;

    //alt + insert na generovanie
    public Cislo(double hodnota) {
        this.hodnota = hodnota;
    }

    public double getHodnota() {
        return hodnota;
    }

    public void setHodnota(double hodnota) {
        this.hodnota = hodnota;
    }

    @Override
    public String toString() {
        return String.format("%.2f", this.hodnota);
    }
    
    public void vypisNasobilku(){
        
        for (int i = 1; i < 11; i++) {
            System.out.println(i + " * " + this.hodnota + " = " + (this.hodnota*i));
            System.out.format("%d + %.2f = %.2f\n\n", i, this.hodnota, this.hodnota*i);
        }
    }
    
    
    
    
    
    
    
}
