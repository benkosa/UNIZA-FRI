import java.awt.Rectangle;

/**
 * Write a description of class Player here.
 * 
 * @author (Benjamin Kosa) 
 */
public class Player {
    private Square square;
    private String direction;   
    

    public Player(int x, int y, int size) {
        this.square = new Square(x, y, size, "red", true);
    }
    
    public void draw(){
        this.square.draw();
    }
    
    public void move(){
        this.square.move(this.direction);
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
