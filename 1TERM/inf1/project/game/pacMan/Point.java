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
    
    private boolean isSuper;

    public Point(int x, int y, int size, String color)
    {
        int newSize = size/3;
        this.square = new Square(x+newSize, y+newSize, newSize, color, false, false);
        this.isSuper = false;
      }
    
    public void setIs(boolean is){
        this.square.setExist(is);
        this.square.setColision(is);
    }
    
    public void setSuper(){
        this.isSuper = true;
        
        int size = square.getSize();
        square.setSize(size * 2);
        
        square.setX(square.getX()-size/2);
        square.setY(square.getY()-size/2);
        
        
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
