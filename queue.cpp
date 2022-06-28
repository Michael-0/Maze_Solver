#include "queue.h"
#include <iostream>
using namespace std;

int point::getx()
{
	return x;
}

void point::setpoint(int newx, int newy)
{
	x = newx;
	y = newy;
}

point::point(int p, int q)
{
	x = p; y = q;
}

int point::gety()
{
	return y;
}


queue::queue() {
       // initialize an empty queue
       front = 0; rear = 0; size = 0;
       for (int j=0; j < MSIZE; ++j)
           Q[j] = 0;
       }
      
void queue::insert(int n,int m){
	 point* temp = new point(n,m);
	 insert(temp);
       }
 
void queue::insert(point* x) {
         if (size != MSIZE) {
	   front++; size++;
           if (front == MSIZE) front = 0;
	      Q[front] = x;
         }
       } 

point* queue::del() {
          if (size != 0) {
	      rear++; if (rear == MSIZE) rear = 0;
	      //point temp(Q[rear]->getx(), Q[rear]->gety());
	      size--;
	    return Q[rear];;
          }
          else return new point(-1,-1);
       }

void queue::print() {
 	   for (int j = 1; j <= size; ++j) {
   	   	int i = front - j + 1;
           	cout << "x = " << Q[i]->getx() << " y = " 
					<< Q[i]->gety() << endl;
           	}
 	   cout << "-----------------------" << endl;
       }

bool queue::isEmpty() {
  	   return (size == 0);
      }

