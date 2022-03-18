import commands.Test;

public class Main {
    public static void main(String[] args) {
        Class c1 = null;
        Test comma = null;
        try {
             c1 = Class.forName("commands.Test");
        } catch (ClassNotFoundException e){
            System.err.println("Not found");
        }
        System.out.println(c1.toString() + " pack " + c1.getPackageName() + " name " + c1.getName());
        try{
             comma = (Test)c1.newInstance();
        }catch (Throwable e){

        }
        comma.sayHi();
    }
}
