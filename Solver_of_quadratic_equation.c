#include <stdio.h>
#include <math.h>

const double deviation = 1E-6;

//================================================================

int is_zero(double discr);

void quadratic_equation(double a, double b, double c);

//================================================================

void main()
	{
	printf("Enter the coefficients a, b, c quadratic equation in a row separated by a space\nEquation of the form a*x^2+b*x+c=0\n\n");

	double a, b, c;

	scanf("%lg %lg %lg", &a, &b, &c);
	printf("\n\n");

	quadratic_equation(a, b, c);
	}

//================================================================

int is_zero(double value)
	{
	return (fabs(value) <= deviation);
	}
	
void quadratic_equation(double a, double b, double c)
	{
	if (is_zero(a) && is_zero(b) && is_zero(c))
		{
		printf("This equation has an infinite number of roots\n");
		}
	else if (is_zero(a) && !is_zero(b) && is_zero(c) || !is_zero(a) && is_zero(b) && is_zero(c))
		{
		printf("This equation has 1 root:\nx=0\n");
		}
	else if (!is_zero(a) && !is_zero(b) && is_zero(c))
		{
			if (((- b / a) > 0) && !is_zero(- b / a))
			printf("This equation has 2 roots:\nx1=0\nx2=%lg\n", - b / a);
			if (((- b / a) < 0) && !is_zero(- b / a))
			printf("This equation has 2 roots:\nx1=%lg\nx2=0\n", - b / a);
			if (is_zero(- b / a))
			printf("This equation has 1 root:\nx=0\n");
		}
	else
		{

		double discriminant = b * b - 4 * a * c;

		if (!is_zero(discriminant) && (discriminant > 0) ) 
			{
			printf("This eqeation has 2 roots:\nx1=%lg\nx2=%lg\n", (- b - sqrt(discriminant)) / (2 * a), (- b + sqrt(discriminant)) / (2 * a) );
			}
		else if (is_zero(discriminant)) 
			{
			printf("This equation has 1 root:\nx=%lg\n", - b / (2 * a));
			}
		else 
			{
			printf("This equation hasn't roots\n");
			}
		}
 	}