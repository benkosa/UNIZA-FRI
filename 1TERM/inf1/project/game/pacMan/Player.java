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
    
    private Grid grid;
    

    public Player(Grid grid, int size) {
        this.square = new Square(grid.getBaseX(), grid.getBaseY(), size, "red", true);
        this.grid = grid;
        setCurrentBlock();
    }
    
    public void draw(){
        this.square.draw();
    }
    
    public String getDirection(){
        return this.direction;
    }
    
    public void setDirection(String direction){
        this.direction =direction;
    }
    
    public Grid getGrid(){
        return this.grid;
    }
     
    public void setCurrentBlock(){
        blockX = square.getBlockX();
        blockY = square.getBlockY();
    }
    
    public int getBlockX(){
        return blockX;
    }
    
    public int getBlockY(){
        return blockY;
    }
    
    public Square getSquare(){
        return this.square;
    }
    
    public void move(){
        this.square.move(this);
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
