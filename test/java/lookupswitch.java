public class lookupswitch {
  public static int options(int paramInt) {
    switch (paramInt) {
      case -100:
        return -1;
      case 0:
        return 0;
      case 100:
        return 1;
    } 
    return 200;
  }
  
  public lookupswitch() {
    System.out.println("Ops!");
  }
  
  public static void main(String[] paramArrayOfString) {
    System.out.println(options(-1));    // 200
    System.out.println(options(-100));  // -1
    System.out.println(options(0));     // 0
    System.out.println(options(100));   // 1
    System.out.println(options(10000)); // 200
  }
}
