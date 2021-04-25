public class _int_aritmetica {
  public static void main(String[] paramArrayOfString) {
    int i = 100; // 1100100
    byte b = 30; //   11110
    System.out.println(i + b);  // 130
    System.out.println(i - b);  // 70
    System.out.println(i * b);  // 3000
    System.out.println(i / b);  // 3
    System.out.println(-i);     // -100
    System.out.println(i % b);  // 10
    System.out.println(i & b);  // 4
    System.out.println(i << 2); // 400 = 110010000
    System.out.println(i >> 2); // 25 = 11001
    i = -100;
    System.out.println(i >> 2); // -25 = -11001
    i = 1073741823;
    System.out.println(i);      // 1073741823
  }
}
