// Copyright 2018 Richard Brower brower@bu.edu
#include <iostream>
#include <fstream>
#include <chrono>
#include <stdio.h>
#include <string.h>
using namespace std;

/***********************************************************
Given two arrays: FirstVertex pointing to the EdgeList with destination 
node for an undirected graph G(V,E). 

The input file begins with number of vertices (V = |V|)
and number of edges (E =|E|) and the list of value for 

int FirstVertex[V+1]
int EdgeList[E+1]

The vertices(nodes) are numbered 0,..,|V| -1.  The last entry 
FirstVertex[V] = E pointing to  EdgeList[E] = -1;
represented as a null

You are to compute the number of the connected components.

************************************************************/

// Here is remendary Queue give at end of file.
typedef struct Queue
{
        int capacity;
        int size;
        int front;
        int rear;
        int *elements;
} Queue ;

Queue * createQueue(int maxElements);
void Enqueue(Queue *Q,int element);
int Dequeue(Queue *Q);
int find_connected_components(int *FirstVertex, int V, int *EdgeList,int E);
 void BFS(Queue *Q, int *Found, int *FirstVertex, int V, int *EdgeList,int E);
void PrintAdjacencyListFormat( int *FirstVertex, int V, int *EdgeList,int E);


int main(int argc, char *argv[]){

  chrono::time_point<chrono::steady_clock> start, stop; 
  chrono::duration<double> difference_in_time;
  double difference_in_seconds; // Holds the final run time
  
  ifstream infile1;
  int V;
  int E;
  int NumberCC;
  
  infile1.open(argv[1]);
  if(!infile1){
    cout << "Error opening file " <<endl;
    return -1;
  } 
  
     infile1 >> V;
     infile1 >> E;
    
    int *FirstVertex = new int[V+1];
    for(int i=0; i< V+1 ; i++)
      infile1 >> FirstVertex[i];
    
    FirstVertex[V] = E;
    
   
    int *EdgeList = new int[E+1];
    for(int i=0; i< E+1 ; i++)
      infile1 >> EdgeList[i];
    
    EdgeList[E] = -1;  // null flag
    
    infile1.close();
    

#if 1 // set to 1 to debug 
     cout << endl << "A print in Adjacency  List form to help with Debugging! " << endl;
     PrintAdjacencyListFormat(FirstVertex, V, EdgeList, E);
#endif
     
    
    /* Find NumberCC   */
    start = chrono::steady_clock::now();
    NumberCC=find_connected_components(FirstVertex, V, EdgeList,E);
    stop = chrono::steady_clock::now();
    difference_in_time = stop - start;
    difference_in_seconds = double(difference_in_time.count());
    
    //Begin output file : DO NOT CHANGE
    ofstream outfile(strcat(argv[1],"_out"));
    outfile << difference_in_seconds << endl;
    outfile << NumberCC << endl;
    //End output file

    return 0;
}


int find_connected_components(int *FirstVertex, int V, int *EdgeList,int E)
{  
    int NumberCC  = 0;
    int *Found = new int[V];
    fill_n(Found, V, -1);
    
    Queue *Q = createQueue(V);

    for(int StartNode=0 ; StartNode < V  ; StartNode++){
      if(Found[StartNode] == -1)
	{
	//Prachi printf added line below
	printf("%d ",StartNode);
      Enqueue(Q,StartNode); //push into quene and set found.
    	Found[StartNode] = 1;
    	BFS( Q,  Found, FirstVertex, V, EdgeList, E);
    	NumberCC++;
	}
    }
	//Prachi added printf line below
	printf("\n");
    
    return NumberCC;
}

void BFS(Queue *Q, int *Found, int *FirstVertex, int V, int *EdgeList,int E)
{
  int node;
  static int CountDequeue = 0;
  
    while(Q->size > 0)
    {
       node = Dequeue(Q);
       CountDequeue++;

       //Put children in Q.
       for(int nn = FirstVertex[node]; nn < FirstVertex[node +1]; nn++) 
	{
	  if(Found[EdgeList[nn]] == -1)
	    {
		//Prachi
		printf("%d ",EdgeList[nn]);
	      Enqueue(Q,EdgeList[nn]);
	      Found[EdgeList[nn]] = 1;
 	    }
	}

    }
}


/* QUEUE FUCTIONS */

Queue * createQueue(int maxElements)
{
        /* Create a Queue */
        Queue *Q;
        Q = (Queue*)malloc(sizeof(Queue));
        /* Initialise its properties */
        Q->elements = (int *)malloc(sizeof(int)*maxElements);
        Q->size = 0;
        Q->capacity = maxElements;
        Q->front = 0;
        Q->rear = -1;
        /* Return the pointer */
        return Q;
}

void Enqueue(Queue *Q,int element)
{
        /* If the Queue is full, we cannot push an element into it as there is no space for it.*/
        if(Q->size == Q->capacity)
        {
                printf("Queue is Full\n");
        }
        else
        {
                Q->size++;
                Q->rear = Q->rear + 1;
                /* As we fill the queue in circular fashion */
                if(Q->rear == Q->capacity)
                {
                        Q->rear = 0;
                }
                /* Insert the element in its rear side */ 
                Q->elements[Q->rear] = element;
        }
        return;
}

int  Dequeue(Queue *Q)
{
         int  element = -1;
        /* If Queue size is zero then it is empty. So we cannot pop */
        if(Q->size==0)
        {
	  //              printf("Queue is Empty\n");
                return element;
        }
        /* Removing an element is equivalent to incrementing index of front by one */
        else
        {       element = Q->elements[Q->front];
                Q->size--;
                Q->front++;
                /* As we fill elements in circular fashion */
                if(Q->front==Q->capacity)
                {
                        Q->front=0;
                }
        }
        return element;
}

void PrintAdjacencyListFormat(int *FirstVertex, int V, int *EdgeList,int E)
  {
    int v;
    int e;
    cout << "V = " << V << "  E = " <<E <<endl;
    for( v = 0; v < V; v++)
      {
	cout << endl;
	cout << v  << ": ";
	
	for(e = FirstVertex[v]; e < FirstVertex[v+1]; e++) 
	  cout << EdgeList[e]<< "-> ";

	cout <<"nil";
      }

    cout << endl;
    cout << v  << " : ";
    cout << EdgeList[e]  << " That's Edge List  nil  Folks " << endl;
 
  }