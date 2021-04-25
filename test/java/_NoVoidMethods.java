public class _NoVoidMethods {
    public static void main(String[] paramArrayOfString) {
      System.out.println(Soma(2, 3));
      System.out.println(Soma(35.35D, 30.35D));
      System.out.println(Soma(300000000L, 700000000L));
    }
    
    public static int Soma(int paramInt1, int paramInt2) {
      return paramInt1 + paramInt2;
    }
    
    public static double Soma(double paramDouble1, double paramDouble2) {
      return paramDouble1 + paramDouble2;
    }
    
    public static long Soma(long paramLong1, long paramLong2) {
      return paramLong1 - paramLong2;
    }
  }