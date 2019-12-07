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

    private int score;
    private int points;
    private int life;

    private Grid grid;

    public Player(Grid grid, int size) {
        this.square = new Square(grid.getBaseX(), grid.getBaseY(), size, "yellow", true, true);
        this.grid = grid;
        this.score = 0;
        this.points = 0;
        this.life = 3; 
        setCurrentBlock();
    }
    
    public Player(Grid grid, int size, int score) {
        this.square = new Square(grid.getBaseX(), grid.getBaseY(), size, "yellow", true, true);
        this.grid = grid;
        this.score = score;
        this.points = 0;
        this.life = 3; 
        setCurrentBlock();
    }

    public void draw(){
        this.square.draw();
    }
    
    public void erase(){
        this.square.erase();
    }
    
    public int takeLife(){
        return --this.life;
    }

    public String getDirection(){
        return this.direction;
    }

    public String getLastDirection(){
        return this.lastDirection;
    }

    public void setDirection(String direction){
        this.direction = direction;
    }

    public Grid getGrid(){
        return this.grid;
    }
    
    public void setBase(){
        this.square.setX(grid.getBaseX());
        this.square.setY(grid.getBaseY());
    }
    
    /**
     * zistuje v ktrom bloku sa hrac nachadza
     * a riesi migrovanie cex x os
     */
    public void setCurrentBlock(){            
        blockX = square.getBlockX();
        blockY = square.getBlockY();

        if(blockX < 1)
            this.square.migrateXUP();
        if(blockX > 19)
            this.square.migrateXDOWN();
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

    public Point pickPoint(){
        Point point = this.isPoint();
        if(point != null){
            this.score+=200;
            this.points++;
            point.erase();
            System.out.println("Score: " + this.score + " points: " + points);
            return point;
        }
        return point;
    }
    
    public int getPoints(){
        return this.points;
    }
    
    public int getScore(){
        return this.score;
    }
    
    public void increaseScore(int score){
        this.score += score;
    }

    /** 
     * najde point podla suradnic a otestuje koliziu
     * s hracom
     */ 
    public Point isPoint(){
        Square square2 = this.grid.getPoint(this.blockX, this.blockY).getSquare();
        if(this.square.squareSquare(square2)){
            return this.grid.getPoint(this.blockX, this.blockY);
        }
        return null;
    }

    /**
     * najde blok podla suradnic a otestuje koliziu
     */
    public boolean isCollision(int X, int Y){
        Square square2 = this.grid.getBlock(this.blockX+X, this.blockY+Y).getSquare();
        return this.square.squareSquare(square2);
    }

    /**
     * kontroluje koliziu s tromi blokmi pred hracom
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

    /**
     * vykona pohyb a ak nastala kolizia tak pokracuje 
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
