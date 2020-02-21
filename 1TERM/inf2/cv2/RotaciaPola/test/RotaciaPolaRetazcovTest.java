
import org.junit.Assert;
import org.junit.Test;


public class RotaciaPolaRetazcovTest {
    
    @Test
    public void testSetPoleRetazcovNull() {
        RotaciaPolaRetazcov rotacia = new RotaciaPolaRetazcov();
        
        String[] expected = null;
        rotacia.setPoleRetazcov(expected);
        String[] actual = rotacia.getPoleRetazcov();
        
        Assert.assertArrayEquals(expected, actual);
        
    }
    
    @Test
    public void testPosunVpravoHranice() {
        String[] pole = new String[] { "1", "2", "3", "4", "5" };
        
        RotaciaPolaRetazcov rotacia = new RotaciaPolaRetazcov();
        rotacia.setPoleRetazcov(pole);
        
        rotacia.posunVpravo();
        
        String[] zrotovanePole = rotacia.getPoleRetazcov();
        Assert.assertEquals(pole[0], zrotovanePole[1]);
        Assert.assertEquals(pole[pole.length-1], zrotovanePole[0]);
    }
    
    @Test
    public void testPosunVpravoAkoJeVelkePole() {
        String[] pole = new String[] { "1", "2", "3", "4", "5" };
        
        RotaciaPolaRetazcov rotacia = new RotaciaPolaRetazcov();
        rotacia.setPoleRetazcov(pole);    
        
        // Ked zrotujeme pole o rovnaky pocet prvkov ako ma pole (length), 
        // mali by sme dostat pole s rovnakymi hodnotami 
        rotacia.posunVpravo(pole.length);
        
        String[] zrotovanePole = rotacia.getPoleRetazcov();
        Assert.assertArrayEquals(pole, zrotovanePole);
    }
    
    @Test(timeout = 50)
    public void testPosunVpravoMaxCas() {
        String[] pole = new String[] { "1", "2", "3", "4", "5" };
        
        RotaciaPolaRetazcov rotacia = new RotaciaPolaRetazcov();
        rotacia.setPoleRetazcov(pole);

        // Operacia posunu by mala byt rychla a trvat iba niekolko milisekund
        // aj ked zvolime velke cislo na rotaciu
        rotacia.posunVpravo(pole.length * 10000000);
        
        String[] zrotovanePole = rotacia.getPoleRetazcov();
        Assert.assertArrayEquals(pole, zrotovanePole);
    }
    
}
