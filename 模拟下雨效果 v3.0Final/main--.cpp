#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <iostream>
#include <windows.h>
using namespace std;

int maxstar=10;	// 雨滴总数
int first=280;
double v=0;			//下落速度
int water[610][4];
int h=0;

struct STAR
{
	double	x;
	int		y;
	double	step;
	//int		color;
};

STAR star[100]={0};

// 初始化
void InitStar(int i)
{
	
	star[i].y = rand()%first;
	star[i].x = rand() %800;
	star[i].step = (rand() % 3000) / 3000.0 + v*1.2;
	//star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);	// 速度越快，性质变化
	//star[i].color = RGB(star[i].color, star[i].color, star[i].color);
	
}
/********** 背景 **********/
void background()
{
	// 背景色
	setfillcolor(RGB(255, 255, 255));
	setlinecolor(BLACK);
	rectangle(0, 0, 800, 370);// 站牌
	// 边框
	setfillcolor(RGB(255, 255, 255));
	setlinecolor(RGB(0, 0, 0));
	rectangle(60, 150, 170, 350);
	// 内部
	setfillcolor(RGB(255, 255, 255));
	setlinecolor(RGB(0, 0, 0));
	rectangle(70, 160, 160, 340);
	// 底部
	setfillcolor(RGB(255, 255, 255));
	setlinecolor(RGB(0, 0, 0));
	rectangle(65, 350, 165, 370);
	// 等车棚
	// 顶部
	setfillcolor(RGB(255, 255, 255));
	setlinecolor(RGB(0, 0, 0));
	rectangle(220, 120, 750, 130);
	// 柱子
	setfillcolor(RGB(255, 255, 255));
	setlinecolor(RGB(0, 0, 0));
	rectangle(240, 130, 250, 370);
	rectangle(720, 130, 730, 370);
	// 公告
	setfillcolor(RGB(255, 255, 255));
	setlinecolor(RGB(0, 0, 0));
	rectangle(250, 160, 720, 310);

}
//水波
//DWORD WINAPI  print_wave(LPVOID pvParam)
void print_wave();
{
	int a=1;int b=1;
	int x1,y1,x2,y2;
	int i;				//设置循环计数变量i
	x1=(int)star[i].x-(b/2);
	y1=(int)star[i].y-(a/2);
	x2=(int)star[i].x+(b/2);
	y2=(int)star[i].y+(a/2);
	for (i=0;i<20;i++)//对水波的出现、消失进行循环
	{

		arc(x1,y1,x2,y2,60,60);
		Sleep(100);
		/*if(i%10==0)
		{clearellipse(x1-1,y1-1,x2+1,y2+1);//擦除水波
		}*/
		x1=x1-1;
		y1=y1-1;
		x2=x2+1;
		y2=y2+1;
	}
	arc(x1,y1,x2,y2,60,60);
	//Sleep(1000);
	//clearellipse(x1-1,y1-1,x2+1,y2+1);
}


// 移动雨点
void MoveStar(int i)
{
	// 擦掉原来的雨点
	if(star[i].y<380)
	clearrectangle((int)star[i].x, star[i].y,(int)star[i].x+1,star[i].y+4);
	line(0,370,800,370);
	HANDLE   hThread; 

	// 计算新位置
	star[i].y +=(int) star[i].step;
	//star[i].step+=0.1;       //加速下降
	srand(i*i);
	if (star[i].y > rand()%230+350)	
	{	
		//hThread =  CreateThread(NULL, 0, print_wave, NULL, 0, NULL);
		print_wave(/*(int)star[i].x,(int)star[i].y,3,2*/);
		InitStar(i);
	}
	// 画新雨点
	fillrectangle((int)star[i].x, star[i].y,(int)star[i].x+1,star[i].y+4);
}


// 主函数
void main()
{
	int read_in;
	while(1)
	{
		cout<<"请输入雨量大小(2-5): ";
		cin>>read_in;
		if (read_in>=2&&read_in<=5)
		{
			break;
		} 
	}
	//maxstar=read_in*80;
	//v=(read_in+3)*0.8;
	srand((unsigned)time(NULL));	// 随机种子
	initgraph(800, 600);		// 创建窗口
	setbkcolor(WHITE);
	line(0,370,800,370);	
	cleardevice();
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	// 初始化所有雨滴
	for(int i = 0; i < maxstar; i++)
	{
		InitStar(i);
		star[i].y = rand() % 800;
	}
	first = 30;
	// 雨滴循环下落，随机位置
	while(!kbhit())
	{
		for(int i = 0; i < maxstar; i++)
			MoveStar(i);
		background();
		Sleep(10);
		
	}
	closegraph();					// 关闭窗口
}
