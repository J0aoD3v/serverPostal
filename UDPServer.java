import java.net.*;

public class UDPServer {
    public static void main(String[] args) {
        int porta = 8089;
        System.out.println("SERVIDOR UDP INICIADO NA PORTA " + porta);
        System.out.println("Aperte Ctrl + C para encerrar o servidor.");

        try (DatagramSocket socket = new DatagramSocket(porta)) {
            byte[] buffer = new byte[1024];

            while (true) {
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
                socket.receive(packet);

                String msg = new String(packet.getData(), 0, packet.getLength());
                System.out.println("Cliente (" + packet.getAddress().getHostAddress() + ") >> " + msg);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
