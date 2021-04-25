public class MethodParams {
  public static void main(String[] args) {
    System.out.println(soma(1, 5, 6, 22, 30)); // 64
  }

  public static int soma(int... numeros) {
    int res = 0;
    for(int n:numeros) {
      res += n;
    }
    return res;
  }
}
