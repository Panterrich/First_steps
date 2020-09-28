#include <stdio.h>
#include <math.h>
#include <assert.h>

#define DEBUG_MODE

const double deviation = 1E-6;
const int ZERO = 0; 
const int NUMBER_OF_TESTS = 15;

/// \file

//================================================================
/*!
Checks whether number is value with an accuracy of 1E-6
\param[in] value value - the number to compare with original number
\param[in] number number - original number 
*/
int is_number(double value, double number);

/*!
Solves a square equation ax^2 + bx + c = 0
\param[in]  a a - coefficient
\param[in]  b b - coefficient
\param[in]  c c - coefficient
\param[out] x_1 pointer to the first  root x1
\param[out] x_2 pointer to the second root x2
\return Number of roots
\note In case of infinite number of roots, returns -1
*/
int quadratic_equation(double a, double b, double c, double* x_1, double* x_2);

/*!
Print the answer in the terminal 
\param[in]  roots roots - number of roots
\param[out] x_1 pointer to the first  root x1
\param[out] x_2 pointer to the second root x2
*/
void output(int roots, double* x_1, double* x_2);

/*!
Unit tests input from input.txt and output in output.txt
*/
int unit_test();
/*!
Solves one equation in the terminal 
*/
int manual_test();

//================================================================

/*!
main()
*/
int main()
	{
	#ifdef DEBUG_MODE
		unit_test();
	#else 
		manual_test();
	#endif
	
	return 0;
	}

//================================================================

int is_number(double value, double number)
	{
	return (fabs(value - number) <= deviation);
	}

//================================================================
	
int quadratic_equation(double a, double b, double c, double* x_1, double* x_2)
	{
	assert(x_1 != NULL);
	assert(x_2 != NULL);

	/// Special case of quadratic equation 
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

	else /// Standard solution of quadratic equation 
		{
		double discriminant = b * b - 4 * a * c;

		if (!is_number(discriminant, ZERO) && (discriminant > ZERO) ) 
		{
			*x_1 = (-b - sqrt(discriminant)) / (2 * a);
			*x_2 = (-b + sqrt(discriminant)) / (2 * a);
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
	assert(x_1 != NULL);
	assert(x_2 != NULL);

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
	FILE* input = fopen("input.txt", "r");
	assert(input != NULL);

	if (input == NULL)
	{
		fprintf(stderr, "This file is empty!");
		return 1;
	}

	FILE* output = fopen("output.txt", "w");
	assert(output != NULL);

	double a = 0, b = 0, c = 0, real_x1 = 0, real_x2 = 0;
	int real_roots = 0;

	for (int i = 1; i < NUMBER_OF_TESTS + 1; i++)
		{

		double x1 = 0, x2 = 0;
		int roots = 0;

		fscanf(input, "%lg %lg %lg %d %lg %lg\n", &a, &b, &c, &real_roots, &real_x1, &real_x2);

		roots = quadratic_equation(a, b, c, &x1, &x2);

		if (roots != real_roots)
		{
			fprintf(output, "Test №%d is wrong, the number of roots didnt match\n", i);
		}

		else if (is_number(x1, real_x1) && is_number(x2, real_x2))
		{
			fprintf(output, "Test №%d was comleted correctly\n", i);
		}

		else
		{
			fprintf(output, "Test №%d is wrong, the roots isn't correct\n", i);
		}

		}

	printf("All tests are done\n");

	fclose(input);
	fclose(output);
}