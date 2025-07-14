//
// Created by christian on 7/4/25.
//

#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H
#include "ChrisMath.h"

class funct {
public:
    //taylor series
    static double sine(double a);

    static double cosine(double a);

    static double tangent(double a);

    static double arcSine(double a);

    static double arcCosine(double a);

    static double arcTangent(double a);

    static double natLog(double a);

    static double expon(double a);

    static double power(double a, double b);

    static double ePower(double a, double b);

    static double squareRoot(double a, double epsilon = 1e-5);

    static double factorial(double a);

    static double PI();

    static bool isInteger(double a);

    static int abs(int a);

    static double dabs(double a);

    static double round(double a);

    static double floor(double a);

    static double ceil(double a);

    static double radToDeg(double a);

    static double degToRad(double a);
};


#endif //MATHFUNCTIONS_H