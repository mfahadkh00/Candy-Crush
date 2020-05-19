#pragma once
#include<iostream>
using namespace std;
const int gsize = 10, target = 500, moves = 20;
int rstart = 0, cstart = 0;//denotes starting index of popped candies
char poptype = 0;// whether pop is in a row or a column (r=row, c=column,t=T wrapped, l=L wrapped
int cpopped = 0;//number of candies popped
char candycolor; //color of candy that popped
int randgen()
{
	//to return a random number/candy
	int x = rand() % 5 + 1; //random number between 1 and 5

	return x;
}
void gridup(int grid[][gsize])
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			//grid[i][j] = randgen();
			cout << grid[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl << endl << endl;
}
void gridgen(int grid[][gsize])
{

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			grid[i][j] = randgen();
			//cout << grid[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl << endl << endl;


	grid[3][5] = 5;
	grid[3][6] = 5;
	grid[3][7] = 5;
	grid[3][8] = 5;
	grid[3][9] = 5;

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			//grid[i][j] = randgen();
			cout << grid[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl << endl << endl;
}
char colorcheck(int i)
{
	switch (i)
	{
	case (1):
	{
		return 'r';
		break;
	}
	case 6:
	{
		return 'r';
		break;
	}
	case 11:
	{
		return 'r';
		break;
	}
	case (2):
	{
		return 'b';
		break;
	}
	case (7):
	{
		return 'b';
		break;
	}
	case (12):
	{
		return 'b';
		break;
	}
	case 3:
	{
		return 'g';
		break;
	}
	case 8:
	{
		return 'g';
		break;
	}
	case 13:
	{
		return 'g';
		break;
	}
	case 4:
	{
		return 'y';
		break;
	}
	case 9:
	{
		return 'y';
		break;
	}
	case 14:
	{
		return 'y';
		break;
	}
	case 5:
	{
		return 'o';
		break;
	}
	case 10:
	{
		return 'o';
		break;
	}
	case 15:
	{
		return 'o';
		break;
	}

	}
}

void plain(int grid[][gsize])
{

	for (int i = 0; i < gsize; i++)
	{
		for (int j = 0; j < gsize; j++)
		{
			if ((grid[i][j] == grid[i + 1][j] && grid[i + 1][j] == grid[i + 2][j]) && grid[i][j] <= 5)
			{
				grid[i][j] = 0;
				grid[i + 1][j] = 0;
				grid[i + 2][j] = 0;
				rstart = i;
				cstart = j;
				poptype = 'r';
				cpopped = 3;
				candycolor = colorcheck(grid[i][j]);
			}
			if (grid[i][j] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j + 2] && grid[i][j] <= 5)
			{
				grid[i][j] = 0;
				grid[i][j + 1] = 0;
				grid[i][j + 2] = 0;
				rstart = i;
				cstart = j;
				poptype = 'c';
				cpopped = 3;
				candycolor = colorcheck(grid[i][j]);
			}
		}
	}
}
void stripes(int grid[][gsize])
{
	for (int i = 0; i < gsize; i++)
	{
		for (int j = 0; j < gsize; j++)
		{
			if ((grid[i][j] <= 5) && (grid[i][j] == grid[i + 1][j] && grid[i + 1][j] == grid[i + 2][j] && grid[i + 2][j] == grid[i + 3][j]))
			{
				grid[i][j] = 0;
				grid[i + 1][j] = 0;
				grid[i + 2][j] = 0;
				grid[i + 3][j] = 0;
				rstart = i;
				cstart = j;
				poptype = 'r';
				cpopped = 4;
				candycolor = colorcheck(grid[i][j]);
				grid[i][j] += 5; //changes one plain candy to a striped candy of same color
			}
			if ((grid[i][j] <= 5) && (grid[i][j] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j + 2] && grid[i][j + 2] == grid[i][j + 3]))
			{
				grid[i][j] = 0;
				grid[i][j + 1] = 0;
				grid[i][j + 2] = 0;
				grid[i][j + 3] = 0;
				rstart = i;
				cstart = j;
				poptype = 'c';
				cpopped = 4;
				candycolor = colorcheck(grid[i][j]);
				grid[i][j] += 5; //changes one plain candy to a striped candy of same color
			}
		}
	}
}
void colorbomb(int grid[][gsize])
{
	for (int i = 0; i < gsize; i++)
	{
		for (int j = 0; j < gsize; j++)
		{
			if ((grid[i][j] <= 5) && (grid[i][j] == grid[i + 1][j] && grid[i + 1][j] == grid[i + 2][j] && grid[i + 2][j] == grid[i + 3][j] && grid[i + 4][j]))
			{
				grid[i][j] = 0;
				grid[i + 1][j] = 0;
				grid[i + 2][j] = 0;
				grid[i + 3][j] = 0;
				grid[i + 4][j] = 0;
				rstart = i;
				cstart = j;
				poptype = 'r';
				cpopped = 5;
				grid[i][j] = 16;
			}
			if ((grid[i][j] <= 5) && (grid[i][j] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j + 2] && grid[i][j + 2] == grid[i][j + 3] && grid[i][j + 3] == grid[i][j + 4]))
			{
				grid[i][j] = 0;
				grid[i][j + 1] = 0;
				grid[i][j + 2] = 0;
				grid[i][j + 3] = 0;
				grid[i][j + 4] = 0;
				rstart = i;
				cstart = j;
				poptype = 'c';
				cpopped = 5;
				grid[i][j] = 16;
			}
		}
	}
}
void wrapped(int grid[][gsize])
{
	for (int i = 0; i < gsize; i++)
	{
		for (int j = 0; j < gsize; j++)
		{
			if (grid[i][j] <= 5 && grid[i][j] == grid[i + 1][j] && grid[i + 1][j] == grid[i + 2][j] && grid[i + 1][j] == grid[i + 1][j + 1] && grid[i + 1][j] == grid[i + 1][j + 2])
			{
				grid[i][j] = 0;
				grid[i + 1][j] = 0;
				grid[i + 2][j] = 0;
				grid[i + 1][j + 1] = 0;
				grid[i + 1][j + 2] = 0;
				rstart = i;
				cstart = j;
				poptype = 't';
				cpopped = 5;
				grid[i][j] += 10;
			}
			if (grid[i][j] <= 5 && grid[i][j] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j + 2] && grid[i][j + 1] == grid[i + 1][j + 1] && grid[i + 1][j] == grid[i + 2][j + 1])
			{
				grid[i][j] = 0;
				grid[i][j + 1] = 0;
				grid[i][j + 2] = 0;
				grid[i + 1][j + 1] = 0;
				grid[i + 1][j + 1] = 0;
				rstart = i;
				cstart = j;
				poptype = 't';
				grid[i][j] += 10;
				cpopped = 5;
			}
			if (grid[i][j] <= 5 && grid[i][j] == grid[i + 1][j] && grid[i + 1][j] == grid[i + 2][j] && grid[i + 1][j] == grid[i + 2][j + 1] && grid[i + 2][j + 1] == grid[i + 2][j + 2])
			{
				grid[i][j] = 0;
				grid[i + 1][j] = 0;
				grid[i + 2][j] = 0;
				grid[i + 2][j + 1] = 0;
				grid[i + 2][j + 2] = 0;
				rstart = i;
				cstart = j;
				poptype = 'l';
				cpopped = 5;
				grid[i][j] += 10;
			}
			if (grid[i][j] <= 5 && grid[i][j] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j + 2] && grid[i][j + 2] == grid[i + 1][j + 2] && grid[i + 1][j + 2] == grid[i + 2][j + 2])
			{
				grid[i][j] = 0;
				grid[i + 1][j] = 0;
				grid[i + 2][j] = 0;
				grid[i + 2][j + 1] = 0;
				grid[i + 2][j + 2] = 0;
				rstart = i;
				cstart = j;
				poptype = 'l';
				cpopped = 5;
				grid[i][j] += 10;
			}
		}
	}
}
void plainwrap(int grid[][gsize])
{
	char c1, c2, c3;
	for (int i = 0; i < gsize; i++)
	{
		for (int j = 0; j < gsize; j++)
		{
			c1 = colorcheck(grid[i][j]);
			c2 = colorcheck(grid[i + 1][j]);
			c3 = colorcheck(grid[i + 2][j]);
			if ((grid[i][j] <= 15 && grid[i][j] >= 11) && (c1 == c2 == c3))
			{
				//burst 3x3 block
				rstart = i;
				cstart = j;
				poptype = 'r';
				cpopped = 3;
				candycolor = colorcheck(grid[i][j]);
			}
			c1 = colorcheck(grid[i][j]);
			c2 = colorcheck(grid[i][j + 1]);
			c3 = colorcheck(grid[i][j + 2]);
			if (grid[i][j] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j + 2] && grid[i][j] <= 5)
			{
				grid[i][j] = 0;
				grid[i][j + 1] = 0;
				grid[i][j + 2] = 0;
				rstart = i;
				cstart = j;
				poptype = 'c';
				cpopped = 3;
				candycolor = colorcheck(grid[i][j]);
			}
		}
	}
}

