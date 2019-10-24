public class Rozhodca {
    public Rozhodca() {
    }
    
    public Ruka urciVitaza(Ruka prvyHrac, Ruka druhyHrac) {
        switch(prvyHrac.dajNazovGesta()){
            case "Rock": switch(druhyHrac.dajNazovGesta()){
                case "Rock": return null;
                case "Paper": return druhyHrac;
                case "Scissors": return prvyHrac;
                case "Lizard": return prvyHrac;
                default: return druhyHrac;
            }
            case "Paper": switch(druhyHrac.dajNazovGesta()){
                case "Rock": return prvyHrac;
                case "Paper": return null;
                case "Scissors": return druhyHrac;
                case "Lizard": return druhyHrac;
                default: return prvyHrac;
            }
            case "Scissors": switch(druhyHrac.dajNazovGesta()){
                case "Rock": return druhyHrac;
                case "Paper": return prvyHrac;
                case "Scissors": return null;
                case "Lizard": return prvyHrac;
                default: return druhyHrac;
            }
            case "Lizard": switch(druhyHrac.dajNazovGesta()){
                case "Rock": return prvyHrac;
                case "Paper": return prvyHrac;
                case "Scissors": return druhyHrac;
                case "Lizard": return null;
                default: return prvyHrac;
            }
            default: switch(druhyHrac.dajNazovGesta()){
                case "Rock": return prvyHrac;
                case "Paper": return druhyHrac;
                case "Scissors": return prvyHrac;
                case "Lizard": return druhyHrac;
                default: return null;
            }
        }
    }
}
