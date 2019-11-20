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

    public static int STEP = 3;

    /**
     * Vytvor nový obdĺžnik preddefinovanej farby na preddefinovanej pozícii.
     */
    public Square(int x, int y, int size, String color, boolean exist) {
        this.size = size;
        this.x = x;
        this.y = y;
        this.color = color;
        this.exist = exist;
        this.isColision = true;
    }

    public int getBlockX(){
        return (this.x + this.size/2) / BLOCK_SIZE;
    }

    public int getBlockY(){
        return (this.y + this.size/2) / BLOCK_SIZE;
    }
    
    public boolean getColision(){
        return this.isColision;
    }

    private boolean colison(Square square){       
        
        if(square.isColision == false)
            return false;

        return (square.x <= this.x + this.size
             && square.x + square.size >= this.x
             && square.y <= this.y + this.size
             && square.y + square.size >= this.y);
    }  

    public void move(Player player){
        player.setCurrentBlock();
        if(player.getDirection().equals("up")){
            Square squareColision0 = player.getGrid().getBlock(player.getBlockX(), player.getBlockY()+1).getSquare();
            Square squareColision1 = player.getGrid().getBlock(player.getBlockX()+1, player.getBlockY()+1).getSquare();
            Square squareColision2 = player.getGrid().getBlock(player.getBlockX()-1, player.getBlockY()+1).getSquare();
            if(player.getSquare().colison(squareColision0) == false
            && player.getSquare().colison(squareColision1) == false
            && player.getSquare().colison(squareColision2) == false)            
                y+=STEP;            
            draw();
            return;
        }
        if(player.getDirection().equals("do")){
            Square squareColision0 = player.getGrid().getBlock(player.getBlockX(), player.getBlockY()-1).getSquare();
            Square squareColision1 = player.getGrid().getBlock(player.getBlockX()+1, player.getBlockY()-1).getSquare();
            Square squareColision2 = player.getGrid().getBlock(player.getBlockX()-1, player.getBlockY()-1).getSquare();
            if(player.getSquare().colison(squareColision0) == false
            && player.getSquare().colison(squareColision1) == false
            && player.getSquare().colison(squareColision2) == false)
                y-=STEP;
            draw();
            return;
        }
        if(player.getDirection().equals("ri")){
            Square squareColision0 = player.getGrid().getBlock(player.getBlockX()-1, player.getBlockY()).getSquare();
            Square squareColision1 = player.getGrid().getBlock(player.getBlockX()-1, player.getBlockY()+1).getSquare();
            Square squareColision2 = player.getGrid().getBlock(player.getBlockX()-1, player.getBlockY()-1).getSquare();
            if(player.getSquare().colison(squareColision0) == false
            && player.getSquare().colison(squareColision1) == false
            && player.getSquare().colison(squareColision2) == false)
                x-=STEP;
            draw();
            return;
        }
        if(player.getDirection().equals("le")){
            Square squareColision0 = player.getGrid().getBlock(player.getBlockX()+1, player.getBlockY()).getSquare();
            Square squareColision1 = player.getGrid().getBlock(player.getBlockX()+1, player.getBlockY()+1).getSquare();
            Square squareColision2 = player.getGrid().getBlock(player.getBlockX()+1, player.getBlockY()-1).getSquare();
            if(player.getSquare().colison(squareColision0) == false
            && player.getSquare().colison(squareColision1) == false
            && player.getSquare().colison(squareColision2) == false)
                x+=STEP;
            draw();
            return;
        }    
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
