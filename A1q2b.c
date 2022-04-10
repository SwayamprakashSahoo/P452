//To find the inverse of a matrix
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdbool.h>

#define max 10
float A[max][max] = { 0 }, X[max] = { 0 }, B[max];
float L[max][max] = { 0 }, U[max][max] = { 0 }, Y[max] = { 0 };
int i, j, k, n;
float dinv[max][max] = { 0 }, R[max][max] = { 0 }, approx[max][1] = { 0 }; //R=L+U ; dinv is the diagonal inverse matrix
float temp[max][1], matrixRes[max][1];
void multiply(float A[][max], float B[], int n);
int main()
{
    //Fix the dimensions of the square matrix
    printf("Enter the no. of rows and columns for the square matrix : ");
    scanf("%d", &n);

    //Enter the matrix
    printf("Enter elements of the Matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf(" A[%d][%d] = ", i + 1, j + 1);
            scanf("%f", &A[i][j]);
        }
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
    FILE* fptr2 = fopen("C:/Users/sahoo/Desktop/Computational Asiignments/Jacobi_inv.txt", "w");
    int count = 0;
    float tol = 0.0001;
    bool stop = false;
    for (i = 0; i < n; i++)
    {
        B[i] = 1;
        while (count < 1000 || !stop)
        {
            multiply(R, approx, n);//multiply L+U and the approximation
            for (int row = 0; row < n; row++)
                temp[row][0] = B[row] - matrixRes[row][0];//the matrix(b-Rx)
            multiply(dinv, temp, n);//multiply D inverse and (b-Rx)
            FILE* fptr1 = fopen("C:/Users/sahoo/Desktop/Computational Asiignments/Jacobi_res.txt", "w");
            fprintf(fptr1, "%f\t%f\n", count + 1, matrixRes[0][0] - approx[0][0]);
            for (i = 0; i < n; i++)
            {
                if (abs((matrixRes[i][0] - approx[i][0]) / matrixRes[i][0]) < tol)
                    stop = true;
            }

            for (int octr = 0; octr < n; octr++)
                approx[octr][0] = matrixRes[octr][0];//store matrixRes value in the next approximation

            count++;

        }
        for (j = 0; j < n; j++)
            fprintf(fptr2, "%f\n", matrixRes[j][0]);
    }
    getch();
}

void multiply(float A[][max], float B[], int n)
{
    int ctr, ictr;
    //function to perform multiplication
    for (ctr = 0; ctr < n; ctr++)
    {
        matrixRes[ctr][0] = 0;
        for (int navigate = 0; navigate < n; navigate++)
            matrixRes[ctr][0] = matrixRes[ctr][0] + A[ctr][navigate] * B[navigate];
    }
}
