#include <iostream>
#include <vector>
#include "EasyBMP.h"
#include "queue.h"
#include <cstdlib>

using namespace std;

bool inRange(int x, int y, BMP &input)
{
	bool isInRange;
	if (x < input.TellWidth() && x >= 0 && y < input.TellHeight() && y >= 0)
	{
		isInRange = true;
	}
	else 
	{
		isInRange = false;
	}
	return isInRange;
	
}

void BFS (BMP &input, BMP &output, point* s, point* t, int count, bool green)
{
	bool drawGreen = green;
	// Creating a max value
	int maxval = input.TellWidth() * input.TellHeight();

	// initialize a queue Q
	queue Q;
	
	// insert s into the queue
	Q.insert(s);

	count++;
	
	// copy input to output
	RangedPixelToPixelCopy(input, 0, input.TellWidth(), input.TellHeight(), 0, output, 0, 0);
	
	// initialize visited 2D array
	bool visited[input.TellWidth()][input.TellHeight()];
	
	// set all values of visited to false to start
	for (int i = 0; i < input.TellHeight(); i++)
		for (int j = 0; j < input.TellWidth(); j++)
			visited[j][i] = false;
	
	// setting the starting pixel visited to true	
	visited[s->getx()][s->gety()] = true;
	
	// initialize parent array of points;
	point* p[input.TellWidth()][input.TellHeight()];

	// initialize distance 2D vector
	int d[input.TellWidth()][input.TellHeight()];
	
	
	// setting all other values of distance to MaxInt
	for (int i = 0; i < input.TellHeight(); i++)
	{
		for (int j = 0; j < input.TellWidth(); j++)
		{
			d[j][i] = maxval;
		}
	}
	// set start point distance to 0
	d[s->getx()][s->gety()] = 0;


	while (!Q.isEmpty() && !visited[t->getx()][t->gety()])
	{
		point* u = Q.del();
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (abs(j) + abs(i) < 2)
				{
					// going to the neighbors up down left and right
					int x = u->getx() + j;
					int y = u->gety() + i;
					if (inRange(x, y, input) && input(x,y)->Blue == 255 )
					{

					if (!visited[x][y])
					{
						
						visited[x][y] = true;
						d[x][y] = (d[u->getx()][u->gety()]) + 1;
						int dis = d[x][y];
						p[x][y] = u;
						point* v = new point(x, y);
						Q.insert(v);
						count++;
						/*
						 * Makes every pixel checked turn green.
						 * Still shows the red path over the green
						 */

						if (drawGreen == true)
						{
							output(x,y)->Red = 0;
							output(x,y)->Green = 255;
							output(x,y)->Blue = 0;
						}
					}
					else
					{
						;
					}
					}
				}
			}
		}		
	}
	if (visited[t->getx()][t->gety()] == true)
	{
		point* v = t;
		while (v->getx() != s->getx() || v->gety() != s->gety())
		{
			output(v->getx(), v->gety())->Red = 255;
			output(v->getx(), v->gety())->Blue = 0;
			output(v->getx(), v->gety())->Green = 0;
			v = p[v->getx()][v->gety()];
		}
		output.WriteToFile("output.bmp");
		cout << "The distance to t is: " << d[t->getx()][t->gety()] << endl;
		cout << "Count: " << count << endl;
	}
	else
	{
		cout << "No path from s to t" << endl;
		output.WriteToFile("output.bmp");
	}	

}


void MakeBW (BMP &input)
{
	int w = input.TellWidth();
	int h = input.TellHeight();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			int avgval= 0;
			avgval = (input(j,i)->Red + input(j,i)->Green + input(j,i)->Blue)/3;
			if (avgval >= 128)
			{
				input(j,i)->Red = 255;
				input(j,i)->Green = 255;
				input(j,i)->Blue = 255;
			}
			else
			{
				input(j,i)->Red = 0;
				input(j,i)->Green = 0;
				input(j,i)->Blue = 0;
			}
		}
	}
}
int main()
{
	BMP input;
	BMP output;
	input.ReadFromFile("input.bmp");
	output.SetSize(input.TellWidth(), input.TellHeight());
	output.SetBitDepth(24);
	// User entering start and end point
	int sx = 0;
	int sy = 0;
	int tx = 0;
	int ty = 0;
	cout << "Enter a start x: ";
	cin >> sx;
	cout << endl;
	cout << "Enter a start y: ";
	cin >> sy;
	cout << endl;
	cout << "Enter an end x: ";
	cin >> tx;
	cout << endl;
	cout << "Enter an end y: ";
	cin >> ty;
	cout << endl;

	//Checking the point to make sure it is within the image and not a black pixel
	bool wrongInput = false;
	if (sx >= input.TellWidth() || sy >= input.TellHeight())
	{
		cout << "The start pixel is outside the image" << endl;
		wrongInput = true;
	}

	if (tx >= input.TellWidth() || ty >= input.TellHeight())
	{
		cout << "The target is outside the image" << endl;
		wrongInput = true;
	}	

	if (wrongInput == false && input(sx,sy)->Blue == 0)
	{
		cout << "The start pixel is on a black square" << endl;
		wrongInput = true;
	}

	if (wrongInput == false && input(tx,ty)->Blue == 0)
	{
		cout << "The end pixel is on a black square" << endl;
		wrongInput = true;
	}
	if (wrongInput)
	{
		return 0;
	}

	point* s = new point(sx, sy);
	point* t = new point(tx, ty);
	MakeBW(input);
	BFS (input, output, s, t, 0, true);
	return 0;
}
