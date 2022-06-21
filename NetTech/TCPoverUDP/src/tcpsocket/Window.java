package tcpsocket;

public class Window {
    private final int maxSeq;

    private int windowBase;
    private int windowEnd;
    private int windowCurPos;

    public Window(int maxSeq, int windowsBase, int windowEnd){
        this.maxSeq = maxSeq;
        this.windowBase = windowsBase;
        this.windowEnd = windowEnd;
        windowCurPos = windowsBase;
    }

    public int end(){
        return windowEnd;
    }

    public int curPos(){
        return windowCurPos;
    }

    public int base(){
        return windowBase;
    }

    public void move(){
        windowBase = (windowBase + 1) % maxSeq;
        windowEnd = (windowEnd + 1) % maxSeq;
    }

    public void increaseWindowCurPos(){
        windowCurPos = (windowCurPos + 1) % maxSeq;
    }
}
