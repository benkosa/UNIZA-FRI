import java.awt.Rectangle;

/**
 * Write a description of class Block here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Block
{
    // instance variables - replace the example below with your own
    private Square square;
    private boolean isAir;

    
    public Block(int x, int y, int size, String color){
        this.square = new Square(x, y, size, color, true);
    }

    public void changeToBlack(){
        isAir = true;
        this.square.setColor("black");
    }
    
    public void draw() {
        this.square.draw();
    }

}
