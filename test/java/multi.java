class multi {
  public static void main(String[] paramArrayOfString) {
    String[][] arrayOfString = new String[10][10];
    arrayOfString[0][0] = "teste";
    arrayOfString[0][1] = "teste2";
    arrayOfString[9][5] = "teste4";
    System.out.println(arrayOfString[0][0]);
    System.out.println(arrayOfString[0][1]);
    System.out.println(arrayOfString[9][5]);
  }
}