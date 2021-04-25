public class Vector_1 {
  public static void main(String[] args) {
    int[] nums = new int[10];

    System.out.print("Tamanho do Vetor_1: ");
    System.out.println(nums.length);

    for(int i = 0; i < nums.length; i++) {
      nums[i] = i;
      System.out.println(nums[i]);
    }
  }
}
