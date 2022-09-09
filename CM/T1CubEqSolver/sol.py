import math
import argparse

a = 0
b = 0
c = 0
epsilon = 0
delta = 100

parser = argparse.ArgumentParser()
args = parser.parse_args()
startPoint(args)


def startPoint( args) :
    try :
        a = Double.parseDouble(args[0])
        b = Double.parseDouble(args[1])
        c = Double.parseDouble(args[2])
        epsilon = Double.parseDouble(args[3])
        delta = Double.parseDouble(args[4])
    except java.lang.Exception as e :
        print("Bad args")
        System.exit(0)
    discriminant = calculateDiscriminant(a, b)
    if (abs(discriminant) < epsilon) :
        valInZero = calculateFun(0)
        if (valInZero < 0) :
            findRightRoot()
        elif(valInZero > 0) :
            findLeftRoot()
        else :
            printResultAndEnd(1, 0, 0)

def findRightRoot() :
    left = 0
    right = 100
    while (calculateFun(right) < 0) :
        right += delta
    middle = 0.0
    val = 0.0
    while True :
        middle = (left + right) / 2
        val = calculateFun(middle)
        if (val > 0) :
            right = middle
        else :
            left = middle
        if((abs(val) > epsilon) == False) :
                break
    printResultAndEnd(1, middle, 0)

def findLeftRoot() :
    left = -100
    right = 0
    while (calculateFun(left) > 0) :
        left -= delta
    middle = 0.0
    val = 0.0
    while True :
        middle = (left + right) / 2
        val = calculateFun(middle)
        if (val > 0) :
            right = middle
        else :
            left = middle
        if((abs(val) > epsilon) == False) :
                break
    printResultAndEnd(1, middle, 0)

def  calculateDiscriminant( a,  b) :
    return 2 * 2 * a * a - 4 * 3 * b

def  calculateFun( x) :
    return x * x * x + a * x * x + b * x + c

def printResultAndEnd( countRoots,  root1,  root2) :
    if (countRoots == 1) :
        print("1 Koren`: " + str(root1))
    else :
        print("2 Korenya: " + str(root1) + str(root2))
    System.exit(0)
