#include <iostream>
#include <graphics.h>
using namespace std;
//对点进行对称变换
void wholecolor(int xc, int yc, int x, int y, int color)
{
	putpixel(xc + x, yc + y, color);
	putpixel(xc + x, yc - y, color);
	putpixel(xc - x, yc + y, color);
	putpixel(xc - x, yc - y, color);
}
void ellipse(int xc, int yc, int a, int b, int color)
{
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
		else {

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

int main()
{
	initgraph(640, 480);             //启动图形库
	ellipse(200, 200, 160, 100, GREEN);   //画椭圆		中心(200,200)  长轴160  短轴100
	system("pause");
	closegraph();                   //关闭图形库
	return 0;
}