/*************/
/* 模拟下雨效果*/
/*************/

/*********头文件*********/
#include <graphics.h>
#include <ctime>
#include <conio.h>
#include <iostream>
#include <cmath>
#include "mmsystem.h"				//导入声音头文件 
#pragma comment(lib,"winmm.lib")	//导入声音头文件库

#define PI 3.1415926	//π值

using namespace std;
/*********全局变量*********/
int maxrain;		// 雨点总数
int first = 370;	//雨点初始随机位置相关参量
double v;			//雨点初始下落随机速度相关参量

/*********雨点结构体*********/
struct RAIN       
{
	int	x;			//雨点x坐标
	int		y;			//雨点y坐标	
	double	step;		//雨点速度
};
RAIN rain[600];   //初始化雨点结构体数组


/*********函数声明*********/
DWORD WINAPI MyThread3(PVOID pvParam);
DWORD WINAPI MyThread2(PVOID pvParam);
DWORD WINAPI MyThread1(PVOID pvParam);
void InitRain(int i);
void print_lightning();
void background();
void print_wave(int i);
void MoveRain(int i);
void run_few();
void countdown();
void end_print();
void init();
void running();
void sunup();
void sunrotate();

/*********主函数*********/
void main()
{
	init();							//初始化
	run_few();						//模拟少量雨点效果
	countdown();					//倒计时显示-5s
	print_lightning();				//显示闪电效果
	running();						//模拟下雨效果
	end_print();					//结束下雨效果
	closegraph();					// 关闭窗口
}

/*********线程-背景音乐*********/
DWORD WINAPI MyThread3(PVOID pvParam)
{
	PlaySound(TEXT("F:\\my document\\SmallTerm\\28\\模拟下雨效果 v3.0Final\\Rainymood.wav"), NULL, SND_LOOP | SND_ASYNC);
	return 0;
}

/*********线程-太阳旋转*********/
DWORD WINAPI MyThread1(PVOID pvParam)
{
	while (true)
	{
		sunrotate();
	}
	return 0;
}

/*********线程-鸟鸣音乐*********/
DWORD WINAPI MyThread2(PVOID pvParam)
{
	PlaySound(TEXT("F:\\my document\\SmallTerm\\28\\模拟下雨效果 v3.0Final\\鸟鸣声.wav"), NULL, SND_LOOP | SND_ASYNC);
	return 0;
}

/*********雨点初始化*********/
void InitRain(int i)
{

	rain[i].y = rand() % first;							//随机雨点出现的y坐标--控制在0~30
	rain[i].x = rand() % 800;							//随即雨点出现的x坐标
	rain[i].step = (rand() % 3000) / 3000.0 + v*1.2;	//随机雨点初始速度
}

/*********闪电*********/
void print_lightning()
{
	Sleep(50);
	setfillcolor(WHITE);
	setbkcolor(BLACK);
	cleardevice();
	int i;//设置循环计数变量i
	for (i = 0; i < 3; i++)
	{
		/*第一轮闪电*/
		//绘制闪电1
		POINT pts1[] = { { 200, 30 }, { 180, 90 }, { 200, 90 }, { 180, 150 }, { 210, 80 }, { 190, 80 } };
		solidpolygon(pts1, 6);

		//绘制闪电2
		POINT pts2[] = { { 400, 120 }, { 380, 180 }, { 400, 180 }, { 380, 240 }, { 410, 170 }, { 390, 170 } };
		solidpolygon(pts2, 6);

		//绘制闪电3
		POINT pts3[] = { { 600, 30 }, { 580, 90 }, { 600, 90 }, { 580, 150 }, { 610, 80 }, { 590, 80 } };
		solidpolygon(pts3, 6);

		Sleep(200);
		clearrectangle(180, 30, 210, 150);//擦除闪电
		clearrectangle(380, 120, 410, 240);
		clearrectangle(580, 30, 610, 150);
		Sleep(200);//产生闪烁效果
	}
	for (i = 0; i < 3; i++)
	{
		/*第二轮闪电*/

		//绘制闪电4
		POINT pts4[] = { { 200, 120 }, { 180, 180 }, { 200, 180 }, { 180, 240 }, { 210, 170 }, { 190, 170 } };
		solidpolygon(pts4, 6);

		//绘制闪电5
		POINT pts5[] = { { 400, 30 }, { 380, 90 }, { 400, 90 }, { 380, 150 }, { 410, 80 }, { 390, 80 } };
		solidpolygon(pts5, 6);

		//绘制闪电6
		POINT pts6[] = { { 600, 120 }, { 580, 180 }, { 600, 180 }, { 580, 240 }, { 610, 170 }, { 590, 170 } };
		solidpolygon(pts6, 6);

		Sleep(200);
		clearrectangle(180, 120, 210, 240);//擦除闪电
		clearrectangle(380, 30, 410, 150);
		clearrectangle(580, 120, 610, 240);
		Sleep(200);//产生闪烁效果
	}
	setbkcolor(WHITE);
	cleardevice();
	background();
}

/*********背景绘制*********/
void background()
{
	// 背景色
	setlinecolor(BLACK);
	// 站牌
	rectangle(0, 0, 800, 370);
	// 边框
	rectangle(60, 130, 170, 330);
	// 内部
	rectangle(70, 140, 160, 320);
	// 底部
	rectangle(65, 330, 165, 350);
	// 等车棚
	// 顶部
	rectangle(220, 100, 750, 110);
	// 柱子
	rectangle(240, 110, 250, 350);
	rectangle(720, 110, 730, 350);
	// 公告
	rectangle(250, 140, 720, 290);
	//路边
	rectangle(0, 350, 200, 370);
	rectangle(200, 350, 400, 370);
	rectangle(400, 350, 600, 370);
	rectangle(600, 350, 800, 370);
	//马路线
	rectangle(100, 550, 300, 570);
	rectangle(500, 550, 700, 570);
	settextstyle(35, 24, _T("楷体"));
	settextcolor(BLACK);
	TCHAR s[] = _T("模");
	outtextxy(90, 150, s);
	TCHAR ss[] = _T("拟");
	outtextxy(90, 190, ss);
	TCHAR sss[] = _T("下");
	outtextxy(90, 230, sss);
	TCHAR ssss[] = _T("雨");
	outtextxy(90, 270, ssss);
}

/*********水波的产生及消失*********/
void print_wave(int i)
{
	int a = 10; int b = 30;
	int x1, y1, x2, y2;
	x1 = (int)rain[i].x - (b / 2);
	y1 = (int)rain[i].y - (a / 2);
	x2 = (int)rain[i].x + (b / 2);
	y2 = (int)rain[i].y + (a / 2);
	for (int i = 0; i < 10; i++)			//对水波的出现、消失进行循环
	{

		arc(x1 - 1, y1 - 1, x2 + 1, y2 + 1, 60, 60);
		clearellipse(x1 - 1, y1 - 1, x2 + 1, y2 + 1);//擦除水波
		x1 = x1 - 1;
		y1 = y1 - 1;
		x2 = x2 + 1;
		y2 = y2 + 1;
	}
	clearellipse(x1 - 1, y1 - 1, x2 + 1, y2 + 1);
}

/*********移动雨点（更新雨点位置）*********/
void MoveRain(int i)
{
	clearrectangle((int)rain[i].x, rain[i].y, (int)rain[i].x + 1, rain[i].y + 4);	// 擦掉原来的雨点
	line(0, 370, 800, 370);
	rain[i].y += (int)rain[i].step;     //计算雨点新位置
	rain[i].step += 0.1;				//雨点加速度 0.1
	srand(i*i*(unsigned)time(NULL));				//重设随机种子
	if (rain[i].y > rand() % 230 + 380)			//在落地点绘制水波并重新初始化雨点
	{
		print_wave(i);
		InitRain(i);
	}
	// 画新雨点
	else {
		rectangle((int)rain[i].x, rain[i].y, (int)rain[i].x + 1, rain[i].y + 4);
	}
}

/*********对少量雨点下落的模拟*********/
void run_few()
{
	//一滴雨
	RAIN one;
	one.x = 400;
	one.y = 0;
	one.step = 0.005;
	//雨落
	rectangle((int)one.x, one.y, (int)one.x + 1, one.y + 4);
	while (one.y < 500)
	{
		clearrectangle((int)one.x, one.y, (int)one.x + 1, one.y + 4);
		line(0, 370, 800, 370);
		background();
		TCHAR s[] = _T("一滴雨效果");
		outtextxy(360, 180, s);
		one.y += (int)one.step;
		one.step += 0.04;
		rectangle((int)one.x, one.y, (int)one.x + 1, one.y + 4);
		Sleep(10);
	}
	rectangle((int)one.x, one.y, (int)one.x + 1, one.y + 4);
	//水波
	int a = 2; int b = 10;
	int x1, y1, x2, y2;
	x1 = (int)one.x - (b / 2);
	y1 = (int)one.y - (a / 2);
	x2 = (int)one.x + (b / 2);
	y2 = (int)one.y + (a / 2);
	for (int i = 0; i < 20; i++)			//对水波的出现、消失进行循环
	{

		arc(x1 - 1, y1 - 1, x2 + 1, y2 + 1, 60, 60);
		Sleep(50);
		clearellipse(x1 - 1, y1 - 1, x2 + 1, y2 + 1);//擦除水波
		x1 = x1 - 1;
		y1 = y1 - 1;
		x2 = x2 + 1;
		y2 = y2 + 1;
	}
	Sleep(50);
	clearellipse(x1 - 1, y1 - 1, x2 + 1, y2 + 1);
	clearrectangle(260, 150, 710, 280);
	//两滴雨
	RAIN two1, two2;
	two1.x = 200;
	two2.x = 600;
	two1.y = 0;
	two2.y = 0;
	two1.step = 0.005;
	two2.step = 0.005;
	//雨落
	rectangle((int)two1.x, two1.y, (int)two1.x + 1, two1.y + 4);
	rectangle((int)two2.x, two2.y, (int)two2.x + 1, two2.y + 4);
	while (two1.y < 500)
	{
		clearrectangle((int)two1.x, two1.y, (int)two1.x + 1, two1.y + 4);
		clearrectangle((int)two2.x, two2.y, (int)two2.x + 1, two2.y + 4);
		line(0, 370, 800, 370);
		background();
		TCHAR s[] = _T("两滴雨效果");
		outtextxy(360, 180, s);
		two1.y += (int)two1.step;
		two2.y += (int)two2.step;
		two1.step += 0.04;
		two2.step += 0.04;
		rectangle((int)two1.x, two1.y, (int)two1.x + 1, two1.y + 4);
		rectangle((int)two2.x, two2.y, (int)two2.x + 1, two2.y + 4);
		Sleep(10);
	}
	rectangle((int)two1.x, two1.y, (int)two1.x + 1, two1.y + 4);
	rectangle((int)two2.x, two2.y, (int)two2.x + 1, two2.y + 4);
	//水波
	x1 = (int)two1.x - (b / 2);
	y1 = (int)two1.y - (a / 2);
	x2 = (int)two1.x + (b / 2);
	y2 = (int)two1.y + (a / 2);
	for (int i = 0; i < 20; i++)			//对水波的出现、消失进行循环
	{

		arc(x1 - 1, y1 - 1, x2 + 1, y2 + 1, 60, 60);
		arc(x1 + 400 - 1, y1 - 1, x2 + 400 + 1, y2 + 1, 60, 60);
		Sleep(50);
		clearellipse(x1 - 1, y1 - 1, x2 + 1, y2 + 1);//擦除水波
		clearellipse(x1 + 400 - 1, y1 - 1, x2 + 400 + 1, y2 + 1);
		x1 = x1 - 1;
		y1 = y1 - 1;
		x2 = x2 + 1;
		y2 = y2 + 1;
	}
	Sleep(50);
	clearellipse(x1 - 1, y1 - 1, x2 + 1, y2 + 1);
	clearellipse(x1 + 400 - 1, y1 - 1, x2 + 400 + 1, y2 + 1);
	clearrectangle(260, 150, 710, 280);
	Sleep(100);
}

/*********开始-倒计时*********/
void countdown()
{
	settextstyle(35, 24, _T("楷体"));
	TCHAR s[] = _T("大雨即将来临");
	outtextxy(320, 151, s);
	settextstyle(60, 37, _T("楷体"));
	for (int f = 5; f >= 0; f--)
	{
		_stprintf(s, _T("%d"), f);
		outtextxy(455, 200, s);
		Sleep(1200);
		clearrectangle(450, 190, 520, 250);
	}
	clearrectangle(310, 150, 700, 200);
	HANDLE hThread3 = CreateThread(NULL, 0, MyThread3, NULL, 0, NULL);
	Sleep(20);
}

/*********结束-倒计时*********/
void end_print()
{
	cleardevice();								//清屏
	PlaySound(NULL, NULL, SND_PURGE);			//停止音乐播放
	background();								//重新绘制背景
	TCHAR ss[] = _T("天晴了");
	outtextxy(295, 180, ss);
	sunup();									//日出
	HANDLE hThread1 = CreateThread(NULL, 0, MyThread1, NULL, 0, NULL);	//创建太阳发光线程
	Sleep(3000);
	TCHAR s[] = _T("窗口将在5秒后关闭");
	outtextxy(285, 180, s);
	Sleep(1200);
	for (int f = 4; f >= 0; f--)
	{
		_stprintf(s, _T("%d"), f);		//向字符串写入设置数据格式
		outtextxy(475, 180, s);
		Sleep(990);
	}
}

/*********初始化*********/
void init()
{
	char read_in[100];
	while (1)							//雨量大小选择
	{
		cout << "请输入雨量大小(2-5): ";
		cin >> read_in;
		if (read_in[0] >= '2' && read_in[0] <= '5'&&read_in[1] == '\0')
		{
			break;
		}
	}
	maxrain = (read_in[0] - '0') * 80;			//对雨点数量初始化
	v = ((read_in[0] - '0') + 3)*0.8;			//对雨点随机速度参量初始化
	srand((unsigned)time(NULL));	// 随机种子
	initgraph(800, 600);		// 创建窗口
	setbkcolor(WHITE);				//设置窗口背景为白色
	cleardevice();
	setfillcolor(BLACK);			//设置雨点填充颜色为黑色
	setlinecolor(BLACK);			//设置线条颜色为黑色
	background();
}

/*********模拟下雨效果*********/
void running()
{
	for (int i = 0; i < maxrain; i++)		// 初始化所有雨滴
	{
		InitRain(i);
	}
	first = 30;						//更改雨点初始位置的y坐标
	// 雨滴循环下落，随机位置
	while (!kbhit())
	{

		for (int i = 0; i < maxrain; i++)
			MoveRain(i);			//遍历雨点，更新其位置
		background();				//对背景进行重绘
		settextstyle(30, 19, _T("楷体"));
		TCHAR s[] = _T("按下键盘任意键结束");
		outtextxy(285, 180, s);
		Sleep(10);
	}
}

/*********太阳升起*********/
void sunup()
{
	setfillcolor(WHITE);
	for (int i = 0; i < 160; i++)
	{
		fillcircle(-60 + i, 220 - i, 30);
		line((int)(-60 + 35 * cos(0) + i), (int)(220 + 35 * sin(0) - i), (int)(-60 + 55 * cos(0) + i), (int)(220 + 55 * sin(0) - i));
		line((int)(-60 + 35 * cos(PI / 4) + i), (int)(220 + 35 * sin(PI / 4) - i), (int)(-60 + 55 * cos(PI / 4) + i), (int)(220 + 55 * sin(PI / 4) - i));
		line((int)(-60 + 35 * cos(PI / 2) + i), (int)(220 + 35 * sin(PI / 2) - i), (int)(-60 + 55 * cos(PI / 2) + i), (int)(220 + 55 * sin(PI / 2) - i));
		line((int)(-60 + 35 * cos(PI / 4 * 3) + i), (int)(220 + 35 * sin(PI / 4 * 3) - i), (int)(-60 + 55 * cos(PI / 4 * 3) + i), (int)(220 + 55 * sin(PI / 4 * 3) - i));
		line((int)(-60 + 35 * cos(PI) + i), (int)(220 + 35 * sin(PI) - i), (int)(-60 + 55 * cos(PI) + i), (int)(220 + 55 * sin(PI) - i));
		line((int)(-60 + 35 * cos(PI / 4 * 5) + i), (int)(220 + 35 * sin(PI / 4 * 5) - i), (int)(-60 + 55 * cos(PI / 4 * 5) + i), (int)(220 + 55 * sin(PI / 4 * 5) - i));
		line((int)(-60 + 35 * cos(PI / 2 * 3) + i), (int)(220 + 35 * sin(PI / 2 * 3) - i), (int)(-60 + 55 * cos(PI / 2 * 3) + i), (int)(220 + 55 * sin(PI / 2 * 3) - i));
		line((int)(-60 + 35 * cos(PI / 4 * 7) + i), (int)(220 + 35 * sin(PI / 4 * 7) - i), (int)(-60 + 55 * cos(PI / 4 * 7) + i), (int)(220 + 55 * sin(PI / 4 * 7) - i));
		Sleep(50);
		clearrectangle(-60 + i - 60, 220 - i - 60, -60 + i + 60, 220 - i + 60);
		if (i==80)
		{
			HANDLE hThread2 = CreateThread(NULL, 0, MyThread2, NULL, 0, NULL);
		}
		background();
	}
}

/*********太阳旋转*********/
void sunrotate()
{
	for (int i = 0; i < 5; i++)
	{
		circle(100, 60, 30);
		line((int)(100 + 35 * cos(PI / 5 * i)), (int)(60 + 35 * sin(PI / 5 * i)), (int)(100 + 55 * cos(PI / 5 * i)), (int)(60 + 55 * sin(PI / 5 * i)));
		line((int)(100 + 35 * cos(PI / 5 * i + PI / 4)), (int)(60 + 35 * sin(PI / 5 * i + PI / 4)), (int)(100 + 55 * cos(PI / 5 * i + PI / 4)), (int)(60 + 55 * sin(PI / 5 * i + PI / 4)));
		line((int)(100 + 35 * cos(PI / 5 * i + PI / 2)), (int)(60 + 35 * sin(PI / 5 * i + PI / 2)), (int)(100 + 55 * cos(PI / 5 * i + PI / 2)), (int)(60 + 55 * sin(PI / 5 * i + PI / 2)));
		line((int)(100 + 35 * cos(PI / 5 * i + PI / 4 * 3)), (int)(60 + 35 * sin(PI / 5 * i + PI / 4 * 3)), (int)(100 + 55 * cos(PI / 5 * i + PI / 4 * 3)), (int)(60 + 55 * sin(PI / 5 * i + PI / 4 * 3)));
		line((int)(100 + 35 * cos(PI / 5 * i + PI)), (int)(60 + 35 * sin(PI / 5 * i + PI)), (int)(100 + 55 * cos(PI / 5 * i + PI)), (int)(60 + 55 * sin(PI / 5 * i + PI)));
		line((int)(100 + 35 * cos(PI / 5 * i + PI / 4 * 5)), (int)(60 + 35 * sin(PI / 5 * i + PI / 4 * 5)), (int)(100 + 55 * cos(PI / 5 * i + PI / 4 * 5)), (int)(60 + 55 * sin(PI / 5 * i + PI / 4 * 5)));
		line((int)(100 + 35 * cos(PI / 5 * i + PI / 2 * 3)), (int)(60 + 35 * sin(PI / 5 * i + PI / 2 * 3)), (int)(100 + 55 * cos(PI / 5 * i + PI / 2 * 3)), (int)(60 + 55 * sin(PI / 5 * i + PI / 2 * 3)));
		line((int)(100 + 35 * cos(PI / 5 * i + PI / 4 * 7)), (int)(60 + 35 * sin(PI / 5 * i + PI / 4 * 7)), (int)(100 + 55 * cos(PI / 5 * i + PI / 4 * 7)), (int)(60 + 55 * sin(PI / 5 * i + PI / 4 * 7)));
		Sleep(200);
		clearrectangle(40, 1, 160, 120);
	}
}
