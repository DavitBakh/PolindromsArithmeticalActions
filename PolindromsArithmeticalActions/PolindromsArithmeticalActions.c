#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define PolyndromMaxSize 50
#define ExpressionMaxSize 10

int* GetPalindromeCoefficientArray(char palindrome[PolyndromMaxSize], int palindromSize, int* outResultSize)
{
	int* resultPalindrome = (int*)calloc(PolyndromMaxSize, sizeof(int));
	char palindromSegments[PolyndromMaxSize / 4 + 5][ExpressionMaxSize];

	int segmentsCount = 0;
	for (int i = 0, k = 0; i < palindromSize; i++)
	{
		if (palindrome[i] != '+' && palindrome[i] != '-')
		{
			palindromSegments[segmentsCount][k++] = palindrome[i];
			if (i + 1 == palindromSize)
				palindromSegments[segmentsCount][k] = '\0'; //string end
		}
		else
		{
			palindromSegments[segmentsCount][k] = '\0'; //string end
			k = 0;
			palindromSegments[++segmentsCount][k++] = palindrome[i];
		}
	}
	segmentsCount++;

	int maxIndex = 0;
	for (int i = 0; i < segmentsCount; i++)
	{
		char* current = palindromSegments[i];
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

		resultPalindrome[index] = coefficient;

		if (!i)
			maxIndex = index;
	}


	*outResultSize = maxIndex + 1;
	return resultPalindrome;
}

int main(void)
{
	char* palindrome1 = (char*)malloc(PolyndromMaxSize);
	char* palindrome2 = (char*)malloc(PolyndromMaxSize);
	char action[6];

	strcpy(palindrome1, "5x^3+2x^2+x+1");
	strcpy(palindrome2, "1x^3+5x+3");


	fgets(palindrome1, PolyndromMaxSize, stdin);
	fgets(action, PolyndromMaxSize, stdin);
	fgets(palindrome2, sizeof(palindrome2), stdin);

	int palindrome1Size = strlen(palindrome1);
	int palindrome2Size = strlen(palindrome2);

	int resultSize1 = 0;
	int* resultPolyndrom1 = GetPalindromeCoefficientArray(palindrome1, palindrome1Size, &resultSize1);

	int resultSize2 = 0;
	int* resultPolyndrom2 = GetPalindromeCoefficientArray(palindrome2, palindrome2Size, &resultSize2);

	/*for (int i = 0; i < resultSize1; i++)
	{
		printf("%d ", resultPolyndrom1[i]);
	}*/

	free(palindrome1);
	free(palindrome2);
	free(resultPolyndrom1);
	free(resultPolyndrom2);

	return 0;
}
