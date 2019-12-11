import java.awt.Rectangle;

/**
 * grid sa sklada s Bloko-ov
 * @author Benjamin Kosa
 * @version 2019.12.11
 * UNIZA FRI INFORMATIKA 1
 */
public class Block
{
    // instance variables - replace the example below with your own
    private Square square;
    private boolean isAir;

    
    public Block(int x, int y, int size, String color){
        this.square = new Square(x, y, size, color, true, true);
        this.isAir = true;
    }

    public void changeToBlack(){
        this.isAir = false;        
        this.square.setColor("black");
        this.square.setColision(false);
    }
    
    public boolean getIsAir() {
        return this.isAir;
    }
    
    public Square getSquare() {
        return this.square;
    }
    
    public void draw() {
        this.square.draw();
    }

}
