#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double** Matrix_Multi(double** matA, int rowA, int colA, double** matB, int rowB, int colB);
double** Matrix_Trans(double** mat, int row, int col);
double** Matrix_Inverse(double** mat, int size);
void getResult(double **matA, double **matB, int row, int col);

double** Matrix_Multi(double** matA, int rowA, int colA, double** matB, int rowB, int colB)
{
	int i, j, p;
	if (colA != rowB)
	{
		printf("error! mat1 col not equal mat2 row");
		return 0;
	}

	double** matC = (double**)malloc(rowA* sizeof(double*));
	for (i = 0; i < rowA; i++)
	{
		matC[i] = (double*)malloc(colB* sizeof(double));
	}
	
	for (i = 0; i < rowA; i++)
	{
		for (j = 0; j < colB; j++)
		{
			matC[i][j] = 0;
			for (p = 0; p < colA; p++)
			{
				matC[i][j] += matA[i][p] * matB[p][j];
			}
		}
	}
	return matC;
}

double** Matrix_Trans(double** mat, int row, int col)
{
	int i, j;
	double** matResult = (double**)malloc(col* sizeof(double*));

	for (i = 0; i < col; i++)
	{
		matResult[i] = (double*)malloc(row*sizeof(double));
	}

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			matResult[j][i] = mat[i][j];
		}
	}
	return matResult;
}

double** Matrix_Inverse(double** mat, int size)
{
	int i, j, k;
	double c;
	double** matResult = (double**)malloc(size* sizeof(double*));
	for (i = 0; i < size; i++)
	{
		matResult[i] = (double*)malloc(size*sizeof(double));
		memset(matResult[i], 0, sizeof(double)*size);
		matResult[i][i] = 1;
	}
	

	for (i = 0; i < size; i++)
	{
		for (j = i; j < size; j++)
		{
			if (mat[j][i] != 1 && j == i)
			{
				c = mat[j][i];
				if (c!= 0) 
				{					
					for (k = 0; k < size; k++)
					{
						mat[j][k] /= c;
						matResult[j][k] /=  c;
					}
				}				
			}
			else if (mat[j][i] != 0 && j != i)
			{
				c = mat[j][i];
				for (k = 0; k < size; k++)
				{
					mat[j][k] -= mat[i][k] * c;
					matResult[j][k] -= matResult[i][k] * c;
				}
			}
		}
	}

	for (i = size - 1; i >=0; i--)
	{
		for (j = i; j >=0; j--) 
		{
			if (mat[j][i] != 1 && i == j)
			{
				c = mat[j][i];
				matResult[j][i] /=c;
				mat[j][i] /= c;
			}
			else if (mat[j][i] != 0 && i != j)
			{
				c = mat[j][i];
				for (k = 0; k < size; k++)
				{
					mat[j][k] -= mat[i][k] * c;
					matResult[j][k] -= matResult[i][k] * c;
				}
			}
		}
	}

	return matResult;
}

void getResult(double **matA, double **matB, int row, int col)
{
	int i, j;
	double price = 0.0;
	for (i = 0; i < row; i++)
	{
		for (j = -1; j < col - 1; j++)
		{
			if (j < 0)
			{
				price += matA[0][0];
				continue;
			}
			price += matA[j + 1][0] * matB[i][j];
		}
		price += 0.5;

		printf("%d\n", (int)price);
		price = 0.0;
	}
}

int main(int argc, char** argv)
{
	if (argc!=3)
	{
		printf("argc number should be 3\n");
		return 0;
	}
	int row1, row2, col;
	int i, j;
	FILE* fp1, *fp2;

	double **mat1, **mat2, **matresult1, **matresult2, **matfinal, **mattrans, **matmulti, **matinver, **final;

	fp1 = fopen(argv[1], "r");
	if (fp1 == NULL)
	{
		printf("file %s does not exist\n", argv[1]);
		return 0;
	}
	fscanf(fp1, "%d \n", &col);
	fscanf(fp1, "%d \n", &row1);
	col++;
	mat1 = (double**)malloc(row1* sizeof(double*));
	for (i = 0; i < row1; i++)
	{
		mat1[i] = (double*)malloc(col*sizeof(double));
	}
	for (i = 0; i < row1; i++)
	{
		fscanf(fp1, "%lf,", &mat1[i][col - 1]);
		for (j = 1; j < col; j++)
		{
			fscanf(fp1, "%lf,", &mat1[i][j - 1]);
		}
		fscanf(fp1, "\n");
	}
	fclose(fp1);


	fp2 = fopen(argv[2], "r");
	if (fp2 == NULL)
	{
		printf("file does not exist\n", argv[2]);
		return 0;
	}
	fscanf(fp2, "%d \n", &row2);
	mat2 = (double**)malloc(row2* sizeof(double*));
	for (i = 0; i < row2; i++)
	{
		mat2[i] = (double*)malloc((col - 1)*sizeof(double));
	}
	for (i = 0; i < row2; i++)
	{
		for (j = 0; j < (col - 1); j++)
		{
			fscanf(fp2, "%lf,", &mat2[i][j]);
		}
		fscanf(fp2, "\n");
	}
	fclose(fp2);


	matresult1 = (double**)malloc(row1* sizeof(double*));
	for (i = 0; i < row1; i++)
	{
		matresult1[i] = (double*)malloc(col*sizeof(double));
	}

	for (i = 0; i < row1; i++)
	{
		matresult1[i][0] = 1;
		for (j = 1; j < col; j++)
		{
			matresult1[i][j] = mat1[i][j - 1];
		}
	}

	mattrans = Matrix_Trans(matresult1, row1, col);
	matmulti = Matrix_Multi(mattrans, col, row1, matresult1, row1, col);
	matinver = Matrix_Inverse(matmulti, col);
	matfinal = Matrix_Multi(matinver, col, col, mattrans, col, row1);

	matresult2 = (double**)malloc(row1* sizeof(double*));
	for (i = 0; i < row1; i++)
	{
		matresult2[i] = (double*)malloc(sizeof(double));
	}
	for (i = 0; i < row1; i++)
	{
		matresult2[i][0] = mat1[i][col - 1];
	}
	final = Matrix_Multi(matfinal, col, row1, matresult2, row1, 1);

	getResult(final, mat2, row2, col);

	return 0;
}


