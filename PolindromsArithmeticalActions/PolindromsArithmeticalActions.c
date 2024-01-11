#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define PolynomMaxSize 50

//TODO Minimaize array size
void PrintPolynom(int polynom[PolynomMaxSize], int size)
{
	printf("\n");

	for (int i = size - 1; i >= 0; i--)
	{
		if (polynom[i] != 0)
		{
			if (i > 1)
			{
				if (polynom[i] > 0)
				{
					printf("+%dx^%d", polynom[i], i);
				}
				else
				{
					printf("%dx^%d", polynom[i], i);
				}
			}
			else if (i == 1)
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

	if (size == 0)
		printf("0");
}

int* GetPolynomCoefficientArray(char polynom[PolynomMaxSize], int polynomSize, int* outResultSize)
{
	int* resultPolynom = (int*)calloc(PolynomMaxSize, sizeof(int));
	char polynomSegments[PolynomMaxSize / 4 + 5][10]; //10 expression max size

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

		for (int j = 1; j < expressionSize; j++)
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
			indexStr = NULL;
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

int* GetPolynomDerivative(int polynom[PolynomMaxSize], int size, int* outResultSize)
{
	*outResultSize = size - 1;
	int* resultPolynom = (int*)calloc(*outResultSize, sizeof(int));

	for (int i = 1; i < size; i++)
		resultPolynom[i - 1] = i * polynom[i];

	return resultPolynom;
}

int* MultiplyPolynoms(int polynom1[PolynomMaxSize], int polynom1Size, int polynom2[PolynomMaxSize], int polynom2Size, int* outResultSize)
{
	*outResultSize = polynom1Size - 1 + polynom2Size;
	int* resultPolynom = (int*)malloc(*outResultSize * sizeof(int));

	for (int k = 0; k < *outResultSize; k++)
	{
		int result = 0;
		for (int i = 0; i <= k; i++)
		{
			if (i >= polynom1Size || k - i >= polynom2Size)
				continue;

			result += polynom1[i] * polynom2[k - i];
		}

		resultPolynom[k] = result;
	}

	return resultPolynom;
}

void MultiplyPolynomToNumber(int polynom[PolynomMaxSize], int size, int number)
{
	for (int i = 0; i < size; i++)
		polynom[i] *= number;
}

void PowPolynom(int** polynom, int* size, int x)
{
	*polynom = realloc(*polynom, ((*size) + x) * sizeof(int));
	for (int i = *size - 1; i >= 0; i--)
	{
		(*polynom)[i + x] = (*polynom)[i];
		if (i < x)
			(*polynom)[i] = 0;
	}
	*size += x;
}

int* DevidePolynoms(int polynom1[PolynomMaxSize], int polynom1Size, int polynom2[PolynomMaxSize], int polynom2Size, int* outResultSize, int** outRemainderPolynom, int* outReminderSize)
{
	if (polynom1Size < polynom2Size)
	{
		*outRemainderPolynom = polynom1;
		*outReminderSize = polynom1Size;

		*outResultSize = 0;
		return NULL;
	}
	int* q;
	/*if (polynom1Size == polynom2Size)
	{
		int temp = polynom1[polynom1Size - 1] / polynom2[polynom2Size - 1];
		q = (int*)malloc(1 * sizeof(int));
		q[0] = temp;
		*outResultSize = 1;
		MultiplyPolynomToNumber(polynom2, polynom2Size, temp);
		*outRemainderPolynom = GetPolynomsSubstract(polynom1, polynom1Size, polynom2, polynom2Size, outReminderSize);
		return q;
	}*/

	int index = (polynom1Size - 1) - (polynom2Size - 1);
	*outResultSize = index + 1;

	q = (int*)calloc((index + 1), sizeof(int));
	int* polynom2Copy = (int*)malloc(polynom2Size * sizeof(int));

	while (polynom1Size >= polynom2Size)
	{
		int coefficient = polynom1[polynom1Size - 1] / polynom2[polynom2Size - 1];
		index = (polynom1Size - 1) - (polynom2Size - 1);
		q[index] = coefficient;

		int copySize = polynom2Size;
		for (int i = 0; i < polynom2Size; i++)
			polynom2Copy[i] = polynom2[i];

		MultiplyPolynomToNumber(polynom2Copy, copySize, coefficient);
		PowPolynom(&polynom2Copy, &copySize, index);

		int tempSize = 0;
		int* temp = GetPolynomsSubstract(polynom1, polynom1Size, polynom2Copy, copySize, &tempSize);

		polynom1 = temp;
		polynom1Size = tempSize;
	}

	*outRemainderPolynom = polynom1;
	*outReminderSize = polynom1Size;
	return q;

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
	polynom1 = NULL;

	int coefficients2Size = 0;
	int* polynom2Coefficients = GetPolynomCoefficientArray(polynom2, polynom2Size, &coefficients2Size);
	free(polynom2);
	polynom2 = NULL;

	int* resultPolynom = NULL, resultSize = 0;
	int* remainderPolynom = NULL, remainderSize = 0;
	switch (action)
	{
	case'+':
		resultPolynom = GetPolynomsSum(polynom1Coefficients, coefficients1Size, polynom2Coefficients, coefficients2Size, &resultSize);
		break;
	case'-':
		resultPolynom = GetPolynomsSubstract(polynom1Coefficients, coefficients1Size, polynom2Coefficients, coefficients2Size, &resultSize);
		break;
	case'*':
		resultPolynom = MultiplyPolynoms(polynom1Coefficients, coefficients1Size, polynom2Coefficients, coefficients2Size, &resultSize);
		break;
	case'/':
		resultPolynom = DevidePolynoms(polynom1Coefficients, coefficients1Size, polynom2Coefficients, coefficients2Size, &resultSize, &remainderPolynom, &remainderSize);
		break;
	case'\'':
		resultPolynom = GetPolynomDerivative(polynom1Coefficients, coefficients1Size, &resultSize);
		break;
	default:
		printf("Wrong Action!!!");
		break;
	}

	PrintPolynom(resultPolynom, resultSize);
	if (remainderPolynom != NULL)
	{
		PrintPolynom(remainderPolynom, remainderSize);
		free(remainderPolynom);
		remainderPolynom = NULL;
	}

	free(polynom1Coefficients);
	polynom1Coefficients = NULL;
	free(polynom2Coefficients);
	polynom2Coefficients = NULL;
	free(resultPolynom);
	resultPolynom = NULL;

	return 0;
}
