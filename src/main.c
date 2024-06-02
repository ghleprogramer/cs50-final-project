// a program for creating fractal images

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
	// F fractal, Q quality, P power, M max iteration, C center, R range, J conjugate, H help
	char *options = "F:Q:P:M:C:R:HhJ";
	usage *intput = malloc(sizeof(usage)); // struct holds user options
	char check = prase(argc, argv, options, intput);
	if (check != '0') {
		check_func(check);
		exit(1);
	}

	printf("this is the good good fractal creation software made by ghamdi lmt\n");
	
	// image and fractal values from usage struct
	int hight = intput->h;
	int width = intput->w;
	char fractal = intput->f;
	int n = intput->p;
	int maxlooplength = intput->m;
	double xcenter = intput->xc;  
	double ycenter = intput->yc;
	double range = intput->r;
	int conj = intput->conj;
	free(intput);

	// Declaration of function pointer variable (thanks gpt)
	int(*fractal_function)(double x, double iy, int n, int maxlength);
	// chosing fractal function
	if (fractal == 'M' && conj) {
		fractal_function = conj_mandel_fractal;
	} else if (fractal == 'M') {
		fractal_function = mandel_fractal;
	} else if (fractal == 'B' && conj) {
		fractal_function = conj_ship_fractal;
	} else if (fractal == 'B') {
		fractal_function = ship_fractal;
	}

	// image ratio normalised x and y complex plane value sets
	double xset_range = range * ((double)width / (double)hight);
	double yset_range = range;
	double *x = centered_rangelist(xcenter, xset_range, width);
	double *y = centered_rangelist(ycenter, yset_range, hight);
	if (x == NULL || y == NULL) {
		printf("not enough space in memory");
		exit(2);
	}

	// escape array holds the number of itertions for each x,y value to escape
	int *escape_ary = calloc(hight * width, sizeof(int));
	if (escape_ary == NULL) {
		printf("not enough space in memory");
		exit(4);
	}

	// running the fractal function on all x,y values and storing them 
	for (int i = 0; i < hight; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int indx = i*width + j;
			escape_ary[indx] = fractal_function(x[j], y[i], n,maxlooplength);
		}
	}

	// grayscale image data array writen by color function
	uint8_t *stb_ary = norm_escape_stb(hight, width, escape_ary);
	if (stb_ary == NULL) {
		printf("not enough space in memory");
		exit(5);
	}
	// black and white image data array writen by color function
	uint8_t *stb_mono_ary = escape_stb_mono(hight, width, escape_ary);
	if (stb_mono_ary == NULL) {
		printf("not enough space in memory");
		exit(6);
	}

	// writing the images via the stb image library(stb_image_write.h)
	stbi_write_bmp("frct_stb.bmp", width, hight, 3, stb_ary);
	// stbi_write_bmp("frct_mono_stb.bmp", width, hight, 1, stb_mono_ary); // not different enough to save
	stbi_write_png("frct_stb.png", width, hight, 3, stb_ary, sizeof(uint8_t) * 3 * width);
	stbi_write_png("frct_mono_stb.png", width, hight, 1, stb_mono_ary, sizeof(uint8_t) * width);

	free(stb_mono_ary);
	free(stb_ary);
	free(escape_ary);
	free(y);
	free(x);

	return 0;
}
