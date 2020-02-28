/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import sk.uniza.fri.kosa.wof.prostredie.Miestnost;
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
        Assert.assertNull(this.nemaVychody.getVychodnyVychod());
        Assert.assertNull(this.nemaVychody.getZapadnyVychod());
        Assert.assertNull(this.nemaVychody.getSevernyVychod());
        Assert.assertNull(this.nemaVychody.getJuznyVychod());
    }

    @Test
    public void sever() {
        Assert.assertEquals("sever", this.sever.getPopis());
        Assert.assertSame(this.vychod, this.sever.getVychodnyVychod());
        Assert.assertSame(this.zapad, this.sever.getZapadnyVychod());
        Assert.assertNull(this.sever.getSevernyVychod());
        Assert.assertSame(this.juh, this.sever.getJuznyVychod());
    }

    @Test
    public void juh() {
        Assert.assertEquals("juh", this.juh.getPopis());
        Assert.assertSame(this.vychod, this.juh.getVychodnyVychod());
        Assert.assertSame(this.zapad, this.juh.getZapadnyVychod());
        Assert.assertSame(this.sever, this.juh.getSevernyVychod());
        Assert.assertNull(this.juh.getJuznyVychod());
    }
}
