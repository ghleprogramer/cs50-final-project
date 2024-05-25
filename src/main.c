// this program outputs a bmp image for a shosen fractal
// centerd at a given cordenate in given range
// cmake -S. -B build/ --fresh

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "../include/fractal_functions.h"
#include "../include/range_to_list.h"
#include "../include/usage_check.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

typedef struct
{
    uint8_t  rgbtBlue;
    uint8_t  rgbtGreen;
    uint8_t  rgbtRed;
} RGBTRIPLE;

int main(int argc, char *argv[])
{
	usagereturn user_usage;
	int check = usage_conrtol(argc, argv, &user_usage);
	if (check)
	{
		usage_print(check);
		return 1;
	}
	printf("this is the good good fractal creation software made by ghamdi lmt\n");
	
	int n = 2;
	int maxlooplength = user_usage.looplengh;
	int hight = user_usage.yres;
	int width = user_usage.xres;
	double xcenter = user_usage.px;  
	double ycenter = user_usage.py;  
	double range = user_usage.range;

	// Declaration of function pointer variable (thanks gpt)
	int(*fractal_function)(double x, double iy, int n, int maxlength);
	if (user_usage.fractal == 'M')
	{
		fractal_function = mandel_fractal;
	}
	if (user_usage.fractal == 'B')
	{
		fractal_function = ship_fractal;
	}

	double xset_range = range * ((double)width / (double)hight);
	double yset_range = range;
	double *x = centered_rangelist(xcenter, xset_range, width);
	double *y = centered_rangelist(ycenter, yset_range, hight);
	if (x == NULL || y == NULL)
	{
		return 2;
	}

	RGBTRIPLE *img_ary = calloc(hight * width, sizeof(RGBTRIPLE));
	int *escape_ary = calloc(hight * width, sizeof(int));

	int max_escape_val = 0;
	for (int i = 0; i < hight; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int indx = i*width + j;
			escape_ary[indx] = fractal_function(x[j], y[i], n,maxlooplength);
			if (escape_ary[indx] > max_escape_val)
			{
				max_escape_val = escape_ary[indx];
			}
		}
	}

	double color_range[] = {0, 255};
	double *color_array = length_rangelist(color_range, max_escape_val + 1);
	for (int i = 0; i < hight * width; i++)
	{
		int color = round(color_array[escape_ary[i]]);
		img_ary[i].rgbtRed = color;
		img_ary[i].rgbtGreen = color;
		img_ary[i].rgbtBlue = color;
	}

	uint8_t *stb_ary = calloc(hight * width * 3, sizeof(uint8_t));
	int stb_indx = 0;
	for (int i = 0; i < hight * width; i++)
	{
		stb_ary[stb_indx] = img_ary[i].rgbtRed;
		stb_indx++;
		stb_ary[stb_indx] = img_ary[i].rgbtGreen;
		stb_indx++;
		stb_ary[stb_indx] = img_ary[i].rgbtBlue;
		stb_indx++;
	}

	uint8_t *stb_mono_ary = calloc(hight * width, sizeof(uint8_t));
	for (int i = 0; i < hight * width; i++)
	{
		stb_mono_ary[i] = round(color_array[escape_ary[i]]);
	}

	stbi_write_bmp("frct_stb.bmp", width, hight, 3, stb_ary);
	stbi_write_png("frct_stb.png", width, hight, 3, stb_ary, sizeof(RGBTRIPLE) * width);
	stbi_write_png("frct_mono_stb.png", width, hight, 1, stb_mono_ary, sizeof(uint8_t) * width);

	free(stb_mono_ary);
	free(stb_ary);
	free(escape_ary);
	free(img_ary);
	free(y);
	free(x);
	free(color_array);
	return 0;
}

