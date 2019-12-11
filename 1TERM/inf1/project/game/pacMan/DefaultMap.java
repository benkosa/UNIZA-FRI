
/**
 * Mapa default.
 *
 * @author Benjamin Kosa
 * @version 2019.12.11
 * UNIZA FRI INFORMATIKA 1
 */
public class DefaultMap
{
    // instance variables - replace the example below with your own
    private Block[][] grid; //21*21
    private Point[][] pointGrid; //21*21
    
    private int playerBaseX;
    private int playerBaseY;
    
    private int[] enemyBaseX;
    private int[] enemyBaseY;
    
    private static final int BLOCK_SIZE = 33;
    private static final int GAME_SIZE = 21;

    /**
     * Constructor for objects of class DefaultMap
     */
    public DefaultMap()
    {
        grid = new Block[GAME_SIZE][GAME_SIZE];
        pointGrid = new Point[GAME_SIZE][GAME_SIZE];
        playerBaseX = BLOCK_SIZE*10;
        playerBaseY = BLOCK_SIZE*15;
        
        enemyBaseX = new int[]{BLOCK_SIZE*9, BLOCK_SIZE*10, BLOCK_SIZE*11, BLOCK_SIZE*10};
        enemyBaseY = new int[]{BLOCK_SIZE*9, BLOCK_SIZE*9, BLOCK_SIZE*9, BLOCK_SIZE*8};
    }
    
    public int[] getEnemyBaseX(){
        return enemyBaseX;
    }
    
    public int[] getEnemyBaseY(){
        return enemyBaseY;
    }
    
    public int getBaseX(){
        return playerBaseX;
    }
    
    public int getBaseY(){
        return playerBaseY;
    }   

    public Point[][] getPoints(){
        int x = 0;
        int y = 0;        
        int[][] map = { 
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0},
            {0,0,1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1,0,0},
            {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
            {0,0,1,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,1,0,0},
            {0,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,0,0},
            {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
            {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
            {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
            {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
            {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
            {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
            {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
            {0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0},
            {0,0,1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1,0,0},
            {0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0},
            {0,0,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,0,0},
            {0,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,0,0},
            {0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,0,0},
            {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
        };        

        for(int i = 0; i < GAME_SIZE; i++){            
            for(int j = 0; j< GAME_SIZE; j++){
                if(map[j][i] == 0)
                    pointGrid[i][j] = new Point(x, y, BLOCK_SIZE, "white");
                else{
                    pointGrid[i][j] = new Point(x, y, BLOCK_SIZE, "white");
                    pointGrid[i][j].setIs(true);
                }
                y+=BLOCK_SIZE;
            }
            x+=BLOCK_SIZE;
            y = 0;
        }
        pointGrid[3][3].setSuper();
        pointGrid[18][3].setSuper();
        
        pointGrid[3][15].setSuper();
        pointGrid[18][15].setSuper();
        
        return pointGrid;
    
    }

    public Block[][] getMap(){
        int x = 0;
        int y = 0;        
        int[][] map = { 
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1},
            {1,0,1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1,0,1},
            {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
            {1,0,1,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,1,0,1},
            {1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,0,1},
            {1,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,1},
            {1,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,1},
            {0,0,0,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,0,0,0},
            {1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1},
            {0,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0},
            {1,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,0,1,1,1,1},
            {1,0,0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,1},
            {1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1},
            {1,0,1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1,0,1},
            {1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1},
            {1,0,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,0,0,1},
            {1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,0,1},
            {1,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,0,1},
            {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}
        };        

        for(int i = 0; i < GAME_SIZE; i++){            
            for(int j = 0; j< GAME_SIZE; j++){
                if(map[j][i] == 0)
                    grid[i][j] = new Block(x, y, BLOCK_SIZE, "blue");
                else{
                    grid[i][j] = new Block(x, y, BLOCK_SIZE, "blue");
                    grid[i][j].changeToBlack();
                }
                y+=BLOCK_SIZE;
            }
            x+=BLOCK_SIZE;
            y = 0;
        }
        return grid;
    }    
}
