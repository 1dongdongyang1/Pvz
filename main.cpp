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

int curX, curY;	//��ǰѡ�е�ֲ����ƶ������е�λ��
int curPlant;	//0��û��ѡ��  1��ѡ���һ��ֲ��

bool fileExist(const char* name)	//�ж��ļ��Ƿ����
{
	FILE* fp = fopen(name,"r");		//���ļ�Ϊ���򷵻�NULL
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

		//����ֲ��ÿ֡��ͼƬ
		for (int j = 0; j < 20; j++)
		{
			sprintf_s(name, sizeof(name), "res/zhiwu/%d/%d.png", i, j + 1);
			//���ж�����ļ��Ƿ����
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
	BeginBatchDraw();	//��ʼ����
	putimage(0, 0, &imgBg);
	putimagePNG(250, 0, &imgBar);
	for (int i = 0; i < plantCount; i++)
	{
		int x = 338 + i * 65;
		int y = 6;
		putimagePNG(x, y, &imgCards[i]);
	}

	//��Ⱦ�϶������е�ֲ��
	if (curPlant)
	{
		IMAGE* img = imgPlant[curPlant - 1][0];
		putimagePNG(curX - img->getwidth() / 2, curY - img->getheight() / 2, img);	//�����õ���C++����
	}

	EndBatchDraw();	//����˫����
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