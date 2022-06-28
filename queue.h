#ifndef QUEUE_H
#define QUEUE_H

const int MSIZE = 1000;
// point class is used by queue class
class point{
	private:
		int x; 
		int y;
		

	public:
		point(int p, int q);
		int getx();
		int gety();
		void setpoint(int newx, int newy);
};

class queue {
	private:
		point* Q[MSIZE];
		int front, rear, size;

	public:
		queue();
		void insert (int n, int m);
		void insert(point* x);
		point* del();
		void print();
		bool isEmpty();
};
#endif
