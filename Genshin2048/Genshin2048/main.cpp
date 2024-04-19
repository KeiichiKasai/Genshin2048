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
int BestScore, CurrentScore,Score;
IMAGE img0, img2, img4, img8, img16, img32, img64, img128, img256, img512, img1024, img2048;
void CreateData(); //√
void InitGame(); // √
void InitData(); // √
int Check();// √
void Find2048(); // √
void TakeNote(); // √
int CompareNote();// √
void moveUP();// √
void moveDOWN();// √
void moveLEFT();// √
void moveRIGHT();// √
void Reset();
void Vectory();
void Defeat();
void RefreshImage();
void Start();
void Menu();



void moveUP(){
	int i, j, m = 0, n = 0;
	for (i = 0; i < 4; i++){

		//移动操作
		j = 0; n = 0;		 //j为当前判定的所在行
		while (n < 3 && j < 3){  //n为移动的次数
			if (!Data[j][i]) {  //若发现空白格
				for (m = j; m < 3; m++)Data[m][i] = Data[m + 1][i];   //下方数据向上平移1格，覆盖空白格
				Data[3][i] = 0;	//最后一行置0
				n++;			//移动的次数+1
			}
			else j++; //否则：让当前判定的所在行+1
		}

		//合并操作
		for (j = 0; j < 3; j++) {
			if (Data[j][i] == Data[j + 1][i] && Data[j][i]!=0) {//相同(且不是0)则合并
				Data[j][i] = Data[j][i] * 2;//上面的保存合并后的数字
				Data[j + 1][i] = 0;			//下面的清零
				CurrentScore += Data[j][i];
				if (CurrentScore > BestScore)BestScore = CurrentScore;
			}
		}

		//移动操作
		j = 0; n = 0;
		while (n < 3 && j < 3){
			if (Data[j][i] == 0){
				for (m = j; m < 3; m++)
					Data[m][i] = Data[m + 1][i];
				Data[3][i] = 0;
				n++;
			}
			else j++;
		}
	}
	if (!CompareNote())CreateData();
}

void moveDOWN(){
	int i, j;
	int m = 0, n = 0;
	for (i = 0; i < 4; i++){
		//移动操作
		j = 3; n = 0;
		while (n < 3 && j>0){
			if (!Data[j][i]){
				for (m = j; m > 0; m--)Data[m][i] = Data[m - 1][i];
				Data[0][i] = 0;
				n++;
			}
			else j--;
		}

		//合并操作
		for (j = 3; j > 0; j--) {//行
			if (Data[j][i] == Data[j - 1][i] && Data[j][i] != 0){
				Data[j][i] = Data[j][i] * 2;//下面的保存合并后的数字
				Data[j - 1][i] = 0;			//上面的清零
				CurrentScore += Data[j][i];
				if (CurrentScore > BestScore)BestScore = CurrentScore;
			}
		}
		//移动操作
		j = 3; n = 0;
		while (n < 3 && j>0){
			if (!Data[j][i]){
				for (m = j; m > 0; m--)Data[m][i] = Data[m - 1][i];
				Data[0][i] = 0;
				n++;
			}
			else j--;
		}
	}
	if (!CompareNote())CreateData();
}

void moveLEFT(){
	int i, j;
	int m = 0, n = 0;
	for (i = 0; i < 4; i++){
		//移动操作
		j = 0; n = 0;
		while (n < 3 && j < 3){
			if (!Data[i][j]){
				for (m = j; m < 3; m++)Data[i][m] = Data[i][m + 1];
				Data[i][3] = 0;
				n++;
			}
			else j++;
		}
		//合并操作
		for (j = 0; j < 3; j++) {
			if (Data[i][j] == Data[i][j + 1] && Data[i][j] != 0) {
				Data[i][j] = Data[i][j] * 2;
				Data[i][j + 1] = 0;
				CurrentScore += Data[i][j];
				if (CurrentScore > BestScore)BestScore = CurrentScore;
			}
		}
		//移动操作
		j = 0; n = 0;
		while (n < 3 && j < 3){
			if (!Data[i][j]){
				for (m = j; m < 3; m++)Data[i][m] = Data[i][m + 1];
				Data[i][3] = 0;
				n++;
			}
			else j++;
		}
	}
	if (!CompareNote())CreateData();
}

void moveRIGHT(){
	int i, j;
	int m = 0, n = 0;
	for (i = 0; i < 4; i++){
		//移动操作
		j = 3; n = 0;
		while (n < 3 && j>0){
			if (!Data[i][j]){
				for (m = j; m > 0; m--)Data[i][m] = Data[i][m - 1];
				Data[i][0] = 0;
				n++;
			}
			else j--;
		}
		//合并操作
		for (j = 3; j > 0; j--) {
			if (Data[i][j] == Data[i][j - 1] && Data[i][j] != 0) {
				Data[i][j] = Data[i][j] * 2;
				Data[i][j - 1] = 0;
				CurrentScore += Data[i][j];
				if (CurrentScore > BestScore)BestScore = CurrentScore;
			}
		}
		//移动操作
		j = 3; n = 0;
		while (n < 3 && j>0){
			if (!Data[i][j]){
				for (m = j; m > 0; m--)Data[i][m] = Data[i][m - 1];
				Data[i][0] = 0;
				n++;
			}
			else j--;
		}
	}
	if (!CompareNote())CreateData();
}

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
void Find2048() {
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (Data[i][j] == 2048)Vectory();
		}
	}
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
void Reset() {
	cleardevice();
	CurrentScore = 0;
	InitData();
	CreateData();
	CreateData();
}
void Vectory() {
	IMAGE t;
	cleardevice();
	mciSendString("close music", NULL, 0, NULL);
	loadimage(&t, "./image/vectory.png", Width, Height);
	putimage(0, 0, &t);
}
void Defeat() {
	IMAGE t;
	cleardevice();
	mciSendString("close music", NULL, 0, NULL);
	loadimage(&t, "./image/defeat.png",Width,Height);
	putimage(0, 0, &t);
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
	int kb;
	FlushBatchDraw();
	kb = _getch();
	TakeNote();
	if (kb == 75)moveUP();
	else if (kb == 77)moveDOWN();
	else if (kb == 72)moveLEFT();
	else if (kb == 80)moveRIGHT();
	else if (kb == 27)Reset();
	
}
void RefreshImage() {
	int i, j;
	char CSstr[10],BSstr[10];
	IMAGE paimeng,a1,a2,a3,a4;
	cleardevice();
	BeginBatchDraw();
	setfont(100, 0, "Microsoft Yahei UI Bold");
	setcolor(RGB(141,122,105)); //2048 字体
	outtextxy(15, 0, "2048");

	setfillcolor(RGB(184, 175, 160));//当前得分 和 最高得分 背景 

	solidroundrect(210,10,330,80,15,15);
	setfont(28, 0, "Microsoft Yahei UI Bold");
	setbkcolor(RGB(184, 175, 160));// 当前得分 字体背景 
	settextcolor(RGB(248, 247, 241));//当前得分 字体
	outtextxy(230, 20, "当前得分");
	setbkcolor(RGB(184, 175, 160));
	_itoa(CurrentScore, CSstr, 10);
	outtextxy(260, 52, CSstr);//分数

	solidroundrect(350, 10, 460, 80, 15, 15);
	outtextxy(365, 20, "最高得分");
	setbkcolor(RGB(184, 175, 160));//最高得分 字体背景
	_itoa(BestScore, BSstr, 10);
	outtextxy(390, 52, BSstr);

	setfillcolor(RGB(141, 122, 105));
	solidroundrect(210, 95, 460, 137, 15, 15);
	setbkcolor(RGB(141, 122, 105));//背景颜色
	setfont(33, 0, "Microsoft Yahei UI Bold");
	outtextxy(248, 100, "重新开始[Esc]");

	

	loadimage(&paimeng, "./image/paimeng.png",190,100);
	loadimage(&a1, "./image/a1.png",66,66);
	loadimage(&a2, "./image/a2.png",66,66);
	loadimage(&a3, "./image/a3.png",66,66);
	loadimage(&a4, "./image/a4.png",66,66);	
	putimage(10, 100, &paimeng);
	putimage(200, 141, &a1);
	putimage(266, 141, &a2);
	putimage(332, 141, &a3);
	putimage(398, 141, &a4);
	

	setfillcolor(RGB(187, 173, 160));//里面边框配色
	solidroundrect(10, 210, 460, 660, 20, 20);

	

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			switch (Data[i][j]) {
			case 0:loadimage(&img0, "./image/blank.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img0); break;
			case 2:loadimage(&img2, "./image/x2.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img2); break;
			case 4:loadimage(&img4, "./image/x4.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img4); break;
			case 8:loadimage(&img8, "./image/x8.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img8); break;
			case 16:loadimage(&img16, "./image/x16.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img16); break;
			case 32:loadimage(&img32, "./image/x32.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img32); break;
			case 64:loadimage(&img64, "./image/x64.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img64); break;
			case 128:loadimage(&img128, "./image/x128.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img128); break;
			case 256:loadimage(&img256, "./image/x256.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img256); break;
			case 512:loadimage(&img512, "./image/x512.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img512); break;
			case 1024:loadimage(&img1024, "./image/x1024.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img1024); break;
			case 2048:loadimage(&img2048, "./image/x2048.png", 100, 100); putimage(i * 110 + 20, j * 110 + 220, &img2048); break;
			}
		}
	}
	FlushBatchDraw();
	if (Check())Defeat();
	
}

void Start() {
	CurrentScore = 0;
	InitData();
	CreateData();
	CreateData();
	while (1){
		RefreshImage();
		BeginBatchDraw();//批量画图，无闪烁
		setbkcolor(RGB(250, 250, 250));
		Update();
		Find2048();
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
	setbkcolor(RGB(250, 250, 250));
}

void InitGame()
{
	
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
	setbkcolor(RGB(250, 250, 250));//背景
	settextcolor(RGB(250, 250, 250));

	MOUSEMSG m;
	while (1){
		BeginBatchDraw();//批量绘图
		Menu();
		FlushBatchDraw();//结束批量绘图   没这个会闪屏
		
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
