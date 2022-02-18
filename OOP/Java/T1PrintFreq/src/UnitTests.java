import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertEquals;

public class UnitTests {
    Handler handler;

    @Test
    void exceptionTesting(){
        handler = new Handler("test132.txt");
    Throwable exc = assertThrows(NullPointerException.class,() -> handler.collectStatisticFromFile());
    assertEquals("Cannot invoke \"java.util.Scanner.hasNextLine()\" because \"this.fileScanner\" is null", exc.getMessage());
    }
}
