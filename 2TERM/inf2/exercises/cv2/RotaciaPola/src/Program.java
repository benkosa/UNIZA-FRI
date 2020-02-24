
public class Program {

    public static void main(String[] args) {
        System.out.println("Pole:");
        String[] pole = new String[5];
        for (int i = 0; i < pole.length; i++) {
            pole[i] = Integer.toString(i + 1);
            System.out.print(pole[i] + " ");
        }
        
        RotaciaPolaRetazcov rotacia = new RotaciaPolaRetazcov();
        rotacia.setPoleRetazcov(pole);
        
        System.out.println("\n\nPole po rotacii o 1:");
        rotacia.posunVpravo(1);
        for (String polozka : rotacia.getPoleRetazcov()) {
            System.out.print(polozka + " ");
        }
        
        System.out.println("\n\nPole po rotacii o 2:");
        rotacia.posunVpravo(2);
        for (String polozka : rotacia.getPoleRetazcov()) {
            System.out.print(polozka + " ");
        }
    }
    
}
