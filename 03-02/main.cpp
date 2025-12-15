#include <cstdio>
#include "Test.h"

int main() {

    Test<int, int>         t1(10, 20);
    Test<float, float>     t2(3.5f, 2.0f);
    Test<double, double>   t3(9.0, 9.1);

    Test<int, float>       t4(7, 7.2f);
    Test<int, double>      t5(100, 12.34);
    Test<float, double>    t6(0.25f, 0.1);

    std::printf("Min(int,int)       = %g\n", (double)t1.Min());
    std::printf("Min(float,float)   = %g\n", (double)t2.Min());
    std::printf("Min(double,double) = %g\n", (double)t3.Min());

    std::printf("Min(int,float)     = %g\n", (double)t4.Min());
    std::printf("Min(int,double)    = %g\n", (double)t5.Min());
    std::printf("Min(float,double)  = %g\n", (double)t6.Min());

    return 0;
}
