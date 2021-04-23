public class _recursao {
  public static void imprimir(int paramInt) {
    System.out.println(paramInt);
    paramInt++;
    if (paramInt < 15)
      imprimir(paramInt); 
  }
  
  public static void main(String[] paramArrayOfString) {
    byte b = 10;
    imprimir(b);
  }
}

