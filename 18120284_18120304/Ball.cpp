#include "Ball.h"

Ball::Ball()
{
}

Ball::~Ball()
{
}

Ball::Ball(float x, float y)
{
	this->x = x;
	this->y = y;
	this->xball = x;
	this->yball = y;
	this->vx = 0;
	this->vy = 0;
}

void Ball::drawball()
{
	//tạo ra bằng cách in ra màn hình console các kí tự ' ' và 'o'
	COORD c;
	c.X = int(this->xball);
	c.Y = int(this->yball);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);	//xác định tọa độ cột và hàng phía trước của bóng
	cout << ' ';													//in ra các kí tự ' '
	c.X = int(this->x);
	c.Y = int(this->y);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);	//xác định tọa độ hiện tại của bóng
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);	//chọn màu cho bóng (màu vàng)
	cout << 'o';													//in quả bóng
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	this->xball = this->x;
	this->yball = this->y;
}