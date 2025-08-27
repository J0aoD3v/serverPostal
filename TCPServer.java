import java.io.*;
import java.net.*;

public class TCPServer {
    public static void main(String[] args) {
        int porta = 8089;
        System.out.println("SERVIDOR INICIADO NA PORTA " + porta);
        System.out.println("Aperte Ctrl + C para encerrar o servidor.");

        try (ServerSocket serverSocket = new ServerSocket(porta)) {
            while (true) {
                Socket socket = serverSocket.accept();
                System.out.println("CONECÇÃO ESTABELECIDA COM " + socket.getInetAddress().getHostAddress());

                BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                String msg;

                while ((msg = in.readLine()) != null) {
                    System.out.println("Cliente >> " + msg);
                }

                System.out.println("Cliente desconectado: " + socket.getInetAddress().getHostAddress());
                socket.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
