import java.util.Random;
import java.util.ArrayList;

/**
 * Write a description of class Enemy here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Enemy
{
    private boolean comboMode;
    private int id;
    private Square square;
    private String direction;
    private String lastDirection;
    private Player player;
    //info o tom v ktorom bloku sa hrac nachadza
    private int blockX;
    private int blockY;

    private Grid grid;

    private int[][] cesta; // Matica, v ktorej sa bude nachadzat najdena cesta

    // Mozne pohyby (mame 4 moznosti - hore, dole, dolava, doprava)
    private int a[];       // Xove suradnice moznych pohybov
    private int b[];       // Yove suradnice moznych pohybov

    // Suradnice ciela - pravy dolny roh matice (teoreticky by mohol byt ciel aj v inom bode)
    private int cielX;
    private int cielY;
    private String defaultColor;

    private ArrayList<String> instructions;

    private int[][] blud = { 
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

    public Enemy(Grid grid, int size, int id, String color, Player player) {
        defaultColor = color;
        this.id = id;
        this.square = new Square(grid.getEnemyBaseX(id), grid.getEnemyBaseY(id), size, color, true, true);
        this.grid = grid;
        this.player = player;
        this.comboMode = false;

        // Mozne pohyby (mame 4 moznosti - hore, dole, dolava, doprava)        
        this.a = new int [4];           // Xove suradnice pohybu
        this.b = new int [4];           // Yove suradnice pohybu

        instructions = new ArrayList<String>();

        // Moznosti pohybu (a - riadok, b - stlpec)
        this.a[0] = -1; this.b[0] = 0;  // hore
        this.a[1] = 1;  this.b[1] = 0;  // dole
        this.a[2] = 0;  this.b[2] = 1;  // doprava
        this.a[3] = 0;  this.b[3] = -1; // dolava

        swapMovements();swapMovements();
        swapMovements();swapMovements();

        // Pociatocne vytvorenie cesty
        this.cesta = new int[grid.getMap().length][];
        for (int i = 0; i < grid.getMap().length; i++)
            this.cesta[i] = new int[grid.getMap()[i].length];

        // Inicializacia cesty - este som nebol na ziadnom policku
        for (int i = 0; i < grid.getMap().length; i++){
            for (int j = 0; j < grid.getMap()[i].length; j++){
                this.cesta[i][j] = 0;
                if(grid.getBlock(i,j).getIsAir() == true)
                    this.blud[i][j] = 0;
                else
                    this.blud[i][j] = 1;
            }
        }

        setCurrentBlock();
        //System.out.println(this.square.getColor() + " " + this.blockX + " " + this.blockY + " " + this.direction);
        this.generateInstructions();       
        changeMovement();
        //System.out.println(this.square.getColor() + " " + this.blockX + " " + this.blockY + " " + this.direction);
    }

    // Vypis vysledky (poradie navstivenia jednotlivych policok)
    private void vypisVysledky(){
        System.out.print("Bludisko:");
        for (int j = 0; j < 4 * this.blud[0].length - 1; j++)
            System.out.print(" ");
        System.out.println("Nájdená cesta:");

        // Vypis bludisko
        for (int i = 0; i < this.blud.length; i++){
            for (int j = 0; j < this.blud[i].length; j++){
                if (this.blud[i][j] < 10)
                    System.out.print(" ");
                System.out.print(blud[i][j]);
                if (j < this.blud[i].length - 1) // za posledny prvok uz medzery nepisem,
                    System.out.print("  ");
            }
            System.out.print("          ");

            // Vypis najdenu cestu
            for (int j = 0; j < this.cesta[i].length; j++){
                if (this.cesta[i][j] < 10)
                    System.out.print(" ");
                if (this.cesta[i][j] == 0)
                    System.out.print(".");
                else
                    System.out.print(this.cesta[i][j]);
                if (j < this.cesta[i].length - 1) // za posledny prvok uz medzery nepisem,
                    System.out.print("  ");
            }
            System.out.println();
        }
    }

    private boolean vyskusaj(int cisloSkoku, int aktX, int aktY)
    {
        int k, u, v;                // k - pomocna premenna pre indexovanie pohybu - hore, dole, doprava, dolava
        // u - Xova suradnica aktualneho policka
        // v - Yova suradnica aktualneho policka
        boolean skokDopadolUspesne; // pomocna premenna na uchovanie vysledku noveho pohybu
        k = -1;
        do // Postupne prechadzaj mozne tahy
        {
            k++;
            skokDopadolUspesne = false;

            // Najdi novy bod na zaklade sucasneho bodu a suradnic skoku
            u = aktX + a[k]; 
            v = aktY + b[k];
            if(cisloSkoku == 20){

                swapMovements();swapMovements();
                swapMovements();swapMovements();
                return true;
            }
            if ((0 <= u) && (u < this.blud.length)){ // Ak sa bod nachadza v bludisku
                if ((0 <= v) && (v < this.blud[u].length)){
                    // Ak som tam este nebol a mozem tam ist
                    //if(++count > 10) return false;
                    if ((this.cesta[u][v] == 0) && (this.blud[u][v] == 1)){
                        this.cesta[u][v] = cisloSkoku;
                        this.addInstruction(a[k], b[k]);
                        // Ak este nie som v cieli, pokusam sa ist dalej 
                        if ((u != cielX) || (v != cielY)){
                            skokDopadolUspesne = vyskusaj(cisloSkoku + 1, u, v);
                            if (!skokDopadolUspesne){
                                this.cesta[u][v] = 0;
                                if( instructions.size() > 0 )
                                    instructions.remove( instructions.size() - 1 );
                            }
                        }
                        else{
                            skokDopadolUspesne = true;
                            this.addInstruction(a[k], b[k]);
                        }
                    }
                }
            }
        }
        while (!(skokDopadolUspesne || (k == 3)));
        return skokDopadolUspesne;
    }

    public void addInstruction(int x, int y){
        if(x == -1 && y == 0)
            instructions.add("le");
        if(x == 1 && y == 0)
            instructions.add("ri"); 
        if(x == 0 && y == 1)
            instructions.add("up");
        if(x == 0 && y == -1)
            instructions.add("do"); 
    }

    public void generateInstructions(){

        cielX = player.getBlockX();
        cielY = player.getBlockY();

        for (int i = 0; i < this.blud.length; i++){
            for (int j = 0; j < this.blud[i].length; j++)
                this.cesta[i][j] = 0;
        }
        this.vyskusaj(1, this.blockX, this.blockY);        
    }

    public void najdiAvypisCestu(){

        cielX = player.getBlockX();
        cielY = player.getBlockY();

        for (int i = 0; i < this.blud.length; i++){
            for (int j = 0; j < this.blud[i].length; j++)
                this.cesta[i][j] = 0;
        }

        if (this.vyskusaj(1, this.blockX, this.blockY)){
            this.vypisVysledky();
            for(String o: this.instructions)
                System.out.print(o + ", ");
            System.out.println();
        }else
            System.out.println("Riešenie pre toto bludisko neexistuje!");
    }

    private void swapMovements(){
        Random generator = new Random();
        int id1 = generator.nextInt(4);
        int id2 = generator.nextInt(4);

        int tmp = this.a[id1];        
        this.a[id1] = this.a[id2];
        this.a[id2] = tmp;

        tmp = this.b[id1];        
        this.b[id1] = this.b[id2];
        this.b[id2] = tmp;
    }

    private void swapMovementsInteligently(){        
        Random generator = new Random();

        int pBx = player.getBlockX();
        int pBy = player.getBlockY();

        int eBx = this.getBlockX();
        int eBy = this.getBlockY();

        int id1 = generator.nextInt(2)+2;
        int id2 = generator.nextInt(2)+2; 

        if(pBx < eBx && pBy > eBy){       // dole v pravo
            System.out.println("dole v pravo");
            this.a[0] = 1;  this.b[0] = 0;  // dole
            this.a[1] = 0;  this.b[1] = 1;  // doprava

            this.a[id1] = -1; this.b[id1] = 0;  // hore            
            this.a[id2] = 0;  this.b[id2] = -1; // dolava
        }
        else if (pBx > eBx && pBy > eBy){ // dole v lavo
            System.out.println("dole v lavo");
            this.a[0] = 1;  this.b[0] = 0;  // dole           
            this.a[1] = 0;  this.b[1] = -1; // dolava

            this.a[id1] = 0;  this.b[id1] = 1;  // doprava
            this.a[id2] = -1; this.b[id2] = 0;  // hore

        }else if(pBx < eBx && pBy < eBy){ // hore v pravo
            System.out.println("hore v pravo");
            this.a[0] = -1; this.b[0] = 0;  // hore
            this.a[1] = 0;  this.b[1] = 1;  // doprava

            this.a[id1] = 1;  this.b[id1] = 0;  // dole          
            this.a[id2] = 0;  this.b[id2] = -1; // dolava
        }
        else if (pBx > eBx && pBy > eBy){ // hore v lavo
            System.out.println("hore v lavo");
            this.a[0] = -1; this.b[0] = 0;  // hore         
            this.a[1] = 0;  this.b[1] = -1; // dolava

            this.a[id1] = 0;  this.b[id1] = 1;  // doprava
            this.a[id2] = 1;  this.b[id2] = 0;  // dole 

        }
        else{
            System.out.println("random");
            swapMovements();swapMovements();
            swapMovements();swapMovements();
        }
    }

    public void draw(){
        this.square.draw();
    }

    public String getDirection(){
        return this.direction;
    }

    public String getLastDirection(){
        return this.lastDirection;
    }

    public void setDirection(String direction){
        this.direction = direction;
    }

    public Grid getGrid(){
        return this.grid;
    } 

    public boolean setCurrentBlock(){
        boolean ret = false;
        if(square.getBlockX() == blockX && square.getBlockY() == blockY)
            ret = true;

        blockX = square.getBlockX();
        blockY = square.getBlockY();

        return ret;
    }

    public int getBlockX(){
        return blockX;
    }

    public int getBlockY(){
        return blockY;
    }

    public Square getSquare(){
        return this.square;
    }

    /**
     * najde blok podla suradnic a otestuje koliziu
     * @param int X
     * @param int Y
     */
    public boolean isCollision(int X, int Y){
        Square square2 = this.grid.getBlock(this.blockX+X, this.blockY+Y).getSquare();
        return this.square.squareSquare(square2);
    }

    /**
     * kontroluje koliziu s tromi blokmi pred hracom
     * @param String direction
     */
    public boolean moveTo(String direction){
        if(direction.equals("up")){
            this.square.increaseY();
            if(this.isCollision(0, 1) || this.isCollision(1, 1) || this.isCollision(-1, 1)){            
                this.square.decreaseY();
                return false;
            }
            return true;
        }
        if(direction.equals("do")){
            this.square.decreaseY();
            if(this.isCollision(0, -1) || this.isCollision(1, -1) || this.isCollision(-1, -1)){
                this.square.increaseY();
                return false;
            }
            return true;
        }
        if(direction.equals("ri")){
            this.square.decreaseX();
            if(this.isCollision(-1, 0) || this.isCollision(-1, 1) || this.isCollision(-1, -1)){
                this.square.increaseX();
                return false;
            }
            return true;
        }
        if(direction.equals("le")){
            this.square.increaseX();
            if(this.isCollision(1, 0) || this.isCollision(1, 1) || this.isCollision(1, -1)){
                this.square.decreaseX();
                return false;
            }
            return true;
        }
        return true;
    }
    
    
    /**
     * meni pohyb na zaklade vygenerovanych instrukcii
     */
    public void changeMovement(){
        String direction =  "";
        if(instructions.size() == 0){     

            swapMovements();swapMovements();
            swapMovements();swapMovements();
            this.generateInstructions();
        }
        direction = instructions.get(0);
        instructions.remove(0);

        //System.out.println(this.square.getColor() + " " + instructions.size());
        if(direction.equals("up")){
            this.moveUp();
        }
        if(direction.equals("do")){
            this.moveDown();
        }
        if(direction.equals("ri")){
            this.moveRight();
        }
        if(direction.equals("le")){
            this.moveLeft();       
        }

    }

    /* vykona pohyb a ak nastala kolizia tak pokracuje 
     * v predoslom pohybe
     */    
    public void move(){ 
        if(this.setCurrentBlock() == false){
            this.changeMovement();
            //System.out.println(this.square.getColor() + " " + this.blockX + " " + this.blockY + " " + this.direction);            
        }
        //if(instructions.size() != 0)
        if(this.moveTo(this.getDirection()) == false)
            this.moveTo(this.getLastDirection());

        draw();
    }

    public void startComboMode(){
        this.square.setColor("white");
        this.comboMode = true;
    }

    public void stopComboMode(){
        this.square.setColor(defaultColor);        
        this.comboMode = false;

    }

    public void kill(){
        this.square.setX(grid.getEnemyBaseX(this.id));
        this.square.setY(grid.getEnemyBaseY(this.id));

        this.setCurrentBlock();
        instructions.clear();
        generateInstructions();
        changeMovement();
    }

    public void moveUp(){
        this.lastDirection = this.direction;
        this.direction = "up";
    }

    public void moveDown(){
        this.lastDirection = this.direction;
        this.direction = "do";
    }

    public void moveRight(){
        this.lastDirection = this.direction;
        this.direction = "le";
    }

    public void moveLeft(){
        this.lastDirection = this.direction;
        this.direction = "ri";
    }

    public void erase(){
        this.square.erase();
    }

}
