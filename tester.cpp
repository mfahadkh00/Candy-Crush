#include<iostream>
#include<windows.h>
#include"FadiCCGraphics.h"
#include"myconsole.h"
using namespace std;
int main()
{
	myLine(20, 20, 400, 20, pink);
	myLine(20, 20, 20, 310, pink);
	myLine(20, 310, 400, 310, pink);
	myLine(400, 310, 400, 20, pink);
	PlaceCursor(2, 0);
	cout << "  1    2";
	Sleep(1000);
	
	system("Pause");
	return 0;
}

