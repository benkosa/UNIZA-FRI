import java.awt.Rectangle;

/**
 * Write a description of class Player here.
 * 
 * @author (Benjamin Kosa) 
 */
public class Player {
    private Square square;
    private String direction;
    private String lastDirection;
    //info o tom v ktorom bloku sa hrac nachadza
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
    
    public String getLastDirection(){
        return this.lastDirection;
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
    
    /* najde blok podla suradnic a otestuje koliziu
     */
    public boolean isCollision(int X, int Y){
        Square square2 = this.grid.getBlock(this.blockX+X, this.blockY+Y).getSquare();
        return this.square.squareSquare(square2);
    }
    
    /* kontroluje koliziu s tromi blokmi pred hracom
     */
    public boolean moveTo(String direction){
        if(direction.equals("up")){
            this.square.increaseY();
            if(this.isCollision(0, 1) || this.isCollision(1, 1) || this.isCollision(-1, 1)){            
                this.square.decreaseY();
                return false;
            }
            return true;
        }
        if(direction.equals("do")){
            this.square.decreaseY();
            if(this.isCollision(0, -1) || this.isCollision(1, -1) || this.isCollision(-1, -1)){
                this.square.increaseY();
                return false;
            }
            return true;
        }
        if(direction.equals("ri")){
            this.square.decreaseX();
            if(this.isCollision(-1, 0) || this.isCollision(-1, 1) || this.isCollision(-1, -1)){
                this.square.increaseX();
                return false;
            }
            return true;
        }
        if(direction.equals("le")){
            this.square.increaseX();
            if(this.isCollision(1, 0) || this.isCollision(1, 1) || this.isCollision(1, -1)){
                this.square.decreaseX();
                return false;
            }
            return true;
        }
        return true;
    }
    
    /* vykona pohyb a ak nastala kolizia tak pokracuje 
     * v predoslom pohybe
     */    
    public void move(){        
        this.setCurrentBlock();        
        if(this.moveTo(this.getDirection()) == false)
            this.moveTo(this.getLastDirection());
            
        draw();
    }
    
    public void moveUp(){
        this.lastDirection = this.direction;
        this.direction = "up";
    }
    
    public void moveDown(){
        this.lastDirection = this.direction;
        this.direction = "do";
    }
    
    public void moveRight(){
        this.lastDirection = this.direction;
        this.direction = "le";
    }
    
    public void moveLeft(){
        this.lastDirection = this.direction;
        this.direction = "ri";
    } 
    

}
