public class vetor_string {
  public static void main(String[] args) {
    String[] arrayOfString = new String[10];

    for(int i = 0; i < arrayOfString.length; i++) {
      arrayOfString[i] = "String " + i;
    }
    
    for(int i = 0; i < arrayOfString.length; i++) {
      System.out.println(arrayOfString[i]);
    }
  }
}
