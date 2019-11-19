
/**
 * Write a description of class Game here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Game {
    /**
     * Constructor for objects of class Game
     */
    Manazer main;
    Player player;
    public Game() {
        // initialise instance variables
        main = new Manazer();
        player = new Player();
        main.spravujObjekt(player);
    }
}
