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
public class MiestnostTest {

    private Miestnost nemaVychody;
    private Miestnost zapad;
    private Miestnost vychod;
    private Miestnost sever;
    private Miestnost juh;

    @Before
    public void setUp() {
        this.nemaVychody = new Miestnost("nema vychody");
        this.nemaVychody.nastavVychody(null, null, null, null);
        this.zapad = new Miestnost("zapad");
        this.vychod = new Miestnost("vychod");
        this.sever = new Miestnost("sever");
        this.juh = new Miestnost("juh");
        this.zapad.nastavVychody(this.sever, this.vychod, this.juh, null);
        this.vychod.nastavVychody(this.sever, null, this.juh, this.zapad);
        this.sever.nastavVychody(null, this.vychod, this.juh, this.zapad);
        this.juh.nastavVychody(this.sever, this.vychod, null, this.zapad);
    }

    @Test
    public void nemaVychody() {
        Assert.assertEquals("nema vychody", this.nemaVychody.getPopis());
        Assert.assertNull(this.nemaVychody.getVychod("vychod"));
        Assert.assertNull(this.nemaVychody.getVychod("zapad"));
        Assert.assertNull(this.nemaVychody.getVychod("sever"));
        Assert.assertNull(this.nemaVychody.getVychod("juh"));
    }

    @Test
    public void sever() {
        Assert.assertEquals("sever", this.sever.getPopis());
        Assert.assertSame(this.vychod, this.sever.getVychod("vychod"));
        Assert.assertSame(this.zapad, this.sever.getVychod("zapad"));
        Assert.assertNull(this.sever.getVychod("sever"));
        Assert.assertSame(this.juh, this.sever.getVychod("juh"));
    }

    @Test
    public void juh() {
        Assert.assertEquals("juh", this.juh.getPopis());
        Assert.assertSame(this.vychod, this.juh.getVychod("vychod"));
        Assert.assertSame(this.zapad, this.juh.getVychod("zapad"));
        Assert.assertSame(this.sever, this.juh.getVychod("sever"));
        Assert.assertNull(this.juh.getVychod("juh"));
    }

    @Test
    public void getPopisVychodov() {
        Assert.assertEquals("Vychody:", this.nemaVychody.getPopisVychodov());
        Assert.assertEquals("Vychody: sever vychod zapad", this.juh.getPopisVychodov());
        Assert.assertEquals("Vychody: sever vychod juh", this.zapad.getPopisVychodov());
    }
}
