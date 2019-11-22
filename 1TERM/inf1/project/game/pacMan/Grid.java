
/**
 * Write a description of class Grid here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
import java.util.Arrays; 
public class Grid
{
    
    private Block[][] grid; //21*21
    private Point[][] pointGrid; //21*21
    //startovaci bod pre hraca
    private int playerBaseX;
    private int playerBaseY;
    
    private static final int BLOCK_SIZE = 33;
    private static final int GAME_SIZE = 21;

    /**
     * Constructor for objects of class Grid
     */
    public Grid(){
        grid = new Block[GAME_SIZE][GAME_SIZE];
        pointGrid = new Point[GAME_SIZE][GAME_SIZE];
    }
     
    public int getBaseX(){
        return playerBaseX;
    }
    
    public int getBaseY(){
        return playerBaseY;
    }
    
    public Block getBlock(int x, int y){
        return grid[x][y];
    }
    
    public void leadDefaulutMap(){
        DefaultMap map = new DefaultMap();
        this.grid = map.getMap();
        this.pointGrid = map.getPoints();
        
        this.playerBaseX = map.getBaseX();
        this.playerBaseY = map.getBaseY();
    }
    
    public void draw(){
        for(int i = 0; i < GAME_SIZE; i++){
            for(int j = 0; j< GAME_SIZE; j++){ 
                grid[i][j].draw();
                pointGrid[i][j].draw();
            }
        }
    }
    


}
