import java.lang.Thread;

public class Main extends Thread {

  public static void main(String[] args) {

    // Vetor para as 5 threads
    Main[] childs = new Main[5];

    // Criacao de threads
    for (Main thread : childs) {
      thread = new Main();
      thread.start();
    }

  }

  // Metodo que roda quando a thread eh criada
  public void run() {
    System.out.println("Hello World!");
  }

}
