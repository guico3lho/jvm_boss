class vetor2 {
    public static void main(String[] paramArrayOfString) {
      int[] arrayOfInt1 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
      int[] arrayOfInt2 = { -5, 3, 6426246, -433242 };
      float[] arrayOfFloat1 = { 2.0F, 3.0F, -5.0F };
      float[] arrayOfFloat2 = { 1.0F, 3.0F, -5.0F };
      byte[] arrayOfByte = { -2, 4, 0 };
      char[] arrayOfChar = { 'a', '0', ')' };
      short[] arrayOfShort = { 15, 1000, -2 };
      byte b;

      for (b = 0; b < 10; b++)
        arrayOfInt1[b] = b; 
      arrayOfInt1[0] = arrayOfInt1[0] + 100000;

      for (b = 0; b < 10; b++)
        System.out.println(arrayOfInt1[b]); 
      System.out.println(arrayOfInt1.length);
      System.out.println();

      for (b = 0; b < 4; b++)
        System.out.println(arrayOfInt2[b]); 
      System.out.println(arrayOfInt2.length);
      System.out.println();

      for (b = 0; b < 3; b++)
        System.out.println(arrayOfFloat1[b]); 
      System.out.println(arrayOfFloat1.length);
      System.out.println();


      for (b = 0; b < 3; b++)
        System.out.println(arrayOfFloat2[b]); 
      System.out.println(arrayOfFloat2.length);
      System.out.println();

      for (b = 0; b < 3; b++)
        System.out.println(arrayOfByte[b]); 
      System.out.println(arrayOfByte.length);
      System.out.println();

      for (b = 0; b < 3; b++)
        System.out.println(arrayOfChar[b]); 
      System.out.println(arrayOfChar.length);
      System.out.println();
      
      for (b = 0; b < 3; b++)
        System.out.println(arrayOfShort[b]); 
      System.out.println(arrayOfShort.length);
      System.out.println();
    }
  }
  