#include<ostream>
#include"FadiCCGraphics.h"
//#include"Head.h"

using namespace std;
const int gsize = 9;
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

//void wrappedgraphic(int x1, int y1, char color)
//{
//	COLORREF colorSide, colorCentre;
//	switch (color)
//	{
//	case 'r':
//	{
//		colorSide = lred;
//		colorCentre = red;
//		break;
//	}
//	case 'b':
//	{
//		colorSide = lblue;
//		colorCentre = blue;
//		break;
//	}
//	case 'g':
//	{
//		colorSide = lgreen;
//		colorCentre = green;
//		break;
//	}
//	case 'y':
//	{
//		colorSide = lyellow;
//		colorCentre = yellow;
//		break;
//	}
//	case 'o':
//	{
//		colorSide = lorange;
//		colorCentre = orange;
//		break;
//	}
//	}
//
//	//rect coordinates: x1+40=x2, y1+30=y2
//	myRect(x1, y1, x1+40, y1+30, colorSide, colorSide);
//
//	//ellipse coordinates: E_x1=x1+5,E_y1=y1+5, E_x2=x1+35, E_y2=y1+25
//	myEllipse(x1+5, y1+5, x1+35, y1+25, colorCentre, colorCentre);
//}
//void colorbombgraphic(int x1, int y1)
//{
//	myEllipse(x1, y1, x1 + 40, y1 + 30, brown, brown);
//	myEllipse(x1 + 5, y1 + 5, x1 + 15, y1 + 15, yellow, yellow);
//	myEllipse(x1 + 25, y1 + 5, x1 + 35, y1 + 15, green, green);
//	myEllipse(x1 + 25, y1 + 20, x1 + 35, y1 + 25, red, red);
//	myEllipse(x1 + 5, y1 + 20, x1 + 15, y1 + 25, blue, blue);
//}
//void plaingraphic(int x1, int y1, char color)
//{
//	COLORREF colorSide, colorCentre;
//	switch (color)
//	{
//	case 'r':
//	{
//		colorSide = lred;
//		colorCentre = red;
//		break;
//	}
//	case 'b':
//	{
//		colorSide = lblue;
//		colorCentre = blue;
//		break;
//	}
//	case 'g':
//	{
//		colorSide = lgreen;
//		colorCentre = green;
//		break;
//	}
//	case 'y':
//	{
//		colorSide = lyellow;
//		colorCentre = yellow;
//		break;
//	}
//	case 'o':
//	{
//		colorSide = lorange;
//		colorCentre = orange;
//		break;
//	}
//	}
//
//	myEllipse(x1, y1, x1 + 15, y1 + 30, colorSide, colorCentre);
//}
//void stripedgraphic(int x1, int y1,char color)
//{
//	COLORREF colorSide, colorCentre;
//	switch (color)
//	{
//	case 'r':
//	{
//		colorSide = lred;
//		colorCentre = red;
//		break;
//	}
//	case 'b':
//	{
//		colorSide = lblue;
//		colorCentre = blue;
//		break;
//	}
//	case 'g':
//	{
//		colorSide = lgreen;
//		colorCentre = green;
//		break;
//	}
//	case 'y':
//	{
//		colorSide = lyellow;
//		colorCentre = yellow;
//		break;
//	}
//	case 'o':
//	{
//		colorSide = lorange;
//		colorCentre = orange;
//		break;
//	}
//	}
//
//	
//	myEllipse(x1, y1, x1+20, y1+30,colorSide, colorCentre);
//	myLine(x1+5, y1+5, x1+15, y1+25, colorSide);
//
//	
//}
//void myEllipse(int x1, int y1, int x2, int y2,COLORREF colorForeground,COLORREF colorBackground)

int main()
{
	//const int gsize = 10, target = 500, moves = 20;
	//int grid[gsize][gsize];
	//char candy[gsize][gsize];
	//int score = 0;//denotes current user score

	//dimensions of one block on grid= 40x30
	
	//grid
	myRect(20, 20, 380, 290, black,white);
	wrappedgraphic(20, 20, 'o');
	plaingraphic(70, 20, 'y');
	stripedgraphic(100, 20, 'b');
	colorbombgraphic(140, 20);


	////plain candy graphics (x-gap=15,y-gap=30)
	//myEllipse(50, 50, 65, 80,lred,red); //red
	//myEllipse(100, 50, 115, 80, lblue, blue);//blue
	//myEllipse(150, 50, 165, 80, green, green);//green
	//myEllipse(200, 50, 215, 80, lyellow, yellow);//yellow
	//myEllipse(250, 50, 265, 80, lorange, orange);//orange
	
	//
	////wrapped candy graphics 
	//myRect(50, 100, 90, 130, lred, lred);
	//myEllipse(55, 105, 85, 125, red, red);
	
	//myRect(50, 100, 90, 130, lblue,lblue);
	//myEllipse(55, 105, 85, 125, blue, blue);

	//stripes candy graphics
	//myEllipse(20, 50, 40, 85, blue, lblue);
	//myLine(25, 55, 35, 80, blue);


	//myEllipse(50, 50, 70, 85, red, lred);
	//myLine(55, 55, 65, 80, red);
	//
	//myEllipse(80, 50, 100, 85, green, lgreen);
	//myLine(85, 55, 95, 80, green);

	//myEllipse(110, 50, 130, 85, orange, lorange);
	//myLine(115, 55, 125, 80, orange);

	////colorbomb
	/*myEllipse(50, 50, 90, 80, brown, brown);
	myEllipse(55, 55, 65, 65,yellow, yellow);
	myEllipse(75, 55, 85, 65, green, green);
	myEllipse(75, 70, 85, 75, red, red);
	myEllipse(55, 70, 65, 75, blue,blue);
	*/
	
	
	
	Sleep(30000);
	//myRect(60, 60, 80, 80, 0, 255, 0, 0, 255, 0);
	Sleep(5000);


	system("Pause");
	return 0;
}
