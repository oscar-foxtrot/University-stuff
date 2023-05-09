#define u0 0 // initial condition

double x0 = 0;
double xn = 1;
int n;

double f(double x)
{
	return sin(x * x + x);
}
// Calculating the given integral
// using the method of midpoint rectangles (giving the precision of the 4th order here)
double integrate(double xibeg, double xiend) //from X_ibeg to X_iend including both X_ibeg and X_iend.
{
	int m = n * n;
	double res = 0;
	double ab = xn - x0;
	int ibeg = round(xibeg / ab * m);
	int iend = round(xiend / ab * m);
	if (iend == 0)
		return 0;
	for (int j = ibeg; j <= iend - 1; ++j)
	{
		double t = x0 + j * (ab / m) + 0.5 * ab / m;
		res += f(t) * (ab / m);
	}
	return res;
}

#define f(x, u) integrate(x0, x)

// With the use of Runge-Kutta method (2nd order) with the parameter "alpha"
// an approximate solution for the given Cauchy problem is calculated.

double get_y_i_plus_one(double x_i, double y_i, double alpha);

double *get_solution(double alpha) //returns an array with the values of the function
{
	double res = 0;
	double y_i = u0;
	double x_i = x0;
	
	double *funcarr = malloc(sizeof(double) * (n + 1));
	funcarr[0] = y_i;
	for (int i = 1; i <= n; ++i)
	{
		y_i = get_y_i_plus_one(x_i, y_i, alpha);
		funcarr[i] = y_i;
		x_i += (xn - x0) / n;
	}
	return funcarr;
}

double get_y_i_plus_one(double x_i, double y_i, double alpha)
{	
	double h = (xn - x0) / n; 
	double res = y_i + ((1 - alpha) * f(x_i, y_i) + 
		alpha * f(x_i + h / (2 * alpha), y_i + h * f(x_i, y_i) / (2 * alpha))) * h;
	return res;
}

int main (int argc, char *argv[])
{
	double alpha;
	printf("Enter N: ");
	fflush(stdout);
	scanf("%d", &n);
	printf("Enter alpha: ");
	fflush(stdout);
	scanf("%lf", &alpha);
	printf("\n");
	fflush(stdout);
	
	double *sol;
	sol = get_solution(alpha);
	for (int i = 0; i <= n; ++i)
	{
		printf("%lf %.10lf\n", i * (xn - x0) / n, sol[i]);
		fflush(stdout);
	}
	
	return 0;
}
