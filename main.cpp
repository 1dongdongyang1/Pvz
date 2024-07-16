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
IMAGE imgBar;
IMAGE imgCards[plantCount];
IMAGE* imgPlant[plantCount][20];

int curX, curY;	//当前选中的植物，在移动过程中的位置
int curPlant;	//0：没有选中  1：选择第一种植物

bool fileExist(const char* name)	//判断文件是否存在
{
	FILE* fp = fopen(name,"r");		//若文件为空则返回NULL
	if (fp)
	{
		fclose(fp);
	}
	return fp != NULL;
}

void gameInit()
{ 
	loadimage(&imgBg, "res/bg.jpg");
	loadimage(&imgBar, "res/bar5.png");

	memset(imgPlant, 0, sizeof(imgPlant));

	char name[64];
	for (int i = 0; i < plantCount; i++)
	{
		sprintf_s(name, sizeof(name), "res/Cards/card_%d.png", i + 1);
		loadimage(&imgCards[i], name);

		//生成植物每帧的图片
		for (int j = 0; j < 20; j++)
		{
			sprintf_s(name, sizeof(name), "res/zhiwu/%d/%d.png", i, j + 1);
			//先判断这个文件是否存在
			if (fileExist(name))
			{
				imgPlant[i][j] = new IMAGE;	//C++
				loadimage(imgPlant[i][j], name);
			}
			else
				break;
		}
	}

	curPlant = 0;
	initgraph(WIN_WIDTH, WIN_HEIGHT);
}

void updateWindow()
{
	BeginBatchDraw();	//开始缓冲
	putimage(0, 0, &imgBg);
	putimagePNG(250, 0, &imgBar);
	for (int i = 0; i < plantCount; i++)
	{
		int x = 338 + i * 65;
		int y = 6;
		putimagePNG(x, y, &imgCards[i]);
	}

	//渲染拖动过程中的植物
	if (curPlant)
	{
		IMAGE* img = imgPlant[curPlant - 1][0];
		putimagePNG(curX - img->getwidth() / 2, curY - img->getheight() / 2, img);	//这里用到了C++的类
	}

	EndBatchDraw();	//结束双缓冲
}

void userClick()
{
	ExMessage msg;
	static int status = 0;
	if (peekmessage(&msg))
	{
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (msg.x > 338 && msg.x < 338 + 65 * plantCount && msg.y < 96)
			{
				int index = (msg.x - 338) / 65;
				status = 1;
				curPlant = index + 1;
			}
		}
		else if (msg.message == WM_MOUSEMOVE && status == 1)
		{
			curX = msg.x;
			curY = msg.y; 
		}
		else if (msg.message == WM_LBUTTONUP)
		{

		}
	}
}

int main(void)
{
	gameInit();
	while (1)
	{
		userClick();
		updateWindow();

	}
	return 0;
}