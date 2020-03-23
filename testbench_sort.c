#include <stdio.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <Windows.h>

#define printarr(arr, n) printf("\n\n");for(int a = 0; a < n; a++)printf("%d, ", arr[a]);

float testbench(int, int, int, int);
int* counting_sort(int*, int, int);

int main(void) {
	int show;
	int try = 0;
	do {
		try++;
		system("cls");
		printf("Show Array? Y/N\n\n");
		show = _getch();
		if (show == 'Y' || show == 'y') show = 1;
		else show = 0;

		for (int i = 0; i < 5; i++) {
			printf("Try %d | Data 10^%d | RT : %6.1f ns\n", try, i + 2, testbench(1, 100, pow(10, i + 2), show));
			if (show == 1) system("pause");
		}

		printf("\nRetry? Y/N");
		show = _getch();
		if (show == 'Y' || show == 'y') show = 1;
		else show = 0;
	}
	while (show == 1);
	return 0;
}

float testbench(int min_number, int max_number, int n_data, int show) {
	srand(time(NULL));

	//Generating Array
	int* arr = malloc(sizeof(int) * n_data);
	for (int a = 0; a < n_data; a++) {
		//Generating Random Number
		arr[a] = rand() % (max_number + 1 - min_number) + min_number;
	}

	if (show == 1) { printarr(arr, n_data) };

	//Star RunningTime Counter
	clock_t rt = clock();
	//Sorting

	arr = counting_sort(arr, max_number, n_data); //SORTING FUNCTION HERE

	//Stop RunningTime Counter
	rt = clock() - rt;

	if (show == 1) { printarr(arr, n_data) };
	free(arr);
	return (float)rt;
}

/*  Counting sort function  */
int* counting_sort(int* A, int k, int n)
{
	int i, j;
	int* B = malloc(sizeof(int) * n);
	int* C = malloc(sizeof(int) * (k + 1));

	//Initializing counting array C[i] to 0
	for (i = 0; i <= k; i++)
		C[i] = 0;
	//Store count of each element in array C
	for (j = 0; j < n; j++)
		C[A[j]] = C[A[j]] + 1;

	/* Change C[i] such that it contains actual
	position of these elements in output array*/
	for (i = 1; i < k + 1; i++)
		C[i] = C[i] + C[i - 1];

	//Creating Output array from C[i]
	//and decrementing value of C[i].
	for (j = n - 1; j >= 0; j--)
	{
		B[C[A[j]] - 1] = A[j];
		C[A[j]] = C[A[j]] - 1;
	}

	free(A);
	free(C);
	return B;
}
