#include "7.2 Insertion Sort.h"
#include"../Library/General.h"
#define Compare(X, Y) (((X) > (Y)) ? (BIGGER) : (((X) == (Y)) ? (EQUAL) : (SMALLER)))

void InsertionSort(ElementType List[], int Length)
{
	ElementType Tmp;
	int j;

	for (int i = 1; i < Length; i++)
	{
		Tmp = List[i];
		for (j = i; j > 0 && Compare(List[j - 1], Tmp) == BIGGER; j--)
			List[j] = List[j - 1];
		List[j] = Tmp;
	}
}