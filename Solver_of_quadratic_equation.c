#include <stdio.h>
#include <math.h>
#include <assert.h>

#define ZERO 0 
#define NUMBER_OF_TESTS 15

#define DEBUG_MODE

const double deviation = 1E-6;

//================================================================

int is_number(double value, double number);

int quadratic_equation(double a, double b, double c, double* x_1, double* x_2);

void output(int roots, double* x_1, double* x_2);

int unit_test();

int manual_test();

//================================================================

int main()
	{
	#ifdef DEBUG_MODE
		unit_test();
	#else 
		manual_test();
	#endif
	}

//================================================================

int is_number(double value, double number)
	{
	return (fabs(value-number) <= deviation);
	}

//================================================================
	
int quadratic_equation(double a, double b, double c, double* x_1, double* x_2)
	{
		//assert(x_1 != NULL);
	if (is_number(a, ZERO) && is_number(b, ZERO) && is_number(c, ZERO))
		{
		return -1;
		}
	else if (is_number(a, ZERO) && is_number(b, ZERO) && !is_number(c, ZERO))
		{
		return 0;
		}
	else if ((is_number(a, ZERO) && !is_number(b, ZERO) && is_number(c, ZERO)) || (!is_number(a, ZERO) && is_number(b, ZERO) && is_number(c, ZERO)))
		{
		*x_1 = 0;
		return 1;
		}
	else if (is_number(a, ZERO) && !is_number(b, ZERO) && !is_number(c, ZERO))
		{
		*x_1 = -c / b;
		return 1;
		}
	else if (!is_number(a, ZERO) && !is_number(b, ZERO) && is_number(c, ZERO))
		{
			if (((-b / a) > ZERO) && !is_number(-b / a, ZERO))
				{
				*x_1 = 0;
				*x_2 = -b / a;
				return 2;
				}
			if (((-b / a) < ZERO) && !is_number(-b / a, ZERO))
				{
				*x_1 = -b / a;
				*x_2 = 0;
				return 2;
				}
			if (is_number(-b / a, ZERO))	
				{
				*x_1 = 0;
				return 1;
				}
		}
	else
		{

		double discriminant = b * b - 4 * a * c;

		if (!is_number(discriminant, ZERO) && (discriminant > ZERO) ) 
			{
			*x_1=(-b - sqrt(discriminant)) / (2 * a);
			*x_2=(-b + sqrt(discriminant)) / (2 * a);
			return 2;
			}
		else if (is_number(discriminant, ZERO)) 
			{
			*x_1 = -b / (2 * a);
			return 1;
			}
		else 
			{
			return 0;
			}
		}
 	}

//====================================================================================

void output(int roots, double* x_1, double* x_2)
	{
		switch(roots) 
			{
				case -1: 
					printf("This equation has an infinite number of roots.\n\n");
					break;
				case 0:
					printf("This equation hasn't roots.\n\n");
					break;
				case 1:
					printf("This equation has %d root:\nx=%lg\n\n", roots, *x_1);
					break;
				case 2:
					printf("This equation has %d roots:\nx1=%lg\nx2=%lg\n\n", roots, *x_1, *x_2);
					break;
			}
	}

//=================================================================================

int manual_test()
	{

	printf("Enter the real coefficients a, b, c quadratic equation in a row separated by a space\nEquation of the form a*x^2+b*x+c=0\n\n");

	double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
	int roots = 0;

	if (scanf("%lg %lg %lg", &a, &b, &c) != 3)
		{
		printf("\n\nError, you entered the wrong coefficients!\n\n");
		return 1;
		}

	printf("\n\n");

	roots = quadratic_equation(a, b, c, &x1, &x2);

	output(roots, &x1, &x2);
	}

//===================================================================================

int unit_test()
	{
		FILE* input;
		FILE* output;

		input = fopen("input.txt", "r");
		//assert(input != NULL);

		if (input == NULL)
			{
				fprintf(stderr, "This file is empty!");
				return 1;
			}

		output = fopen("output.txt", "w");

		double a = 0, b = 0, c = 0;
		int i = 0;

		for (i = 0; i < NUMBER_OF_TESTS; i++)
			{

			double x1 = 0, x2 = 0;
			int roots = 0;

			fscanf(input, "%lg %lg %lg", &a, &b, &c);

			roots = quadratic_equation(a, b, c, &x1, &x2);

			switch(roots)
				{
					case 0: fprintf(output, "No roots\n"); break;
					case 1: fprintf(output, "%lg\n", x1); break;
					case 2: fprintf(output, "%lg %lg\n", x1, x2); break;
					case -1: fprintf(output, "infinite\n");
				}
			}
		printf("All tests are done\n");
		fclose(input);
		fclose(output);
	}