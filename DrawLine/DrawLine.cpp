/*
	使用EasyX图形库来构造绘图环境
	实现中点画线、bresenham画线、椭圆的画法、对称的画法
	默认坐标原点在左上方
	这里新设置一个坐标系，原点在屏幕中心
*/
#include <iostream>
#include <graphics.h>
#include<conio.h>
using namespace std;

void coordinatetransform(int &x, int &y)			//坐标系转换，将新坐标系转换到原始坐标系
{
	x = x + 640;
	y = 480 - y;
}

//对点进行对称变换
void wholecolor(int xc, int yc, int x, int y, int color)
{
	putpixel(xc + x, yc + y, color);
	putpixel(xc + x, yc - y, color);
	putpixel(xc - x, yc + y, color);
	putpixel(xc - x, yc - y, color);
}
//画椭圆的算法
void DrawEllipse(int xc, int yc, int a, int b, int color)
{
	coordinatetransform(xc, yc);
	int x = 0, y = b;
	int aa = a*a, bb = b*b;
	int d = (int)(bb + aa*(-b + 0.25) + 0.5);    //初始值
	wholecolor(xc, yc, x, y, color);
	while (bb*x < aa*y)                     //四分之一圆的上半部分
	{
		if (d < 0) {
			d += bb*(2 * x + 3);
			x++;
		}
		else{
			d += bb*(2 * x + 3) + aa*(-2 * y + 2); y--; x++;
		}
		wholecolor(xc, yc, x, y, color);
	}
	d = (int)(bb*(x + 0.5)*(x + 0.5) + aa*(y - 1)*(y - 1) - aa*bb + 0.5);
	while (y > 0) {                                //四分之一圆的下半部分
		if (d > 0) {
			d += aa*(-2 * y + 3);
			y--;
		}
		else {
			d += bb*(2 * x + 2) + aa*(-2 * y + 3);
			x++; y--;
		}
		wholecolor(xc, yc, x, y, color);
	}
}
//中点画线法
void Midline(int x1, int y1, int x2, int y2, int color)
{
	coordinatetransform(x1, y1);
	coordinatetransform(x2, y2);
	int x = x1, y = y1;
	int a = y1 - y2, b = x2 - x1;
	int cx = (b >= 0 ? 1 : (b = -b, -1));
	int cy = (a <= 0 ? 1 : (a = -a, -1));
	putpixel(x, y, color);
	int d, d1, d2;
	if (-a <= b)		// 斜率绝对值 <= 1
	{
		d = 2 * a + b;
		d1 = 2 * a;
		d2 = 2 * (a + b);
		while (x != x2)
		{
			if (d < 0)
				y += cy, d += d2;
			else
				d += d1;
			x += cx;
			putpixel(x, y, color);
		}
	}
	else				// 斜率绝对值 > 1
	{
		d = 2 * b + a;
		d1 = 2 * b;
		d2 = 2 * (a + b);
		while (y != y2)
		{
			if (d < 0)
				d += d1;
			else
				x += cx, d += d2;
			y += cy;
			putpixel(x, y, color);
		}
	}
}

//Bresenham画线算法
void Bresenham(int x1, int y1, int x2, int y2,int color)
{
	coordinatetransform(x1, y1);
	coordinatetransform(x2, y2);
	int x, y, dx, dy, p1, i;
	dx = x2 - x1;
	dy = y2 - y1;
	if (abs(dx) > abs(dy)) //斜率绝对值在（0,1），步进方向为x轴
	{
		if (x1 < x2)      //默认画点从左往右画
		{
			x = x1;
			y = y1;
		}
		else
		{
			x = x2;
			y = y2;
		}
		putpixel(x, y, color);
		p1 = 2 * abs(dy) - abs(dx);          //计算初始pi的值
		for (i = min(x1, x2); i < max(x1, x2); i++)
		{
			x = x + 1;
			if (p1 >= 0)
			{
				if (dx*dy >= 0)
					y = y + 1;
				else
					y = y - 1;                        //若Pi>=0,y(i+1)=y(i)±1
				p1 = p1 + 2 * (abs(dy) - abs(dx));    //更新pi
			}
			else
			{
				y = y;                                //若Pi<0,y(i+1)=y(i)
				p1 = p1 + 2 * abs(dy);                //更新pi
			}
			putpixel(x, y, color);
		}
	}
	else
	{
		if (y1 < y2)
		{                     //步进方向为y轴，默认画点从下往上画          
			x = x1;
			y = y1;
		}
		else
		{
			x = x2;
			y = y2;
		}
		putpixel(x, y, color);
		p1 = 2 * abs(dx) - abs(dy);
		for (i = min(y1, y2); i < max(y1, y2); i++)
		{
			y = y + 1;
			if (p1 >= 0)
			{
				if (dx*dy >= 0)                             //判断x方向是增加还是减少，很关键
					x = x + 1;
				else
					x = x - 1;
				p1 = p1 + 2 * (abs(dx) - abs(dy));
			}
			else
			{
				x = x;
				p1 = p1 + 2 * abs(dx);
			}
			putpixel(x, y, color);
		}
	}
}

/*
	此函数用于求对称点
	(x1,y1),(x2,y2)	确定对称轴
	(px,py)			为待求的对称点
	(* symmetricX,* symmetricY)		为(px,py)关于直线的对称点
*/
void SymmetricPoint(int x1, int y1, int x2, int y2, int px, int py, int* symmetricX, int* symmetricY)
{
	float A = (y1 - y2);
	float B = (x2 - x1);
	float C = x1*y2 - x2*y1;
	float D = (A*px + B*py + C) / (A*A + B*B);
	int x = int(double(px) - 2.0*A*D);
	int y = int(double(py) - 2.0*B*D);
	*symmetricX = x;
	*symmetricY = y;
}

void init()					//初始化图形界面
{
	initgraph(1280, 960);       //初始化绘图界面
	line(0, 480, 1280, 480);		//画一条水平直线充当X轴
	line(1270, 470, 1280, 480);
	line(1270, 490, 1280, 480);
	line(640, 0, 640, 960);		//画一条垂直直线充当Y轴
	line(630, 10, 640, 0);
	line(650, 10, 640, 0);
	ellipse(650, 490, 660, 505);	//画个椭圆充当坐标原点
}

int main()
{
	init();			
	int xa, ya, xb, yb;
	Midline(-100, -200, 300, 300,RED);				//中点画线法画线，作为对称轴
	Bresenham(30,70,-200,200,GREEN);			//Bresenham画线法画线，作为对称直线

	SymmetricPoint(-100, -200, 300, 300, 30, 70, &xa, &ya);
	SymmetricPoint(-100, -200, 300, 300, -200, 200, &xb, &yb);
	Bresenham(xa, ya,xb, yb, GREEN);			//Bresenham画线法画线，作为对称后得到的直线

	DrawEllipse(200, 200, 160, 100, YELLOW);			//画椭圆		中心(200,200)  长轴160  短轴100
	system("pause");
	closegraph();             //关闭图形
	return 0;
}