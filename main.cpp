#include<stdio.h>
#include<graphics.h>	
#include"tools.h"

#define WIN_WIDTH 900
#define WIN_HEIGHT 600

enum
{
	Peashooter,
	Sunflower,
	plantCount
};

IMAGE imgBg;	
IMAGE imgBar;	//植物卡牌栏
IMAGE imgCards[plantCount];

void gameInit()
{ 
	loadimage(&imgBg, "res/bg.jpg");
	loadimage(&imgBar, "res/bar5.png");	//初始化卡牌栏

	//初始化植物卡牌
	char name[64];
	for (int i = 0; i < plantCount; i++)
	{
		//生成植物卡牌的文件名
		sprintf_s(name, sizeof(name), "res/Cards/card_%d.png", i + 1);	//注意这里使用的是vs编译器自带的sprintf_s
		loadimage(&imgCards[i], name);
	}
	
	initgraph(WIN_WIDTH, WIN_HEIGHT);

}

void updateWindow()
{
	putimage(0, 0, &imgBg);
	//putimage(250, 0, &imgBar);
	putimagePNG(250, 0, &imgBar);	//渲染卡牌栏

	//渲染卡牌
	for (int i = 0; i < plantCount; i++)
	{
		int x = 338 + i * 65;
		int y = 6;
		putimagePNG(x, y, &imgCards[i]);
	}

}

int main(void)
{
	gameInit();
	updateWindow();

	system("pause");
	return 0;
}