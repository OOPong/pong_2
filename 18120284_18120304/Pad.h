#define _WIN32_WINNT 0x0501
#include <windows.h>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <cstdlib>
#include <string>

using namespace std;

#pragma once
class Pad
{
public:
	float x, y, xpad, ypad, vx;			//x và y là tọa độ phía trước của thanh đỡ, xpad và ypad là tạo độ phía sau của thanh đỡ
	int size;							//size là độ dài của thanh đỡ
	Pad();
	~Pad();
	Pad(float, float, int);
	void drawpad(); //tạo ra đối tượng thanh đỡ bóng trên màn hình
};

