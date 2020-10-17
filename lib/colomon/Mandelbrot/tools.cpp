#include <complex>
#include <stdio.h>

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

unsigned char color_map [] = {
    0, 0, 252,
    64, 0, 252,
    124, 0, 252,
    188, 0, 252,
    252, 0, 252,
    252, 0, 188,
    252, 0, 124,
    252, 0, 64,
    252, 0, 0,
    252, 64, 0,
    252, 124, 0,
    252, 188, 0,
    252, 252, 0,
    188, 252, 0,
    124, 252, 0,
    64, 252, 0,
    0, 252, 0,
    0, 252, 64,
    0, 252, 124,
    0, 252, 188,
    0, 252, 252,
    0, 188, 252,
    0, 124, 252,
    0, 64, 252,
    124, 124, 252,
    156, 124, 252,
    188, 124, 252,
    220, 124, 252,
    252, 124, 252,
    252, 124, 220,
    252, 124, 188,
    252, 124, 156,
    252, 124, 124,
    252, 156, 124,
    252, 188, 124,
    252, 220, 124,
    252, 252, 124,
    220, 252, 124,
    188, 252, 124,
    156, 252, 124,
    124, 252, 124,
    124, 252, 156,
    124, 252, 188,
    124, 252, 220,
    124, 252, 252,
    124, 220, 252,
    124, 188, 252,
    124, 156, 252,
    180, 180, 252,
    196, 180, 252,
    216, 180, 252,
    232, 180, 252,
    252, 180, 252,
    252, 180, 232,
    252, 180, 216,
    252, 180, 196,
    252, 180, 180,
    252, 196, 180,
    252, 216, 180,
    252, 232, 180,
    252, 252, 180,
    232, 252, 180,
    216, 252, 180,
    196, 252, 180,
    180, 252, 180,
    180, 252, 196,
    180, 252, 216,
    180, 252, 232,
    180, 252, 252,
    180, 232, 252,
    180, 216, 252,
    180, 196, 252,
    0, 0, 112,
    28, 0, 112,
    56, 0, 112,
    84, 0, 112,
    112, 0, 112,
    112, 0, 84,
    112, 0, 56,
    112, 0, 28,
    112, 0, 0,
    112, 28, 0,
    112, 56, 0,
    112, 84, 0,
    112, 112, 0,
    84, 112, 0,
    56, 112, 0,
    28, 112, 0,
    0, 112, 0,
    0, 112, 28,
    0, 112, 56,
    0, 112, 84,
    0, 112, 112,
    0, 84, 112,
    0, 56, 112,
    0, 28, 112,
    56, 56, 112,
    68, 56, 112,
    84, 56, 112,
    96, 56, 112,
    112, 56, 112,
    112, 56, 96,
    112, 56, 84,
    112, 56, 68,
    112, 56, 56,
    112, 68, 56,
    112, 84, 56,
    112, 96, 56,
    112, 112, 56,
    96, 112, 56,
    84, 112, 56,
    68, 112, 56,
    56, 112, 56,
    56, 112, 68,
    56, 112, 84,
    56, 112, 96,
    56, 112, 112,
    56, 96, 112,
    56, 84, 112,
    56, 68, 112,
    80, 80, 112,
    88, 80, 112,
    96, 80, 112,
    104, 80, 112,
    112, 80, 112,
    112, 80, 104,
    112, 80, 96,
    112, 80, 88,
    112, 80, 80,
    112, 88, 80,
    112, 96, 80,
    112, 104, 80,
    112, 112, 80,
    104, 112, 80,
    96, 112, 80,
    88, 112, 80,
    80, 112, 80,
    80, 112, 88,
    80, 112, 96,
    80, 112, 104,
    80, 112, 112,
    80, 104, 112,
    80, 96, 112,
    80, 88, 112,
    0, 0, 64,
    16, 0, 64,
    32, 0, 64,
    48, 0, 64,
    64, 0, 64,
    64, 0, 48,
    64, 0, 32,
    64, 0, 16,
    64, 0, 0,
    64, 16, 0,
    64, 32, 0,
    64, 48, 0,
    64, 64, 0,
    48, 64, 0,
    32, 64, 0,
    16, 64, 0,
    0, 64, 0,
    0, 64, 16,
    0, 64, 32,
    0, 64, 48,
    0, 64, 64,
    0, 48, 64,
    0, 32, 64,
    0, 16, 64,
    32, 32, 64,
    40, 32, 64,
    48, 32, 64,
    56, 32, 64,
    64, 32, 64,
    64, 32, 56,
    64, 32, 48,
    64, 32, 40,
    64, 32, 32,
    64, 40, 32,
    64, 48, 32,
    64, 56, 32,
    64, 64, 32,
    56, 64, 32,
    48, 64, 32,
    40, 64, 32,
    32, 64, 32,
    32, 64, 40,
    32, 64, 48,
    32, 64, 56,
    32, 64, 64,
    32, 56, 64,
    32, 48, 64,
    32, 40, 64,
    44, 44, 64,
    48, 44, 64,
    52, 44, 64,
    60, 44, 64,
    64, 44, 64,
    64, 44, 60,
    64, 44, 52,
    64, 44, 48,
    64, 44, 44,
    64, 48, 44,
    64, 52, 44,
    64, 60, 44,
    64, 64, 44,
    60, 64, 44,
    52, 64, 44,
    48, 64, 44,
    44, 64, 44,
    44, 64, 48,
    44, 64, 52,
    44, 64, 60,
    44, 64, 64,
    44, 60, 64,
    44, 52, 64,
    44, 48, 64
};

struct Color
{
    unsigned short red;
    unsigned short green;
    unsigned short blue;
};

extern "C" unsigned int
get_color_part (unsigned int color, unsigned int part)
{
    return color_map [color * 3 + part];
}

extern "C" struct Color
get_color (unsigned int index)
{
    struct Color value;
    value.red = color_map [index * 3 + 0];
    value.green = color_map [index * 3 + 1];
    value.blue = color_map [index * 3 + 2];
    return value;
}

extern "C" struct Color
linear_blend_color (unsigned int color1, unsigned int color2, double t)
{
    struct Color low = get_color (color1);
    struct Color high = get_color (color2);
    struct Color value;
    value.red = low.red + t * (high.red - low.red);
    value.green = low.green + t * (high.green - low.green);
    value.blue = low.blue + t * (high.blue - low.blue);
    return value;
}

extern "C" struct Color
log_color(unsigned int pixel)
{
    double log_pixel = log(pixel) / log(2);
    double low = floor(log_pixel);
    unsigned int high = low + 1;
    double fraction = log_pixel - low;
    return linear_blend_color (low, high, fraction);
}

extern "C" void
modified_log_color_c (unsigned int pixel, unsigned int *red, unsigned int *green, unsigned int *blue)
{
    struct Color color;
    if (pixel < 64)
    {
        unsigned int remainder = pixel % 16;
        unsigned int low = pixel / 16;
        unsigned int high = low + 1;
        double fraction = (1.0 / 16.0) * (double) remainder;
        color = linear_blend_color (low, high, fraction);
    }
    else
    {
        double log_pixel = log(pixel) / log(sqrt(2)) - 8;
        // printf ("pixel = %d  log_pixel = %g\n", pixel, log_pixel);
        double low = floor(log_pixel);
        unsigned int high = low + 1;
        double fraction = log_pixel - low;
        color = linear_blend_color (low, high, fraction);
    }
    *red = color.red;
    *green = color.green;
    *blue = color.blue;
    // printf ("red = %d green = %d blue = %d\n", *red, *green, *blue);
}

