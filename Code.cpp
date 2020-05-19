#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include "FadiCCGraphics.h"
#include "myconsole.h"

using namespace std;
//candy legend
	/*
	S=STRIPED, W=WRAPPED, CB= COLOR BOMB, R=RED,B=BLUE, O=ORANGE.....
1	R
2	B
3	G
4	Y
5	O
6	RS
7	BS
8	GS
9	YS
10	OS
11	RW
12	BW
13	GW
14	YW
15	OW
16	CB



	*/
const int gsize = 9, target = 5000;
int rstart = 0, cstart = 0;//   r_c start: starting index of popped candies
int row1 = 0, row2 = 0, col1 = 0, col2 = 0; //index of 2 candies user wants to swap
char poptype = 0;// whether pop is in a row or a column (r=row, c=column,t=T wrapped, l=L wrapped
int cpopped = 0;//number of candies popped
char candycolor; //color of candy that popped
int score = 0, moves = 20;//denotes current user score


void gridgen(int grid[][gsize+3],int n);
int randgen();
void plain(int grid[][gsize+3]);
void stripes(int grid[][gsize+3]);
void stripes_3(int grid[][gsize + 3]);
void colorbomb(int grid[][gsize+3]);
char colorcheck(int i);
void plainwrap(int grid[][gsize+3]);
void wrapped(int grid[][gsize+3]);
int userinput(int grid[][gsize+3],int &i);
void cbombcbomb(int grid[][gsize+3],int c1,int c2);
void candyboard(int grid[][gsize+3]);
void pointer(int grid[][gsize+3]);
void scorer(char color, int num);
void gamesave(int grid[][gsize+3]);
void gameload(int grid[][gsize+3]);
void bombstriped(int grid[][gsize+3],int candy, int row, int col);
void bombwrap(int grid[][gsize + 3], int candy, int row, int col);
void swapp(int grid[][gsize+3], int& Row1, int& Col1);
void swapfail(int grid[][gsize+3], int R, int C, int R1, int C1);
void wrapstripe(int grid[][gsize+3], int row, int col, int candy);
void plainbomb(int grid[][gsize+3],int candy1,int candy2);
void plain_stripe(int grid[][gsize+3]);
void initial_check(int grid[][gsize+3]);
void shift(int grid[][gsize + 3], int cpopped, int index_c, int  index_r);
void shifting(int grid[][gsize+3]);
void wrapped_wrapped(int grid[][gsize+3], int row, int col, int candy);


int main()
{
	//const int gsize = 10, target=500,moves=20;
	//system("mode 650");
	int grid[gsize+3][gsize+3];
	int y;
	srand(time(0));
	cout << "--------------------Candy Crush--------------------------" << endl << "To Pause/Save Game enter Row and Column to be -1,-1" << endl;
	system("Pause");
	ClearScreen();
	cout << "To load a previous game, press 1";
	cin >> y;
	ClearScreen();
	if (y == 1)
	{
		gameload(grid);
		gridgen(grid, 1);
	}
	else
	{
		ClearScreen();
		gridgen(grid, 0);
	}
	//pointer(grid);

	
	//initial checks for the grid
	plain(grid);
	stripes_3(grid);
	plain_stripe(grid);
	plain(grid);
	stripes(grid);
	initial_check(grid);


	for (int i = 0, x1, y1, randwrap; i <= moves || score <= target; i++)
	{
		gridgen(grid, 1);
		PlaceCursor(0, 20);
		userinput(grid,i);
		Sleep(300);
		ClearScreen();
	}
	
	PlaceCursor(0, 10);
	if (score >= target)
	{
		ClearScreen();
		cout << "------------------------------CONGRATULATIONS U WIN--------------------------" << endl;
	}
	else
	{
		ClearScreen();
		cout << "--------------------------BETTER LUCK NEXT TIME--------------------------" << endl;

	}
	PlaceCursor(0, 30);
	system("Pause");
	return 0;
}

void gridgen(int grid[][gsize+3],int n)
{
	//if n is 0 then generate random numbers else just display board
	if (n == 0)
	{
		for (int i = 0; i < gsize; i++)
		{
			for (int j = 0; j < gsize; j++)
			{
				grid[i][j] = randgen();
				//cout << grid[i][j] << "  ";
				//cout << endl << endl;
			}
			//cout << endl;
		}
		//grid[3][1] = 1;
		//grid[3][2] = 1;
		//grid[3][3] = 6;
		//grid[4][1] = 1;
		//grid[5][1] = 1;
	}
	
	candyboard(grid);

	
	//grid[0][1] = 5;
	//grid[1][1] = 5;
	//grid[2][1] = 15;
	//grid[3][8] = 5;
	//grid[3][9] = 5;
	//cout << endl << endl << endl;
	//for (int i = 0; i <= gsize; i++)
	//{
	//	for (int j = 0; j <= gsize; j++)
	//	{
	//		cout << grid[i][j] << "  ";
	//		//cout << endl << endl;
	//	}
	//	cout << endl;
	//}
}
int randgen()
{
	//to return a random number/candy
	int x = rand() % 10 + 1; //random number between 1 and 10

	return x;
}
int userinput(int grid[][gsize + 3], int &i)
{
	bool flag = false;
	
	if (i != 0)
		gridgen(grid, 1);


	//-1,-1 to end game (add those limits to input validation)
	
	cout << "Enter the Row and Column Index of Candy #1" << endl ;
	cin >> row1 >> col1;
	if (row1 == -1 && col1 == -1)
	{
		ClearScreen();
		gamesave(grid);
		cout << "Game Saved, thank you for playing" << endl;
		i = moves + 1;
		return 0;
		flag = false;

	}
	while (row1 > gsize || col1 > gsize) //input validation
	{
		cout << "Invalid Input, Row/Column must be between 0 and 9";
		cin >> row1 >> col1;
	}

	cout << "Enter the Row and Column Index of Candy #2" << endl;
	cin >> row2 >> col2;
	while (row2 > gsize || col2 > gsize) //input validation
	{
		cout << "Invalid Input, Row/Column must be between 0 and 9";
		cin >> row2 >> col2;
	}

	//to check if boxes are adjacent 
	if (!((row2 == (row1 - 1) && col1 == col2) || (row2 == (row1 + 1) && col1 == col2)
		|| (row1 == row2 && col2 == (col1 - 1)) || (row1 == row2 && col2 == (col1 + 1))))
	{
		cout << "Invalid Boxes chosen, boxes need to be adjacent to one another" << endl;
		flag = false;
		/*
		cout << "Enter the Row and Column Index of Candy #1" << endl;
		cin >> row1 >> col1;
		while (row1 > gsize || col1 > gsize) //input validation
		{
			cout << "Invalid Input, Row/Column must be between 0 and 9";
			cin >> row1 >> col1;
		}
		cout << "Enter the Row and Column Index of Candy #2" << endl;
		cin >> row2 >> col2;
		while (row2 > gsize || col2 > gsize) //input validation
		{
			cout << "Invalid Input, Row/Column must be between 0 and 9";
			cin >> row2 >> col2;
		}
		*/
	}
	else
		flag = true;

	/*char c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12;
	c1 = colorcheck(grid[row1][col1]);
	c2 = colorcheck(grid[row1 + 1][col1]);
	c3 = colorcheck(grid[row1 + 2][col1]);
	c4 = colorcheck(grid[row1][col1]);
	c5 = colorcheck(grid[row1][col1 + 1]);
	c6 = colorcheck(grid[row1][col1 + 2]);
	c7 = colorcheck(grid[row2][col2]);
	c8 = colorcheck(grid[row2 + 1][col2]);
	c9 = colorcheck(grid[row2 + 2][col2]);
	c10 = colorcheck(grid[row2][col2]);
	c11 = colorcheck(grid[row2][col2 + 1]);
	c12 = colorcheck(grid[row2][col2 + 2]);
*/
	int temp = grid[row2][col2], temp2 = grid[row1][col1];
	//bool specialpop = false;
	/*//check min 3 in a row/col or 3 matching colors in row/col, if true then swap permitted
	if (((grid[row1][col1] == grid[row1 + 1][col1] && grid[row1 + 1][col1] == grid[row1 + 2][col1]) ||
		(grid[row1][col1] == grid[row1][col1 + 1] && grid[row1][col1 + 1] == grid[row1][col1 + 2])) ||
		((c1 == c2) && (c2 == c3) || (c4 == c5 && c5 == c6))) //&& flagvertically check 1 candy is a wrapped and all same colors
	{
		swap(grid[row1][col1], grid[row2][col2]);
	}*/
	/*//to check special swaps (CB-CB, STRIPED-WRAPPED, WRAPPED-WRAPPED
	if ((temp == 16 || temp2 == 16) || ((temp >= 6 && temp <= 10) && (temp2 >= 11 && temp2 <= 15)) || ((temp2 >= 6 && temp2 <= 10) && (temp >= 11 && temp <= 15)) || (temp2 >= 11 && temp2 <= 15) && (temp >= 11 && temp <= 15))
		specialpop = true;

*/
//check min 3 in a row/col or 3 matching colors in row/col, if true then swap permitted
	if (flag)
	{

		//cout << "Swap";
		swap(grid[row1][col1], grid[row2][col2]);
		ClearScreen();
		gridgen(grid, 1);
		Sleep(300);

		//add checking functions here
		cbombcbomb(grid, temp, temp2);
		plainbomb(grid, temp, temp2);
		bombstriped(grid, temp2, row1, col1);
		bombwrap(grid, temp2, row2, col2);
		wrapstripe(grid, temp2, row2, col2);
		wrapped_wrapped(grid, row1, col1, temp2);

		colorbomb(grid);
		wrapped(grid);
		stripes_3(grid);
		plain_stripe(grid);
		plainwrap(grid);
		stripes(grid);
		plain(grid);



		ClearScreen();
		gridgen(grid, 1);
		Sleep(300);



		ClearScreen();
		gridgen(grid, 1);
		Sleep(300);
		//ClearScreen();
		PlaceCursor(0, 20);
		cout << "Score: " << score << endl;
		moves--;
		PlaceCursor(0, 22);
		cout << "Moves: " << moves << endl;
		Sleep(750);
		//PlaceCursor(50, 54);
		//system("Pause");
		ClearScreen();
		gridgen(grid, 1);
		Sleep(300);
		ClearScreen();
		/*}
		else
		{
			cout << "No candies burst, try another box to swap" << endl;
			swapfail(grid, row1, col1, row2, col2);
			flag = false;
		}
		*/
		//if (!flag)
			//cout << "Invalid Move, try again" << endl;

	}
	//}

}
void plain(int grid[][gsize+3])
{

	for (int i = 0; i < gsize; i++)
	{
		for (int j = 0; j < gsize; j++)
		{
			if ((grid[i][j] == grid[i + 1][j] && grid[i + 1][j] == grid[i + 2][j]) && grid[i][j] <= 5)
			{

				rstart = i;
				cstart = j;
				poptype = 'r';
				cpopped = 3;
				candycolor = colorcheck(grid[i][j]);
				scorer(candycolor, cpopped);
				grid[i][j] = 0;
				grid[i + 1][j] = 0;
				grid[i + 2][j] = 0;
				shifting(grid);
			}
			if (grid[i][j] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j + 2] && grid[i][j] <= 5)
			{

				rstart = i;
				cstart = j;
				poptype = 'c';
				cpopped = 3;
				candycolor = colorcheck(grid[i][j]);
				scorer(candycolor, cpopped);
				grid[i][j] = 0;
				grid[i][j + 1] = 0;
				grid[i][j + 2] = 0;
				shifting(grid);
			}
		}
	}
}
void stripes(int grid[][gsize+3])
{
	for (int i = 0; i < gsize; i++)
	{
		for (int j = 0; j < gsize; j++)
		{
			if ((grid[i][j] <= 5) && (grid[i][j] == grid[i + 1][j] && grid[i + 1][j] == grid[i + 2][j] && grid[i + 2][j] == grid[i + 3][j]))
			{

				rstart = i;
				cstart = j;
				poptype = 'r';
				cpopped = 4;
				candycolor = colorcheck(grid[i][j]);
				scorer(candycolor, cpopped);
				grid[i][j] = 0;
				grid[i + 1][j] = 0;
				grid[i + 2][j] = 0;
				grid[i + 3][j] = 0;
				grid[i][j] += 5; //changes one plain candy to a striped candy of same color
				shifting(grid);
			}
			if ((grid[i][j] <= 5) && (grid[i][j] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j + 2] && grid[i][j + 2] == grid[i][j + 3]))
			{

				rstart = i;
				cstart = j;
				poptype = 'c';
				cpopped = 4;
				candycolor = colorcheck(grid[i][j]);
				scorer(candycolor, cpopped);
				grid[i][j] = 0;
				grid[i][j + 1] = 0;
				grid[i][j + 2] = 0;
				grid[i][j + 3] = 0;
				grid[i][j] += 5; //changes one plain candy to a striped candy of same color
				shifting(grid);
			}
		}
	}
}
void colorbomb(int grid[][gsize+3])
{
	for (int i = 0; i < gsize; i++)
	{
		for (int j = 0; j < gsize; j++)
		{
			if ((grid[i][j] <= 5) && (grid[i][j] == grid[i + 1][j] && grid[i + 1][j] == grid[i + 2][j] && grid[i + 2][j] == grid[i + 3][j] && grid[i + 4][j]))
			{

				rstart = i;
				cstart = j;
				poptype = 'r';
				cpopped = 5;
				candycolor = colorcheck(grid[i][j]);
				scorer(candycolor, cpopped);
				grid[i][j] = 0;
				grid[i + 1][j] = 0;
				grid[i + 2][j] = 0;
				grid[i + 3][j] = 0;
				grid[i + 4][j] = 0;
				grid[i][j] = 16;
				shifting(grid);
			}
			if ((grid[i][j] <= 5) && (grid[i][j] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j + 2] && grid[i][j + 2] == grid[i][j + 3] && grid[i][j + 3] == grid[i][j + 4]))
			{
				rstart = i;
				cstart = j;
				poptype = 'c';
				cpopped = 5;
				candycolor = colorcheck(grid[i][j]);
				scorer(candycolor, cpopped);
				grid[i][j] = 16;
				grid[i][j] = 0;
				grid[i][j + 1] = 0;
				grid[i][j + 2] = 0;
				grid[i][j + 3] = 0;
				grid[i][j + 4] = 0;
				shifting(grid);
			}
		}
	}
}
void wrapped(int grid[][gsize+3])
{
	/*for (int i = 0; i < gsize; i++)
	{
		for (int j = 0; j < gsize; j++)
		{
			if (grid[i][j] <= 5 && grid[i][j] == grid[i + 1][j] && grid[i + 1][j] == grid[i + 2][j] && grid[i + 1][j] == grid[i + 1][j + 1] && grid[i + 1][j] == grid[i + 1][j + 2])
			{

				rstart = i;
				cstart = j;
				poptype = 't';
				cpopped = 5;
				candycolor = colorcheck(grid[i][j]);
				scorer(candycolor, cpopped);

				grid[i][j] = 0;
				grid[i + 1][j] = 0;
				grid[i + 2][j] = 0;
				grid[i + 1][j + 1] = 0;
				grid[i + 1][j + 2] = 0;
				grid[i][j] += 10;
				shifting(grid);
			}
			if (grid[i][j] <= 5 && grid[i][j] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j + 2] && grid[i][j + 1] == grid[i + 1][j + 1] && grid[i + 1][j] == grid[i + 2][j + 1])
			{

				rstart = i;
				cstart = j;
				poptype = 't';
				cpopped = 5;
				candycolor = colorcheck(grid[i][j]);
				scorer(candycolor, cpopped);
				grid[i][j] = 0;
				grid[i][j + 1] = 0;
				grid[i][j + 2] = 0;
				grid[i + 1][j + 1] = 0;
				grid[i + 1][j + 1] = 0;
				grid[i][j] += 10;
				shifting(grid);

			}
			//if (grid[i][j] <= 5 && grid[i][j] == grid[i + 1][j] && grid[i + 1][j] == grid[i + 2][j] && grid[i + 1][j] == grid[i + 2][j + 1] && grid[i + 2][j + 1] == grid[i + 2][j + 2])

			if (grid[i][j] <= 5 && grid[i][j] == grid[i + 1][j] && grid[i + 1][j] == grid[i + 2][j] && grid[i][j] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j + 2])
			{

				rstart = i;
				cstart = j;
				poptype = 'l';
				cpopped = 5;
				candycolor = colorcheck(grid[i][j]);
				scorer(candycolor, cpopped);
				grid[i + 1][j] = 0;
				grid[i + 2][j] = 0;
				grid[i][j + 1] = 0;
				grid[i][j + 2] = 0;
				grid[i][j] += 10;
				shifting(grid);
			}
			if (grid[i][j] <= 5 && grid[i][j] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j + 2] && grid[i][j + 2] == grid[i + 1][j + 2] && grid[i + 1][j + 2] == grid[i + 2][j + 2])
			{

				rstart = i;
				cstart = j;
				poptype = 'l';
				cpopped = 5;
				candycolor = colorcheck(grid[i][j]);
				scorer(candycolor, cpopped);
				grid[i + 1][j] = 0;
				grid[i + 2][j] = 0;
				grid[i + 2][j + 1] = 0;
				grid[i + 2][j + 2] = 0;
				grid[i][j] += 10;
				shifting(grid);
			}
		}
	}
	*/
	for (int i = 0; i < gsize; i++)
	{
		for (int j = 0; j < gsize; j++)
		{
			if (grid[i][j] <= 5 && grid[i][j] == grid[i + 1][j] && grid[i + 1][j] == grid[i + 2][j] && grid[i + 1][j] == grid[i + 1][j + 1] && grid[i + 1][j] == grid[i + 1][j + 2])//  |-- shapped
			{

				rstart = i;
				cstart = j;
				poptype = 't';
				cpopped = 5;
				candycolor = colorcheck(grid[i][j]);
				scorer(candycolor, cpopped);

				grid[i][j] = 0;
				grid[i + 1][j] = 0;
				grid[i + 2][j] = 0;
				grid[i + 1][j + 1] = 0;
				grid[i + 1][j + 2] = 0;
				grid[i][j] += 10;
				shifting(grid);
			}
			if (grid[i][j] <= 5 && grid[i][j] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j + 2] && grid[i][j + 1] == grid[i + 1][j + 1] && grid[i][j] == grid[i + 2][j + 1])
			{

				rstart = i;
				cstart = j;
				poptype = 't';
				cpopped = 5;
				candycolor = colorcheck(grid[i][j]);
				scorer(candycolor, cpopped);

				grid[i][j + 1] = 0;
				grid[i][j + 2] = 0;
				grid[i + 1][j + 1] = 0;
				grid[i + 1][j + 2] = 0;
				grid[i][j] += 10;
				shifting(grid);

			}
			//if (grid[i][j] <= 5 && grid[i][j] == grid[i + 1][j] && grid[i + 1][j] == grid[i + 2][j] && grid[i + 1][j] == grid[i + 2][j + 1] && grid[i + 2][j + 1] == grid[i + 2][j + 2])

			if (grid[i][j] <= 5 && grid[i][j] == grid[i + 1][j] && grid[i + 1][j] == grid[i + 2][j] && grid[i][j] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j + 2])
			{

				rstart = i;
				cstart = j;
				poptype = 'l';
				cpopped = 5;
				candycolor = colorcheck(grid[i][j]);
				scorer(candycolor, cpopped);

				grid[i + 1][j] = 0;
				grid[i + 2][j] = 0;
				grid[i][j + 1] = 0;
				grid[i][j + 2] = 0;
				grid[i][j] += 10;
				shifting(grid);
			}
			if (grid[i][j] <= 5 && grid[i][j] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j + 2] && grid[i][j + 2] == grid[i + 1][j + 2] && grid[i + 1][j + 2] == grid[i + 2][j + 2])
			{

				rstart = i;
				cstart = j;
				poptype = 'l';
				cpopped = 5;
				candycolor = colorcheck(grid[i][j]);
				scorer(candycolor, cpopped);
				grid[i + 1][j] = 0;
				grid[i + 2][j] = 0;
				grid[i + 2][j + 1] = 0;
				grid[i + 2][j + 2] = 0;
				grid[i][j] += 10;
				shifting(grid);
			}
		}
	}
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
	return 0;
}
void plainwrap(int grid[][gsize+3])
{
	char c1, c2, c3;
	for (int i = 0; i < gsize; i++)
	{
		for (int j = 0; j < gsize; j++)
		{
			c1 = colorcheck(grid[i][j]);
			c2 = colorcheck(grid[i + 1][j]);
			c3 = colorcheck(grid[i + 2][j]);
			if (((grid[i][j] <= 15 && grid[i][j] >= 11) || (grid[i + 1][j] <= 15 && grid[i + 1][j] >= 11) || (grid[i + 2][j] <= 15 && grid[i + 2][j] >= 11))
				&& (c1 == c2) && (c2 == c3)) //vertically check 1 candy is a wrapped and all same colors
			{
				rstart = i;
				cstart = j;
				poptype = 'r';
				cpopped = 9;
				candycolor = colorcheck(grid[i][j]);
				scorer(candycolor, cpopped);
				//to see which candy is wrapped
				if (grid[i][j] <= 15 && grid[i][j] >= 11)
				{
					//burst 3x3 block
					grid[i - 1][j] = 0;
					grid[i - 1][j + 1] = 0;
					grid[i - 1][j - 1] = 0;
					grid[i][j] = 0;
					grid[i][j + 1] = 0;
					grid[i][j - 1] = 0;
					grid[i + 1][j] = 0;
					grid[i + 1][j + 1] = 0;
					grid[i + 1][j - 1] = 0;
					shifting(grid);
				}
				else if (grid[i + 1][j] <= 15 && grid[i + 1][j] >= 11)
				{
					int x = i + 1, y = j;
					grid[x - 1][y] = 0;
					grid[x - 1][y + 1] = 0;
					grid[x - 1][y - 1] = 0;
					grid[x][y] = 0;
					grid[x][y + 1] = 0;
					grid[x][y - 1] = 0;
					grid[x + 1][y] = 0;
					grid[x + 1][y + 1] = 0;
					grid[x + 1][y - 1] = 0;
					shifting(grid);
				}
				else if (grid[i + 2][j] <= 15 && grid[i + 2][j] >= 11)
				{
					int x = i + 1, y = j;
					grid[x - 1][y] = 0;
					grid[x - 1][y + 1] = 0;
					grid[x - 1][y - 1] = 0;
					grid[x][y] = 0;
					grid[x][y + 1] = 0;
					grid[x][y - 1] = 0;
					grid[x + 1][y] = 0;
					grid[x + 1][y + 1] = 0;
					grid[x + 1][y - 1] = 0;
					shifting(grid);
				}

				////burst 3x3 block
				//grid[i - 1][j] = 0;
				//grid[i - 1][j + 1] = 0;
				//grid[i - 1][j - 1] = 0;
				//grid[i][j] = 0;
				//grid[i][j + 1] = 0;
				//grid[i][j - 1] = 0;
				//grid[i + 1][j] = 0;
				//grid[i + 1][j + 1] = 0;
				//grid[i + 1][j - 1] = 0;


			}
			c1 = colorcheck(grid[i][j]);
			c2 = colorcheck(grid[i][j + 1]);
			c3 = colorcheck(grid[i][j + 2]);
			if (((grid[i][j] <= 15 && grid[i][j] >= 11) || (grid[i][j + 1] <= 15 && grid[i][j + 1] >= 11) || (grid[i][j + 2] <= 15 && grid[i][j + 2] >= 11))
				&& (c1 == c2) && (c2 == c3)) //horizontal check for same color and 1 wrapped
			{

				rstart = i;
				cstart = j;
				poptype = 'c';
				cpopped = 9;
				candycolor = colorcheck(grid[i][j]);
				scorer(candycolor, cpopped);

				//burst 3x3 block
				if (grid[i][j] <= 15 && grid[i][j] >= 11)
				{
					//burst 3x3 block
					grid[i - 1][j] = 0;
					grid[i - 1][j + 1] = 0;
					grid[i - 1][j - 1] = 0;
					grid[i][j] = 0;
					grid[i][j + 1] = 0;
					grid[i][j - 1] = 0;
					grid[i + 1][j] = 0;
					grid[i + 1][j + 1] = 0;
					grid[i + 1][j - 1] = 0;
					shifting(grid);
				}
				else if (grid[i][j + 1] <= 15 && grid[i][j + 1] >= 11)
				{
					int x = i, y = j + 1;
					grid[x - 1][y] = 0;
					grid[x - 1][y + 1] = 0;
					grid[x - 1][y - 1] = 0;
					grid[x][y] = 0;
					grid[x][y + 1] = 0;
					grid[x][y - 1] = 0;
					grid[x + 1][y] = 0;
					grid[x + 1][y + 1] = 0;
					grid[x + 1][y - 1] = 0;
					shifting(grid);
				}
				else if (grid[i][j + 2] <= 15 && grid[i][j + 2] >= 11)
				{
					int x = i, y = j + 2;
					grid[x - 1][y] = 0;
					grid[x - 1][y + 1] = 0;
					grid[x - 1][y - 1] = 0;
					grid[x][y] = 0;
					grid[x][y + 1] = 0;
					grid[x][y - 1] = 0;
					grid[x + 1][y] = 0;
					grid[x + 1][y + 1] = 0;
					grid[x + 1][y - 1] = 0;
					shifting(grid);
				}


				////burst 3x3 block
				//grid[i - 1][j] = 0;
				//grid[i - 1][j + 1] = 0;
				//grid[i - 1][j - 1] = 0;
				//grid[i][j] = 0;
				//grid[i][j + 1] = 0;
				//grid[i][j - 1] = 0;
				//grid[i + 1][j] = 0;
				//grid[i + 1][j + 1] = 0;
				//grid[i + 1][j - 1] = 0;
			}
		}
	}
}
void cbombcbomb(int grid[][gsize+3], int c1, int c2) //c1 and c2 are candies 1 and 2
{
	//when 2 color bombs are swapped, the whole board will be destroyed
	//need to count score of each candy and then blow and regenerate board
	if (c1 == 16 && c2 == 16)
	{
		//score counter for every candy on board based on color
		char ctemp;

		for (int i = 0; i < gsize; i++)
		{
			for (int j = 0; j < gsize; j++)
			{
				ctemp = colorcheck(grid[i][j]);
				switch (ctemp)
				{
				case'r':
				{
					score += 30;
					break;
				}
				case 'y':
				{
					score += 30;
					break;
				}
				case 'g':
				{
					score += 40;
					break;
				}
				case 'b':
				{
					score += 50;
					break;
				}
				case 'o':
				{
					score += 60;
					break;
				}
				default:
				{
					break;
				}
				}
			}
		}


		//new board	
		gridgen(grid, 0);
	}

}
void bombstriped(int grid[][gsize+3], int candy, int row, int col)
{
/*	char ctemp;
	int candy2 = grid[row][col];
	int plain_c = candy - 5;
	if (candy == 16 && (candy2 > 5 && candy2 <= 10)|| candy2 == 16 && (candy > 5 && candy <= 10))
	{
		if (candy2 == 16 && grid[row][col + 1] == candy || grid[row][col + 1] == 16 && candy2 == candy)
		{

			for (int x = 0; x < gsize; x++)
			{
				for (int y = 0; y < gsize; y++)
				{
					if (grid[x][y] == plain_c)
					{
						grid[x][y] += 5;
						//gridgen();
						for (int i = 0; i < gsize; i++)
						{

							ctemp = colorcheck(grid[x][i]);
							switch (ctemp)
							{
							case'r':
							{
								score += 30;
								break;
							}
							case 'y':
							{
								score += 30;
								break;
							}
							case 'g':
							{
								score += 40;
								break;
							}
							case 'b':
							{
								score += 50;
								break;
							}
							case 'o':
							{
								score += 60;
								break;
							}
							default:
							{
								break;
							}
							}
							grid[x][i] = 0;
						}

					}
				}
			}
			shifting(grid);
		}
		else if (candy2 == 16 && grid[row + 1][col] == candy || grid[row + 1][col] == 16 && candy2 == candy)
		{
			for (int x = 0; x < gsize; x++)
			{
				for (int y = 0; y < gsize; y++)
				{
					if (grid[x][y] == plain_c)
					{
						grid[x][y] += 5;
						//gridgen();
						for (int i = 0; i < gsize; i++)
						{

							ctemp = colorcheck(grid[i][y]);
							switch (ctemp)
							{
							case'r':
							{
								score += 30;
								break;
							}
							case 'y':
							{
								score += 30;
								break;
							}
							case 'g':
							{
								score += 40;
								break;
							}
							case 'b':
							{
								score += 50;
								break;
							}
							case 'o':
							{
								score += 60;
								break;
							}
							default:
							{
								break;
							}
							}
							grid[i][y] = 0;
						}

					}
				}
			}
			shifting(grid);
		}
	}
*/
char ctemp;
int plain = candy - 5;
if (grid[row][col] == 16 && grid[row + 1][col] == candy ||
	grid[row + 1][col] == 16 && grid[row][col] == candy)
{
	for (int x = 0; x < gsize; x++)
	{
		for (int y = 0; y < gsize; y++)
		{
			if (grid[x][y] == plain)
			{
				grid[x][y] == plain + 5;
			}
		}
		for (int i = 0; i < gsize; i++)
		{

			ctemp = colorcheck(grid[x][i]);
			switch (ctemp)
			{
			case'r':
			{
				score += 30;
				break;
			}
			case 'y':
			{
				score += 30;
				break;
			}
			case 'g':
			{
				score += 40;
				break;
			}
			case 'b':
			{
				score += 50;
				break;
			}
			case 'o':
			{
				score += 60;
				break;
			}
			default:
			{
				break;
			}
			}
			grid[x][i] = 0;
		}

	}

	for (int i = 0; i < gsize; i++)
	{
		grid[i][col] = 1 + (rand() % 5);
	}
}
else 	if (grid[row][col] == 16 && grid[row][col + 1] == candy ||
	grid[row][col + 1] == 16 && grid[row][col] == candy)
{
	for (int x = 0; x < gsize; x++)
	{
		for (int y = 0; y < gsize; y++)
		{
			if (grid[x][y] == plain)
			{
				grid[x][y] == plain + 5;
			}
		}
		for (int i = 0; i < gsize; i++)
		{

			ctemp = colorcheck(grid[x][i]);
			switch (ctemp)
			{
			case'r':
			{
				score += 30;
				break;
			}
			case 'y':
			{
				score += 30;
				break;
			}
			case 'g':
			{
				score += 40;
				break;
			}
			case 'b':
			{
				score += 50;
				break;
			}
			case 'o':
			{
				score += 60;
				break;
			}
			default:
			{
				break;
			}
			}
			grid[x][i] = 0;
		}

	}
	for (int i = 0; i < gsize; i++)
	{
		grid[i][col] = 0;
	}

	shifting(grid);


}
}
void wrapstripe(int grid[][gsize+3], int row, int col, int candy)
{
	char ctemp;
	if (candy >= 10 && candy <= 15 || candy >= 6 && candy <= 10)
	{
		if (grid[row][col] == candy && (grid[row][col + 1] <= 15 && grid[row][col + 1] >= 10) || grid[row][col + 1] == candy && (grid[row][col] <= 15 && grid[row][col] >= 10) || grid[row][col] == candy && (grid[row][col + 1] <= 10 && grid[row][col + 1] >= 6) || grid[row][col + 1] == candy && (grid[row][col] <= 10 && grid[row][col] >= 6) || grid[row][col] == candy && (grid[row + 1][col] <= 15 && grid[row + 1][col] >= 10) || grid[row + 1][col] == candy && (grid[row][col] <= 15 && grid[row][col] >= 10) || grid[row][col] == candy && (grid[row + 1][col] <= 10 && grid[row + 1][col] >= 6) || grid[row + 1][col] == candy && (grid[row][col] <= 10 && grid[row][col] >= 6))
		{
			for (int i = row - 1; i <= row + 1; i++)
			{
				for (int j = 0; j < gsize; j++)
				{

					ctemp = colorcheck(grid[i][j]);
					switch (ctemp)
					{
					case'r':
					{
						score += 30;
						break;
					}
					case 'y':
					{
						score += 30;
						break;
					}
					case 'g':
					{
						score += 40;
						break;
					}
					case 'b':
					{
						score += 50;
						break;
					}
					case 'o':
					{
						score += 60;
						break;
					}
					default:
					{
						break;
					}
					}
					grid[i][j] = 0;
				}

			}
			for (int i = 0; i < gsize; i++)
			{
				for (int j = col - 1; j < col + 1; j++)
				{

					ctemp = colorcheck(grid[i][j]);
					switch (ctemp)
					{
					case'r':
					{
						score += 30;
						break;
					}
					case 'y':
					{
						score += 30;
						break;
					}
					case 'g':
					{
						score += 40;
						break;
					}
					case 'b':
					{
						score += 50;
						break;
					}
					case 'o':
					{
						score += 60;
						break;
					}
					default:
					{
						break;
					}
					}
					grid[i][j] = 0;
				}
			}
		}
		shifting(grid);
	}
}
void wrapped_wrapped(int grid[][gsize+3], int row, int col, int candy)
{
	/*
	char ctemp;
	if (candy <= 15 && candy > 10)
	{
		if (row >= 2 && row <= 7 && col >= 2 && col <= 7)
		{
			if (grid[row][col] == candy && grid[row + 1][col] == candy)
			{
				for (int i = -2; i < 3; i++)
				{
					for (int j = -2; j < 3; j++)
					{
						ctemp = colorcheck(grid[i][j]);
						switch (ctemp)
						{
						case'r':
						{
							score += 30;
							break;
						}
						case 'y':
						{
							score += 30;
							break;
						}
						case 'g':
						{
							score += 40;
							break;
						}
						case 'b':
						{
							score += 50;
							break;
						}
						case 'o':
						{
							score += 60;
							break;
						}
						default:
						{
							break;
						}
						}
						grid[i][j] = 0;

					}
				}

			}


		}
		shifting(grid);
	}
	

	*/
	char ctemp;
	if (candy <= 15 && candy > 10)
	{
		if (row > 2 && row < 7 && col > 2 && col < 7)
		{
			if (grid[row][col] == candy && grid[row + 1][col] == candy)
			{
				for (int i = -2; i < 3; i++)
				{
					for (int j = -2; j < 3; j++)
					{
						ctemp = colorcheck(grid[i][j]);
						switch (ctemp)
						{
						case'r':
						{
							score += 30;
							break;
						}
						case 'y':
						{
							score += 30;
							break;
						}
						case 'g':
						{
							score += 40;
							break;
						}
						case 'b':
						{
							score += 50;
							break;
						}
						case 'o':
						{
							score += 60;
							break;
						}
						default:
						{
							break;
						}
						}
						grid[i][j] = 0;

					}
				}

			}
			for (int i = -2; i < 3; i++)
			{
				for (int j = -2; j < 3; j++)
				{
					grid[row + i][col + j] = 0;
				}
			}
		}
		shifting(grid);
	}
}
void candyboard(int grid[][gsize+3])
{
	
	
	myLine(20, 20, 400, 20,pink);
	myLine(20, 20, 20, 310, pink);
	myLine(20, 310, 400, 310, pink);
	myLine(400, 310, 400, 20, pink);
	//PlaceCursor(2, 0);
	//cout << "   0    1    2    3    4    5    6    7    8    ";
	//Sleep(1000);
	/*for (int i = 0; i <= 8; i++)
	{
		myLine(x1[0], y1[0], x2[0], y2[0], 123);
		x1[0] += 51, x2[0] += 51;
	}
	for (int i = 0; i <= 8; i++)
	{
		myLine(x1[1], y1[1], x2[1], y2[1], 123);
		y1[1] += 51, y2[1] += 51;
	}
	*/
	int x1 = 30, y1 = 30;
	for (int i = 0; i < gsize; i++)
	{
		for (int j = 0; j < gsize; j++)
		{
			switch (grid[i][j])
			{
			case 1:
			{
				plaingraphic(x1, y1, 'r');
				break;
			}
			case 2:
			{
				plaingraphic(x1, y1, 'b');
				break;
			}
			case 3:
			{
				plaingraphic(x1, y1, 'g');
				break;

			}
			case 4:
			{
				plaingraphic(x1, y1, 'y');
				break;

			}
			case 5:
			{
				plaingraphic(x1, y1, 'o');
				break;

			}
			case 6:
			{
				stripedgraphic(x1, y1, 'r');
				break;
			}
			case 7:
			{
				stripedgraphic(x1, y1, 'b');
				break;
			}
			case 8:
			{
				stripedgraphic(x1, y1, 'g');
				break;
			}
			case 9:
			{
				stripedgraphic(x1, y1, 'y');
				break;
			}
			case 10:
			{
				stripedgraphic(x1, y1, 'o');
				break;
			}
			case 11:
			{
				wrappedgraphic(x1, y1, 'r');
				break;
			}
			case 12:
			{
				wrappedgraphic(x1, y1, 'b');
				break;
			}
			case 13:
			{
				wrappedgraphic(x1, y1, 'g');
				break;
			}
			case 14:
			{
				wrappedgraphic(x1, y1, 'y');
				break;
			}
			case 15:
			{
				wrappedgraphic(x1, y1, 'o');
				break;
			}
			case 16:
			{
				colorbombgraphic(x1, y1);
				break;
			}
			}
			x1 += 40;
		}
		y1 += 30;
		x1 = 30;
	}
	Sleep(900);
	
}
void pointer(int grid[][gsize+3])
{
	//time_t start, end;
	//start = time(NULL);
	int once = 1, row = 0, col = 0;
	int key;
	int x1 = 30, y1 = 30, x2 = 60, y2 = 60; //x-gap is 40 and y-gap is 50
	myPointer(x1, y1, x2, y2, 0, 0, 220, 0, 0, 0);
	
	candyboard(grid); //boardcreate(arr, once); 
	key = 1;
	int i = 1;
	while (key != 6)	//to exit from game "(Difftime == 60), key = 6"
	{
		while (isCursorKeyPressed(key) == 1)
		{

			if (key == 3 && x2 < 360)//right key
			{
				x1 += 40, x2 += 40;
				col++;					
			}
			if (key == 4 && y2 < 290) //downwards key
			{
				y1 += 30, y2 += 30;
				row++;
			}
			if (key == 1 && x1 > 30) //left key
			{
				x1 -= 40, x2 -= 40;
				col--;
			}
			if (key == 2 && y1 > 30) //up key
			{
				y1 -= 30, y2 -= 30;
				row--;
			}
			if (key == 5) //enter key
			{
				ClearScreen();
				gridgen(grid, 1);
				Sleep(300);
				swapp(grid, row, col);
			}
			if (key == 6) //escape key to end game
			{
				ClearScreen();
				cout << "Game Saved" << endl;
				gamesave(grid);
			}
			ClearScreen();
			myPointer(x1, y1, x2, y2, 250, 0, 0, 0, 0, 0);
		}
		candyboard(grid);
		//end = time(NULL);
		//if (difftime(end, start) == 2)
			//key = 6;
	}
}
void swapp(int grid[][gsize + 3], int& R, int& C)
{
	int once = 1;
	int row2=0, col2=0;
	int score = 0;
	int key = 1;
	char c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14;
	int temp, temp2;
	bool specialpop = false;

	while (key != 5)
	{
		while (isCursorKeyPressed(key) == 1) //to check box to swap with
		{
			if (key == 1) //for left side swap
			{
				row2 = row1, col2 = col1 - 1;
				/*c1 = colorcheck(grid[row1][col1]);
				c2 = colorcheck(grid[row1 + 1][col1]);
				c3 = colorcheck(grid[row1 + 2][col1]);
				c4 = colorcheck(grid[row1 - 1][col1]);
				c5 = colorcheck(grid[row1][col1 + 1]);
				c6 = colorcheck(grid[row1][col1 + 2]);
				c7 = colorcheck(grid[row2][col2]);
				c8 = colorcheck(grid[row2 + 1][col2]);
				c9 = colorcheck(grid[row2 + 2][col2]);
				c10 = colorcheck(grid[row2][col2 - 1]);
				c11 = colorcheck(grid[row2][col2 + 1]);
				c12 = colorcheck(grid[row2][col2 - 2]);
				c13 = colorcheck(grid[row2 - 1][col2]);
				c14 = colorcheck(grid[row2 - 2][col2]);
*/

				temp = grid[row2][col2], temp2 = grid[row1][col1];

				//check min 3 in a row/col or 3 matching colors in row/col, if true then swap permitted

				//to check special swaps (CB-CB, STRIPED-WRAPPED, WRAPPED-WRAPPED
				//if ((temp == 16 || temp2 == 16) || ((temp >= 6 && temp <= 10) && (temp2 >= 11 && temp2 <= 15)) || ((temp2 >= 6 && temp2 <= 10) && (temp >= 11 && temp <= 15)) || (temp2 >= 11 && temp2 <= 15) && (temp >= 11 && temp <= 15))
				//	specialpop = true;

				////check min 3 in a row/col or 3 matching colors in row/col, if true then swap permitted
				//if (specialpop || ((temp == grid[row1 + 1][col1] && temp == grid[row1 + 2][col1]) || (temp == grid[row1][col1 + 1] && temp == grid[row1][col1 + 2])
				//	|| (temp == grid[row1 - 1][col1] && temp == grid[row1 - 2][col1]) || (temp == grid[row1][col1 - 1] && temp == grid[row1][col1 - 2]) || (temp2 == grid[row2 + 1][col2] && temp2 == grid[row2 + 2][col2]) || (temp2 == grid[row2][col2 + 1] && temp2 == grid[row2][col2 + 2]) ||
				//	(temp2 == grid[row2][col2 - 1] && temp2 == grid[row2][col2 - 2]) || (temp2 == grid[row2 - 1][col2] && temp2 == grid[row2 - 2][col2]) || (c7 == c2 && c2 == c3) || (c7 == c5 && c5 == c6) || (c1 == c8 && c8 == c9)
				//	|| (c1 == c10 && c10 == c12) || (c1 == c13 && c13 == c14) || (c7 == c4 && c4 == c10)))
				//{
				//swap(grid[row1][col1], grid[row2][col2]);
				swap(grid[R][C], grid[R][C - 1]);
				ClearScreen();
				gridgen(grid, 1);
				Sleep(300);

				//add checking functions here
				plain(grid);

				ClearScreen();
				gridgen(grid, 1);
				Sleep(300);

				//scorer

			}

			/*else
			{
				swapfail(grid, row1, col1, row2, col2);
			}*/


			//}
			if (key == 2) //up swap
			{
				row2 = row1 - 1, col2 = col1;
				/*c1 = colorcheck(grid[row1][col1]);
				c2 = colorcheck(grid[row1 + 1][col1]);
				c3 = colorcheck(grid[row1 + 2][col1]);
				c4 = colorcheck(grid[row1 - 1][col1]);
				c5 = colorcheck(grid[row1][col1 + 1]);
				c6 = colorcheck(grid[row1][col1 + 2]);
				c7 = colorcheck(grid[row2][col2 + 2]);
				c8 = colorcheck(grid[row1][col1 - 1]);
				c9 = colorcheck(grid[row1][col1 - 2]);
				c10 = colorcheck(grid[row2][col2 - 1]);
				c11 = colorcheck(grid[row2][col2 + 1]);
				c12 = colorcheck(grid[row2][col2 - 2]);
				c13 = colorcheck(grid[row2 - 1][col2]);
				c14 = colorcheck(grid[row2 - 2][col2]);*/

				temp2 = grid[row1][col1], temp = grid[row2][col2];

				//if ((temp == 16 || temp2 == 16) || ((temp >= 6 && temp <= 10) && (temp2 >= 11 && temp2 <= 15)) || ((temp2 >= 6 && temp2 <= 10) && (temp >= 11 && temp <= 15)) || (temp2 >= 11 && temp2 <= 15) && (temp >= 11 && temp <= 15))
				//	specialpop = true;

				////check min 3 in a row/col or 3 matching colors in row/col, if true then swap permitted
				//if ((specialpop || (((temp == grid[row2][col2 + 1] && temp == grid[row2][col2 + 2]) || ((temp == grid[row2][col2 - 1] && temp == grid[row2][col2 - 2]) || (temp == grid[row2 - 1][col2] && temp == grid[row2 - 2][col2]) ||
				//	(temp2 == grid[row1 + 1][col1] && temp2 == grid[row1 + 2][col1]) || (temp2 == grid[row1][col1 - 1] && temp2 == grid[row1][col1 - 2]) || (temp2 == grid[row1][col1 + 1] && temp2 == grid[row1][col1 + 2]) ||
				//	((c4 == c2 && c2 == c3) || (c4 == c5 && c5 == c6) || (c4 == c8 && c8 == c9) || (c1 == c10 && c10 == c12) || (c1 == c13 && c13 == c14) || (c1 == c11 && c11 == c7)))))))
				//{
				swap(grid[row1][col1], grid[row2][col2]);
				ClearScreen();
				gridgen(grid, 1);
				Sleep(300);

				//add checking functions here
				plain(grid);

				ClearScreen();
				gridgen(grid, 1);
				Sleep(300);

				//scorer


				/*}
				else
				{
					swapfail(grid, row1, col1, row2, col2);
				}*/


			}
			if (key == 3) //right shift
			{
				temp2 = grid[row2][col2], temp = grid[row1][col1];
				/*row2 = row1, col2 = col1 - 1;
				c1 = colorcheck(grid[row1][col1]);
				c2 = colorcheck(grid[row1 + 1][col1]);
				c3 = colorcheck(grid[row1 + 2][col1]);
				c4 = colorcheck(grid[row1 - 1][col1]);
				c5 = colorcheck(grid[row1][col1 + 1]);
				c6 = colorcheck(grid[row1][col1 + 2]);
				c7 = colorcheck(grid[row2][col2]);
				c8 = colorcheck(grid[row2 + 1][col2]);
				c9 = colorcheck(grid[row2 + 2][col2]);
				c10 = colorcheck(grid[row2][col2 - 1]);
				c11 = colorcheck(grid[row2][col2 + 1]);
				c12 = colorcheck(grid[row2][col2 - 2]);
				c13 = colorcheck(grid[row2 - 1][col2]);
				c14 = colorcheck(grid[row2 - 2][col2]);




				//check min 3 in a row/col or 3 matching colors in row/col, if true then swap permitted

				//to check special swaps (CB-CB, STRIPED-WRAPPED, WRAPPED-WRAPPED
				if ((temp == 16 || temp2 == 16) || ((temp >= 6 && temp <= 10) && (temp2 >= 11 && temp2 <= 15)) || ((temp2 >= 6 && temp2 <= 10) && (temp >= 11 && temp <= 15)) || (temp2 >= 11 && temp2 <= 15) && (temp >= 11 && temp <= 15))
					specialpop = true;

				//check min 3 in a row/col or 3 matching colors in row/col, if true then swap permitted
				if ((specialpop || (((temp == grid[row1 + 1][col1] && temp == grid[row1 + 2][col1]) || (temp == grid[row1][col1 + 1] && temp == grid[row1][col1 + 2]) || (temp == grid[row1 - 1][col1] && temp == grid[row1 - 2][col1]) ||
					(temp == grid[row1][col1 - 1] && temp == grid[row1][col1 - 2]) || (temp2 == grid[row2 + 1][col2] && temp2 == grid[row2 + 2][col2]) || (temp2 == grid[row2][col2 + 1] && temp2 == grid[row2][col2 + 2]) ||
					(temp2 == grid[row2][col2 - 1] && temp2 == grid[row2][col2 - 2]) || temp2 == grid[row2 - 1][col2] && temp2 == grid[row2 - 2][col2]) || ((c7 == c2 && c2 == c3) || (c7 == c5 && c5 == c6)) || (c1 == c8 && c8 == c9)
					|| (c1 == c10 && c10 == c12) || (c1 == c13 && c13 == c14) || (c7 == c4 && c4 == c10))))
				{
				*/	swap(grid[row1][col1], grid[row2][col2]);
				ClearScreen();
				gridgen(grid, 1);
				Sleep(300);

				//add checking functions here
				plain(grid);

				ClearScreen();
				gridgen(grid, 1);
				Sleep(300);

				//scorer

			}
			//else
			//{
			//	swapfail(grid, row1, col1, row2, col2);
			//}


			if (key == 4) //down
			{
				temp2 = grid[row2][col2], temp = grid[row1][col1];
				/*row2 = row1, col2 = col1 - 1;
				c1 = colorcheck(grid[row1][col1]);
				c2 = colorcheck(grid[row1 + 1][col1]);
				c3 = colorcheck(grid[row1 + 2][col1]);
				c4 = colorcheck(grid[row1 - 1][col1]);
				c5 = colorcheck(grid[row1][col1 + 1]);
				c6 = colorcheck(grid[row1][col1 + 2]);
				c7 = colorcheck(grid[row2][col2]);
				c8 = colorcheck(grid[row2 + 1][col2]);
				c9 = colorcheck(grid[row2 + 2][col2]);
				c10 = colorcheck(grid[row2][col2 - 1]);
				c11 = colorcheck(grid[row2][col2 + 1]);
				c12 = colorcheck(grid[row2][col2 - 2]);
				c13 = colorcheck(grid[row2 - 1][col2]);
				c14 = colorcheck(grid[row2 - 2][col2]);




				//check min 3 in a row/col or 3 matching colors in row/col, if true then swap permitted

				//to check special swaps (CB-CB, STRIPED-WRAPPED, WRAPPED-WRAPPED
				if ((temp == 16 || temp2 == 16) || ((temp >= 6 && temp <= 10) && (temp2 >= 11 && temp2 <= 15)) || ((temp2 >= 6 && temp2 <= 10) && (temp >= 11 && temp <= 15)) || (temp2 >= 11 && temp2 <= 15) && (temp >= 11 && temp <= 15))
					specialpop = true;

				//check min 3 in a row/col or 3 matching colors in row/col, if true then swap permitted
				if ((specialpop || (((temp == grid[row1 + 1][col1] && temp == grid[row1 + 2][col1]) || (temp == grid[row1][col1 + 1] && temp == grid[row1][col1 + 2]) || (temp == grid[row1 - 1][col1] && temp == grid[row1 - 2][col1]) ||
					(temp == grid[row1][col1 - 1] && temp == grid[row1][col1 - 2]) || (temp2 == grid[row2 + 1][col2] && temp2 == grid[row2 + 2][col2]) || (temp2 == grid[row2][col2 + 1] && temp2 == grid[row2][col2 + 2]) ||
					(temp2 == grid[row2][col2 - 1] && temp2 == grid[row2][col2 - 2]) || temp2 == grid[row2 - 1][col2] && temp2 == grid[row2 - 2][col2]) || ((c7 == c2 && c2 == c3) || (c7 == c5 && c5 == c6)) || (c1 == c8 && c8 == c9)
					|| (c1 == c10 && c10 == c12) || (c1 == c13 && c13 == c14) || (c7 == c4 && c4 == c10))))
				{
				*/	swap(grid[row1][col1], grid[row2][col2]);
				ClearScreen();
				gridgen(grid, 1);
				Sleep(300);

				//add checking functions here
				plain(grid);

				ClearScreen();
				gridgen(grid, 1);
				Sleep(300);

				//scorer
				//else
			//	{
				//	swapfail(grid, row1, col1, row2, col2);
				//}

			}
		}
	}
}
void scorer(char color, int num)
{
	switch (color)
	{
	case'r':
	{
		score +=(30*num);
		break;
	}
	case 'y':
	{
		score += (30*num);
		break;
	}
	case 'g':
	{
		score += (40*num);
		break;
	}
	case 'b':
	{
		score += (50*num);
		break;
	}
	case 'o':
	{
		score += (60*num);
		break;
	}
	default:
	{
		break;
	}
	}
}
void gamesave(int grid[][gsize+3])
{
	fstream fout;
	fout.open("SaveData.txt", ios::out);
	for (int i = 0; i < gsize; i++)
	{
		for (int j = 0; j < gsize; j++)
		{
			fout << grid[i][j]<<" " ;
		}
		
	}
	fout <<" "<< score<<" "<< moves;
	fout.close();
}
void gameload(int grid[][gsize+3])
{
	fstream fin;
	fin.open("SaveData.txt", ios::in);
	for (int i = 0; i < gsize; i++)
	{
		for (int j = 0; j < gsize; j++)
		{
			fin >> grid[i][j];
		}
		
	}
	fin >> score;
	fin >> moves;
	fin.close();
	//cout <<score<< moves;
	
}
void swapfail(int grid[][gsize+3], int R, int C, int R1, int C1)
{
	swap(grid[R][C], grid[R1][C1]);
	ClearScreen();
	gridgen(grid, 1);
	Sleep(100);
	swap(grid[R][C], grid[R1][C1]);
	ClearScreen();
	gridgen(grid, 1);
}
void plainbomb(int grid[][gsize+3], int candy1, int candy2)
{
	char c, c2;
	if ((candy1 == 16 || candy2 == 16) && (candy1 <= 6 || candy2 <= 6))
	{
		if (candy1 == 16)
		{
			c = colorcheck(candy2);
			for (int i = 0; i < gsize; i++)
			{
				for (int j = 0; j < gsize; j++)
				{
					c2 = colorcheck(grid[i][j]);
					if (c == c2)
					{
						grid[i][j] = 0;
					}
				}
			}
		}
		else
		{
			c = colorcheck(candy1);
			for (int i = 0; i < gsize; i++)
			{
				for (int j = 0; j < gsize; j++)
				{
					c2 = colorcheck(grid[i][j]);
					if (c == c2)
					{
						grid[i][j] = 0;
					}
				}
			}
		}
		shifting(grid);
	}
}
void bombwrap(int grid[][gsize+3],int candy, int row, int col)
{
	char ctemp;
	int plain_c = candy - 10;
	if (grid[row][col] == 16 && grid[row][col + 1] == candy || grid[row][col + 1] == 16 && grid[row][col] == candy || grid[row][col] == 16 && grid[row + 1][col] == candy || grid[row + 1][col] == 16 && grid[row][col] == candy)
	{
		for (int x = 0; x < gsize; x++)
		{
			for (int y = 0; y < gsize; y++)
			{
				if (grid[x][y] == plain_c)
				{
					grid[x][y] += 10;
					for (int i = x - 1; i <= x + 1; i++)
					{
						for (int j = y - 1; j <= y + 1; j++)
						{
							ctemp = colorcheck(grid[i][j]);
							switch (ctemp)
							{
							case'r':
							{
								score += 30;
								break;
							}
							case 'y':
							{
								score += 30;
								break;
							}
							case 'g':
							{
								score += 40;
								break;
							}
							case 'b':
							{
								score += 50;
								break;
							}
							case 'o':
							{
								score += 60;
								break;
							}
							default:
							{
								break;
							}
							}
							grid[i][j] = 0;
						}
					}


				}
			}
		}
		shifting(grid);
	}
}
void plain_stripe(int grid[][gsize+3])
{
	char c1, c2, c3;
	for (int i = 0; i < gsize; i++)
	{
		for (int j = 0; j < gsize; j++)
		{
		c1 = colorcheck(grid[i][j]);
			c2 = colorcheck(grid[i + 1][j]);
			c3 = colorcheck(grid[i + 2][j]);
			//vertical crushing, full row is burst
			if ((c1 == c2 && c2 == c3) && ((grid[i][j] >= 6 && grid[i][j] <= 10) || (grid[i + 1][j] >= 6 && grid[i + 1][j] <= 10) || (grid[i + 2][j] >= 6 && grid[i + 2][j] <= 10)))
			{

				rstart = i;
				cstart = j;
				poptype = 'r';
				cpopped = gsize;
				scorer(c1, cpopped);
				if (grid[i][j] >= 6 && grid[i][j] <= 10)
				{
					for (int k = 0; k < gsize; k++)
					{
						grid[i][k] = 0;
					}
				}
				else if ((grid[i + 1][j] >= 6 && grid[i + 1][j] <= 10))
				{
					for (int k = 0; k < gsize; k++)
					{
						grid[i + 1][k] = 0;
					}
				}
				else if ((grid[i + 2][j] >= 6 && grid[i + 2][j] <= 10))
				{
					for (int k = 0; k < gsize; k++)
					{
						grid[i + 2][k] = 0;
					}
				}

				grid[i][j] = 0;
				grid[i + 1][j] = 0;
				grid[i + 2][j] = 0;
			}
			shifting(grid);
			//vertical check then full column is blown
			c1 = colorcheck(grid[i][j]);
			c2 = colorcheck(grid[i][j + 1]);
			c3 = colorcheck(grid[i][j + 2]);
			if ((c1 == c2 && c2 == c3) && ((grid[i][j] >= 6 && grid[i][j] <= 10) || (grid[i][j + 1] >= 6 && grid[i][j + 1] <= 10) || (grid[i][j + 2] >= 6 && grid[i][j + 2] <= 10)))
			{

				rstart = i;
				cstart = j;
				poptype = 'c';
				cpopped = gsize;
				candycolor = colorcheck(grid[i][j]);
				scorer(candycolor, cpopped);
				if (grid[i][j] >= 6 && grid[i][j] <= 10)
				{
					for (int k = 0; k < gsize; k++)
					{
						grid[k][j] = 0;
					}
				}
				else if ((grid[i][j + 1] >= 6 && grid[i][j + 1] <= 10))
				{
					for (int k = 0; k < gsize; k++)
					{
						grid[k][j + 1] = 0;
					}
				}
				else if ((grid[i][j + 2] >= 6 && grid[i][j + 2] <= 10))
				{
					for (int k = 0; k < gsize; k++)
					{
						grid[k][j + 2] = 0;
					}
				}
				grid[i][j] = 0;
				grid[i][j + 1] = 0;
				grid[i][j + 2] = 0;
			}
			shifting(grid);
		}
	}
}
void initial_check(int grid[][gsize+3])
{
	for (int i = 0; i < gsize; i++)
	{
		for (int j = 0; j < gsize; j++)
		{
			if (grid[i][j] == 0)
			{
				grid[i][j]=randgen();
			}
		}
	}
	Sleep(300);
	ClearScreen();
	gridgen(grid, 1);
	//shifting
	shifting(grid);
	Sleep(300);
	ClearScreen();
}
void shift(int grid[][gsize+3], int cpopped, int index_c, int  index_r)
{
	for (int i = index_r; i >= cpopped; i--)
	{
		grid[i][index_c] = grid[i - cpopped][index_c];
	}
	//srand(time(0));
	for (int i = cpopped - 1; i >= 0; i--)
	{
		grid[i][index_c] = randgen();
	}
}
void shifting(int grid[][gsize+3])
{
	for (int x = 0; x < gsize; x++)
	{
		for (int y = 0; y < gsize; y++)
		{
			if (grid[x][y] == 0)
			{
				shift(grid, 1, y, x);
			}
		}
	}
}
void stripes_3(int grid[][gsize + 3])
{
	//to destroy any matching stripes
	int temp;
	bool stripe = false;
	for (int i = 0; i < gsize; i++)
	{
		for (int j = 0; j < gsize; j++)
		{
			temp = grid[i][j];
			if (temp >= 6 && temp <= 10)
				stripe = true;
			if (stripe&&(grid[i][j] == grid[i + 1][j] && grid[i + 1][j] == grid[i + 2][j]))
			{

				rstart = i;
				cstart = j;
				poptype = 'r';
				cpopped = 9;
				candycolor = colorcheck(grid[i][j]);
				scorer(candycolor, cpopped);
				for (int k = 0; k < gsize; k++)
				{
					grid[k][j] = 0;
				}
				i++;
				shifting(grid);
				
			}
			if (stripe&&(grid[i][j] == grid[i][j + 1] && grid[i][j + 1] == grid[i][j + 2]))
			{

				rstart = i;
				cstart = j;
				poptype = 'c';
				cpopped = 9;
				candycolor = colorcheck(grid[i][j]);
				scorer(candycolor, cpopped);
				for (int k = 0; k < gsize; k++)
				{
					grid[i][k] = 0;
				}
				j++;
				shifting(grid);
			}
		}
	}

}
