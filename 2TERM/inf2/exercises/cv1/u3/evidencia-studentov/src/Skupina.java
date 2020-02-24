import java.util.*; 
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author kosa11
 */
public class Skupina {
    private String cisloSkupiny;
    ArrayList<Student> studenti;

    public Skupina(String cisloSkupiny) {
        this.cisloSkupiny = cisloSkupiny;
        ArrayList<Student> studenti = new ArrayList<Student>();
    }

    public String getCisloSkupiny() {
        return cisloSkupiny;
    }
    
    public void pridajStudenta(Student student) {
        this.studenti.add(student);
    }
    
    public void odoberStudenta(Student student) {
        if (!studenti.contains(student)) {
            return;
        }
        Iterator<Student> iter = studenti.iterator();
        while (iter.hasNext()) {
            if(iter.next() == student){
                iter.remove();
                return;
            }
        }
    }
    
    public Student dajStudenta(String osobneCislo) {
        for (Student student : studenti) {
            if (student.getOsobneCislo().equals(osobneCislo)) {
                return student;
            }
        }
        return null;
    }
    
    public void vypisStudentov() {
        for (Student student : studenti) {
            student.toString();
        }
    }
}
