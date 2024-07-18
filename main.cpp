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

int curX, curY;	
int curPlant;	

typedef struct Plant
{
	int type;			//0:没有植物	1：第一种植物 
	int frameIndex;		//序列帧的序号
}Plant;

Plant map[3][9];	//植物种植的二维数组

bool fileExist(const char* name)
{
	FILE* fp = fopen(name,"r");
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
	memset(map, 0, sizeof(map));	//初始化map为0
	char name[64];
	for (int i = 0; i < plantCount; i++)
	{
		sprintf_s(name, sizeof(name), "res/Cards/card_%d.png", i + 1);
		loadimage(&imgCards[i], name);
		for (int j = 0; j < 20; j++)
		{
			sprintf_s(name, sizeof(name), "res/zhiwu/%d/%d.png", i, j + 1);
			if (fileExist(name))
			{
				imgPlant[i][j] = new IMAGE;
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
	BeginBatchDraw();
	putimage(0, 0, &imgBg);
	putimagePNG(250, 0, &imgBar);
	for (int i = 0; i < plantCount; i++)
	{
		int x = 338 + i * 65;
		int y = 6;
		putimagePNG(x, y, &imgCards[i]);
	}
	if (curPlant)
	{
		IMAGE* img = imgPlant[curPlant - 1][0];
		putimagePNG(curX - img->getwidth() / 2, curY - img->getheight() / 2, img);
	}
	for (int i = 0; i < 3;i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (map[i][j].type > 0)
			{
				int x = 256 + j * 81;
				int y = 194 + i * 102;
				int PlantType = map[i][j].type - 1;
				int index = map[i][j].frameIndex;
				putimagePNG(x, y, imgPlant[PlantType][index]);
			}
		}
	}
	EndBatchDraw();
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
			if (msg.x > 256 && msg.y < 489 && msg.y>179)
			{
				int row = (msg.y - 179) / 102;
				int col = (msg.x - 256) / 81;
				if (map[row][col].type == 0)
				{
					map[row][col].type = curPlant;
					map[row][col].frameIndex = 0;
				}
			}
			curPlant = 0;
			status = 0;
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