import tcpsocket.ClientSocket;
import tcpsocket.ConnectionException;
import tcpsocket.SegmentException;
import tcpsocket.ServerSocket;

import java.io.IOException;
import java.net.InetAddress;

public class Main {
    public static void main(String[] args) throws SegmentException, IOException, ConnectionException {
        Thread servThread = new Thread(() -> {
                ServerSocket serverSocket = new ServerSocket();
                try {
                    serverSocket.listen(InetAddress.getByName("localhost"), 11112);
                    serverSocket.accept();
                    while (serverSocket.isConnected()){
                        byte[] data = serverSocket.receive();
                        String str = new String(data);
                        System.out.println("\t\t\t SERVER GOT STR: " + str);
                    }
                }catch (ConnectionException ignored){}
                catch (Exception e){
                    throw new RuntimeException();
                }
        });
        servThread.start();

        ClientSocket socket = new ClientSocket(InetAddress.getByName("localhost"),11111);
        socket.connect(InetAddress.getByName("localhost"),11112);
        for (int i = 1; i <100; i++) {
            socket.send(("String"+i).getBytes());
        }
        socket.closeConnection();
    }

}
