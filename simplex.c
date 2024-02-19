//making simplex calculator using c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
void simplex();
void print_tableau();
void pivot(int, int);
int m, n;
double **a;
int main()
{
    printf("Enter the number of equations: ");
    scanf("%d", &m);
    printf("Enter the number of variables: ");
    scanf("%d", &n);
    a = (double **)malloc((m + 1) * sizeof(double *));
    for (int i = 0; i <= m; i++)
	a[i] = (double *)malloc((m + n + 2) * sizeof(double));
    printf("Enter the coefficients of the equations:\n");
    for (int i = 0; i < m; i++)
    {
	for (int j = 0; j < n; j++)
	{
	    scanf("%lf", &a[i][j]);
	}
    }
    printf("Enter the constants on the right side of the equations:\n");
    for (int i = 0; i < m; i++)
    {
	scanf("%lf", &a[i][n]);
    }
    printf("Enter the coefficients of the Z-equation:\n");
    for (int j = 0; j < n; j++)
    {
	scanf("%lf", &a[m][j]);
    }
    a[m][n] = 0;
    printf("The initial tableau is:\n");
    print_tableau();
    simplex();
    for (int i = 0; i < m; i++)
    {
	free(a[i]);
    }
    free(a);
    return 0;
}
void simplex()
{
    while (1)
    {
	int min = 0;
	for (int j = 1; j < m + n; j++)
	{
	    if (a[m][j] < a[m][min])
	    {
		min = j;
	    }
	}
	if (a[m][min] >= 0)
	{
	    break;
	}
	int min_ratio = 0;
	for (int i = 0; i < m; i++)
	{
	    if (a[i][n] <= 0)
	    {
		continue;
	    }
	    else
	    {
		if (a[i][min] <= 0)
		{
		    continue;
		}
		else
		{
		    if (a[i][n] / a[i][min] < a[min_ratio][n] / a[min_ratio][min])
		    {
			min_ratio = i;
		    }
		}
	    }
	}
	pivot(min_ratio, min);
	printf("After the pivot, the tableau is:\n");
	print_tableau();
    }
    printf("The optimal solution is: %lf\n", a[m][n]);
}
void print_tableau()
{
    for (int i = 0; i <= m; i++)
    {
	for (int j = 0; j <= m + n; j++)
	{
	    printf("%lf ", a[i][j]);
	}
	printf("\n");
    }
}
void pivot(int row, int col)
{
    for (int i = 0; i <= m; i++)
    {
	for (int j = 0; j <= m + n; j++)
	{
	    if (i != row && j != col)
	    {
		a[i][j] -= a[row][j] * a[i][col] / a[row][col];
	    }
	}
    }
    for (int j = 0; j <= m + n; j++)
    {
	if (j != col)
	{
	    a[row][j] /= a[row][col];
	}
    }
    for (int i = 0; i <= m; i++)
    {
	if (i != row)
	{
	    a[i][col] /= -a[row][col];
	}
    }
    a[row][col] = 1;
}
