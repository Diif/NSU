package tcpsocket;

import utilities.PacketUtility;

import static utilities.PacketUtility.*;

import java.io.IOException;
import java.net.*;
import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.Timer;
import java.util.TimerTask;


public class ClientSocket {
    private static final int SO_TIMEOUT = 250;
    private static final int TCP_TIMEOUT = 2000;
    private static final int MAX_TRIES = 20;
    private static final int MAX_SEQ = 11;
    private static final int WINDOW_SIZE = 5;
    private final DatagramSocket socket;
    private InetAddress connectionAddress;
    private int connectionPort;
    private final DatagramPacket receiveBuffer;
    private final Window window;
    Timer timer;
    private int nextSeq;
    private int numTries;
    private boolean timerRunning;

    public ClientSocket(InetAddress address,int port) throws SocketException {
        socket = new DatagramSocket(port, address);
        socket.setSoTimeout(SO_TIMEOUT);
        receiveBuffer = new DatagramPacket(new byte[HEADER_SIZE], HEADER_SIZE);
        timerRunning = false;
        window = new Window(MAX_SEQ,0,WINDOW_SIZE-1 );
    }

    public void connect(InetAddress addr, int port) throws IOException, ConnectionException {
        if(socket.isConnected()){
            throw new ConnectionException("Socket is already connected.");
        }
        initVarsForConnection();
        makeHandshake(addr,port);
        socket.connect(addr,port);
        if(!socket.isConnected()){
            throw new PortUnreachableException();
        }
        connectionAddress = addr;
        connectionPort = port;
    }

    private void initVarsForConnection(){
        nextSeq = 0;
    }

    private void makeHandshake(InetAddress addr, int port) throws IOException, ConnectionException {
        DatagramPacket[] segment = {makeSegment(SYN, nextSeq, ByteBuffer.allocate(Integer.BYTES *2).putInt(MAX_SEQ).putInt(WINDOW_SIZE).array(),addr,port)};
        increaseSeq();
        sendAndACKSegments(segment);
    }

    private void sendAndACKSegments(DatagramPacket[] segments) throws IOException, ConnectionException {
        int segmentCurPosIndex = 0;
        int smallestNotACKedSegmentIndex = segmentCurPosIndex;

        while (smallestNotACKedSegmentIndex < segments.length){
            segmentCurPosIndex = sendSegment(segmentCurPosIndex,segments);
            smallestNotACKedSegmentIndex = testForACK(smallestNotACKedSegmentIndex,segments);
        }
    }

    private int sendSegment(int segmentCurPosIndex, DatagramPacket[] segments) throws IOException {
        int segmentCount = segments.length;
        if(window.end() != window.curPos() && segmentCurPosIndex!=segmentCount){
            socket.send(segments[segmentCurPosIndex]);
            if(!timerRunning){
                startTimer(segments[segmentCurPosIndex]);
            }
            segmentCurPosIndex++;
            window.increaseWindowCurPos();
        }
        return segmentCurPosIndex;
    }

    private int testForACK(int smallestNotACKedSegmentIndex,DatagramPacket[] segments) throws IOException, ConnectionException {
        while (true) {
            try {
                socket.receive(receiveBuffer);
                if (PacketUtility.isACK(receiveBuffer)) {
                    int nextNotAckedSeq = PacketUtility.getSeq(receiveBuffer);
                    int notAckedseq = PacketUtility.getSeq(segments[smallestNotACKedSegmentIndex]);

                    //received very old ack (out of window), ignore.
                    if(nextNotAckedSeq < (window.base()-1) % MAX_SEQ && nextNotAckedSeq > (window.end() + 1)){
                        System.out.println("ACK DROP1 base " + window.base() + " end " + window.end());
                        continue;
                    }
                    //invalid seq, smth wrong. Ignore.
                    if(nextNotAckedSeq < 0 || nextNotAckedSeq >= MAX_SEQ){
                        System.out.println("ACK DROP2");
                        continue;
                    }
                    //received already acked seq(in window), ignore.
                    if (Math.abs(window.base() - nextNotAckedSeq) < Math.abs(window.base() - notAckedseq)) {
                        System.out.println("ACK DROP3");
                        continue;
                    }

                    //accumulative ack and break while.
                    stopTimer();
                    while (nextNotAckedSeq != notAckedseq) {
                        window.move();
                        notAckedseq = (notAckedseq + 1) % MAX_SEQ;
                        smallestNotACKedSegmentIndex++;
                    }
                    if (segments.length > smallestNotACKedSegmentIndex) {
                        startTimer(segments[smallestNotACKedSegmentIndex]);
                    }
                    break;

                }
            } catch (SocketTimeoutException e) {
                if (numTries >= MAX_TRIES) {
                    throw new ConnectionException("Server does not respond.");
                }
            }
        }
        return smallestNotACKedSegmentIndex;
    }

    public void send(byte[] data) throws IOException, ConnectionException {
        if(!socket.isConnected()){
            throw new PortUnreachableException();
        }
        DatagramPacket[] segments = splitDataIntoPackets(data);
        sendAndACKSegments(segments);
    }

    private DatagramPacket[] splitDataIntoPackets(byte[] data){
        int numPackets = data.length / PacketUtility.MAX_DATA_SIZE_BYTES;
        if(data.length% PacketUtility.MAX_DATA_SIZE_BYTES != 0){
            numPackets++;
        }
        DatagramPacket[] segments = new DatagramPacket[numPackets];
        for (int i = 0; i < numPackets; i++){
            byte[] segmentData;
            if(i == numPackets-1){
                segmentData = Arrays.copyOfRange(data,i* MAX_DATA_SIZE_BYTES,data.length);
            } else {
                segmentData = Arrays.copyOfRange(data,i* MAX_DATA_SIZE_BYTES,(i+1)* MAX_DATA_SIZE_BYTES);
            }
            DatagramPacket s = PacketUtility.makeSegment(DATA,nextSeq, segmentData, connectionAddress,connectionPort);
            increaseSeq();
            segments[i] = s;
        }
        return segments;
    }

    public void closeConnection() throws IOException, ConnectionException {
        DatagramPacket p = PacketUtility.makeSegment(FIN,nextSeq,null,connectionAddress,connectionPort);
        increaseSeq();
        DatagramPacket[] packet = {p};
        sendAndACKSegments(packet);
        System.out.println("Client closed connection.");
    }
    private void increaseSeq(){
    nextSeq = (nextSeq +1) % MAX_SEQ;
    }

    private void startTimer(DatagramPacket segment){
        if(timerRunning){
            throw  new RuntimeException();
        }
        numTries = 0;
        timer = new Timer();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                synchronized (segment){
                    numTries++;
                    try {
                        socket.send(segment);
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                    if(numTries >= MAX_TRIES){
                        stopTimer();
                    }
                }
            }
        }, TCP_TIMEOUT, TCP_TIMEOUT);
        timerRunning = true;
    }

    private void stopTimer(){
        if(timerRunning) {
            timer.cancel();
            timer.purge();
            timerRunning = false;
        }
    }

}

