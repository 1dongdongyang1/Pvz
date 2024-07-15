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
IMAGE imgBar;	//ֲ�￨����
IMAGE imgCards[plantCount];

void gameInit()
{ 
	loadimage(&imgBg, "res/bg.jpg");
	loadimage(&imgBar, "res/bar5.png");	//��ʼ��������

	//��ʼ��ֲ�￨��
	char name[64];
	for (int i = 0; i < plantCount; i++)
	{
		//����ֲ�￨�Ƶ��ļ���
		sprintf_s(name, sizeof(name), "res/Cards/card_%d.png", i + 1);	//ע������ʹ�õ���vs�������Դ���sprintf_s
		loadimage(&imgCards[i], name);
	}
	
	initgraph(WIN_WIDTH, WIN_HEIGHT);

}

void updateWindow()
{
	putimage(0, 0, &imgBg);
	//putimage(250, 0, &imgBar);
	putimagePNG(250, 0, &imgBar);	//��Ⱦ������

	//��Ⱦ����
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