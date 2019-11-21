
/**
 * Write a description of class DefaultMap here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class DefaultMap
{
    // instance variables - replace the example below with your own
    private Block[][] grid; //21*21
    private Point[][] pointGrid; //21*21
    
    private int playerBaseX;
    private int playerBaseY;
    
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
    }
    
    public int getBaseX(){
        return playerBaseX+1;
    }
    
    public int getBaseY(){
        return playerBaseY+1;
    }   

    public Point[][] getPoints(){
        int x = 0;
        int y = 0;

        for(int i = 0; i < GAME_SIZE; i++){            
            for(int j = 0; j< GAME_SIZE; j++){                
                pointGrid[i][j]= new Point(x, y, BLOCK_SIZE, "white");
                y+=BLOCK_SIZE;
            }
            x+=BLOCK_SIZE;
            y = 0;
        }

        for(int i = 2; i <= 9; i++){
            pointGrid[i][1].setIs(true);
            pointGrid[i][13].setIs(true);
        }
        for(int i = 11; i <= 18; i++){
            pointGrid[i][1].setIs(true);
            pointGrid[i][13].setIs(true);
        }
        for(int i = 2; i <= 18; i++){
            pointGrid[i][3].setIs(true);
            pointGrid[i][19].setIs(true);
        }
        for(int i = 2; i <= 5; i++){
            pointGrid[i][5].setIs(true);
            pointGrid[i][17].setIs(true);
        }
        for(int i = 7; i <= 9; i++){
            pointGrid[i][5].setIs(true);
            pointGrid[i][17].setIs(true);
        }
        for(int i = 11; i <= 13; i++){
            pointGrid[i][5].setIs(true);
            pointGrid[i][17].setIs(true);
        }
        for(int i = 15; i <= 18; i++){
            pointGrid[i][5].setIs(true);
            pointGrid[i][17].setIs(true);
        }
        //y-os    
        for(int i = 2; i <= 4; i++){
            pointGrid[2][i].setIs(true);
            pointGrid[18][i].setIs(true);
        }
        for(int i = 2; i <= 4; i++){
            pointGrid[2][i].setIs(true);
            pointGrid[18][i].setIs(true);
        }
        for(int i = 5; i <= 15; i++){
            pointGrid[i][15].setIs(true);
        }
        for(int i = 13; i <= 14; i++){
            pointGrid[2][i].setIs(true);
            pointGrid[18][i].setIs(true);
        }
        for(int i = 17; i <= 19; i++){
            pointGrid[2][i].setIs(true);
            pointGrid[18][i].setIs(true);
        }
        for(int i = 2; i <= 16; i++){
            pointGrid[5][i].setIs(true);
            pointGrid[15][i].setIs(true);
        }
        pointGrid[7][4].setIs(true);
        pointGrid[13][4].setIs(true);
        pointGrid[13][4].setIs(true);
        pointGrid[9][2].setIs(true);
        pointGrid[11][2].setIs(true);
        pointGrid[7][16].setIs(true);
        pointGrid[13][16].setIs(true);
        pointGrid[2][15].setIs(true);
        pointGrid[3][15].setIs(true);
        pointGrid[3][16].setIs(true);
        pointGrid[17][15].setIs(true);
        pointGrid[17][16].setIs(true);
        pointGrid[18][15].setIs(true);
        pointGrid[8][15].setIs(true);
        pointGrid[7][16].setIs(true);
        pointGrid[13][16].setIs(true);
        pointGrid[9][18].setIs(true);
        pointGrid[11][18].setIs(true);
        pointGrid[9][14].setIs(true);
        pointGrid[11][14].setIs(true);
        
        return pointGrid;
    }

    public Block[][] getMap(){
        int x = 0;
        int y = 0;

        for(int i = 0; i < GAME_SIZE; i++){            
            for(int j = 0; j< GAME_SIZE; j++){                
                grid[i][j] = new Block(x, y, BLOCK_SIZE, "blue");
                y+=BLOCK_SIZE;
            }
            x+=BLOCK_SIZE;
            y = 0;
        }
        for(int i = 2; i <= 9; i++){
            grid[i][1].changeToBlack();
            grid[i][13].changeToBlack();
        }
        for(int i = 11; i <= 18; i++){
            grid[i][1].changeToBlack();
            grid[i][13].changeToBlack();
        }
        for(int i = 2; i <= 18; i++){
            grid[i][3].changeToBlack();
            grid[i][19].changeToBlack();
        }
        for(int i = 2; i <= 5; i++){
            grid[i][5].changeToBlack();
            grid[i][17].changeToBlack();
        }
        for(int i = 7; i <= 9; i++){
            grid[i][5].changeToBlack();
            grid[i][17].changeToBlack();
        }
        for(int i = 11; i <= 13; i++){
            grid[i][5].changeToBlack();
            grid[i][17].changeToBlack();
        }
        for(int i = 15; i <= 18; i++){
            grid[i][5].changeToBlack();
            grid[i][17].changeToBlack();
        }
        for(int i = 0; i <= 3; i++){
            grid[i][7].changeToBlack();
            grid[i][11].changeToBlack();
        }
        for(int i = 7; i <= 13; i++){
            grid[i][7].changeToBlack();
            grid[i][11].changeToBlack();
        }
        for(int i = 17; i <= 20; i++){
            grid[i][7].changeToBlack();
            grid[i][11].changeToBlack();
        }
        for(int i = 0; i <= 7; i++)
            grid[i][9].changeToBlack();
        for(int i = 9; i <= 11; i++)
            grid[i][9].changeToBlack();
        for(int i = 13; i <= 20; i++)
            grid[i][9].changeToBlack();
        for(int i = 5; i <= 15; i++)
            grid[i][15].changeToBlack();
        //y-os    
        for(int i = 0; i <= 7; i++){
            grid[0][i].changeToBlack();
            grid[20][i].changeToBlack();
        }    
        for(int i = 11; i <= 20; i++){
            grid[0][i].changeToBlack();
            grid[20][i].changeToBlack();
        }
        for(int i = 2; i <= 4; i++){
            grid[2][i].changeToBlack();
            grid[18][i].changeToBlack();
        }
        for(int i = 2; i <= 4; i++){
            grid[2][i].changeToBlack();
            grid[18][i].changeToBlack();
        }
        for(int i = 13; i <= 14; i++){
            grid[2][i].changeToBlack();
            grid[18][i].changeToBlack();
        }
        for(int i = 17; i <= 19; i++){
            grid[2][i].changeToBlack();
            grid[18][i].changeToBlack();
        }
        for(int i = 2; i <= 16; i++){
            grid[5][i].changeToBlack();
            grid[15][i].changeToBlack();
        }
        grid[7][4].changeToBlack();
        grid[13][4].changeToBlack();
        grid[13][4].changeToBlack();
        grid[9][2].changeToBlack();
        grid[11][2].changeToBlack();
        grid[7][12].changeToBlack();
        grid[13][12].changeToBlack();
        grid[9][6].changeToBlack();
        grid[11][6].changeToBlack();
        grid[10][8].changeToBlack();
        for(int i = 7; i <= 13; i++){
            grid[7][i].changeToBlack();
            grid[13][i].changeToBlack();
        }
        grid[7][16].changeToBlack();
        grid[13][16].changeToBlack();
        grid[2][15].changeToBlack();
        grid[3][15].changeToBlack();
        grid[3][16].changeToBlack();
        grid[17][15].changeToBlack();
        grid[17][16].changeToBlack();
        grid[18][15].changeToBlack();
        grid[8][15].changeToBlack();
        grid[7][16].changeToBlack();
        grid[13][16].changeToBlack();
        grid[9][18].changeToBlack();
        grid[11][18].changeToBlack();
        grid[9][14].changeToBlack();
        grid[11][14].changeToBlack();
        return grid;
    }
    
    
}
