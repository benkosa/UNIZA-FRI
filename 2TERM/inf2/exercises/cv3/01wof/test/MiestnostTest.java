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
        Assert.assertNull(this.nemaVychody.vychodnyVychod);
        Assert.assertNull(this.nemaVychody.zapadnyVychod);
        Assert.assertNull(this.nemaVychody.severnyVychod);
        Assert.assertNull(this.nemaVychody.juznyVychod);
    }

    @Test
    public void sever() {
        Assert.assertEquals("sever", this.sever.getPopis());
        Assert.assertSame(this.vychod, this.sever.vychodnyVychod);
        Assert.assertSame(this.zapad, this.sever.zapadnyVychod);
        Assert.assertNull(this.sever.severnyVychod);
        Assert.assertSame(this.juh, this.sever.juznyVychod);
    }

    @Test
    public void juh() {
        Assert.assertEquals("juh", this.juh.getPopis());
        Assert.assertSame(this.vychod, this.juh.vychodnyVychod);
        Assert.assertSame(this.zapad, this.juh.zapadnyVychod);
        Assert.assertSame(this.sever, this.juh.severnyVychod);
        Assert.assertNull(this.juh.juznyVychod);
    }
}
