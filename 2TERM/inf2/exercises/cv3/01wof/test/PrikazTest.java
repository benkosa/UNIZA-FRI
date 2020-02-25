/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import org.junit.Before;
import org.junit.Test;
import org.junit.Assert;

/**
 *
 * @author janik
 */
public class PrikazTest {

    private Prikaz chodJuh;
    private Prikaz ukonciNull;
    private Prikaz nullSever;

    @Before
    public void setUp() {
        this.chodJuh = new Prikaz("chod", "juh");
        this.ukonciNull = new Prikaz("ukonci", null);
        this.nullSever = new Prikaz(null, "sever");
    }

    @Test
    public void getNazov() {
        Assert.assertEquals("chod", this.chodJuh.getNazov());
        Assert.assertNull(this.nullSever.getNazov());
        Assert.assertEquals("ukonci", this.ukonciNull.getNazov());
    }

    @Test
    public void getParameter() {
        Assert.assertEquals("juh", this.chodJuh.getParameter());
        Assert.assertEquals("sever", this.nullSever.getParameter());
        Assert.assertNull(this.ukonciNull.getParameter());
    }

    @Test
    public void jeNeznamy() {
        Assert.assertFalse(this.chodJuh.jeNeznamy());
        Assert.assertTrue(this.nullSever.jeNeznamy());
        Assert.assertFalse(this.ukonciNull.jeNeznamy());
    }

    @Test
    public void maParameter() {
        Assert.assertTrue(this.chodJuh.maParameter());
        Assert.assertTrue(this.nullSever.maParameter());
        Assert.assertFalse(this.ukonciNull.maParameter());
    }
}
