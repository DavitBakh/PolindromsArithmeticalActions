#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PolyndromMaxSize 50

int* GetPalindromeCoefficientArray(char palindrome[PolyndromMaxSize], int polyndromSize, int* outResultPalindromeSize)
{
	int* resultPalindrome = (int*)malloc(PolyndromMaxSize * sizeof(int));
	char temp[PolyndromMaxSize / 4 + 5][10];

	for (int i = 0, j = 0, k = 0; i < polyndromSize; i++)
	{
		if (palindrome[i] != '+' && palindrome[i] != '-')
		{
			temp[j][k++] = palindrome[i];
		}
		else
		{
			temp[j][k] = '\0'; //navsyaki konec stroki
			k = 0;
			temp[++j][k++] = palindrome[i];
		}
	}

	//size
	return resultPalindrome;
}

int main(void)
{
	char* palindrome1 = (char*)malloc(PolyndromMaxSize);
	char* palindrome2 = (char*)malloc(PolyndromMaxSize);

	strcpy(palindrome1, "5x^3+2x^2+x+1");
	strcpy(palindrome2, "1x ^ 3 + 5x + 3");
	char action[10];

	/*fgets(palindrome1, sizeof(palindrome1), stdin);
	fgets(action, sizeof(action), stdin);
	fgets(palindrome2, sizeof(palindrome2), stdin);*/

	int palindrome1Size = strlen(palindrome1);
	int palindrome2Size = strlen(palindrome2);

	int resultSize1 = 0;
	int* resultPolyndrom1 = GetPalindromeCoefficientArray(palindrome1, palindrome1Size, &resultSize1);

	free(palindrome1);
	free(palindrome2);
	free(resultPolyndrom1);

	return 0;
}
