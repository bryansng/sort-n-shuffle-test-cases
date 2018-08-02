#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sortAndShuffle.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#define DEBUG 0		// together with VERBOSE, shows end result percentage of each pattern, and its tolerance range.
#define VERBOSE 0	// shows bias towards which pattern.
#define DEVELOP 0	// shows percentage of each pattern in each run, i.e. each N.

/* Function tests a given unsorted array, if it sorts linearly (i.e. in ascending order). */
// Pass, because array sorted in ascending order.
void sortTestLinear(void)
{
	int arr[5] = {5, 3, 4, 1, 2};
	int arrSorted[5] = {1, 2, 3, 4, 5};
	quickSort(arr, 5);
	
	for (int i = 0; i < 5; i++)
		if (arr[i] != arrSorted[i])
		{
			CU_FAIL("quickSort not sorting correctly.");
			break;
		}
}

/* Function tests a given sorted array if its elements after sort will be untouched. */
// Pass, because sorted array sorts back to itself.
void sortTestSorted(void)
{
	int arr[5] = {1, 10, 100, 1000, 10000};
	int arrSorted[5] = {1, 10, 100, 1000, 10000};
	quickSort(arr, 5);
	
	for (int i = 0; i < 5; i++)
		if (arr[i] != arrSorted[i])
		{
			CU_FAIL("quickSort not sorting for already sorted numbers.");
			break;
		}
}

/* Function tests a given reversed sorted array if it will sort back in ascending order. */
// Pass, because array is resorted in ascending order.
void sortTestReverseSorted(void)
{
	int arr[5] = {10000, 1000, 100, 10, 1};
	int arrSorted[5] = {1, 10, 100, 1000, 10000};
	quickSort(arr, 5);
	
	for (int i = 0; i < 5; i++)
		if (arr[i] != arrSorted[i])
		{
			CU_FAIL("quickSort not sorting for reversed sorted numbers.");
			break;
		}
}

/* Function tests a given array with small numbers if it sorts in ascending order. */
// Pass, because numbers are sorted in ascending order as expected.
void sortTestSmall(void)
{
	int arr[5] = {16, 4, 2, 0, 8};
	int arrSorted[5] = {0, 2, 4, 8, 16};
	quickSort(arr, 5);
	
	for (int i = 0; i < 5; i++)
		if (arr[i] != arrSorted[i])
		{
			CU_FAIL("quickSort not sorting for small numbers.");
			break;
		}
}

/* Function tests a given array with large numbers if it sorts in ascending order. */
// Pass, because numbers are sorted in ascending order as expected.
void sortTestLarge(void)
{
	int arr[5] = {1024, 64, 256, 65536, 8};
	int arrSorted[5] = {8, 64, 256, 1024, 65536};
	quickSort(arr, 5);
	
	for (int i = 0; i < 5; i++)
		if (arr[i] != arrSorted[i])
		{
			CU_FAIL("quickSort not sorting for large numbers.");
			break;
		}
}

/* Function tests a given array with extremely large numbers if it sorts in ascending order. */
// Fail, because variables that are declared as type int can only hold 32-bits numbers, anything beyond that will consider as buffer overflow.
// [−32,767, +32,767] OR [-2,147,483,647 to +2,147,483,647]
void sortTestPos32Bits(void)
{
	int arr[5] = {1099511627775, 65536, 2147483647, 16777215, 4294967295};
	int arrSorted[5] = {65536, 16777215, 2147483647, 4294967295, 1099511627775};
	quickSort(arr, 5);
	
	for (int i = 0; i < 5; i++)
		if (arr[i] != arrSorted[i])
		{
			CU_FAIL("quickSort not sorting for positive numbers occupying memory space larger than 32-bits.");
			break;
		}
}

/* Function tests a given array with extremely small numbers if it sorts in ascending order. */
// Fail, because variables that are declared as type int can only hold 32-bits numbers, anything beyond that will consider as buffer overflow.
// [−32,767, +32,767] OR [-2,147,483,647 to +2,147,483,647]
void sortTestNeg32Bits(void)
{
	int arr[5] = {-1099511627775, -65536, -2147483647, -16777215, -4294967295};
	int arrSorted[5] = {-1099511627775, -4294967295, -2147483647, -16777215, -65536};
	quickSort(arr, 5);
	
	for (int i = 0; i < 5; i++)
		if (arr[i] != arrSorted[i])
		{
			CU_FAIL("quickSort not sorting for negative numbers occupying memory space larger than 32-bits.");
			break;
		}
}

/* Function tests a given array with repeated numbers if it sorts in ascending order. */
// Pass, because all the ones are sorted together as such.
void sortTestRepeated(void)
{
	int arr[5] = {5, 1, 1, 1, 5};
	int arrSorted[5] = {1, 1, 1, 5, 5};
	quickSort(arr, 5);
	
	for (int i = 0; i < 5; i++)
		if (arr[i] != arrSorted[i])
		{
			CU_FAIL("quickSort not sorting correctly for repeated numbers.\n");
			break;
		}
}

/* Function tests a given array with zeroes if it sorts in ascending order. */
// Pass, because all zeroes are smaller than positive numbers, and are sorted as such.
void sortTestZero(void)
{
	int arr[5] = {1, 0, 0, 2, 1};
	int arrSorted[5] = {0, 0, 1, 1, 2};
	quickSort(arr, 5);
	
	for (int i = 0; i < 5; i++)
		if (arr[i] != arrSorted[i])
		{
			CU_FAIL("quickSort not sorting when there is zero.");
			break;
		}
}

/* Function tests a given array with negative integers if it sorts in ascending order. */
// Pass, because negative numbers are sorted in the expected order.
void sortTestNegative(void)
{
	int arr[6] = {-1, 0, -10, -5, -3, 10};
	int arrSorted[6] = {-10, -5, -3, -1, 0, 10};
	quickSort(arr, 6);
	
	for (int i = 0; i < 6; i++)
		if (arr[i] != arrSorted[i])
		{
			CU_FAIL("quickSort not sorting for negative numbers.");
			break;
		}
}

/* Function tests a given array with decimals if it sorts in ascending order. */
// Pass, because numbers after decimal point is truncated, leaving integer parts. The array is then sorted as if it is an integer array.
void sortTestDecimal(void)
{
	int arr[5] = {432.133, -11.5, 12.3, 0.39, 2.4};
	int arrSorted[6] = {-11, 0, 2, 12, 432};
	quickSort(arr, 5);
	
	for (int i = 0; i < 5; i++)
		if (arr[i] != arrSorted[i])
		{
			CU_FAIL("quickSort not sorting for decimal numbers.");
			break;
		}
}

/* Function tests a given array of decimals and integers if it sorts in ascending order. */
// Pass, because numbers after decimal point is truncated, leaving integer parts. Integer numbers are left untouched.
void sortTestDecimalWithIntegers(void)
{
	int arr[5] = {432.133, -11, 12, 0.39, 2.4};
	int arrSorted[6] = {-11, 0, 2, 12, 432};
	quickSort(arr, 5);
	
	for (int i = 0; i < 5; i++)
		if (arr[i] != arrSorted[i])
		{
			CU_FAIL("quickSort not sorting for decimal numbers with integer numbers.");
			break;
		}
}

/* Function tests a given array with only 1 elements if it sorts in ascending order. */
// Pass, because it just compares with itself.
void sortTestOneElement(void)
{
	int arr[1] = {10};
	int arrSorted[1] = {10};
	quickSort(arr, 1);
	
	for (int i = 0; i < 1; i++)
		if (arr[i] != arrSorted[i])
		{
			CU_FAIL("quickSort not sorting for arrays with only 1 element.");
			break;
		}
}

/* Function tests a given array with no elements if it sorts in ascending order. */
// Fail, In C, we cannot declare arrays of size zero, and its useless to sort an empty array.
void sortTestEmpty(void)
{
	int arr[0] = {};
	int N = 0; // number of elements.
	
	quickSort(arr, N);
	
	if (N == 0)
		CU_FAIL("quickSort cannot sort arrays with no elements.");
}





/* Function tests a given array with no elements if it shuffles. */
// Fail, In C, we cannot declare arrays of size zero, and its useless to shuffle an empty array.
void shuffleTestEmpty(void)
{
	int arr[0] = {};
	int N = 0; // number of elements.
	
	fisherYates(arr, N);
	
	if (N == 0)
		CU_FAIL("fisherYates cannot shuffle arrays with no elements.");
}

/* Function tests a given array with only 1 element if it shuffles to itself. */
// Fail, because if statement in shuffle function prevents the fail.
void shuffleTestOneElement(void)
{
	int arr[1] = {1};
	int arrNotShuffled[1] = {1};
	
	fisherYates(arr, 1);
	
	if (arr[0] == arrNotShuffled[0])
		CU_FAIL("fisherYates not working for arrays with only 1 element as it will map back to itself.");
}

/* Function tests a given array by shuffling it 1000 times until we shuffled an array that has elements that map back to itself. If no such array exists, shuffle algorithm passes the test. NOTE: Function assumes that the elements in the array is not suppose to shuffle back to itself, whereas a real shuffle can shuffle back to itself. */
// Pass, because if statement in shuffle function prevents the fail.
void shuffleTestIndividual(void)
{
	int arrNotShuffled[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int exit = 0;
	
	for (int j = 1; j <= 1000; j++)
	{
		int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		
		srand(time(NULL));
		fisherYates(arr, 10);
		
		for (int i = 0; i < 10; i++)
			if (arr[i] == arrNotShuffled[i])
			{
				CU_FAIL("After shuffling, shuffled elements should not map back to original index.");
				exit = 1;
				break;
			}
			
		if (exit)
			break;
	}
}

/* Function tests given array by shuffling it 1000 times until we shuffled an array that maps all its elements back to itself. If no such array exists, shuffle algorithm passes the test. NOTE: Function assumes that the array is not suppose to shuffle back to itself, whereas a real shuffle can shuffle back to itself. */
// Pass, because if statement in shuffle function prevents the fail.
void shuffleTestToItself(void)
{
	int arrNotShuffled[3] = {1, 2, 3};
	
	for (int i = 1; i <= 1000; i++)
	{
		int arr[3] = {1, 2, 3};
		
		srand(time(NULL));
		fisherYates(arr, 3);
		
		if ((arr[0] == arrNotShuffled[0]) && (arr[1] == arrNotShuffled[1]) && (arr[2] == arrNotShuffled[2]))
		{
			CU_FAIL("After shuffling, shuffled arrays should not be the same as original.");
			break;
		}
	}
}

/* Function tests a given array for any bias. By testing a specific example where the number of elements is 3, and the array elements are 1, 2 and 3. NOTE: Function assumes that mapping back to itself is a shuffle, i.e., 1,2,3 after shuffle, can be 1,2,3 - 1,3,2 - 3,2,1 - 2,1,3. */
// Above two shuffle test cases are only sufficient for the shuffle algorithm used. To test for true shuffle-ness, the following test case should be sufficient.
// Fail, because shuffle algorithm is bias towards some pattern more than others.
void shuffleTestNotBias(void)
{
	double first = 0;	// 1,2,3
	double second = 0;	// 1,3,2
	double third = 0;	// 2,1,3
	double fourth = 0;	// 2,3,1
	double fifth = 0;	// 3,1,2
	double sixth = 0;	// 3,2,1
	
	int N = 1000;		// number of tries.
	srand(time(NULL));	// seed random generator with time to get random rand() each test.
	
	for (int i = 0; i < N; i++)
	{
		srand(rand());	// seed with random generator.
		int arr[3] = {1, 2, 3};
		fisherYates(arr, 3);
		
		// prints the shuffled array, for develop only.
		#if (DEVELOP)
			for (int j = 0; j < 3; j++)
				printf("%d ", arr[j]);
		#endif
		
		// Increments the variables based on the shuffled array pattern.
		//
		// There are 6 possibilities, 3! = 6.
		if (arr[0] == 1 && arr[1] == 2 && arr[2] == 3)
			first++;
		else if (arr[0] == 1 && arr[1] == 3 && arr[2] == 2)
			second++;
		else if (arr[0] == 2 && arr[1] == 1 && arr[2] == 3)
			third++;
		else if (arr[0] == 2 && arr[1] == 3 && arr[2] == 1)
			fourth++;
		else if (arr[0] == 3 && arr[1] == 1 && arr[2] == 2)
			fifth++;
		else if (arr[0] == 3 && arr[1] == 2 && arr[2] == 1)
			sixth++;
		
		// prints the probability of each pattern, in each round, for develops only.
		#if (DEVELOP)
			printf("\n");
			printf("1,2,3: %.2lf\%\n", first*100/N);
			printf("1,3,2: %.2lf\%\n", second*100/N);
			printf("2,1,3: %.2lf\%\n", third*100/N);
			printf("2,3,1: %.2lf\%\n", fourth*100/N);
			printf("3,1,2: %.2lf\%\n", fifth*100/N);
			printf("3,2,1: %.2lf\%\n", sixth*100/N);
			printf("\n");
		#endif
	}
	
	// calculates the final percentage of each pattern, assigns them into the pattern's respective variables.
	first *= 100.0/N;
	second *= 100.0/N;
	third *= 100.0/N;
	fourth *= 100.0/N;
	fifth *= 100.0/N;
	sixth *= 100.0/N;
	
	double tolerance = 4.0; // probability tolerance or threshold for acceptance.
	
	double left = (double) (100/6) - tolerance;		// left side.
	double right = (double) (100/6) + tolerance;	// right side.
	
	// prints tolerance and each pattern's percentage, for debug and verbose only.
	#if (DEBUG && VERBOSE)
		printf("\n\nResults accepted if each pattern percentage within range:\n");
		printf("left: %.2lf\n", left);
		printf("right: %.2lf\n\n", right);
		
		printf("1,2,3 %.2lf% - bias result: %d\n", first, !(first >= left && first <= right));
		printf("1,3,2 %.2lf% - bias result: %d\n", second, !(second >= left && second <= right));
		printf("2,1,3 %.2lf% - bias result: %d\n", third, !(third >= left && third <= right));
		printf("2,3,1 %.2lf% - bias result: %d\n", fourth, !(fourth >= left && fourth <= right));
		printf("3,1,2 %.2lf% - bias result: %d\n", fifth, !(fifth >= left && fifth <= right));
		printf("3,2,1 %.2lf% - bias result: %d\n\n", sixth, !(sixth >= left && sixth <= right));
	#endif
	
	if (first > right || second > right || third > right || fourth > right || fifth > right || sixth > right)
		CU_FAIL("Shuffle algorithm produces a bias.");
	
	// If not in the accepted range, consider test as fail, for verbose only.
	//
	// 16-tolerance < x < 16+tolerance
	#if (VERBOSE)
		if (!(first > left && first < right))
			CU_FAIL("Bias towards 1,2,3.");
		if (!(second > left && second < right))
			CU_FAIL("Bias towards 1,3,2.");
		if (!(third > left && third < right))
			CU_FAIL("Bias towards 2,1,3.");
		if (!(fourth > left && fourth < right))
			CU_FAIL("Bias towards 2,3,1.");
		if (!(fifth > left && fifth < right))
			CU_FAIL("Bias towards 3,1,2.");
		if (!(sixth > left && sixth < right))
			CU_FAIL("Bias towards 3,2,1.");
	#endif
}

int main()
{
	CU_initialize_registry();
	
	/*
	CU_pSuite sortSuite = CU_add_suite("sort", 0, 0);
	CU_add_test(sortSuite, "sortLinear", sortTestLinear);
	CU_add_test(sortSuite, "sortSorted", sortTestSorted);
	CU_add_test(sortSuite, "sortReverseSorted", sortTestReverseSorted);
	CU_add_test(sortSuite, "sortRepeated", sortTestRepeated);
	CU_add_test(sortSuite, "sortSmall", sortTestSmall);
	CU_add_test(sortSuite, "sortLarge", sortTestLarge);
	CU_add_test(sortSuite, "sortPos32Bits", sortTestPos32Bits);
	CU_add_test(sortSuite, "sortNeg32Bits", sortTestNeg32Bits);
	CU_add_test(sortSuite, "sortZero", sortTestZero);
	CU_add_test(sortSuite, "sortNegative", sortTestNegative);
	CU_add_test(sortSuite, "sortDecimal", sortTestDecimal);
	CU_add_test(sortSuite, "sortDecimalWithInts", sortTestDecimalWithIntegers);
	CU_add_test(sortSuite, "sortOneElement", sortTestOneElement);
	CU_add_test(sortSuite, "sortEmpty", sortTestEmpty);
	*/
	CU_pSuite shuffleSuite = CU_add_suite("shuffle", 0, 0);
	CU_add_test(shuffleSuite, "shuffleEmpty", shuffleTestEmpty);
	CU_add_test(shuffleSuite, "shuffleOneElement", shuffleTestOneElement);
	CU_add_test(shuffleSuite, "shuffleIndividual", shuffleTestIndividual);
	CU_add_test(shuffleSuite, "shuffleToItself", shuffleTestToItself);
	CU_add_test(shuffleSuite, "shuffleNotBias", shuffleTestNotBias);
	
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
}
