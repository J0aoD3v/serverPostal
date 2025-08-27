import java.io.*;
import java.net.*;

public class TCPClient {
    public static void main(String[] args) {
        String host = "127.0.0.1";
        int porta = 8089;

        System.out.println("Digite mensagens (escreva 'FIM' para encerrar):");

        try (Socket socket = new Socket(host, porta)) {
            BufferedReader teclado = new BufferedReader(new InputStreamReader(System.in));
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            String msg;

            while (true) {
                System.out.print("Cliente >> ");
                msg = teclado.readLine();
                out.println(msg);
                if (msg.equalsIgnoreCase("FIM")) {
                    System.out.println("Conexão encerrada");
                    break;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
