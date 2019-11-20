import java.awt.Rectangle;

/**
 * Obdĺžnik, s ktorým možno pohybovať a nakreslí sa na plátno.
 * 
 * @author  Michael Kolling and David J. Barnes
 * @version 1.0  (15 July 2000)
 */

public class Square {
    private int size;
    private int x;
    private int y;
    private String color;
    private boolean exist;
    private boolean isColision;

    public static int STEP = 3;

    /**
     * Vytvor nový obdĺžnik preddefinovanej farby na preddefinovanej pozícii.
     */
    public Square(int x, int y, int size, String color, boolean exist) {
        this.size = size;
        this.x = x;
        this.y = y;
        this.color = color;
        this.exist = exist;
        this.isColision = true;
    }

    public int getBlockX(){
        return this.x / this.size;
    }

    public int getBlockY(){
        return this.y / this.size;
    }

    private boolean colison(Square square){
        return (square.x < this.x + this.size &&
        square.x + square.size > this.x &&
        square.y < this.y + this.size &&
        square.y + square.size > this.y);
    }

    
    public void move(Player player){
        if(player.getDirection().equals("up")){
            y+=STEP;
            draw();
            return;
        }
        if(player.getDirection().equals("do")){
            y-=STEP;
            draw();
            return;
        }
        if(player.getDirection().equals("ri")){
            x-=STEP;
            draw();
            return;
        }
        if(player.getDirection().equals("le")){
            x+=STEP;
            draw();
            return;
        }    
    }

    public void setColor(String color){
        this.color = color;
    }

    public void setExist(boolean exist){
        this.exist = exist;
    }

    public void setColision(boolean colision){
        this.isColision = colision;
    }

    /*
     * Draw the square with current specifications on screen.
     */
    public void draw() {
        if (this.exist) {
            Platno canvas = Platno.dajPlatno();
            canvas.draw(this, this.color,
                new Rectangle(this.x, this.y, this.size, this.size));
        }
    }

    /*
     * Erase the square on screen.
     */
    public void erase() {
        if (this.exist) {
            Platno canvas = Platno.dajPlatno();
            canvas.erase(this);
        }
    }
}
