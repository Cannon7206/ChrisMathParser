//
// Created by christian on 7/4/25.
//

#include "funct.h"
#include <iostream>


bool isEven(const int a) {
    return a % 2 == 0;
}

double funct::PI() {
    return 3.141592653589793;
}

int funct::abs(const int a) {
    return a > 0 ? a : -a;
}

double funct::dabs(const double a) {
    return a > 0 ? a : -a;
}

double funct::round(const double a) {
    return floor(a + 0.5);
}

double funct::floor(const double a) {
    return static_cast<int>(a);
}

double funct::ceil(const double a) {
    if (floor(a) == a) return a;
    if (a > 0) return floor(a) + 1;
    else return floor(a);
}

bool funct::isInteger(const double a) {
    return funct::floor(a) == a;
}

double funct::expon(const double a) {
    if (a == 0) {
        return 1;
    } else {
        double result = 0;
        for (int k = 0; k < 25; k++) {
            const double term = power(a, k) / factorial(k);
            result += term;
        }
        return result;
    }
}

double funct::pExpon(const double a) {
    if (a == 0) {
        return 1;
    } else {
        double result = 0;
        for (int k = 0; k < 25; k++) {
            const double term = power(a, k) / factorial(k);
            result += term;
        }
        return result;
    }
}

double funct::factorial(const double a) {
    if (funct::isInteger(a) == true) {
        int result = 1;
        for (int i = 1; i <= a; i++) {
            result = result * i;
        }
        return result;
    } else {
        std::cout << "error, number is not a fraction" << std::endl;
        return 0;
    }
}

double funct::squareRoot(const double a, const double epsilon) {
    if (a < 0) {
        std::cout << "error, number is negative" << std::endl;
        return 0;
    } else if (a == 0) {
        return 0;
    } else if (a == 1) {
        return 1;
    } else {
        double guess = a / 2;
        while (dabs(a - guess) > epsilon) {
            const double newGuess = 0.5 * (guess + a / guess);
            guess = newGuess;
        }
        return guess;
    }
}

double funct::power(const double a, const double b) {
    if (b == 0) return 1;
    if (a == 0) return 0;
    double result = 1;
    const double exponent = dabs(b);
    if (!isInteger(b)) {
        if (b <= 0) throw std::domain_error("error, number is negative");
        result = pExpon(b * pNatLog(a));
    } else
        for (int i = 0; i < exponent; ++i) {
            result *= a;
        }
    if (b < 0) return 1.0 / result;
    return result;
}

double funct::degToRad(const double a) {
    return a * PI() / 180;
}

double funct::radToDeg(const double a) {
    return a * 180 / PI();
}

double funct::sine(const double a) {
    double radian = degToRad(a);
    while (radian > PI()) {
        radian -= 2 * PI();
    }
    while (radian < -PI()) {
        radian += 2 * PI();
    }
    double result = 0;
    for (int i = 0; i < 10; ++i) {
        const double term = power(-1, i) * power(radian, 2 * i + 1) / factorial(2 * i + 1);
        result += term;
    }
    return result;
}

double funct::cosine(const double a) {
    double radian = degToRad(a);
    while (radian > PI()) {
        radian -= 2 * PI();
    }
    while (radian < -PI()) {
        radian += 2 * PI();
    }
    double result = 0;
    for (int i = 0; i < 10; ++i) {
        const double term = power(-1, i) * power(radian, 2 * i) / factorial(2 * i);
        result += term;
    }
    return result;
}

double funct::tangent(const double a) {
    double radian = degToRad(a);
    while (radian > PI() / 2) {
        radian -= PI();
    }
    while (radian < -PI() / 2) {
        radian += PI();
    }
    return sine(radian) / cosine(radian);
}

double funct::arcSine(double a) {
    if (a > -1 || a < 1) {
        double result = 0;
        for (int i = 0; i < 10; ++i) {
            const double term = (factorial(2 * i) / (power(4, i) * power(factorial(i), 2) * (2 * i + 1))) * power(
                                    a, 2 * i + 1);
            result += term;
        }
        return result;
    } else throw std::domain_error("error, number is out of bound");
}

double funct::arcCosine(double a) {
    if (a > -1 || a < 1) {
        return PI() / 2 - arcSine(a);
    } else throw std::domain_error("error, number is out of bound");
}

double funct::arcTangent(const double a) {
    if (a > -1 || a < 1) {
        double result = 0;
        for (int i = 0; i < 10; ++i) {
            const double term = power(-1, i) * power(a, 2 * i + 1) / (2 * i + 1);
            result += term;
        }
        return result;
    } else throw std::domain_error("error, number is out of bound");
}

double funct::natLog(const double a) {
    if (a <= 0) {
        throw std::domain_error("error, number is out of bound");
    }
    double y = (a - 1) / (a + 1);
    double result = 0;
    for (int i = 0; i < 20; ++i) {
        const double term = power(y, 2 * i + 1) / (2 * i + 1);
        result += term;
    }
    return 2 * result;
}

double funct::pNatLog(const double a) {
    if (a <= 0) {
        throw std::domain_error("error, number is out of bound");
    }
    double y = (a - 1) / (a + 1);
    double result = 0;
    for (int i = 0; i < 20; ++i) {
        const double term = power(y, 2 * i + 1) / (2 * i + 1);
        result += term;
    }
    return 2 * result;
}
