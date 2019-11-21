#ifndef __HEADER_H__
#define __HEADER_H__

#include "Ball.h"

void set(Ball& ball, Pad& p1, Pad& p2, int& p1score, int& p2score, bool start);	//là hàm để cài đặt các đối tượng trong game vào đúng vị trí bắt đầu để chơi game
void setconsole();			//là hàm để cài đặt cửa sổ console vừa đủ với bàn chơi game
void hidemousecursor();		//là hàm ẩn con trỏ chuột
void setframework();	
void start();
void rungame();

#endif