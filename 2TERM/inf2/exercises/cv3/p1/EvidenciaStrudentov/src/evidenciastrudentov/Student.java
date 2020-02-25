package evidenciastrudentov;

public class Student {
    
    private final String osobneCislo;
    private final String meno;
    private final String priezvisko;
    private String cisloSkupiny;
    
    public Student(String osobneCislo, String meno, String priezvisko) {
        this.osobneCislo = osobneCislo;
        this.meno = meno;
        this.priezvisko = priezvisko;
    }

    public String getOsobneCislo() {
        return osobneCislo;
    }

    public String getMeno() {
        return meno;
    }

    public String getPriezvisko() {
        return priezvisko;
    }

    public String getCisloSkupiny() {
        return cisloSkupiny;
    }

    public void setCisloSkupiny(String cisloSkupiny) {
        this.cisloSkupiny = cisloSkupiny;
    }

    @Override
    public String toString() {
        return meno + " " + priezvisko + " (" + osobneCislo + "), " + cisloSkupiny;
    }
    
}
