/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package evidenciastrudentov;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Assert;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author kosa11
 */
public class SkupinaTest {
    
    private Skupina skupina;
    
    public SkupinaTest() {
    }
    
    @BeforeClass
    public static void setUpClass() {
    }
    
    @AfterClass
    public static void tearDownClass() {
    }
    
    @Before
    public void setUp() {
        skupina = new Skupina("5ZY01A");
    }
    
    @After
    public void tearDown() {
    }
    
    @Test
    public void testPridajStudenta () {
        Student student = new Student("123", "j", "t");
        skupina.pridajStudenta(student);
        
        Assert.assertEquals(1, skupina.dajPocetStudentov());
        
        Student studentVrateny = skupina.dajStudenta("123");
        
        Assert.assertSame(student, studentVrateny);
    }
    
    @Test
    public void testPridanieTohoIstehoStudetaViacKrat() {
        
        Student student = new Student("123", "j", "t");
        for (int i = 0; i < 10; i++) {
            skupina.pridajStudenta(student); 
        }
        
        Assert.assertEquals(1, skupina.dajPocetStudentov());
        
    }
    
    @Test
    public void testPridajStudentaNull() {
        
        skupina.pridajStudenta(null);
        
        Assert.assertEquals(0, skupina.dajPocetStudentov());
        
    }
    
    @Test
    public void testPridajStudentaSrovnakymCislom() {
        Student student = new Student("123", "j", "t");
        skupina.pridajStudenta(student);
        
        Student student2 = new Student("123", "je", "tu");
        skupina.pridajStudenta(student2); 
        

        
        Assert.assertEquals(1, skupina.dajPocetStudentov());
        
    }
    
    @Test
    public void testOdoberExistujucehoStudenta() {
        Student student = new Student("123", "j", "t");
        skupina.pridajStudenta(student);
        
        skupina.odoberStudenta("123");
        
        Assert.assertEquals(0, skupina.dajPocetStudentov()); 
    }
    
    @Test
    public void testOdoberNeexistujucehoStudenta() {
        Student student = new Student("123", "j", "t");
        skupina.pridajStudenta(student);
        
        skupina.odoberStudenta("1234");
        
        Assert.assertEquals(1, skupina.dajPocetStudentov()); 
    }
    
    @Test
    public void testVlastnostiSkupiny() {
        Skupina skupina = new Skupina("123");
       
        Assert.assertEquals(0, skupina.dajPocetStudentov()); 
        Assert.assertEquals("123", skupina.getCislo());
    }
    
    @Test
    public void testVlastnostiStudenta() {
        Student student = new Student("123", "j", "t");
        
        Assert.assertEquals("123", student.getOsobneCislo());
        Assert.assertEquals("j", student.getMeno());
        Assert.assertEquals("t", student.getPriezvisko());
        Assert.assertNull(student.getCisloSkupiny());
        
        skupina.pridajStudenta(student);
        Assert.assertEquals(skupina.getCislo(), student.getCisloSkupiny());
    }
    
}
