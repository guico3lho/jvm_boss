public class recursao {
  public static void imprimir(int n) {
    System.out.println(n);
    n++;
    if (n < 5) imprimir(n); 
  }
  
  public static void main(String[] paramArrayOfString) {
    byte b = 0;
    imprimir(b);
  }
}

