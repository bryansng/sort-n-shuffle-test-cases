#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sortAndShuffle.h"
#define DEBUG 1 	// must be enabled during unit testing.
#define DEFAULT 1	// 1 to choose given bias shuffle algo, 0 to choose unbias shuffle algo.

/*
 * This function sorts an array by
 * using the quick sort algorithm
 * Input
 * 		array: the array to be sorted
 * 		length:  the length of the array
 *
 */
void quickSort(int *array, int length){
	int i,j,swap, minIndex;

	for (i = 0 ; i < ( length - 1 ); i++)
	{
		minIndex = i;
		for (j = i+1; j < length; j++)
		{
			if (array[minIndex] > array[j])
				minIndex = j;
		}
		 /* swap functions */
		swap = array[minIndex];
		array[minIndex] = array[i];
		array[i] = swap;

		}
	}

/*
 * This function shuffles an array by
 * using the Fisher Yates algorithm
 * 		array: the array to be sorted
 * 		length:  the length of the array
 *
 */
void fisherYates(int *array, int length){
	int i,j,swap;
	
	// disabled to test for bias, added back in each test.
	#if (!DEBUG)
		srand(time(NULL));
	#endif
	
	#if DEFAULT
		// A Shuffle Algorithm - Biased shuffles.
		for (i = 1 ; i < length; i++)
		{
			j = rand() % i;
			if(j != i){
				// swap functions
				swap = array[i];
				array[i] = array[j];
				array[j] = swap;
			}
		}
	#else
		// Knuth Fisher Yates Algorithm - Unbiased shuffles.
		for (i = 0; i < length-1; i++)
		{
			j = i + (rand() % (length-i)); // from first to last.
			
			swap = array[i];
			array[i] = array[j];
			array[j] = swap;
		}
	#endif
}
