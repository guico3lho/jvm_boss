public class tableswitch {
  public static int chooseNear(int paramInt) {
    switch (paramInt) {
      case 0:
        return 0;
      case 1:
        return 1;
      case 2:
        return 2;
    } 
    return -1;
  }
  
  public tableswitch() {
    System.out.println("Ops!");
  }
  
  public static void main(String[] paramArrayOfString) {
    System.out.println(chooseNear(-1));
    System.out.println(chooseNear(0));
    System.out.println(chooseNear(1));
    System.out.println(chooseNear(2));
    System.out.println(chooseNear(3));
  }
}
