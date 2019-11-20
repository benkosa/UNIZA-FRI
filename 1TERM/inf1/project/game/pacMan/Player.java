import java.awt.Rectangle;

/**
 * Write a description of class Player here.
 * 
 * @author (Benjamin Kosa) 
 */
public class Player {
    private Square square;
    private String direction;
    private int blockX;
    private int blockY;
    

    public Player(int x, int y, int size) {
        this.square = new Square(x, y, size, "red", true);
    }
    
    public void draw(){
        this.square.draw();
    }
    
    public String getDirection(){
        return this.direction;
    }
    
    public void getCurrentBlock(){
        blockX = square.getBlockX();
        blockY = square.getBlockY();
    }
    
    public void move(){
        this.square.move(this);
        this.getCurrentBlock();
    }
    
    public void moveUp(){
        this.direction = "up";
    }
    
    public void moveDown(){
        this.direction = "do";
    }
    
    public void moveRight(){
        this.direction = "le";
    }
    
    public void moveLeft(){
        this.direction = "ri";
    } 
    

}
