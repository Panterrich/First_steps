#include <stdio.h>
#include <math.h>

#define ZERO 0 

const double deviation = 1E-6;

//================================================================

int is_number(double value, double number);

int quadratic_equation(double a, double b, double c, double* x_1, double* x_2);

void output(int roots, double* x_1, double* x_2);

//================================================================

void main()
	{
	printf("Enter the coefficients a, b, c quadratic equation in a row separated by a space\nEquation of the form a*x^2+b*x+c=0\n\n");

	double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
	int roots = 0;

	scanf("%lg %lg %lg", &a, &b, &c);
	printf("\n\n");

	roots = quadratic_equation(a, b, c, &x1, &x2);

	output(roots, &x1, &x2);
	}

//================================================================

int is_number(double value, double number)
	{
	return (fabs(value-number) <= deviation);
	}

//================================================================
	
int quadratic_equation(double a, double b, double c, double* x_1, double* x_2)
	{
	if (is_number(a, ZERO) && is_number(b, ZERO) && is_number(c, ZERO))
		{
		return -1;
		}
	else if (is_number(a, ZERO) && !is_number(b, ZERO) && is_number(c, ZERO) || !is_number(a, ZERO) && is_number(b, ZERO) && is_number(c, ZERO))
		{
		*x_1 = 0;
		return 1;
		}
	else if (!is_number(a, ZERO) && !is_number(b, ZERO) && is_number(c, ZERO))
		{
			if (((- b / a) > ZERO) && !is_number(- b / a, ZERO))
				{
				*x_1 = 0;
				*x_2 = - b / a;
				return 2;
				}
			if (((- b / a) < ZERO) && !is_number(- b / a, ZERO))
				{
				*x_1 = - b / a;
				*x_2 = 0;
				return 2;
				}
			if (is_number(- b / a, ZERO))	
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
			*x_1=(- b - sqrt(discriminant)) / (2 * a);
			*x_2=(- b + sqrt(discriminant)) / (2 * a);
			return 2;
			}
		else if (is_number(discriminant, ZERO)) 
			{
			*x_1 = - b / (2 * a);
			return 1;
			}
		else 
			{
			return 0;
			}
		}
 	}

//==================================================================================

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
