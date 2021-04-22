public class _lookupswitch {
  public static int chooseFar(int paramInt) {
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
  
  public _lookupswitch() {
    System.out.println("Ops!");
  }
  
  public static void main(String[] paramArrayOfString) {
    System.out.println(chooseFar(-1));    // 200
    System.out.println(chooseFar(-100));  // -1
    System.out.println(chooseFar(0));     // 0
    System.out.println(chooseFar(100));   // 1
    System.out.println(chooseFar(10000)); // 200
  }
}
