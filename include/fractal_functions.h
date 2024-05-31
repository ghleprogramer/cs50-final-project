#ifndef FRACTAL_FUNCTION_H_
#define FRACTAL_FUNCTION_H_

int mandel_fractal(double x, double iy, int n, int maxlength);
int conj_mandel_fractal(double x, double y, int n, int maxlength);
int ship_fractal(double x, double iy, int n, int maxlength);
int conj_ship_fractal(double x, double y, int n, int maxlength);

#endif
