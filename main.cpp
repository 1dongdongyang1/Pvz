#include<stdio.h>
#include<graphics.h>	//EasyXͼ�ο��ͷ�ļ�����Ҫ��װEaxyXͼ�ο�

#define WIN_WIDTH 900
#define WIN_HEIGHT 600

IMAGE imgBg;	//��ʾ����ͼƬ

void gameInit()
{
	//���ر���
	//	1.ֱ�Ӵ�ӡ��������ֱ����printf��ӡ����	ȱ�㣺�Ƚ���
	//	2.�ȷŵ��ڴ������ȥ���ٴӱ�������ʾ�������ͻ�ȵ�һ�ֿ죬������õľ������ַ�ʽ
	//���ַ����ĳɡ����ֽ��ַ����� 
	loadimage(&imgBg, "res/Map/map0.jpg");

	//������Ϸ��ͼ�δ���
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