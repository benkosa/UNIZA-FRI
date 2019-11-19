import java.awt.Rectangle;

/**
 * Write a description of class Player here.
 * 
 * @author (Benjamin Kosa) 
 */
public class Player {
    private int x;
    private int y;
    private int size;
    private String color;
    
    private int step = 3;

    public Player() {
        x = 100;
        y = 100;
        size = 30;
        color = "red";
    }
    
    private void move(String direction){
        if(direction.equals("up")){
            x-=step;
            return;
        }
        if(direction.equals("do")){
            x+=step;
            return;
        }
        if(direction.equals("ri")){
            y+=step;
            return;
        }
        if(direction.equals("le")){
            y-=step;
            return;
        }    
    }

    /*
     * Draw the square with current specifications on screen.
     */
    private void drawP() {
        Platno canvas = Platno.dajPlatno();
        canvas.draw(this, this.color,
            new Rectangle(this.x, this.y, this.size, this.size));
        canvas.wait(10);

    }

    /*
     * Erase the square on screen.
     */
    private void eraseP() {
        Platno canvas = Platno.dajPlatno();
        canvas.erase(this);

    }
}
