class _double_aritmetica {
  static double TESTEDOCARALHO(double paramDouble) {
    return paramDouble;
  }
  
  public static void main(String[] paramArrayOfString) {
    double d1 = 5.4D;
    System.out.println(d1);   // 5.4
    double d2 = 3.5D;
    System.out.println(d2);   // 3.5
    double d3 = d1 + d2;
    System.out.println(d3);   // 8.9
    double d4 = d1 - d2;
    System.out.println(d4);   // 1.9
    double d5 = d1 / d2;
    System.out.println(d5);   // 1.54285..
    double d6 = d1 * d2;
    System.out.println(d6);   // 18.9
    double d7 = d1 % d2;
    System.out.println(d7);   // 1.9
    // boolean bool = true;
    // double d8 = bool;
    // System.out.println(d8);
    long l = 1L;
    double d9 = l;
    System.out.println(d9);   // 1.0
    float f = 5.0F;
    double d10 = f;
    System.out.println(d10);  // 1.0
    byte b = 5;
    double d11 = b;
    System.out.println(d11);  // 5.0
    System.out.println(TESTEDOCARALHO(d1));
  }
}

