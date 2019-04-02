#include <gsl/gsl_ieee_utils.h>

int main (void)
{
	float f = 1.1;
	int i = 0;
	for(i; i<135; i++)
	{
		gsl_ieee_printf_float(&f);
		printf ("\n");
		f = f/2.0;
	}
}
