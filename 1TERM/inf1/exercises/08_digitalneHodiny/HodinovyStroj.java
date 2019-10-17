 

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.Timer;

public class HodinovyStroj implements ActionListener {
    private DigitalneHodiny hodiny;
    private Timer timer;
    private long oldTick;    
    private static final long TICK_LENGTH = 250000000;

    /**
     * Vytvori hodinovy stroj.
     * 
     * @param hodiny hodiny, v ktorych sa hodinovy stroj nachadza         
     */
    public HodinovyStroj(DigitalneHodiny hodiny) {
        this.hodiny = hodiny;
        
        this.timer = new javax.swing.Timer(25, null);        
        this.timer.addActionListener(this);      
        
        this.oldTick = 0;
        this.timer.start();
    }
    
    public void actionPerformed(ActionEvent event) {
        long newTick = System.nanoTime();
        if (newTick - this.oldTick >= HodinovyStroj.TICK_LENGTH || newTick < HodinovyStroj.TICK_LENGTH) {
            this.oldTick = (newTick / HodinovyStroj.TICK_LENGTH) * HodinovyStroj.TICK_LENGTH;
            if(this.hodiny != null)
                this.hodiny.tik(); 
        }
    }
    
    public void setHodiny(DigitalneHodiny hodiny){
        this.hodiny = hodiny;
    }

}
