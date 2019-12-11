import java.awt.Rectangle;

/**
 * @author Benjamin Kosa
 * @version 2019.12.11
 * UNIZA FRI INFORMATIKA 1
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
    
    /**
     * nastavi ze bod exzistuje
     */
    public void setIs(boolean is){
        this.square.setExist(is);
        this.square.setColision(is);
    }
    
    /**
     * nastavi specialny bod ktory spusta mod
     * na zabytie nepriatela
     */
    public void setSuper(){
        this.isSuper = true;

        int size = square.getSize();
        square.setSize(size * 2);

        square.setX(square.getX()-size/2);
        square.setY(square.getY()-size/2);

    }
    
    public boolean isSuper(){
        return this.isSuper;
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
