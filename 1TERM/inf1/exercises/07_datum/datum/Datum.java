/**
 * Write a description of class Datum here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Datum {
    /**
     * Constructor for objects of class Datum
     */
    private int mesiac;
    private int rok;
    
    private static final int PRIESTUPNY = 366;
    private static final int NEPRIESTUPNY = 365;
    
    private static final int POCIATOCNY_ROK = 1900;
    
    public Datum() {
        this.rok = 2019;
        this.mesiac = 11;
        
    }
    
    public int getMesiac(){
        return this.mesiac;
    }
    
    public int getRok(){
        return this.rok;
    }
    
    public void setRok(int rok){
        if (rok >= 1900)
            this.rok = rok;
        else
            this.rok = 1900;
    }
    
    public void setMesiac(int mesiac){
        if (mesiac >= 1 && mesiac <= 12)
            this.mesiac = mesiac;
        else
            this.mesiac = 1;
    }
    
    private boolean jePriestupny(){
        return (this.rok % 4 == 0) && ((this.rok % 100 != 0) || (this.rok % 400 == 0));
    }
    
    private boolean jePriestupny(int rok){
        return (rok % 4 == 0) && ((rok % 100 != 0) || (rok % 400 == 0));
    }
    
    private int getMaxPocetDniMesiaca(){
        switch (this.mesiac){
            case 4:
            case 6:
            case 9:
            case 11:
                return 30;
            case 2:
                //je priestupny
                if(this.jePriestupny())
                    return 29;
                    
                return 28;
            default: 
                return 31;
        }
    }    
   
    public int getPocetDniOdZaciatkuRoka(){        
        int count = 0;
        switch(this.mesiac){
            case 12: if(this.mesiac != 12)count += 31;
            case 11: if(this.mesiac != 11)count += 30;
            case 10: if(this.mesiac != 10)count += 31;
            case 9: if(this.mesiac != 9)count += 30;
            case 8: if(this.mesiac != 8)count += 31;
            case 7: if(this.mesiac != 7)count += 31;
            case 6: if(this.mesiac != 6)count += 30;
            case 5: if(this.mesiac != 5)count += 31;
            case 4: if(this.mesiac != 4)count += 30;
            case 3: if(this.mesiac != 3)count += 31;
            case 2:
                if(this.jePriestupny()){
                    if(this.mesiac != 2)count += 29;
                }else{    
                    if(this.mesiac != 2)count += 28;
                }
            case 1: if(this.mesiac != 1)count += 31;
        } 
        
        return count;        
    }
    
    private int getPocetDniVroku(int rok){
        return this.jePriestupny(rok) ? PRIESTUPNY : NEPRIESTUPNY;
    }
    
    private String getNazovDna(int pocetDni){
        switch(pocetDni){
            case 0: return "MON";
            case 1: return "TUE";
            case 2: return "WED";
            case 3: return "THU";
            case 4: return "FRI";
            case 5: return "SAT";
            default: return "SUN";         
        }
    }
    
    private boolean fromMonth(int val){
        return val > 0 ? (val < getMaxPocetDniMesiaca()+1 ? true : false) : false;
    }
    
    private int getPocetDniOd1900(){
        int pocetDni = 1;
        for(int i = POCIATOCNY_ROK; i< this.rok; i++)
            pocetDni += this.getPocetDniVroku(i);
        return pocetDni += this.getPocetDniOdZaciatkuRoka();
    }
    
    public void pocetDniOd1900(){
        int pocetDni = getPocetDniOd1900();
        
        //pocetDni % 7 vrati cislo od 0 - 6 kde 0 je pondelok...
        //kedze vyisujem od pondelka ale pociatocny den moze byt
        //aj napriklad piatok dam *-1 to mi hodi pociatocny den
        //pre pondelok a nakoniec +1 riesi problem s 0
        int pociatocnyDen = (pocetDni % 7)*-1+1;      
       
        String output = "";
        for(int i = 0; i < 7; i++){
            output += getNazovDna(i) + " ";
            pociatocnyDen++;
            for(int j = 0; j < 30; j+=7){
                int kalendarnyDen = pociatocnyDen + j;
                output += (fromMonth(kalendarnyDen) == true ? kalendarnyDen : " ") + (kalendarnyDen < 10 ? "  " : " ");
            }
            output += "\n";
        }
        System.out.println(output);
    }    

}
