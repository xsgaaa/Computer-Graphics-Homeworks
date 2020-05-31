/*
	本程序借助EasyX图形库绘制B样条曲线
*/#include <graphics.h> 
#include<conio.h> 
#include<stdio.h>
#include<iostream>

using namespace std;

void b_spline(int color, float p[4][2]) /*画b样条曲线函数*/ 
{
	float t, t2, t3, xt, yt;
	int rate = 100, x, y;
	setcolor(color);
	for (t = 0; t <= 1; t += 1.0 / rate)
	{
		t2 = t*t;
		t3 = t*t*t;
		xt = ((1 - 3 * t + 3 * t2 - t3)*p[0][0] + (4 - 6 * t2 + 3 * t3)*p[1][0] + (1 + 3 * t + 3 * t2 - 3 * t3)*p[2][0] + t3*p[3][0]) / 6;
		yt = ((1 - 3 * t + 3 * t2 - t3)*p[0][1] + (4 - 6 * t2 + 3 * t3)*p[1][1] + (1 + 3 * t + 3 * t2 - 3 * t3)*p[2][1] + t3*p[3][1]) / 6;
		x = (int)(xt);
		y = (int)(yt);
		if (t == 0) moveto(x, y);
		lineto(x, y);
	}
}

void main()
{
	int i;
	float p[4][2];
	p[0][0]=120;			//第一个控制点
	p[0][1]=240;
	p[1][0]=300;			//第二个控制点
	p[1][1]=100;
	p[2][0]=400;			//第三个控制点
	p[2][1]=100;
	p[3][0]=500;			//第四个控制点
	p[3][1]=250;
	initgraph(640,480);
	cleardevice();
	setcolor(GREEN);
	moveto(p[0][0], p[0][1]);
	for (i = 1; i <=3; i++)
		lineto(p[i][0], p[i][1]);				//绘制控制点的连线（绿色）
	b_spline(LIGHTRED, p);			//绘制B样条曲线（红色）
	system("pause");
}
