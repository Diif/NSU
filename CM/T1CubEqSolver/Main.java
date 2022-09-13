public class Main {

    static double a=0;
    static double b=0;
    static double c=0;
    static double epsilon=0;
    static double delta=100;

    public static void main(String[] args) {
        initVars(args);

        double discriminant = calculateDiscriminant(a,b);

        if(Math.abs(discriminant) < epsilon || discriminant < 0) {
            oneRootCase();
        }else {
            twoRootCase(discriminant);
        }

    }

    private static void twoRootCase(double discriminant){
        double extremum1 = ((-2*a) - Math.sqrt(discriminant)) / (6);
        double extremum2 = ((-2*a) + Math.sqrt(discriminant)) / (6);

        double point1 = calculateFun(extremum1);
        double point2 = calculateFun(extremum2);
        double point1Abs = Math.abs(point1);
        double point2Abs = Math.abs(point2);

        if(point1Abs < epsilon && point2Abs < epsilon){
            printResultAndEnd(2, extremum1,extremum2,0);
        }
        if(point1Abs < epsilon){
            printResultAndEnd(2, findRightRoot(extremum1), extremum1,0);
        }
        if(point2Abs < epsilon){
            printResultAndEnd(2, findLeftRoot(extremum2), extremum2,0);
        }
        if(point1 < 0 && point2 < 0){
            printResultAndEnd(1, findRightRoot(extremum2), 0,0);
        }
        if(point1 > 0 && point2 > 0){
            printResultAndEnd(1, findLeftRoot(extremum1), 0,0);
        }
        printResultAndEnd(3, findLeftRoot(extremum1),findRootInBorders(extremum1,extremum2), findRightRoot(extremum2));


    }
    private static void oneRootCase(){
        double valInZero = calculateFun(0);
        if(valInZero < 0){
            printResultAndEnd(1,findRightRoot(0),0,0);
        }else if(valInZero > 0){
            printResultAndEnd(1,findLeftRoot(0),0,0);
        } else {
            printResultAndEnd(1,0,0,0);
        }
    }

    private static double findRootInBorders(double border1, double border2){
        double left = border1, right = border2;

        if(calculateFun(border1) <=0 || calculateFun(border2) >= 0 || border1 >= border2){
            System.out.println("internal error");
            System.exit(0);
        }

        double middle, val;
        do {
            middle = (left+right) / 2;
            val = calculateFun(middle);
            if(val > 0){
                left = middle;
            } else {
                right = middle;
            }
        }
        while (Math.abs(val) > epsilon);

        return middle;
    }
    private static double findRightRoot(double zeroPoint){
        double left = zeroPoint, right = epsilon*10 + delta;

        while (calculateFun(right) < 0){
            right+=delta;
        }


        double middle, val;
        do {
            middle = (left+right) / 2;
            val = calculateFun(middle);
            if(val > 0){
                right = middle;
            } else {
                left = middle;
            }
        }
        while (Math.abs(val) > epsilon);

        return middle;
    }

    private static double findLeftRoot(double zeroPoint){
        double left = -epsilon*10 - delta, right = zeroPoint;

        while (calculateFun(left) > 0){
            left-=delta;
        }


        double middle, val;
        do {
            middle = (left+right) / 2;
            val = calculateFun(middle);
            if(val > 0){
                right = middle;
            } else {
                left = middle;
            }
        }
        while (Math.abs(val) > epsilon);

        return middle;
    }

    private static double calculateDiscriminant(double a, double b){
        return 2*2*a*a - 4*3*b;
    }

    private static double calculateFun(double x){
        return x*x*x + a*x*x + b*x + c;
    }

    private static void printResultAndEnd(int countRoots, double root1, double root2, double root3){
        if(countRoots == 1){
            System.out.println("1 Корень: " + root1);
        } else if(countRoots == 2){
            System.out.println("2 Корня: " + root1 + " и " + root2);
        } else {
            System.out.println("3 Корня: " + root1 + " и " + root2 + " и " + root3);
        }
        System.exit(0);
    }

    private static void initVars(String[] args){
        try {
            a = Double.parseDouble(args[0]);
            b = Double.parseDouble(args[1]);
            c = Double.parseDouble(args[2]);
        } catch (Exception e){
            System.out.println("Bad args");
            System.exit(0);
        }
        try {
            epsilon = Double.parseDouble(args[3]);
            delta = Double.parseDouble(args[4]);
        } catch (Exception e){
            epsilon = 0.001;
            delta = 10;
        }
        if(epsilon <= 0 || delta <= 0){
            System.out.println("Bad args");
            System.exit(0);
        }
    }

}
