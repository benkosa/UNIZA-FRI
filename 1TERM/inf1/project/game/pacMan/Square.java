import java.awt.Rectangle;

/**
 * Obdĺžnik, s ktorým možno pohybovať a nakreslí sa na plátno.
 * 
 * @author  Michael Kolling and David J. Barnes
 * @version 1.0  (15 July 2000)
 */

public class Square {
    private int size;
    private int x;
    private int y;
    private String color;
    private boolean exist;
    private boolean isColision;
    

    private static final int BLOCK_SIZE = 33;
    private static final int GAME_SIZE = 21;

    public static int STEP = 3;

    /**
     * Vytvor nový obdĺžnik preddefinovanej farby na preddefinovanej pozícii.
     */
    public Square(int x, int y, int size, String color, boolean exist, boolean isColision) {
        this.size = size;
        this.x = x;
        this.y = y;
        this.color = color;
        this.exist = exist;
        this.isColision = isColision;
    }
    
    /*
     * kontroluje v ktorom bloku sa nachadza stred hraca
    **/
    public int getBlockX(){
        return (this.x + this.size/2) / BLOCK_SIZE;
    }

    public int getBlockY(){
        return (this.y + this.size/2) / BLOCK_SIZE;
    }

    public boolean getColision(){
        return this.isColision;
    }
    
    public int getSize(){
        return this.size;
    }
    
    public int getX(){
        return this.x;
    }
    
    public int getY(){
        return this.y;
    }
    
    public String getColor(){
        return this.color;
    }


    public boolean squareSquare(Square square){       
        //ak najde blok s ktorym sa nerobi kolizia        
        if(square.isColision == false)
            return false;
        //vrati true ak naslo koliziu
        return (square.x < this.x + this.size
            && square.y < this.y + this.size
            && square.x + square.size > this.x
            && square.y + square.size > this.y);
    }    
    
    
    public void setColor(String color){
        this.color = color;
    }

    public void setExist(boolean exist){
        this.exist = exist;
    }

    public void setColision(boolean colision){
        this.isColision = colision;
    }
    
    public void setX(int x){
        this.x = x;
    }
    
    public void setY(int y){
        this.y = y;
    }
    
    public void setSize(int size){
        this.size = size;
    }
    
    public void migrateXUP(){
            x = BLOCK_SIZE * (GAME_SIZE-2);
    }
    public void migrateXDOWN(){
            x = BLOCK_SIZE;
    }
    
    public void increaseX (){
        this.x+=STEP;
    }
    
    public void decreaseX (){
        this.x-=STEP;
    }
    
    public void increaseY(){
        this.y+=STEP;
    }
    
    public void decreaseY (){
        this.y-=STEP;
    }

    /*
     * Draw the square with current specifications on screen.
     */
    public void draw() {
        if (this.exist) {
            Platno canvas = Platno.dajPlatno();
            canvas.draw(this, this.color,
                new Rectangle(this.x, this.y, this.size, this.size));
        }
    }

    /*
     * Erase the square on screen.
     */
    public void erase() {
        if (this.exist) {
            Platno canvas = Platno.dajPlatno();
            canvas.erase(this);
        }
    }
}
