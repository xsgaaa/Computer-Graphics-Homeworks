#include <iostream>
#include <graphics.h>
using namespace std;
//�Ե���жԳƱ任
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
	int d = (int)(bb + aa*(-b + 0.25) + 0.5);    //��ʼֵ
	wholecolor(xc, yc, x, y, color);
	while (bb*x < aa*y)                     //�ķ�֮һԲ���ϰ벿��
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

int main()
{
	initgraph(640, 480);             //����ͼ�ο�
	ellipse(200, 200, 160, 100, GREEN);   //����Բ		����(200,200)  ����160  ����100
	system("pause");
	closegraph();                   //�ر�ͼ�ο�
	return 0;
}