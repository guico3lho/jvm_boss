public class Switch {
  public static void main(String[] args) {

    int pos = 5;
    
    switch(pos) {
      case 1:
      System.out.println("Primeiro lugar");
      break;
      case 2:
      System.out.println("Segundo lugar");
      break;
      case 3:
      System.out.println("Terceiro lugar");
      break;
      case 4: case 5: case 6:
      System.out.println("Premio de participacao");
      break;
      default:
      System.out.println("Nao ganhou.");
      break;
    }
  }
  
}
