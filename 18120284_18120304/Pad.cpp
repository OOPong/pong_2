#include "Pad.h"

Pad::Pad()
{
}

Pad::~Pad()
{
}

Pad::Pad(float x, float y, int size)
{
	this->x = x;
	this->y = y;
	this->size = size;
	this->xpad = x;
	this->ypad = y;
}

void Pad::drawpad()
{
	//tạo ra bằng cách in ra màn hình console các kí tự ' ' và '=' 
	COORD c;
	c.X = int(floor(this->xpad)) - this->size;
	c.Y = int(floor(this->ypad));
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);	//xác định tọa độ cột và hàng của thanh đỡ
	for (int i = -this->size; i < this->size; ++i)
		cout << ' ';							//in ra kí tự ' '
	c.X = int(floor(this->x)) - this->size;
	c.Y = int(floor(this->y));
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);  
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);	//chọn màu cho thanh đỡ (màu xanh dương)
	for (int i = -this->size; i < this->size; ++i)
		cout << '=';
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	xpad = x;
	ypad = y;
}
