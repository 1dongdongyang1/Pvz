#include<stdio.h>
#include<graphics.h>	//EasyX图形库的头文件，需要安装EaxyX图形库

#define WIN_WIDTH 900
#define WIN_HEIGHT 600

IMAGE imgBg;	//表示背景图片

void gameInit()
{
	//加载背景
	//	1.直接打印，类似于直接用printf打印出来	缺点：比较慢
	//	2.先放到内存变量里去，再从变量里显示出来，就会比第一种快，这里采用的就是这种方式
	//把字符集改成“多字节字符集” 
	loadimage(&imgBg, "res/Map/map0.jpg");

	//创建游戏的图形窗口
	initgraph(WIN_WIDTH, WIN_HEIGHT);

}

void updateWindow()
{
	putimage(0, 0, &imgBg);
}

int main(void)
{
	gameInit();
	updateWindow();

	system("pause");
	return 0;
}