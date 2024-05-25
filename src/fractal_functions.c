#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define mandelbrot_EscapeValue 2
#define burningship_EscapeValue 60

int mandel_fractal(double x, double y, int n, int maxlength)
{    
	double complex c = x + I*y;
	double complex z = c;
	for (int i = 1; i < maxlength; i++)
	{
		if (cabs(z) > mandelbrot_EscapeValue)
		{
			return i;
		}
        z = cpow(z, n) + c;
	}
	return 0;
}

int ship_fractal(double x, double y, int n, int maxlength)
{
	double complex c = x + I*y;
	double complex z = c;
	for (int i = 1; i < maxlength; i++)
	{
		if (cabs(z) > burningship_EscapeValue)
		{
			return i;
		}
        z = cpow(fabs(creal(z)) + I*fabs(cimag(z)), n) + c;
	}
	return 0;    
}
