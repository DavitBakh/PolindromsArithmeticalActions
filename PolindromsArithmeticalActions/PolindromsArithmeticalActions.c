#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define PolynomMaxSize 50
#define ExpressionMaxSize 10

//TODO Minimaize array size
void PrintPolynom(int polynom[PolynomMaxSize], int size)
{
	for (int i = size - 1; i >= 0; i--)
	{
		if (polynom[i] != 0)
		{
			if (i > 1)
			{
				if (polynom[i] > 0)
				{
					printf("+%dx^%d",polynom[i], i);
				}
				else
				{
					printf("%dx^%d", polynom[i], i);
				}
			}
			else if(i == 1)
			{
				if (polynom[i] > 0)
				{
					printf("+%dx", polynom[i]);
				}
				else
				{
					printf("%dx", polynom[i]);
				}
			}
			else
			{
				if (polynom[i] > 0)
				{
					printf("+%d", polynom[i]);
				}
				else
				{
					printf("%d", polynom[i]);
				}
			}
		}
	}
}

int* GetPolynomCoefficientArray(char polynom[PolynomMaxSize], int polynomSize, int* outResultSize)
{
	int* resultPolynom = (int*)calloc(PolynomMaxSize, sizeof(int));
	char polynomSegments[PolynomMaxSize / 4 + 5][ExpressionMaxSize];

	int segmentsCount = 0;
	for (int i = 0, k = 0; i < polynomSize; i++)
	{
		if (polynom[i] != '+' && polynom[i] != '-')
		{
			polynomSegments[segmentsCount][k++] = polynom[i];
			if (i + 1 == polynomSize)
				polynomSegments[segmentsCount][k] = '\0'; //string end
		}
		else
		{
			polynomSegments[segmentsCount][k] = '\0'; //string end
			k = 0;
			polynomSegments[++segmentsCount][k++] = polynom[i];
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

int* GetPolynomsSum(int polynom1[PolynomMaxSize], int polynom1Size, int polynom2[PolynomMaxSize], int polynom2Size, int* outResultSize)
{
	int size = fmax(polynom1Size, polynom2Size);
	int* resultPolynom = (int*)calloc(size, sizeof(int));

	for (int i = 0; i < size; i++)
		resultPolynom[i] = polynom1[i] + polynom2[i];

	int i = size - 1;
	while (i >= 0)
	{
		if (resultPolynom[i] != 0)
			break;

		i--;
	}

	*outResultSize = i + 1;
	return resultPolynom;
}

int* GetPolynomsSubstract(int polynom1[PolynomMaxSize], int polynom1Size, int polynom2[PolynomMaxSize], int polynom2Size, int* outResultSize)
{
	int size = fmax(polynom1Size, polynom2Size);
	int* resultPolynom = (int*)calloc(size, sizeof(int));

	for (int i = 0; i < size; i++)
		resultPolynom[i] = polynom1[i] - polynom2[i];

	int i = size - 1;
	while (i >= 0)
	{
		if (resultPolynom[i] != 0)
			break;

		i--;
	}

	*outResultSize = i + 1;
	return resultPolynom;
}

int main(void)
{
	char* polynom1 = (char*)malloc(PolynomMaxSize);
	char* polynom2 = (char*)malloc(PolynomMaxSize);
	char action;

	//TODO Remove after testing
	strcpy(polynom1, "5x^3+2x^2+x+1");
	strcpy(polynom2, "1x^3+5x+3");


	scanf("%s", polynom1);
	getchar();// <== remove newline
	scanf("%c", &action);
	getchar();
	if (action != '\'')
		scanf("%s", polynom2);

	int polynom1Size = strlen(polynom1);
	int polynom2Size = strlen(polynom2);

	int coefficients1Size = 0;
	int* polynom1Coefficients = GetPolynomCoefficientArray(polynom1, polynom1Size, &coefficients1Size);
	free(polynom1);

	int coefficients2Size = 0;
	int* polynom2Coefficients = GetPolynomCoefficientArray(polynom2, polynom2Size, &coefficients2Size);
	free(polynom2);

	int* resultPolynom = NULL, resultSize = 0;
	switch (action)
	{
	case'+':
		resultPolynom = GetPolynomsSum(polynom1Coefficients, coefficients1Size, polynom2Coefficients, coefficients2Size, &resultSize);
		break;
	case'-':
		resultPolynom = GetPolynomsSubstract(polynom1Coefficients, coefficients1Size, polynom2Coefficients, coefficients2Size, &resultSize);
		break;
	case'*':

		break;
	case'/':
		break;
	case'\'':

		break;
	default:
		printf("Wrong Action!!!");
		break;
	}

	PrintPolynom(resultPolynom, resultSize);

	free(polynom1Coefficients);
	free(polynom2Coefficients);

	return 0;
}
