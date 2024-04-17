#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <graphics.h>
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib,"winmm.lib")
#define Width 480
#define Height 680
int Data[4][4];//存储格子信息，当Data[i][j]=0时，为空白格
int Temp[4][4];
int BestScore, CurrentScore;
IMAGE img0, img2, img4, img8, img16, img32, img64, img128, img256, img512, img1024, img2048;
void CreateData();
void InitGame();
void InitData();
int Check();
int Find2048();
void TakeNote();
int CompareNote();
void Up();
void Down();
void Left();
void Right();
void Reset();
void Vectory();
void Defeat();
void RefreshImage();
void Start();
void Menu();

void InitData() {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			Data[i][j] = 0;
		}
	}
}
int Check() {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (Data[i][j] == 0)return 0; //有一格为空，游戏未结束
			if (i > 0 && Data[i - 1][j] == Data[i][j])return 0;//有两个相邻的格子相同，游戏未结束
			if (j > 0 && Data[i][j - 1] == Data[i][j])return 0;
		}
	}
	return 1;
}
int	Find2048() {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (Data[i][j])return 1;
		}
	}
	return 0;
}
void TakeNote() {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			Temp[i][j] = Data[i][j];
		}
	}
}
int CompareNote() {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (Temp[i][j] != Data[i][j])return 0;
		}
	}
	return 1;
}
void Up() {
	int i, j, m, step = 0;
	
	for (j = 0; j < 4; j++) {
		i = 0, step = 0;
		while (i < 3 && step < 3) {
			if (!Data[i][j]) {
				for (m = i; m < 3; m++)Data[m][j] = Data[m + 1][j];
				Data[3][i] = 0;
				step++;
			}
			else i++;
		}
		for (i = 0; i < 3; i++) {
			if (Data[i][j] == Data[i + 1][j] && Data[i][j] != 0) {
				Data[i][j] = Data[i][j] * 2;
				Data[j + 1][i] = 0;
				CurrentScore += Data[i][j];
				if (CurrentScore > BestScore)BestScore = CurrentScore;
			}
			i = 0, step = 0;
			while (i < 3 && step < 3) {
				if (!Data[i][j]) {
					for (m = i; m < 3; m++)Data[m][i] = Data[m + 1][i];
					Data[3][i] = 0;
					step++;
				}
				else j++;
			}
		}
	}
	if (!CompareNote()) CreateData();
}
void Down() {
	int i, j, m, step = 0;
	
	for (j = 0; j < 4; j++) {
		i = 3, step = 0;
		while (i >0 && step < 3) {
			if (! Data[i][j]) {
				for (m = i; m > 0; m--) Data[m][j] = Data[m - 1][j];
				Data[0][j] = 0;
				step++;
			}
			else i--;
		}
		for (i = 3; i > 0; i--) {
			if (Data[i][j] == Data[i - 1][j] && Data[i][j] != 0) {
				Data[i][j] = Data[i][j] * 2;
				Data[i-1][j] = 0;
				CurrentScore += Data[i][j];
				if (CurrentScore > BestScore)BestScore = CurrentScore;
			}
		}
		i = 3, step = 0;
		while (i > 3 && step < 3) {
			if (!Data[i][j]) {
				for (m = i; m > 0; m--)Data[m][i] = Data[m - 1][i];
				Data[0][i] = 0;
				step++;
			}
			else j--;
		}
	}
	if (!CompareNote()) CreateData();
}
void Left() {
	int i, j, m, step = 0;
	
	for (i = 0; i < 4; i++) {
		j = 0, step = 0;
		while (j < 3 && step < 3) {
			if (!Data[i][j]) {
				for (m = j; m < 3; m++)Data[i][m] = Data[i][m + 1];
				Data[i][3] = 0;
				step++;
			}
			else j++;
		}	
		for (j = 0; j < 3; j++) {
			if (Data[i][j] == Data[i][j + 1] && Data[i][j] != 0) {
				Data[i][j] = Data[i][j] * 2;
				Data[i][j + 1] = 0;
				CurrentScore += Data[i][j];
				if (CurrentScore > BestScore)BestScore = CurrentScore;
			}
		}
		j = 0, step = 0;
		while (j < 3 && step < 3) {
			if (!Data[i][j]) {
				for (m = j; m < 3; m++)Data[i][m] = Data[i][m + 1];
				Data[i][3] = 0;
				step++;
			}
			else j++;
		}
	}
	if (!CompareNote()) CreateData();
}
void Right() {
	int i, j, m, step = 0;
	
	for (i = 0; i < 4; i++) {
		j = 3, step = 0;
		while (j > 0 && step < 3) {
			if (!Data[i][j]) {
				for (m = j; m >0 ; m--)Data[i][m] = Data[i][m - 1];
				Data[i][0] = 0;
				step++;
			}
			else j--;
		}
		for (j = 3; j >0; j--) {
			if (Data[i][j] == Data[i][j - 1] && Data[i][j] != 0) {
				Data[i][j] = Data[i][j] * 2;
				Data[i][j - 1] = 0;
				CurrentScore += Data[i][j];
				if (CurrentScore > BestScore)BestScore = CurrentScore;
			}
		}
		j = 0, step = 0;
		while (j > 0 && step < 3) {
			if (!Data[i][j]) {
				for (m = j; m < 3; m++)Data[i][m] = Data[i][m + 1];
				Data[i][3] = 0;
				step++;
			}
			else j--;
		}
	}
	if (!CompareNote()) CreateData();
}
void Reset() {

}
void Vectory() {
	cleardevice();
	mciSendString("close music", NULL, 0, NULL);

}
void Defeat() {
	cleardevice();
	mciSendString("close music", NULL, 0, NULL);
	
}
void CreateData(){
	int x, y, choice, data;
	srand((int)time(0));
	while (1) {
		x = rand() % 4;
		y = rand() % 4;

		if (Data[x][y] != 0)continue;//随机到已有数据的格子就continue

		choice = rand() % 5;
		if (choice == 0)data = 4;
		else data = 2;

		Data[x][y] = data;
		break;
	}
}
void Update() {
	int kb,i,j,num;
	EndBatchDraw();
	kb = _getch();
	TakeNote();
	if (kb == 72)Up();
	else if (kb == 80)Down();
	else if (kb == 75)Left();
	else if (kb == 77)Right();
	else if (kb == 27)Reset();
	
}
void RefreshImage() {
	int i, j;
	char CSstr[10],BSstr[10];
	cleardevice();
	setfont(100, 0, "Microsoft Yahei UI Bold");
	setcolor(RGB(217, 250, 244)); //2048 字体
	outtextxy(15, 0, "2048");

	setfillcolor(RGB(184, 175, 160));//当前得分 和 最高得分 背景 

	solidroundrect(210,10,330,80,15,15);
	setfont(28, 0, "Microsoft Yahei UI Bold");
	setbkcolor(RGB(184, 175, 160));// 当前得分 字体背景 
	settextcolor(RGB(248, 247, 241));//当前得分 字体
	outtextxy(230, 20, "当前得分");
	setbkcolor(RGB(184, 175, 160));
	_itoa(CurrentScore, CSstr, 10);
	outtextxy(265, 52, CSstr);//分数

	solidroundrect(350, 10, 460, 80, 15, 15);
	outtextxy(380, 20, "最高得分");
	setbkcolor(RGB(184, 175, 160));//最高得分 字体背景
	_itoa(BestScore, BSstr, 10);
	outtextxy(395, 52, BSstr);

	setfillcolor(RGB(141, 122, 105));
	solidroundrect(210, 95, 460, 137, 15, 15);
	setbkcolor(RGB(141, 122, 105));//背景颜色
	setfont(33, 0, "Microsoft Yahei UI Bold");
	outtextxy(248, 100, "返回主页面(esc)");

	setfillcolor(RGB(141, 122, 105));
	solidroundrect(210, 152, 460, 195, 15, 15);
	setbkcolor(RGB(141, 122, 105));//背景颜色
	setfont(33, 0, "Microsoft Yahei UI Bold");
	outtextxy(268, 160, "重新开始(t)");

	setfillcolor(RGB(187, 173, 160));//里面边框配色
	solidroundrect(10, 210, 460, 660, 20, 20);

	if (Check())Defeat();

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			switch (Data[i][j]) {
			case 0:loadimage(&img0, "./image/blank.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img0); break;
			case 2:loadimage(&img2, "./image/2.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img2); break;
			case 4:loadimage(&img4, "./image/4.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img4); break;
			case 8:loadimage(&img8, "./image/8.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img8); break;
			case 16:loadimage(&img16, "./image/16.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img16); break;
			case 32:loadimage(&img32, "./image/32.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img32); break;
			case 64:loadimage(&img64, "./image/64.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img64); break;
			case 128:loadimage(&img128, "./image/128.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img128); break;
			case 256:loadimage(&img256, "./image/256.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img256); break;
			case 512:loadimage(&img512, "./image/512.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img512); break;
			case 1024:loadimage(&img1024, "./image/1024.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img1024); break;
			case 2048:loadimage(&img2048, "./image/2048.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img2048); break;
			}
		}
	}
}

void Start() {
	InitData();
	CreateData();
	CreateData();
	while (1){
		RefreshImage();
		BeginBatchDraw();//批量画图，无闪烁
		setbkcolor(RGB(251, 248, 241));
		Update();
		if(Find2048())Vectory();
	}
}
void Menu()
{
	cleardevice();
	IMAGE bk;
	loadimage(&bk, "./image/background.jpg", Width, Height);
	putimage(0, 0, &bk);
	setfont(80, 50, "幼圆");//字体设置
	RECT r1 = { 0,0,Width,Height / 3 };
	setbkcolor(RGB(96, 142, 182));
	drawtext("2048", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setbkcolor(RGB(109, 156, 196));
	setfont(30, 12, "幼圆");
	RECT r2 = { Width / 2 - 45, Height / 3 + 15,Width / 2 + 45,Height / 3 + 45 };
	drawtext("开始游戏", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3 = { Width / 2 - 45, Height / 3 + 75,Width / 2 + 45,Height / 3 + 105 };
	drawtext("退出游戏", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void InitGame()
{
	//开场动画
	//mciSendString("open ./bgm/start.mp3 alias music ", NULL, 0, NULL);//背景音乐
	//mciSendString("play music repeat", NULL, 0, NULL);
	//initgraph(1288, 724);
	//IMAGE s, e;
	//loadimage(&s, "image/genshi.png", 1288, 724);
	//loadimage(&e, "image/genshin1.png", 1288, 724);
	//putimage(0, 0, &s);
	//Sleep(2500);
	//putimage(0, 0, &e);
	//_getch();
	//closegraph();



	initgraph(Width, Height);//长宽
	setbkcolor(RGB(96, 143, 183));//背景
	settextcolor(RGB(251, 248, 241));

	MOUSEMSG m;
	while (1){
		Menu();
		EndBatchDraw();//结束批量绘图   没这个会闪屏
		BeginBatchDraw();//批量绘图
		m = GetMouseMsg();//获取鼠标信息
		if (m.mkLButton == 1){
			if (m.x > Width / 2 - 45 && m.x<Width / 2 + 45 && m.y>Height / 3 + 15 && m.y < Height / 3 + 45)
				Start();
			else if (m.x > Width / 2 - 45 && m.x<Width / 2 + 45 && m.y>Height / 3 + 75 && m.y < Height / 3 + 105)
				exit(0);
		}
	}
}
int main() {
	InitGame();
	return 0;
}
