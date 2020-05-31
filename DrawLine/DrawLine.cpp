/*
	ʹ��EasyXͼ�ο��������ͼ����
	ʵ���е㻭�ߡ�bresenham���ߡ���Բ�Ļ������ԳƵĻ���
	Ĭ������ԭ�������Ϸ�
	����������һ������ϵ��ԭ������Ļ����
*/
#include <iostream>
#include <graphics.h>
#include<conio.h>
using namespace std;

void coordinatetransform(int &x, int &y)			//����ϵת������������ϵת����ԭʼ����ϵ
{
	x = x + 640;
	y = 480 - y;
}

//�Ե���жԳƱ任
void wholecolor(int xc, int yc, int x, int y, int color)
{
	putpixel(xc + x, yc + y, color);
	putpixel(xc + x, yc - y, color);
	putpixel(xc - x, yc + y, color);
	putpixel(xc - x, yc - y, color);
}
//����Բ���㷨
void DrawEllipse(int xc, int yc, int a, int b, int color)
{
	coordinatetransform(xc, yc);
	int x = 0, y = b;
	int aa = a*a, bb = b*b;
	int d = (int)(bb + aa*(-b + 0.25) + 0.5);    //��ʼֵ
	wholecolor(xc, yc, x, y, color);
	while (bb*x < aa*y)                     //�ķ�֮һԲ���ϰ벿��
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
	while (y > 0) {                                //�ķ�֮һԲ���°벿��
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
//�е㻭�߷�
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
	if (-a <= b)		// б�ʾ���ֵ <= 1
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
	else				// б�ʾ���ֵ > 1
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

//Bresenham�����㷨
void Bresenham(int x1, int y1, int x2, int y2,int color)
{
	coordinatetransform(x1, y1);
	coordinatetransform(x2, y2);
	int x, y, dx, dy, p1, i;
	dx = x2 - x1;
	dy = y2 - y1;
	if (abs(dx) > abs(dy)) //б�ʾ���ֵ�ڣ�0,1������������Ϊx��
	{
		if (x1 < x2)      //Ĭ�ϻ���������һ�
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
		p1 = 2 * abs(dy) - abs(dx);          //�����ʼpi��ֵ
		for (i = min(x1, x2); i < max(x1, x2); i++)
		{
			x = x + 1;
			if (p1 >= 0)
			{
				if (dx*dy >= 0)
					y = y + 1;
				else
					y = y - 1;                        //��Pi>=0,y(i+1)=y(i)��1
				p1 = p1 + 2 * (abs(dy) - abs(dx));    //����pi
			}
			else
			{
				y = y;                                //��Pi<0,y(i+1)=y(i)
				p1 = p1 + 2 * abs(dy);                //����pi
			}
			putpixel(x, y, color);
		}
	}
	else
	{
		if (y1 < y2)
		{                     //��������Ϊy�ᣬĬ�ϻ���������ϻ�          
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
				if (dx*dy >= 0)                             //�ж�x���������ӻ��Ǽ��٣��ܹؼ�
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
	�˺���������ԳƵ�
	(x1,y1),(x2,y2)	ȷ���Գ���
	(px,py)			Ϊ����ĶԳƵ�
	(* symmetricX,* symmetricY)		Ϊ(px,py)����ֱ�ߵĶԳƵ�
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

void init()					//��ʼ��ͼ�ν���
{
	initgraph(1280, 960);       //��ʼ����ͼ����
	line(0, 480, 1280, 480);		//��һ��ˮƽֱ�߳䵱X��
	line(1270, 470, 1280, 480);
	line(1270, 490, 1280, 480);
	line(640, 0, 640, 960);		//��һ����ֱֱ�߳䵱Y��
	line(630, 10, 640, 0);
	line(650, 10, 640, 0);
	ellipse(650, 490, 660, 505);	//������Բ�䵱����ԭ��
}

int main()
{
	init();			
	int xa, ya, xb, yb;
	Midline(-100, -200, 300, 300,RED);				//�е㻭�߷����ߣ���Ϊ�Գ���
	Bresenham(30,70,-200,200,GREEN);			//Bresenham���߷����ߣ���Ϊ�Գ�ֱ��

	SymmetricPoint(-100, -200, 300, 300, 30, 70, &xa, &ya);
	SymmetricPoint(-100, -200, 300, 300, -200, 200, &xb, &yb);
	Bresenham(xa, ya,xb, yb, GREEN);			//Bresenham���߷����ߣ���Ϊ�Գƺ�õ���ֱ��

	DrawEllipse(200, 200, 160, 100, YELLOW);			//����Բ		����(200,200)  ����160  ����100
	system("pause");
	closegraph();             //�ر�ͼ��
	return 0;
}