public class Comparison {
  public static void main(String[] args) {
    int a = 1;

    if (a == 1) {
      System.out.println("Igual a 1");
    } else {
      System.out.println("Nao igual a 1");
    }

    if(a > 0) {
      System.out.println("Maior que 0");
    }

    if (a < 10) {
      System.out.println("Menor que 10");
    }
    
    if(a >= 1) {
      System.out.println("Maior ou igual a 1");
    }
    
    if (a <= 1) {
      System.out.println("Menor ou igual a 1");
    } 
    
    if(a > 10) {
      System.out.println("Maior que 10");
    }

    int result = (a > 0 ? 1 : 0);
    System.out.print("Operador ternario: ");
    System.out.println(result);
  }
}
