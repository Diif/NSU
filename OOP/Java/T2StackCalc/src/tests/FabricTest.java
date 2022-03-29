package tests;

import calculator.Fabric;
import commands.Command;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

import java.util.HashMap;

public class FabricTest {
    @Test
    public void testMethods(){
        Fabric fabric = new Fabric("src/tests/config.conf");
        HashMap<String, Command> map = fabric.createCommandsMap();
        assertEquals(9, map.size());
        assertTrue(map.containsKey("+"));
        assertTrue(map.containsKey("DEFINE"));
        assertTrue(map.containsKey("/"));
        assertTrue(map.containsKey("*"));
        assertTrue(map.containsKey("PRINT"));
        assertTrue(map.containsKey("PUSH"));
        assertTrue(map.containsKey("SQRT"));
        assertTrue(map.containsKey("-"));
        assertTrue(map.containsKey("#"));
    }


}