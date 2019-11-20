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
        isAir = false;        
        this.square.setColor("black");
        this.square.setColision(false);
    }
    
    public Square getSquare() {
        return this.square;
    }
    
    public void draw() {
        this.square.draw();
    }

}
