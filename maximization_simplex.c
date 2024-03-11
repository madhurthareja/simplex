#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

void simplex();
void printTableau();
void pivot(int, int);
double **allocateTableau(int, int);
void freeTableau(double **, int);
bool findPivotColumn(int *, int, int);
bool findPivotRow(int *, int, int, int);

int m, n; 
double **a; 
int main() {
    printf("Enter the number of constraints: ");
    scanf("%d", &m);
    
    printf("Enter the number of decision variables: ");
    scanf("%d", &n);

      a = allocateTableau(m, n);
    printf("Enter the coefficients for each constraint, followed by the constraint value:\n");
    for (int i = 0; i < m; i++) {
        printf("Constraint %d:\n", i + 1);
        for (int j = 0; j <= n; j++) { 
            if (j < n)
                printf("Coefficient for variable %d: ", j + 1);
            else
                printf("Right-hand side value: ");
            scanf("%lf", &a[i][j]);
        }
    }

    printf("Enter the coefficients for the objective function Z:\n");
    for (int j = 0; j < n; j++) {
        printf("Coefficient for variable %d: ", j + 1);
        scanf("%lf", &a[m][j]);
        a[m][j] = -a[m][j]; 
    }
    a[m][n] = 0; 

    printf("Initial tableau:\n");
    printTableau();

    simplex();

    freeTableau(a, m);

    return 0;
}

void simplex() {
    int row, col;

    while (findPivotColumn(&col, m, n) && findPivotRow(&row, col, m, n)) {
        printf("Pivoting on row %d, column %d\n", row + 1, col + 1);
        pivot(row, col);
        printf("Tableau after pivot:\n");
        printTableau();
    }

    printf("Optimal solution found:\n");
    printTableau();
    printf("Optimal value of objective function: %lf\n", -a[m][n]); 
}

void printTableau() {
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            printf("%8.2lf ", a[i][j]);
        }
        printf("\n");
    }
}

double **allocateTableau(int m, int n) {
    double **tab = (double **)malloc((m + 1) * sizeof(double *));
    for (int i = 0; i <= m; i++) {
        tab[i] = (double *)malloc((n + 1) * sizeof(double));
    }
    return tab;
}

void freeTableau(double **tab, int m) {
    for (int i = 0; i <= m; i++) {
        free(tab[i]);
    }
    free(tab);
}

bool findPivotColumn(int *col, int m, int n) {
    double lowest = 0;
    for (int j = 0; j < n; j++) {
        if (a[m][j] < lowest) {
            lowest = a[m][j];
            *col = j;
        }
    }
    return lowest < 0;
}

bool findPivotRow(int *row, int col, int m, int n) {
    double minRatio = INFINITY;
    bool found = false;
    for (int i = 0; i < m; i++) {
        if (a[i][col] > 0) {
            double ratio = a[i][n] / a[i][col];
            if (ratio < minRatio) {
                minRatio = ratio;
                *row = i;
                found = true;
            }
        }
    }
    return found;
}

void pivot(int row, int col) {
    double pivotValue = a[row][col];
    for (int j = 0; j <= n; j++) a[row][j] /= pivotValue;
    for (int i = 0; i <= m; i++) {
        if (i != row) {
            double factor = a[i][col];
            for (int j = 0; j <= n; j++) {
                a[i][j] -= factor * a[row][j];
            }
        }
    }
}

