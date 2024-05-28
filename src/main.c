// this program outputs a bmp image for a shosen fractal
// centerd at a given cordenate in given range
// cmake -S. -B build/ --fresh
// cd build/ && make && cd .. && ./fractal_gen

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "../include/fractal_functions.h"
#include "../include/range_to_list.h"
#include "../include/color_functions.h"
#include "../include/usage.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

int main(int argc, char **argv)
{
	// F fractal, Q quality, P power, M max iteration, C center, R range
	char *options = "F:Q:P:M:C:R:";
	usage *usage;
	char check = prase(argc, argv, options, usage);
	if (check != '0') {
		check_func(check);
		return 1;
	}

	printf("this is the good good fractal creation software made by ghamdi lmt\n");
	
	int hight = usage->h;
	int width = usage->w;
	char fractal = usage->f;
	int n = usage->p;
	int maxlooplength = usage->m;
	double xcenter = usage->xc;  
	double ycenter = usage->yc;  
	double range = usage->r;

	// Declaration of function pointer variable (thanks gpt)
	int(*fractal_function)(double x, double iy, int n, int maxlength);
	if (fractal == 'M') {
		fractal_function = mandel_fractal;
	} else if (fractal == 'B') {
		fractal_function = ship_fractal;
	}

	double xset_range = range * ((double)width / (double)hight);
	double yset_range = range;
	double *x = centered_rangelist(xcenter, xset_range, width);
	double *y = centered_rangelist(ycenter, yset_range, hight);
	if (x == NULL || y == NULL) {
		printf("not enough space in memory");
		return 2;
	}

	int *escape_ary = calloc(hight * width, sizeof(int));
	if (escape_ary == NULL) {
		printf("not enough space in memory");
		return 3;
	}

	for (int i = 0; i < hight; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int indx = i*width + j;
			escape_ary[indx] = fractal_function(x[j], y[i], n,maxlooplength);
		}
	}

	uint8_t *stb_ary = norm_escape_stb(hight, width, escape_ary);
	if (stb_ary == NULL) {
		printf("not enough space in memory");
		return 5;
	}

	uint8_t *stb_mono_ary = escape_stb_mono(hight, width, escape_ary);
	if (stb_mono_ary == NULL) {
		printf("not enough space in memory");
		return 6;
	}

	stbi_write_bmp("frct_stb.bmp", width, hight, 3, stb_ary);
	stbi_write_bmp("frct_mono_stb.bmp", width, hight, 1, stb_mono_ary);
	stbi_write_png("frct_stb.png", width, hight, 3, stb_ary, sizeof(uint8_t) * 3 * width);
	stbi_write_png("frct_mono_stb.png", width, hight, 1, stb_mono_ary, sizeof(uint8_t) * width);

	free(stb_mono_ary);
	free(stb_ary);
	free(escape_ary);
	free(y);
	free(x);
	return 0;
}