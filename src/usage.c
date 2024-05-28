#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#include "../include/usage.h"

#define fractal_case 'F'
#define quality_case 'Q'
#define range_case 'R'
#define center_case 'C'
#define power_case 'P'
#define max_iter_case 'M'

char prase(int argc, char **argv, char *options, usage *usage)
{
	// defaults
	usage->f = 'B';
	usage->h = 1080;
	usage->w = 1920;
	usage->p = 2;
	usage->xc  = -0.6;
	usage->yc = 0;
	usage->r = 4;
	usage->m = 100;

	char check;
	int opt;
	while ((opt = getopt(argc, argv, options)) != -1)
	{
		check = prase_switch(opt, usage);
		if (check != '0') {
			return check;
		}
	}
	return check;
}

char prase_switch(int opt, usage *usage)
{
	char check = '0'; // succes
	
	switch (opt)
	{
	case fractal_case:
		if (!strstr(" m M B b", optarg) || strlen(optarg) > 2)
		{
			return fractal_case;
		}
		// if option arg starts with space " arg"
		int optarg_indx = 0;
		if (isblank(optarg[0]))
			optarg_indx = 1;
		usage->f = toupper(optarg[optarg_indx]);
		break;

	case power_case:
		usage->p = (int)strtol(optarg, NULL, 10);
		if (usage->p < 1)
			return power_case;
		if (usage->p > 9) {
			printf("fractal function power has been set to %i if it is a mistake the program can be terminated by ctrl+c\n", usage->p);
		}
		break;

	case range_case:
		usage->r = strtod(optarg, NULL);
		if (usage->r < 1)
			return range_case;
		break;

	case center_case:
		// array to hold x and y centers as strings 
		char *xycent_vals[2];
		int cent_vals_indx = 0;
		// getting the values by the getsubopt
		char *token[] = {NULL};
		char *value;
		while (*optarg != '\0')
		{
			if (cent_vals_indx > 1)// too many sub options
				return center_case;
			getsubopt(&optarg, token, &value);
			// memory allocation for and copying of sub option
			xycent_vals[cent_vals_indx] = calloc(strlen(value) + 1, sizeof(char));
			strcpy(xycent_vals[cent_vals_indx], value);
			cent_vals_indx++;
		}
		
		char **check_ptr = malloc(strlen(xycent_vals[0]) + strlen(xycent_vals[1]));
		// input check
		// strtod return documentation from https://manual.cs50.io/3/strtod
		// If no conversion is performed, zero is returned and (unless endptr is null)
		// the value of nptr is stored in the location referenced by endptr.
		usage->xc = strtod(xycent_vals[0], check_ptr);
		if (usage->xc == 0 && !strcmp(*check_ptr, xycent_vals[0]))
			return center_case;
		
		usage->yc = strtod(xycent_vals[1], check_ptr);
		if (usage->yc == 0 && !strcmp(*check_ptr, xycent_vals[1]))
			return center_case;

		free(xycent_vals[0]);
		free(xycent_vals[1]);
		free(check_ptr);
		break;

	case max_iter_case:
		usage->m = strtod(optarg, NULL);
		if (usage->m < 1)
			return max_iter_case;
		break;

	case quality_case:
		int optarg_len = strlen(optarg);
		if (!strstr(" ed ED hd HD 4k 4K 8k 8K", optarg)
			|| optarg_len > 3 || optarg_len == 1)
			return quality_case;

		int optarg_val = 0;
		for (int i = 0; i < optarg_len; i++)
		{
			if(!isblank(optarg[i]))
				optarg_val += toupper(optarg[i]);
		}

		switch (optarg_val)
		{
		case 'E'+'D':
			usage->h = 720;
			usage->w = 1280;
			break;
		
		case 'H'+'D':
			usage->h = 1080;
			usage->w = 1920;
			break;

		case '4'+'K':
			usage->h = 3840;
			usage->w = 2160;
			break;

		case '8'+'K':
			usage->h = 7680;
			usage->w = 4320;
			break;

		default:
			return quality_case;
			break;
		}
		break;

	case '?':
		return '1';
		break;

	default:
		break;
	}

	return check;
}

void check_func(char c)
{
	switch (c)
	{
	case '1':
		break;

	case fractal_case:
		printf("invaled fractal -F M, B\n");
		break;
	
	case power_case:
		printf("invaled power -P pos num\n");
		break;

	case range_case:
		printf("invaled range -R pos num\n");
		break;

	case max_iter_case:
		printf("invaled number of iterations -M pos num\n");
		break;

	case center_case:
		printf("invaled center -C num,num\n");
		break;

	case quality_case:
		printf("invaled quality -Q ED, HD, 4K, 8K\n");
		break;

	default:
		break;
	}
	return;
}