//Solve a set of linear quations using LU decomposition and Jacobi method
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdbool.h>

#define max 10
float A[max][max] = { 0 }, X[max] = { 0 }, B[max] = { 0 };
float L[max][max] = { 0 }, U[max][max] = { 0 }, Y[max] = { 0 };
int i, j, k, n;
float dinv[max][max] = { 0 }, R[max][max] = { 0 }, approx[max][1] = { 0 }; //R=L+U ; dinv is the diagonal inverse matrix
float temp[max][1], matrixRes[max][1];

void multiply(float A[][max], float B[], int n);

void main()
{
    //Fix the no. of variables
    printf("Enter the no. of variables : ");
    scanf("%d", &n);

    //Enter the coefficient matrix
    printf("Enter elements of the coefficient Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf(" A[%d][%d] = ", i + 1, j + 1);
            scanf("%f", &A[i][j]);
        }
    }

    printf("\nEnter the constant terms: \n");
    for (i = 0; i < n; i++)
    {
        printf("B[%d] = ", i + 1);
        scanf("%f", &B[i]);
    }

    //LU decomposition
    for (j = 0; j < n; j++)
    {
        for (i = 0; i < n; i++)
        {
            if (i <= j)
            {
                U[i][j] = A[i][j];
                for (k = 0; k < i - 1; k++)
                    U[i][j] -= L[i][k] * U[k][j];
                if (i == j)
                    L[i][j] = 1;
                else
                    L[i][j] = 0;
            }
            else
            {
                L[i][j] = A[i][j];
                for (k = 0; k <= j - 1; k++)
                    L[i][j] -= L[i][k] * U[k][j];
                L[i][j] /= U[j][j];
                U[i][j] = 0;
            }
        }
    }

    //Printing the results for LU decomposition method
    printf("[L]: \n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%9.3f", L[i][j]);
        printf("\n");
    }
    printf("\n\n[U]: \n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%9.3f", U[i][j]);
        printf("\n");
    }
    for (i = 0; i < n; i++)
    {
        Y[i] = B[i];
        for (j = 0; j < i; j++)
        {
            Y[i] -= L[i][j] * Y[j];
        }
    }
    printf("\n\n[Y]: \n");
    for (i = 0; i < n; i++)
    {
        printf("%9.3f", Y[i]);
    }
    for (i = n - 1; i >= 0; i--)
    {
        X[i] = Y[i];
        for (j = i + 1; j < n; j++)
        {
            X[i] -= U[i][j] * X[j];
        }
        X[i] /= U[i][i];
    }
    printf("\n\n[X]: \n");
    for (i = 0; i < n; i++)
    {
        printf("%9.3f", X[i]);
    }
    

    //Jacobi
    
    //Finding the diagonal inverse matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            if (i == j)
                dinv[i][j] = 1 / A[i][j];
            else
                dinv[i][j] = 0;
        }

    //Finding the R matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            if (i == j)
                R[i][j] = 0;
            else if (i != j)
                R[i][j] = A[i][j];
        }

    int count = 0;
    float tol = 0.0001;
    bool stop = false;
    while (count < 100)
    {
        multiply(R, approx, n);//multiply L+U and the approximation
        for (int row = 0; row < n; row++)
            temp[row][0] = B[row] - matrixRes[row][0];//the matrix(b-Rx)
        multiply(dinv, temp, n);//multiply D inverse and (b-Rx)

        for (i = 0; i < n; i++)
        {
            if (abs(matrixRes[i] - approx[i]) < tol)
                stop = true;
        }

        for (int octr = 0; octr < n; octr++)
            approx[octr][0] = matrixRes[octr][0];//store matrixRes value in the next approximation
        printf("\n\nThe Value after iteration %d is\n", count + 1);
        for (int row = 0; row < n; row++)
            printf("%.3f\n", approx[row][0]);//display the value after the pass

        count++;
    }

    getch();
}

void multiply(float A[][max], float B[], int n)
{
    int ctr, ictr;
    //function to perform multiplication
    for (ctr = 0; ctr < n ; ctr++)
    {
        matrixRes[ctr][0] = 0;
        for (int navigate = 0; navigate < n; navigate++)
            matrixRes[ctr][0] = matrixRes[ctr][0] + A[ctr][navigate] * B[navigate];
    }
}