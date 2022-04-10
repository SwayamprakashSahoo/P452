// Linear equation solution using Gauss-Jordan and LU decompostion 
#include<stdio.h>
#include<conio.h>
#include<math.h>

#define max 10

int main()
{
	float aug[max][max], sol[max], ratio;
	int i, j, k, n;
	
	// Fix the number of variables 
	printf("Enter number of variables: ");
	scanf("%d", &n);
	//Enter the augmented matrix
	printf("Enter coefficients of Augmented Matrix:\n");
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n + 1; j++)
		{
			printf("a[%d][%d] = ", i, j);
			scanf("%f", &aug[i][j]);
		}
	}
	/*Gauss Jordan Elimination */
	for (i = 1; i <= n; i++)
	{
		if (aug[i][i] == 0.0)
		{
			printf("Mathematical Error!");
			exit(0);
		}
		for (j = 1; j <= n; j++)
		{
			if (i != j)
			{
				ratio = aug[j][i] / aug[i][i];
				for (k = 1; k <= n + 1; k++)
				{
					aug[j][k] = aug[j][k] - ratio * aug[i][k];
				}
			}
		}
	}
	// For solution
	for (i = 1; i <= n; i++)
	{
		sol[i] = aug[i][n + 1] / aug[i][i];
	}

	printf("\nSolution:\n");
	for (i = 1; i <= n; i++)
	{
		printf("solution[%d] = %f\n", i, sol[i]);
	}
	getch();
	return(0);
}