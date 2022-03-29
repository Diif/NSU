package calculator;

import java.util.HashMap;
import javax.naming.NamingException;

public class ProgramContext {
    HashMap<String, Object> context;

    public ProgramContext(){
        context = new HashMap<String, Object>();
    }

    public void addToEnvironment(String name, Object obj){
        context.put(name,obj);
    }
    public Object lookup(String name) throws NamingException {
        Object obj = context.get(name);
        if(null == obj){
            throw  new NamingException();
        }
        return obj;
    }

}
