#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define PolynomMaxSize 50
#define ExpressionMaxSize 10

int* GetPolynomCoefficientArray(char polynome[PolynomMaxSize], int polynomSize, int* outResultSize)
{
	int* resultPolynom = (int*)calloc(PolynomMaxSize, sizeof(int));
	char polynomSegments[PolynomMaxSize / 4 + 5][ExpressionMaxSize];

	int segmentsCount = 0;
	for (int i = 0, k = 0; i < polynomSize; i++)
	{
		if (polynome[i] != '+' && polynome[i] != '-')
		{
			polynomSegments[segmentsCount][k++] = polynome[i];
			if (i + 1 == polynomSize)
				polynomSegments[segmentsCount][k] = '\0'; //string end
		}
		else
		{
			polynomSegments[segmentsCount][k] = '\0'; //string end
			k = 0;
			polynomSegments[++segmentsCount][k++] = polynome[i];
		}
	}
	segmentsCount++;

	int maxIndex = 0;
	for (int i = 0; i < segmentsCount; i++)
	{
		char* current = polynomSegments[i];
		int coefficient = atoi(current);
		int expressionSize = strlen(current);


		if (coefficient == 0)
			coefficient = current[0] == '-' ? -1 : 1;

		char* indexStr = NULL;

		for (int j = 1; j < expressionSize; j++) //j = 1 cause first element nam ne interesno
		{
			if (current[j] == '^')
			{
				indexStr = (char*)malloc(expressionSize - j - 1);
				for (int k = 0; k < expressionSize - (j + 1); k++)
					indexStr[k] = current[k + j + 1];

				break;
			}
		}

		int index = 0;
		if (indexStr != NULL)
		{
			index = atoi(indexStr);
			free(indexStr);
		}
		else
		{
			for (int i = 0; i < expressionSize; i++)
			{
				if (current[i] == 'x')
				{
					index = 1;
					break;
				}
			}
		}

		resultPolynom[index] = coefficient;

		if (!i)
			maxIndex = index;
	}


	*outResultSize = maxIndex + 1;
	return resultPolynom;
}

int* GetPolynomSum(char polynome1[PolynomMaxSize], int polynom1Size, char polynome2[PolynomMaxSize], int polynom2Size, int* outResultSize)
{

}


int main(void)
{
	char* polynome1 = (char*)malloc(PolynomMaxSize);
	char* polynome2 = (char*)malloc(PolynomMaxSize);
	char action[6];

	strcpy(polynome1, "5x^3+2x^2+x+1");
	strcpy(polynome2, "1x^3+5x+3");


	fgets(polynome1, PolynomMaxSize, stdin);
	fgets(action, PolynomMaxSize, stdin);
	fgets(polynome2, sizeof(polynome2), stdin);

	int polynome1Size = strlen(polynome1);
	int polynome2Size = strlen(polynome2);

	int resultSize1 = 0;
	int* resultPolynom1 = GetPolynomCoefficientArray(polynome1, polynome1Size, &resultSize1);

	int resultSize2 = 0;
	int* resultPolynom2 = GetPolynomCoefficientArray(polynome2, polynome2Size, &resultSize2);

	/*for (int i = 0; i < resultSize1; i++)
	{
		printf("%d ", resultPolynom1[i]);
	}*/

	free(polynome1);
	free(polynome2);
	free(resultPolynom1);
	free(resultPolynom2);

	return 0;
}
