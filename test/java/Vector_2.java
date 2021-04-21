public class Vector_2 {
  public static void main(String[] args) {
    
    int[] nums = {1, 2, 3, 4, 5};
    System.out.print("Tamanho do Vetor_2: ");
    System.out.println(nums.length);
    
    System.out.println("Loop for no Vetor_2");

    for (int i = 0; i < nums.length; i++ ) {
      System.out.print("[");
      System.out.print(i);
      System.out.print("] = ");
      System.out.println(nums[i]);
    }
  }
}
