#include <stdio.h>
#include <math.h>

const double deviation=1E-6;

int isZero(double discr)
{
	if (fabs(discr)<=deviation) {
		return 1;
	}
	else {
		return 0;
	}
}

void quadratic_equation(double a, double b, double c)
{
	if (a=0){
		printf("%lg", -c/b );
	}
	else {

		double discriminant;

		discriminant=b*b-4*a*c;

		if (! isZero(discriminant) && (discriminant > 0) ) {
			printf("x1=%lg\n x2=%lg\n", (-b-sqrt(discriminant))/(2*a), (-b+sqrt(discriminant))/(2*a) );
		}
		else {
			if (isZero(discriminant)) {
				printf("x=%lg\n", -b/(2*a));
			}
			else {
				printf("Не имеет решений");
			}
		}
	}
 }
void main()
{
	quadratic_equation(1, 2, 1);
}