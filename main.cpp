#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <cilk/reducer_opadd.h>
#include <iostream>

#include <vector>

double integral(std::function<double(double)> f, double from, double to, double step)
{
    cilk::reducer_opadd<double> S(0);
    int steps = (to - from) / step;
	cilk_for(int i = 0; i < steps; i++)
	{
        double x = from + i * step;
		S += f(x);
    }
    return S.get_value() * step;
}


int main()
{
    std::function <double(double)> f = [] (double x) {return 6.0 / (sqrt(x * (2.0 - x)));};
    std::cout << integral(f, 0.5, 1, 0.00s01) << std::endl;

	return 0;
}