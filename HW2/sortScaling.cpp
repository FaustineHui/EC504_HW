#include<iostream>
#include<iomanip>
#include <cstdlib> 
#include <time.h>
#include <math.h>
#include <fstream>
#include "sorting.h"
using namespace std;

#define Debug 0

// Debugging routine: (Good Software would put this in seperate test.h)
void printArray(int a[], int N)
{
	cout << "N =" << N << endl;
	for (int i = 0; i < N; i++)
		cout << a[i] << "\n";
}

int main()
{
	int num[10];
	for (int i = 0; i < 10; i++)
		num[i] = pow(2, i + 4);

	int insertcount = 0;
	int mergecount = 0;
	int quickcount = 0;
	int shellcount = 0;
	int errorinsert[100];
	int errormerge[100];
	int errorquick[100];
	int errorshell[100];
	// ofstream outn("N.txt");
	// ofstream outinsert("insertion.txt");
	// ofstream outmerge("merge.txt");
	// ofstream outquick("quick.txt");
	// ofstream outshell("shell.txt");
	ofstream outall("output.txt");

	outall << setw(5) << "#N" << setw(20) << "insertionSort" << setw(20) << "errorbar" << setw(20) << "mergeSort" << setw(20)
		<< "errorbar" << setw(20) << "quickSort" << setw(20) << "errorbar" << setw(20) << "shellSort" << setw(20) << "errorbar" << endl;
	for (int m = 0; m < 10; m++) {
		int N = num[m];
		int a[N];
		int a_save[N];
		int a_tmp[N];

		srand(137);
		for (int i = 0; i < 32; i++)
			a[i] = (rand() + 1) % 1000000;

		insertcount = 0;
		mergecount = 0;
		quickcount = 0;
		shellcount = 0;

		int Ncases = 100;
		for (int j = 0; j < Ncases; j++)
		{
			for (int i = 0; i < N; i++)
				a_save[i] = a[i];

			swapCount = 0;
			insertionsort(a, N);
			cout << "Case = " << j << " InsertionSort swapCount " << swapCount << endl;
			insertcount += swapCount;
			errorinsert[j] = swapCount;

			swapCount = 0;
			for (int i = 0; i < N; i++)
				a[i] = a_save[i];
			mergeSort(a, a_tmp, 0, N - 1);
			cout << "Case = " << j << " MergeSort swapCount " << swapCount << endl;
			mergecount += swapCount;
			errormerge[j] = swapCount;

			swapCount = 0;
			for (int i = 0; i < N; i++)
				a[i] = a_save[i];
			quicksort(a, 0, N - 1);
			cout << "Case = " << j << " QuickSort swapCount " << swapCount << endl;
			quickcount += swapCount;
			errorquick[j] =  swapCount;

			swapCount = 0;
			for (int i = 0; i < N; i++)
				a[i] = a_save[i];
			shellsort(a, N);
			cout << "Case = " << j << " ShellSort swapCount " << swapCount << endl;
			shellcount += swapCount;
			errorshell[j] = swapCount;

			for (int i = 0; i < N; i++)
				a[i] = a_save[i];
			initialize_and_permute(a, N);
		}
		double insertresult = insertcount / 100;
		double mergeresult = mergecount / 100;
		double quickresult = quickcount / 100;
		double shellresult = shellcount / 100;
		double errorinresult = 0;
		double errormeresult = 0;
		double errorquresult = 0;
		double errorshresult = 0;

		for (int i = 0; i < 100; i++) {
			errorinresult += pow(errorinsert[i] - insertresult, 2);
			errormeresult += pow(errormerge[i] - mergeresult, 2);
			errorquresult += pow(errorquick[i] - quickresult, 2);
			errorshresult += pow(errorshell[i] - shellresult, 2);
		}

		errorinresult = errorinresult / 99;
		errorinresult = sqrt(errorinresult);
		errormeresult = errormeresult / 99;
		errormeresult = sqrt(errormeresult);
		errorquresult = errorquresult / 99;
		errorquresult = sqrt(errorquresult);
		errorshresult = errorshresult / 99;
		errorshresult = sqrt(errorshresult);

		// outn << N << "\n";
		// outinsert << insertresult << "\n";
		// outmerge << mergeresult << "\n";
		// outquick << quickresult << "\n";
		// outshell << shellresult << "\n";
		outall << setw(5) << N << setw(20) << insertresult << setw(20) << errorinresult << setw(20) << mergeresult << setw(20)
			<< errormeresult << setw(20) << quickresult << setw(20) << errorquresult << setw(20) << shellresult << setw(20) << errorshresult << endl;
	}
	// outn.close();
	// outinsert.close();
	// outmerge.close();
	// outquick.close();
	// outshell.close();
	outall.close();
}