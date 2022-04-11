package commands;

import calculator.ProgramContext;

import javax.naming.NamingException;
import java.util.HashMap;

public class Define implements Command{
    @Override
    public final void execute(ProgramContext context) {
        String[] args = null;
        HashMap<String, Double> params = null;
        try {
            args = (String[]) context.lookup("args");
            params = (HashMap<String,Double>) context.lookup("params");
        } catch (NamingException e){
            logger.severe("Can't find args/params in context.\n" + e.getLocalizedMessage());
            throw new RuntimeException("No args/params.");
        }
        assert args != null;
        assert params != null;
        params.put(args[1], Double.valueOf(args[2]));
    }
}
