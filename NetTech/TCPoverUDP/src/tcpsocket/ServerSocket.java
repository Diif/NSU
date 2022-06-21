package tcpsocket;

import utilities.PacketUtility;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.util.Arrays;
import java.util.Random;

public class ServerSocket {
    private DatagramSocket socket;
    private int nextSeq;
    private int MAX_SEQ;
    private int WINDOW_SIZE;
    private Window window;
    private DatagramPacket[] receiveBuffer;
    private int bufferBase;
    private boolean packetReady;
    private Random random;


    public void listen(InetAddress addr, int port) throws SocketException {
        socket = new DatagramSocket(port, addr);
        random = new Random();
        System.out.println("\tServer is listening...");
    }

    public void accept() throws IOException {
        DatagramPacket packetSYN = waitSYN();
        System.out.println("\tServer received SYN packet.");
        acceptSYN(packetSYN);
        System.out.println("\tServer accept SYN packet.");
        sendAck();
        System.out.println("\tServer sent ack for SYN packet.");
    }

    private DatagramPacket waitSYN() throws IOException {
        DatagramPacket recPacket = new DatagramPacket(new byte[PacketUtility.HEADER_SIZE + (Integer.BYTES)*2], PacketUtility.HEADER_SIZE + (Integer.BYTES)*2);

        while (true){
            socket.receive(recPacket);
            if(!PacketUtility.isSYN(recPacket)){
                continue;
            } else if (dropPacket()) {
                System.out.println("\tServer drop SYN packet.");
                continue;
            }
            break;
        }
        return recPacket;
    }

    private void acceptSYN(DatagramPacket recPacket){
        int recSeq = PacketUtility.getSeq(recPacket);
        initSizesFromHandshakePacket(recPacket);
        System.out.println("\tServer sizes initialized. MAX_SEQ: " + MAX_SEQ + " , WINDOW_SIZE: " + WINDOW_SIZE);
        nextSeq = (recSeq+1) % MAX_SEQ;
        socket.connect(recPacket.getAddress(),recPacket.getPort());
        receiveBuffer = new DatagramPacket[WINDOW_SIZE];
        window = new Window(MAX_SEQ,1,WINDOW_SIZE);
    }

    private void initSizesFromHandshakePacket(DatagramPacket p){
        byte[] data = PacketUtility.getData(p);
        final int MAXSEQ_START_POS = 0;
        final int WINDOWSIZE_START_POS = 4;
        MAX_SEQ = PacketUtility.getIntFromData(data,MAXSEQ_START_POS);
        WINDOW_SIZE = PacketUtility.getIntFromData(data,WINDOWSIZE_START_POS);
        packetReady = false;
        bufferBase = 0;
    }

    private void sendAck() throws IOException {
        DatagramPacket ackSegment = PacketUtility.makeSegment(PacketUtility.ACK,nextSeq,null,socket.getInetAddress(), socket.getPort());
        socket.send(ackSegment);
    }

    private void increaseNextSeq(){
        nextSeq = (nextSeq+1)%MAX_SEQ;
    }

    public byte[] receive() throws IOException, ConnectionException {
        while (!packetReady) {
            DatagramPacket recPacket = new DatagramPacket(new byte[PacketUtility.MAX_SEGMENT_SIZE_BYTES], PacketUtility.MAX_SEGMENT_SIZE_BYTES);
            socket.receive(recPacket);
            if(dropPacket()){
                System.out.println("\tServer drop packet with string " + new String(PacketUtility.getData(recPacket)).substring(0, recPacket.getLength() - PacketUtility.HEADER_SIZE));
                continue;
            }
            if(PacketUtility.isFIN(recPacket)){
                increaseNextSeq();
                sendAck();
                socket.disconnect();
                System.out.println("\tServer got FIN.");
                throw  new ConnectionException("Connection closed.");
            }
            handlePacket(recPacket);
        }
        byte[] data= Arrays.copyOfRange(PacketUtility.getData(receiveBuffer[bufferBase]),0, receiveBuffer[bufferBase].getLength() - PacketUtility.HEADER_SIZE);
        receiveBuffer[bufferBase] = null;
        bufferBase = (bufferBase+1) % WINDOW_SIZE;
        if(null == receiveBuffer[bufferBase]){
            packetReady =false;
        }
        return data;
    }

    private void handlePacket(DatagramPacket p) throws IOException {
        int packetSeq = PacketUtility.getSeq(p);
        if(packetSeq == nextSeq){
            increaseNextSeq();
            sendAck();
            receiveBuffer[bufferBase] = p;
            packetReady = true;
            window.move();
            return;
        }
        int bufIndex = calculatePacketIndexInBufferBySeq(packetSeq);
        if(null != receiveBuffer[bufIndex]){
            System.err.println("\tServer incorrect seq, bufIndex ["+bufIndex+"], seq [" + packetSeq +"], base " + window.base() + " end " + window.end() + "bufbase " + bufferBase);
            System.err.println("Data: " + new String(PacketUtility.getData(p)));
            throw new RuntimeException();
        }
        receiveBuffer[bufIndex] = p;
    }

    private int calculatePacketIndexInBufferBySeq(int packetSeq){
        if(window.base() <= packetSeq){
            return (bufferBase + (packetSeq - window.base())) % WINDOW_SIZE;
        }
        return (bufferBase + MAX_SEQ - window.base() + packetSeq + 1) % WINDOW_SIZE;

    }

    public boolean isConnected(){
        return socket.isConnected();
    }
    private boolean dropPacket(){
        return random.nextInt() % 8 == 0;
    }


}
