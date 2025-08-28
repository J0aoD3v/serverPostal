package java;
import java.net.*;
import java.io.*;

public class UDPClient {
    public static void main(String[] args) {
        String host = "127.0.0.1";
        int porta = 8089;

        System.out.println("Digite mensagens (escreva 'FIM' para encerrar):");

        try (DatagramSocket socket = new DatagramSocket();
                BufferedReader teclado = new BufferedReader(new InputStreamReader(System.in))) {

            InetAddress endereco = InetAddress.getByName(host);
            String msg;

            while (true) {
                System.out.print("Cliente >> ");
                msg = teclado.readLine();

                byte[] buffer = msg.getBytes();
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length, endereco, porta);
                socket.send(packet);

                if (msg.equalsIgnoreCase("FIM")) {
                    System.out.println("Conexao encerrada");
                    break;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
