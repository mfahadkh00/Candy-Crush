#include <windows.h> 
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
//#ifndef MYGRAPHICS_H
#define MYGRAPHICS_H
#include <windows.h>

COLORREF red = RGB(255, 0, 0);
COLORREF blue = RGB(0, 0, 255);
COLORREF green = RGB(0, 255, 0);
COLORREF yellow = RGB(255, 255, 0);
COLORREF orange = RGB(255, 140, 0);
COLORREF lred = RGB(255, 204, 203);
COLORREF lblue = RGB(125, 242, 255);
COLORREF lgreen = RGB(204, 255, 58);
COLORREF lyellow = RGB(224, 222, 0);
COLORREF lorange = RGB(255, 196, 148);
COLORREF brown = RGB(165,54,0);
COLORREF pink = RGB(255, 193, 203);
COLORREF purple = RGB(137, 0, 100);
COLORREF white = RGB(0, 0, 0);
COLORREF black = RGB(255, 255, 255);


void myLine(int x1, int y1, int x2, int y2, COLORREF lineColor)
{

	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 3, lineColor); //2 is the width of the pen
	SelectObject(device_context, pen);
	MoveToEx(device_context, x1, y1, NULL);
	LineTo(device_context, x2, y2);
	DeleteObject(pen);

	ReleaseDC(console_handle, device_context);
}
void myRect(int x1, int y1, int x2, int y2, COLORREF lineColor, COLORREF fillColor)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 2, lineColor);
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(fillColor);
	SelectObject(device_context, brush);

	Rectangle(device_context, x1, y1, x2, y2);
	DeleteObject(pen);
	DeleteObject(brush);
	ReleaseDC(console_handle, device_context);
}
void myEllipse(int x1, int y1, int x2, int y2, COLORREF lineColor, COLORREF fillColor)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 3.5, lineColor);
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(fillColor);
	SelectObject(device_context, brush);
	Ellipse(device_context, x1, y1, x2, y2);
	DeleteObject(pen);
	DeleteObject(brush);
	ReleaseDC(console_handle, device_context);

}
void myPointer(int x1, int y1, int x2, int y2, int R, int G, int B, int FR, int FG, int FB)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(FR, FG, FB)); //Fill color is passed as parameter to the function!!!

	SelectObject(device_context, brush);

	Rectangle(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);
}
bool isCursorKeyPressed(int& whickKey)   //whichKey passed as reference.... 
{
	char key;
	key = GetAsyncKeyState(VK_LEFT);
	if (key == 1)
	{
		whickKey = 1;		// 1 if left key is pressed 
		return true;
	}
	key = GetAsyncKeyState(VK_UP);
	if (key == 1)
	{
		whickKey = 2;		// 2 if up key is pressed
		return true;
	}

	key = GetAsyncKeyState(VK_RIGHT);
	if (key == 1)
	{
		whickKey = 3; // 3 if right key is pressed
		return true;
	}
	key = GetAsyncKeyState(VK_DOWN);
	if (key == 1)
	{

		whickKey = 4;   // 4 if down key is pressed
		return true;
	}
	key = GetAsyncKeyState(VK_RETURN);
	if (key == 1)
	{
		whickKey = 5;  // 5 if enter is pressed
		return true;
	}
	key = GetAsyncKeyState(VK_ESCAPE);
	if (key == 1)
	{
		whickKey = 6; //escape key
		return true;
	}
	return false;
}
void Rect2(int x1, int y1, int x2, int y2, int R, int G, int B, int FR, int FG, int FB)
{
	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	//change the color by changing the values in RGB (from 0-255)
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
	SelectObject(device_context, pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(FR, FG, FB)); //Fill color is passed as parameter to the function!!!

	SelectObject(device_context, brush);

	Rectangle(device_context, x1, y1, x2, y2);
	ReleaseDC(console_handle, device_context);
	DeleteObject(pen);
	DeleteObject(brush);
}
void myDrawText(int x, int y, int ht, char str[], COLORREF lineColor, COLORREF fillColor)
{
	WCHAR wstr[20] = {};
	for (int i = 0; i < 20 && str[i]; ++i)
		wstr[i] = str[i];

	RECT rects;
	rects.left = x;
	rects.top = y;
	rects.right = x + ht;
	rects.bottom = y + ht;//(x,y,x+ht,y+ht);

	HWND console_handle = GetConsoleWindow();
	HDC device_context = GetDC(console_handle);

	SetTextColor(device_context, lineColor);
	SetBkColor(device_context, fillColor);
	//DrawText(device_context, wstr, -1, &rects, DT_TOP | DT_NOCLIP);

	ReleaseDC(console_handle, device_context);

}

//dimensions of one block on grid= 40x30
void wrappedgraphic(int x1, int y1, char color)
{
	COLORREF colorSide, colorCentre;
	switch (color)
	{
	case 'r':
	{
		colorSide = lred;
		colorCentre = red;
		break;
	}
	case 'b':
	{
		colorSide = lblue;
		colorCentre = blue;
		break;
	}
	case 'g':
	{
		colorSide = lgreen;
		colorCentre = green;
		break;
	}
	case 'y':
	{
		colorSide = lyellow;
		colorCentre = yellow;
		break;
	}
	case 'o':
	{
		colorSide = lorange;
		colorCentre = orange;
		break;
	}
	}

	//rect coordinates: x1+40=x2, y1+30=y2
	myRect(x1+5, y1+5, x1 + 32, y1 + 25, colorSide, colorSide);

	//ellipse coordinates: E_x1=x1+5,E_y1=y1+5, E_x2=x1+35, E_y2=y1+25
	myEllipse(x1 + 5, y1 + 5, x1 + 30, y1 + 22, colorCentre, colorCentre);
}
void colorbombgraphic(int x1, int y1)
{
	myEllipse(x1, y1, x1 + 40, y1 + 30, brown, brown);
	myEllipse(x1 + 5, y1 + 5, x1 + 15, y1 + 15, yellow, yellow);
	myEllipse(x1 + 25, y1 + 5, x1 + 35, y1 + 15, green, green);
	myEllipse(x1 + 25, y1 + 20, x1 + 35, y1 + 25, red, red);
	myEllipse(x1 + 5, y1 + 20, x1 + 15, y1 + 25, blue, blue);
}
void plaingraphic(int x1, int y1, char color)
{
	COLORREF colorSide, colorCentre;
	switch (color)
	{
	case 'r':
	{
		colorSide = lred;
		colorCentre = red;
		break;
	}
	case 'b':
	{
		colorSide = lblue;
		colorCentre = blue;
		break;
	}
	case 'g':
	{
		colorSide = lgreen;
		colorCentre = green;
		break;
	}
	case 'y':
	{
		colorSide = lyellow;
		colorCentre = yellow;
		break;
	}
	case 'o':
	{
		colorSide = lorange;
		colorCentre = orange;
		break;
	}
	}

	myEllipse(x1+5, y1, x1 + 20, y1 + 30, colorSide, colorCentre);
}
void stripedgraphic(int x1, int y1, char color)
{
	COLORREF colorSide, colorCentre;
	switch (color)
	{
	case 'r':
	{
		colorSide = lred;
		colorCentre = red;
		break;
	}
	case 'b':
	{
		colorSide = lblue;
		colorCentre = blue;
		break;
	}
	case 'g':
	{
		colorSide = lgreen;
		colorCentre = green;
		break;
	}
	case 'y':
	{
		colorSide = lyellow;
		colorCentre = yellow;
		break;
	}
	case 'o':
	{
		colorSide = lorange;
		colorCentre = orange;
		break;
	}
	}


	myEllipse(x1+5, y1, x1 + 25, y1 + 30, colorSide, colorCentre);
	myLine(x1 + 8, y1 + 5, x1 + 18, y1 + 25, colorSide);


}
#pragma once
