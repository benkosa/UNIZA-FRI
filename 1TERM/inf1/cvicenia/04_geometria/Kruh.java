public class Kruh {

    private double stredX;
    private double stredY;
    private double polomer;
    
    public Kruh(double stredX, double stredY, double polomer) {
        this.stredX = stredX;
        this.stredY = stredY;
        this.polomer = polomer;
    }
    
    public double getStredX() {
        return this.stredX;
    }
    
    public double getStredY() {
        return this.stredY;
    }
    
    public double getPolomer() {
        return this.polomer;
    }
    
    public void setStredX(double stredX) {
        this.stredX = stredX;
    }

    public void setStredY(double stredY) {
        this.stredY = stredY;
    }
    
    public void setPolomer(double polomer) {
        this.polomer = polomer;
    }
    
    public double obsah() {
        return 3.14 * this.polomer * this.polomer;
    }
    
    public double obvod() {
        return 6.28 * this.polomer;
    }

}