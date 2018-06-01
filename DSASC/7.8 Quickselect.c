#include<stdio.h>
#include<stdlib.h>
#include"7.8 Quickselect.h"
#include"7.2 Insertion Sort.h"
#include"../Library/General.h"

#define Cutoff (3)
#define IndexError -2147483647

int Compare(ElementType X, ElementType Y)
{
	if (X > Y)
		return BIGGER;
	else if (X == Y)
		return EQUAL;
	else
		return SMALLER;
}

// for debugging
//void PrintSubList(ElementType List[], int Left, int Right)
//{
//	for (int i = 0; i <= Right; i++)
//	{
//		if (i < Left)
//			printf("%*c ", 4, ' ');
//		else
//			printf("%*d ", 4, List[i]);
//	}
//	puts("");
//}

// Return median of Left, Center and Right
// Order these and hide the pivot
ElementType
Median3(ElementType List[], int Left, int Right)
{
	int Center = (Left + Right) / 2;

	if (Compare(List[Left], List[Center]) == BIGGER)
		Swap(&List[Left], &List[Center]);
	if (Compare(List[Left], List[Right]) == BIGGER)
		Swap(&List[Left], &List[Right]);
	if (Compare(List[Center], List[Right]) == BIGGER)
		Swap(&List[Center], &List[Right]);
	// Invariant : List[Left] <= Left[Center] <= List[Right]
	
	// for debugging
	//printf("Median: %d %d %d\n", Left, Center, Right);
	//PrintSubList(List, Left, Right);

	Swap(&List[Center], &List[Right - 1]);	// Hide pivot
	return List[Right - 1];		// return Pivot
}

void
SubQuickselect(ElementType List[], int Left, int Right, int k)
{
	int i, j;
	ElementType Pivot;

	if (Left + Cutoff <= Right)
	{
		Pivot = Median3(List, Left, Right);
		i = Left;
		j = Right - 1;
		while (1)
		{
			while (Compare(List[++i], Pivot) == SMALLER);
			while (Compare(List[--j], Pivot) == BIGGER);
			if (i < j)
				Swap(&List[i], &List[j]);
			else
				break;
		}
		Swap(&List[i], &List[Right - 1]);	// Restore Pivot
		
		// for debugging
		//printf("subQuicksort i: %4d j: %4d\n", i, j);
		//PrintSubList(List, Left, Right);
		if (k < i)
			SubQuickselect(List, Left, i - 1, k);
		else if (k > i)
			SubQuickselect(List, i + 1, Right, k);
	}
	else	// Do an insertion sort on the subarray
	{
		InsertionSort(List + Left, Right - Left + 1);

		// for debugging
		//printf("Insertion Sort: Left: %2d Right: %2d Length: %2d\n", Left, Right, Right - Left + 1);
		//PrintSubList(List, Left, Right);
	}
}

ElementType
Quickselect(ElementType List[], int Length, int k)
{
	if (k > 0 && k <= Length)
	{
		k--;
		SubQuickselect(List, 0, Length - 1, k);
		return List[k];
	}
	else
		return IndexError;
}

void
SubQuicksort(ElementType List[], int Left, int Right)
{
	int i, j;
	ElementType Pivot;

	if (Left + Cutoff <= Right)
	{
		Pivot = Median3(List, Left, Right);
		i = Left;
		j = Right - 1;
		while (1)
		{
			while (Compare(List[++i], Pivot) == SMALLER);
			while (Compare(List[--j], Pivot) == BIGGER);
			if (i < j)
				Swap(&List[i], &List[j]);
			else
				break;
		}
		Swap(&List[i], &List[Right - 1]);	// Restore Pivot

		// for debugging
		//printf("subQuicksort i: %4d j: %4d\n", i, j);
		//PrintSubList(List, Left, Right);

		SubQuicksort(List, Left, i - 1);
		SubQuicksort(List, i + 1, Right);
	}
	else	// Do an insertion sort on the subarray
	{
		InsertionSort(List + Left, Right - Left + 1);

		// for debugging
		//printf("Insertion Sort: Left: %2d Right: %2d Length: %2d\n", Left, Right, Right - Left + 1);
		//PrintSubList(List, Left, Right);
	}
}

void
Quicksort(ElementType List[], int Length)
{
	SubQuicksort(List, 0, Length - 1);
}