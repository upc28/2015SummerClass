#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <iostream>
#include <windows.h>
using namespace std;

int maxstar=10;	// �������
int first=280;
double v=0;			//�����ٶ�
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

// ��ʼ��
void InitStar(int i)
{
	
	star[i].y = rand()%first;
	star[i].x = rand() %800;
	star[i].step = (rand() % 3000) / 3000.0 + v*1.2;
	//star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);	// �ٶ�Խ�죬���ʱ仯
	//star[i].color = RGB(star[i].color, star[i].color, star[i].color);
	
}
/********** ���� **********/
void background()
{
	// ����ɫ
	setfillcolor(RGB(255, 255, 255));
	setlinecolor(BLACK);
	rectangle(0, 0, 800, 370);// վ��
	// �߿�
	setfillcolor(RGB(255, 255, 255));
	setlinecolor(RGB(0, 0, 0));
	rectangle(60, 150, 170, 350);
	// �ڲ�
	setfillcolor(RGB(255, 255, 255));
	setlinecolor(RGB(0, 0, 0));
	rectangle(70, 160, 160, 340);
	// �ײ�
	setfillcolor(RGB(255, 255, 255));
	setlinecolor(RGB(0, 0, 0));
	rectangle(65, 350, 165, 370);
	// �ȳ���
	// ����
	setfillcolor(RGB(255, 255, 255));
	setlinecolor(RGB(0, 0, 0));
	rectangle(220, 120, 750, 130);
	// ����
	setfillcolor(RGB(255, 255, 255));
	setlinecolor(RGB(0, 0, 0));
	rectangle(240, 130, 250, 370);
	rectangle(720, 130, 730, 370);
	// ����
	setfillcolor(RGB(255, 255, 255));
	setlinecolor(RGB(0, 0, 0));
	rectangle(250, 160, 720, 310);

}
//ˮ��
//DWORD WINAPI  print_wave(LPVOID pvParam)
void print_wave();
{
	int a=1;int b=1;
	int x1,y1,x2,y2;
	int i;				//����ѭ����������i
	x1=(int)star[i].x-(b/2);
	y1=(int)star[i].y-(a/2);
	x2=(int)star[i].x+(b/2);
	y2=(int)star[i].y+(a/2);
	for (i=0;i<20;i++)//��ˮ���ĳ��֡���ʧ����ѭ��
	{

		arc(x1,y1,x2,y2,60,60);
		Sleep(100);
		/*if(i%10==0)
		{clearellipse(x1-1,y1-1,x2+1,y2+1);//����ˮ��
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


// �ƶ����
void MoveStar(int i)
{
	// ����ԭ�������
	if(star[i].y<380)
	clearrectangle((int)star[i].x, star[i].y,(int)star[i].x+1,star[i].y+4);
	line(0,370,800,370);
	HANDLE   hThread; 

	// ������λ��
	star[i].y +=(int) star[i].step;
	//star[i].step+=0.1;       //�����½�
	srand(i*i);
	if (star[i].y > rand()%230+350)	
	{	
		//hThread =  CreateThread(NULL, 0, print_wave, NULL, 0, NULL);
		print_wave(/*(int)star[i].x,(int)star[i].y,3,2*/);
		InitStar(i);
	}
	// �������
	fillrectangle((int)star[i].x, star[i].y,(int)star[i].x+1,star[i].y+4);
}


// ������
void main()
{
	int read_in;
	while(1)
	{
		cout<<"������������С(2-5): ";
		cin>>read_in;
		if (read_in>=2&&read_in<=5)
		{
			break;
		} 
	}
	//maxstar=read_in*80;
	//v=(read_in+3)*0.8;
	srand((unsigned)time(NULL));	// �������
	initgraph(800, 600);		// ��������
	setbkcolor(WHITE);
	line(0,370,800,370);	
	cleardevice();
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	// ��ʼ���������
	for(int i = 0; i < maxstar; i++)
	{
		InitStar(i);
		star[i].y = rand() % 800;
	}
	first = 30;
	// ���ѭ�����䣬���λ��
	while(!kbhit())
	{
		for(int i = 0; i < maxstar; i++)
			MoveStar(i);
		background();
		Sleep(10);
		
	}
	closegraph();					// �رմ���
}
