
/**
 * Write a description of class Timer here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class Timer {
    int count;
    int sec;
    public Timer() {
       sec = 0;
       count = 0;
    }
    
    public void tik(){
        if(++this.count > 30){
            this.count = 0;
            this.sec++;
            //System.out.println(sec);
        }
    }
    
    public int getSec(){
        return sec;
    }
}
