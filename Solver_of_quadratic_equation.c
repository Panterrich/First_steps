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

int is_zero(double discr)
	{
	return (fabs(discr) <= deviation);
	}
	
void quadratic_equation(double a, double b, double c)
	{
	if (is_zero(a))
		{
		printf("x=%lg\n", -c / b );
		}
	else 
		{

		double discriminant = b * b - 4 * a * c;

		if (!is_zero(discriminant) && (discriminant > 0) ) 
			{
			printf("x1=%lg\n x2=%lg\n", (- b - sqrt(discriminant)) / (2 * a), (- b + sqrt(discriminant)) / (2 * a) );
			}
		else if (is_zero(discriminant)) 
			{
			printf("x=%lg\n", - b / (2 * a));
			}
		else 
			{
			printf("Не имеет решений\n");
			}
		}
 	}