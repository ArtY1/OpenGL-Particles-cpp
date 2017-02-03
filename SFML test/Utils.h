#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <Windows.h>

using namespace std;

inline float Dist(const sf::Vector2f &v, const sf::Vector2f &u)
{
	return sqrt(pow(v.x-u.x, 2) + pow(v.y-u.y, 2));
}

inline float Norm(const sf::Vector2f &v)
{
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

inline float Clamp(const float f,const float min,const float max)
{
	if (f > max)
		return max;
	else if (f < min)
		return min;
	else
		return f;
}

// FPS
HANDLE _stdOutputH = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO _cTMPBuffer;

CONSOLE_SCREEN_BUFFER_INFO _cFPSBuffer;

inline void PrintAt(const string text, const CONSOLE_SCREEN_BUFFER_INFO &crsPos)
{
	GetConsoleScreenBufferInfo(_stdOutputH, &_cTMPBuffer); // remember the current position of the cursor
	
	SetConsoleCursorPosition(_stdOutputH, crsPos.dwCursorPosition); // move the cursor to the desired position
	cout << text << endl;

	SetConsoleCursorPosition(_stdOutputH, _cTMPBuffer.dwCursorPosition); // put the cursor back

}