#ifndef __BALL_H__
#define __BALL_H__

#include"Pad.h"


#pragma once
class Ball
{
public:
	float x, y, xball, yball, vx, vy;	//x và y là tọa độ phía trước của bóng, xball và yball là tọa độ của bóng ở vị trí hiện tại, vx và vy là vận tốc của bóng theo hàng và theo cột
	Ball();
	~Ball();
	Ball(float, float);
	void drawball(); //tạo ra đối tượng bóng trên màn hình
};

#endif