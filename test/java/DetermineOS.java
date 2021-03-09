public class DetermineOS {
  public static void main(String[] args) {
    String strOSName = System.getProperty("os.name");

    System.out.print("Display the current OS name example.. OS is ");
    if (strOSName != null) {
      if (strOSName.toLowerCase().contains("linux"))
        System.out.println("Linux");
      else
        System.out.print("not Linux");
    }
  }
}
