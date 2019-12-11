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
    private boolean comboMode;
    private int comboTimer;
    public Game() {
        // initialise instance variables 
        comboMode = false;
        comboTimer = 200;
        grid = new Grid();
        grid.leadDefaulutMap();        
        player = new Player(grid, BLOCK_SIZE);     

        main = new Manazer();

        main.spravujObjekt(player);        
        main.spravujObjekt(this);
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

        Point pickedPoint = player.pickPoint();
        if(pickedPoint != null){
            if(player.getPoints() == 151){
                end();
                continueGame(player.getScore());                
            }
            if(pickedPoint.isSuper()){
                System.out.println("combo zcalo");
                comboMode = true;
                comboTimer = 200;
                for (int i = 0; i < 4; i++)          
                    enemyes[i].startComboMode();

            }
        }

        for (int i = 0; i < 4; i++){            
            enemyes[i].move();
            if(playerEnemyColision(player.getSquare(), enemyes[i].getSquare())){
                if(comboMode == true){
                    enemyes[i].kill();
                    player.increaseScore(400);
                    System.out.println("Zabity nepriatel");                    
                }else {
                    int life = player.takeLife();
                    end();
                    start();
                    System.out.println("Zivoty: " + life);
                    if(life == 0){
                        end();
                        startNewGame();
                    }
                }
            }
        }

        if(comboMode == true){
            if(--comboTimer == 0){
                System.out.println("combo skoncilo");
                comboMode = false;
                comboTimer = 200;
                for (int i = 0; i < 4; i++)          
                    enemyes[i].stopComboMode();
            }
        }
    }

    public boolean playerEnemyColision(Square pSquare, Square eSquare){
        if(pSquare.squareSquare(eSquare)){
            System.out.println("nastala kolizia p e");
            return true;
        }
        return false;
    }

    public void start() {
        Platno canvas = Platno.dajPlatno();
        canvas.erase();

        comboMode = false;

        //grid = new Grid();
        //grid.leadDefaulutMap();        
        player.setBase();       

        main = new Manazer();

        main.spravujObjekt(player);        
        main.spravujObjekt(this);
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

    public void continueGame(int score) {
        Platno canvas = Platno.dajPlatno();
        comboMode = false;
        comboTimer = 200;
        canvas.erase();
        canvas.redraw();

        grid = new Grid();
        grid.leadDefaulutMap();        
        player = new Player(grid, BLOCK_SIZE, score);       

        main = new Manazer();

        main.spravujObjekt(player);        
        main.spravujObjekt(this);
        grid.draw();
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

    public void startNewGame() {
        Platno canvas = Platno.dajPlatno();
        comboMode = false;
        comboTimer = 200;
        canvas.erase();
        canvas.redraw();

        grid = new Grid();
        grid.leadDefaulutMap();        
        player = new Player(grid, BLOCK_SIZE);      

        main = new Manazer();

        main.spravujObjekt(player);        
        main.spravujObjekt(this);
        grid.draw();
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
    }
}
