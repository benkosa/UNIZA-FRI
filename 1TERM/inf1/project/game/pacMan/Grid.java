
/**
 * nasklada mapu na grid
 * @author Benjamin Kosa
 * @version 2019.12.11
 * UNIZA FRI INFORMATIKA 1
 */
import java.util.Arrays; 
public class Grid
{
    
    private Block[][] grid; //21*21
    private Point[][] pointGrid; //21*21
    //startovaci bod pre hraca
    private int playerBaseX;
    private int playerBaseY;
    
    private int[] enemyBaseX;
    private int[] enemyBaseY;
    
    private static final int BLOCK_SIZE = 33;
    private static final int GAME_SIZE = 21;

    /**
     * Constructor for objects of class Grid
     */
    public Grid(){
        grid = new Block[GAME_SIZE][GAME_SIZE];
        pointGrid = new Point[GAME_SIZE][GAME_SIZE];
    }
    
    public Block[][] getMap(){
        return grid;
    }
    
    public int getEnemyBaseX(int id){
        return enemyBaseX[id];
    }
    
    public int getEnemyBaseY(int id){
        return enemyBaseY[id];
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
    
    public Point getPoint(int x, int y){
        return pointGrid[x][y];
    }
    
    public void leadDefaulutMap(){
        DefaultMap map = new DefaultMap();
        this.grid = map.getMap();
        this.pointGrid = map.getPoints();
        
        this.playerBaseX = map.getBaseX();
        this.playerBaseY = map.getBaseY();
        
        this.enemyBaseX = map.getEnemyBaseX();
        this.enemyBaseY = map.getEnemyBaseY();
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
