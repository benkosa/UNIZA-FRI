import java.awt.Rectangle;

/**
 * Write a description of class Point here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Point
{
    private Square square;    

    public Point(int x, int y, int size, String color)
    {
        int newSize = size/3;
        this.square = new Square(x+newSize, y+newSize, newSize, color, false, false);
      }
    
    public void setIs(boolean is){
        this.square.setExist(is);
        this.square.setColision(is);
    }
    
    public Square getSquare() {
        return this.square;
    }

    public void draw() {
        this.square.draw();
    }
    
    public void erase() {
        this.square.erase();
        this.square.setExist(false);
        this.square.setColision(false);
    }
}
