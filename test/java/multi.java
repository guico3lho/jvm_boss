class multi {
  public static void main(String[] paramArrayOfString) {

    int[][][] arrayOfInt = new int[2][3][4];

    arrayOfInt[0][0][0] = 1;
    arrayOfInt[0][1][0] = 2;
    arrayOfInt[1][1][1] = 3;

    System.out.println(arrayOfInt[0][0][0]);
    System.out.println(arrayOfInt[0][1][0]);
    System.out.println(arrayOfInt[1][1][1]);

    // String[][][] arrayOfString = new String[2][3][4];

    // arrayOfString[0][0][0] = "teste";
    // arrayOfString[0][1][0] = "teste2";
    // arrayOfString[1][1][1] = "teste4";

    // System.out.println(arrayOfString[0][0][0]);
    // System.out.println(arrayOfString[0][1][0]);
    // System.out.println(arrayOfString[1][1][1]);
  }
}