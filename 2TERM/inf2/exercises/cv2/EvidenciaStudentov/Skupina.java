
import java.util.ArrayList;

public class Skupina {
    
    private String cislo;
    private ArrayList<Student> zoznamStudentov = new ArrayList<>();

    public Skupina(String cisloSkupiny) {
        this.cislo = cisloSkupiny;
    }
    
    public void pridajStudenta(Student student) {
        if (student != null) {
            if (this.zoznamStudentov.contains(student))
            {
                return;
            }
            
            if (this.dajStudenta(student.getOsobneCislo()) != null) {
                return;                
            }
            
            student.setCisloSkupiny(cislo);
            this.zoznamStudentov.add(student);
        }
    }
    
    public void odoberStudenta(String osobneCislo) {
        for (int i = 0; i < this.zoznamStudentov.size(); i++) {
            if (osobneCislo.equals(this.zoznamStudentov.get(i).getOsobneCislo())) {
                this.zoznamStudentov.remove(i);
                return;
            }
        }
    }
    
    public Student dajStudenta(String osobneCislo) {
        for (Student student : this.zoznamStudentov) {
            if (osobneCislo.equals(student.getOsobneCislo())) {
                return student;                
            }
        }
        
        return null;
    }
    
    public void vypisStudentov() {
        for (Student student : this.zoznamStudentov) {
            System.out.println(student);
        }
    }

    public String getCislo() {
        return this.cislo;
    }
    
    public int dajPocetStudentov() {
        return zoznamStudentov.size();
    }
    
}
