#include <complex>

extern "C" unsigned int
mandel_double(double re, double im, unsigned int max_iterations)
{
    std::complex<double> c (re, im);
    std::complex<double> z (0.0, 0.0);
    for (unsigned int i = 0; i < max_iterations; i++)
    {
        if (std::abs(z) > 2) {
            return i + 1;
        }
        z = z * z + c;
    }
    return 0;
}
