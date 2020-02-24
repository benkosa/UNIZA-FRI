/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author kosa11
 */
public class Student {
    private String osobneCislo;
    private String meno;
    private String priezvisko;

    public Student(String meno, String priezvisko, String osobneCislo) {
        this.osobneCislo = osobneCislo;
        this.meno = meno;
        this.priezvisko = priezvisko;
    }

    @Override
    public String toString() {
        return "Student{" + "osobneCislo=" + osobneCislo + ", meno=" + meno + ", priezvisko=" + priezvisko + '}';
    }

    public String getOsobneCislo() {
        return osobneCislo;
    }

    public void setOsobneCislo(String osobneCislo) {
        this.osobneCislo = osobneCislo;
    }

    public String getMeno() {
        return meno;
    }

    public void setMeno(String meno) {
        this.meno = meno;
    }

    public String getPriezvisko() {
        return priezvisko;
    }

    public void setPriezvisko(String priezvisko) {
        this.priezvisko = priezvisko;
    }
    
    
}
