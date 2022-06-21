package utilities;

import tcpsocket.SegmentException;

import java.net.DatagramPacket;
import java.net.InetAddress;
import java.nio.ByteBuffer;
import java.util.Arrays;

public class PacketUtility {
    public final static int MAX_DATA_SIZE_BYTES = 8;
    public final static int HEADER_SIZE = Byte.BYTES + Integer.BYTES;
    public final static int MAX_SEGMENT_SIZE_BYTES = MAX_DATA_SIZE_BYTES + HEADER_SIZE;
    public final static byte DATA= 0b00000000;
    public final static byte ACK = 0b00000001;
    public final static byte SYN = 0b00000010;
    public final static byte FIN = 0b00000100;

    public static DatagramPacket makeSegment(byte type, int seq, byte[] data, InetAddress destAddr, int destPort) throws SegmentException {
        int len = HEADER_SIZE;
        if(null != data) {
            len += data.length;
        }
        if(len > MAX_SEGMENT_SIZE_BYTES){
            throw new SegmentException("Too much data for segment.");
        }
        if(null != data) {
            data = ByteBuffer.allocate(len).put(type).putInt(seq).put(data).array();
        } else {
            data = ByteBuffer.allocate(len).put(type).putInt(seq).array();
        }
        return new DatagramPacket(data, data.length, destAddr,destPort);
    }

    public static boolean isACK(DatagramPacket p){
        return (p.getData()[0] & ACK) == ACK;
    }
    public static boolean isSYN(DatagramPacket p){
        return (p.getData()[0] & SYN) == SYN;
    }
    public static boolean isFIN(DatagramPacket p){
        return (p.getData()[0] & FIN) == FIN;
    }

    public static int getSeq(DatagramPacket p){
        final int SEQ_START_POS = 1;
        byte[] data= p.getData();
        return getIntFromData(data, SEQ_START_POS);
    }

    public static byte[] getData(DatagramPacket p){
        byte[] packetData = p.getData();
        return Arrays.copyOfRange(packetData,HEADER_SIZE, packetData.length);
    }

    public static int getIntFromData(byte[] data, final int startByteIndex){
        final int END = startByteIndex + 3;
        if(END >= data.length){
            System.err.println("Data size: " + data.length + " is less than END size:" + END);
        }
        int res = 0;
        for(int i = startByteIndex; i <= END; i++){
            res = (res << 8) + (data[i] & 0xFF);
        }
        return res;
    }
}
