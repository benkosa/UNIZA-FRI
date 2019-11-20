import java.util.ArrayList;

/**
 * Write a description of class Game here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Game {
    public static final int BLOCK_SIZE = 33;
    /**
     * Constructor for objects of class Game
     */
    private Manazer main;
    private Player player;
    private String direction;
    private Grid grid;
    public Game() {
        // initialise instance variables 
         
        grid = new Grid();
        grid.leadDefaulutMap();        
        player = new Player(grid, BLOCK_SIZE-9);  
        
        main = new Manazer();
        main.spravujObjekt(player);        
        main.spravujObjekt(this);
        grid.draw();
        player.draw();
    }
    
    public void tik() {
        player.move();
    }
    
    public void end() {
        main.prestanSpravovatObjekt(player);
        main.prestanSpravovatObjekt(this);
    }
}
