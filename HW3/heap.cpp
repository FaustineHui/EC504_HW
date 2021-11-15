#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>
#include <math.h>
#include <iomanip>
#include <cstdlib>
#include <ratio>
using namespace std;


/***********************************************************
Main progam template build a Max Heap and Heap Sort in place
************************************************************/

static int OpCount = 0;

int localSize = 100;

void mergeSort(int *a, int *a_tmp, int l, int r);

void Heapify(int *Heap, int n);
void CheckHeapOrder(int *Heap,int n);
int  DeleteHeap(int index,int *Heap,int ntemp);
void InsertHeap(int value ,int *Heap, int ntemp);
void HeapSort(int *Heap, int n);

void swap(int* a, int* b)
{
    //OpCount++;//
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int  uniform(int  m)
{
    srand(time(0));
    return rand() % m;
}

void initialize_and_permute(int* permutation, int n)
{
    for (int i = 0; i <= n - 2; i++) {
        int  j = i + uniform(n - i); /* A random integer such that i ¡Ü j < n */
        swap(&permutation[i], &permutation[j]);   /* Swap the randomly picked element with permutation[i] */
    }
}

int main(int argc, char *argv[]) 
{
  /* Timeing and IO setup */
  chrono::time_point<chrono::steady_clock> start, stop; 
  chrono::duration<double> difference_in_time;
/*  double difference_in_seconds_heap_sort; */ // Holds the final run time
  ifstream infile;
  ofstream outfile;
  
  /* Local data */
  int n;
 
  
  // Input Data:  DO NOT CHANGE 
  infile.open(argv[1]);

  int* Heap = NULL;
  
  if(!infile)
    {
      cout << "No input files so genearated internal random file of size = "<<  localSize  << endl;
      n = localSize;
      cout << "n  = " << n << endl;
      Heap = new int[n+1];
      Heap[0] = n;  // Set zero entry in in heap to n
      for(int i=1; i<n+1 ; i++)  Heap[i] = rand()%100000;
      // Define out put file
       outfile.open("SortedRandomList.dat");
    }
  else
    {
      infile >> n;
      Heap = new int[n+1];
      Heap[0] = n;  // Set zero entry in in heap to n	    
      for(int i=1; i<n+1 ; i++) infile >> Heap[i];
      infile.close();
      // Define out put file 
      outfile.open(strcat(argv[1],"_out"));
    }

   /* Set up Heat */
   
   Heapify(Heap, n);

   CheckHeapOrder(Heap,n);
   
     /* Practive delete and insert */
 
   int ntemp = n;
   int index = 0;
   int value = -1;

   /* 
 You might want to do a Merge Sort and compare to make sure you haven't lost anything and compare with the Merge Sort after Insert/Delete test!
 */
   
# if 1   
   // Try Deleting 5 
   for(int k = 0; k <5; k++)
     {
       index = rand()%n + 1;
       value = DeleteHeap(index,Heap,ntemp); // Also reHeapfies 
       Heap[ntemp] = value;
       ntemp--;
     }
   //Reinsert 5       
   for(int k = 0; k <5; k++)
     {
       value = Heap[ntemp +1];
       InsertHeap(value,Heap, ntemp); // Also reHeapfies
       ntemp++;
     }
      CheckHeapOrder(Heap,n); // Is it still a  Heap?
#endif
      
/* 
 Test and compare  efficiency of Heap Sort  relative to Merge Sort
 */
      
/*  int* a_tmp = new int[n+1];   */   
      
  OpCount = 0;
  start = chrono::steady_clock::now();
   //mergeSort(Heap, a_tmp,  1, n);//
   // REPLACE WITH HEAP SORT //
  HeapSort(Heap, n);
  stop = chrono::steady_clock::now();
  cout << chrono::duration_cast<chrono::microseconds>(stop - start).count() << endl;
  //Begin output file : DO NOT CHANGE  
 
  outfile << Heap[0] << endl;
  for(int i=1; i< Heap[0]+1  ; i++)
    outfile << Heap[i] << endl;

  //End output file

  ofstream outall("partb1.txt");
  outall << setw(10) << "#N" << setw(30) << "HeapSort (time:microseconds)"<< endl;

  for (int i = 0; i < 17; i++) {
      int index = i + 3;
      int N = pow(2, index);
      Heap = new int[N + 1];
      Heap[0] = N;  // Set zero entry in in heap to n
      srand(time(0));
      for (int i = 1; i < N + 1; i++)  Heap[i] = rand() % 100000;

      OpCount = 0;
      start = chrono::steady_clock::now();
      HeapSort(Heap, N);
      stop = chrono::steady_clock::now();
      double result = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
      result = result / 1000;
      outall << setw(10) << N << setw(30) << result << endl;
  }
  outall.close();

  //ofstream outall("partb2.txt");
  //outall << setw(10) << "#Round" << setw(30) << "HeapSort (time:microseconds)" << endl;
  //int k = 100;
  //Heap[0] = k;  // Set zero entry in in heap to n
  //for (int i = 1; i < k + 1; i++) {
  //    Heap[i] = rand() % 100000;
  //}
  //
  //int* tempHeap = NULL;
  //tempHeap = new int[k + 1];
  //for (int i = 0; i < k + 1; i++) {
  //    tempHeap[i] = Heap[i];
  //}
  //for (int i = 0; i < 100; i++) {
  //    start = chrono::steady_clock::now();
  //    HeapSort(tempHeap, k);
  //    stop = chrono::steady_clock::now();
  //    int Round = i + 1;
  //    double result = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
  //    result = result / 1000;
  //    outall << setw(10) << Round << setw(30) << result << endl;
  //    for (int j = 0; j < k + 1; j++) tempHeap[j] = Heap[j];
  //    initialize_and_permute(tempHeap, k);
  //}
  //outall.close();

  //ofstream outall("partb3.txt");
  //outall << setw(10) << "#N" << setw(30) << "HeapSort (time:microseconds)" << endl;
  //
  //for (int i = 0; i < 17; i++) {
  //    int index = i + 3;
  //    int N = pow(2, index);
  //    Heap = new int[N + 1];
  //    Heap[0] = N;  // Set zero entry in in heap to n
  //    for (int j = 1; j < N + 1; j++)  Heap[j] = rand() % 100000;

  //    int* tempHeap = NULL;
  //    tempHeap = new int[N + 1];
  //    for (int j = 0; j < N + 1; j++) tempHeap[j] = Heap[j];

  //    double average = 0;
  //    for (int j = 0; j < 100; j++) {
  //        start = chrono::steady_clock::now();
  //        HeapSort(tempHeap, N);
  //        stop = chrono::steady_clock::now();
  //        average += chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
  //        //cout << average << endl;
  //        for (int k = 0; k < N + 1; k++) tempHeap[k] = Heap[k];
  //        initialize_and_permute(tempHeap, N);
  //    }
  //    double result = average / 100000;
  //    //cout << result << endl;
  //    outall << setw(10) << N << setw(30) << result << endl;
  //}
  //outall.close();
  return 0;
}

void mergeSort(int *a, int *a_tmp, int l, int r)
{

    int i, j, k, m;
   
    if (r > l)
      {
        m = (r+l)/2;
        mergeSort(a, a_tmp, l, m);  
        mergeSort(a,a_tmp, m+1, r);
        for (i = m+1; i > l; i--){
          a_tmp[i-1] = a[i-1];
        }
        for (j = m; j < r; j++){
          a_tmp[r+m-j] = a[j+1]; 
        }
        for (k = l; k <= r; k++){
          a[k] = (a_tmp[i] < a_tmp[j]) ? a_tmp[i++] : a_tmp[j--];       
        }
      }
  }


/****************************************
Provide funtions below
****************************************/

 void maxheap(int* Heap, int n, int i) {
     int leftnode = 2 * i;
     int rightnode = 2 * i + 1;
     int maximum = i;
     if (leftnode <= n && Heap[leftnode] > Heap[maximum]) maximum = leftnode;
     if (rightnode <= n && Heap[rightnode] > Heap[maximum]) maximum = rightnode;
     if (maximum != i) {
         swap(&Heap[maximum], &Heap[i]);
         maxheap(Heap, n, maximum);
     }
 }
//void maxheap(int* Heap, int n, int i) {
//    int father = i;
//    int leftnode = 2 * father;
//    while (leftnode <= n) {
//        if (leftnode < n && Heap[leftnode] < Heap[leftnode+1]) {
//            leftnode++;
//        }
//        if (Heap[father] < Heap[leftnode]) {
//            swap(&Heap[father], &Heap[leftnode]);
//            father = leftnode;
//            leftnode = 2 * father;
//        }
//        else break;
//    }
//}

 void Heapify(int *Heap, int n)
 {
     for (int i = n / 2; i > 0; i--) {
         maxheap(Heap, n, i);
     }
 }

 void  CheckHeapOrder(int *Heap,int n)
  {
     for (int i = n; i >= 2; i--) {
         int father = i / 2;
         if (Heap[i] > Heap[father]) {
             cout << "The order is False." << endl;
             break;
         }
         else if(i == 2) {
             cout << "The order is True." << endl;
         }
     }
  }

int  DeleteHeap(int index,int *Heap,int ntemp)
{
  int save = Heap[index];
  Heap[index] = Heap[ntemp];
  Heapify(Heap, ntemp - 1);
  return  save;
}
void InsertHeap(int value ,int *Heap, int ntemp)
{
    Heap[ntemp + 1] = value;
    Heapify(Heap, ntemp + 1);
}
void HeapSort(int *Heap, int n)
{
    Heapify(Heap, n);
    for (int i = n; i >= 2; i--) {
        swap(&Heap[i], &Heap[1]);
        maxheap(Heap, i - 1, 1);
    }
}
