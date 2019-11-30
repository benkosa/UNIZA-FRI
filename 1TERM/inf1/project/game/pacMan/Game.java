import java.util.ArrayList;

/**
 * Write a description of class Game here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Game {
    public static final int BLOCK_SIZE = 33;
    private Manazer main;
    private Player player;
    private Enemy[] enemyes;
    private String direction;
    private Grid grid;
    private Timer timer;
    public Game() {
        // initialise instance variables 

        grid = new Grid();
        grid.leadDefaulutMap();        
        player = new Player(grid, BLOCK_SIZE);
        timer = new Timer();        

        main = new Manazer();

        main.spravujObjekt(player);        
        main.spravujObjekt(this);
        main.spravujObjekt(timer);
        grid.draw();
        player.draw();

        enemyes = new Enemy[4];
        enemyes[0] = new Enemy(grid, BLOCK_SIZE, 0, "magenta", player);
        enemyes[1] = new Enemy(grid, BLOCK_SIZE, 1, "green", player);
        enemyes[2] = new Enemy(grid, BLOCK_SIZE, 2, "red", player);
        enemyes[3] = new Enemy(grid, BLOCK_SIZE, 3, "white", player);

        for (int i = 0; i < 4; i++)
            enemyes[i].draw();
    }

    public void tik() {   
        player.move();
        player.pickPoint();
        for (int i = 0; i < 4; i++){            
            enemyes[i].move();
            playerEnemyColision(player.getSquare(), enemyes[i].getSquare());
        } 
    }
    
    public void playerEnemyColision(Square pSquare, Square eSquare){
        if(pSquare.squareSquare(eSquare)){
            System.out.println("nastala kolizia p e");
            this.player.takeLife();
            this.end();
            this.start();
        }
    }
    public void start() {
        Platno canvas = Platno.dajPlatno();
        canvas.erase();
        
        //grid = new Grid();
        //grid.leadDefaulutMap();        
        player = new Player(grid, BLOCK_SIZE);
        timer = new Timer();         

        main = new Manazer();

        main.spravujObjekt(player);        
        main.spravujObjekt(this);
        main.spravujObjekt(timer);
        //grid.draw();
        player.moveUp();
        player.moveUp();
        player.draw();

        enemyes = new Enemy[4];
        enemyes[0] = new Enemy(grid, BLOCK_SIZE, 0, "magenta", player);
        enemyes[1] = new Enemy(grid, BLOCK_SIZE, 1, "green", player);
        enemyes[2] = new Enemy(grid, BLOCK_SIZE, 2, "red", player);
        enemyes[3] = new Enemy(grid, BLOCK_SIZE, 3, "white", player);

        for (int i = 0; i < 4; i++)
            enemyes[i].draw();
    }
    
    public void end() {
        for (int i = 0; i < 4; i++)
            enemyes[i].erase();
        player.erase();
        main.prestanSpravovatObjekt(player);
        main.prestanSpravovatObjekt(this);
        main.prestanSpravovatObjekt(timer);
    }
}
