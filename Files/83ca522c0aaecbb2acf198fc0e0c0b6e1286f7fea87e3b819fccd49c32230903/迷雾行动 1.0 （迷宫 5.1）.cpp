#include<iostream>
#include<ctime> 
#include<conio.h>
#include<windows.h>
using namespace std;
const int level_n[]={10,25,30,40};
const int level_m[]={10,20,30,30};
const int dx[]={0,1,0,-1};
const int dy[]={1,0,-1,0};
short f[100][100];
int x, y, val, flag, level, wait_time, cnt_boom=3;
int n, m, fx, fy, macnt;
char name[16];
char k; int nx,ny;
time_t start,now;
bool is_win=1,FFF;
//-------------------------------------
//Code By naijil2013
void ChangeGraph(int WIDTH,int HEIGHT){
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console,&r);
	MoveWindow(console, r.left, r.top, WIDTH, HEIGHT, TRUE);
}
void Set(short x,short y){
	HANDLE hOut;
	COORD pos={y,x};
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut,pos);
}
void Hide(){
	HANDLE hOut;
	CONSOLE_CURSOR_INFO curInFo;
	hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	curInFo.dwSize=1;
	curInFo.bVisible=0;
	SetConsoleCursorInfo(hOut,&curInFo);
}

//-------------------------------------
//Code By zhaolt2012
void Color(int a)
{
    //白 
    if(a==0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    //绿 
    else if(a==1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
    //红 
    else if(a==2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
    //蓝 
    else if(a==3) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
    //粉
    else if(a==4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE); 
    //黄
    else if(a==5) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN); 
    //紫
    else if(a==6) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE); 
    //灰 
    else if(a==7) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    //棕
    else if(a==8) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN);
	//黑 
	else if(a==9) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);
    //随机
    else if(a == -1) Color((rand()-1)%6+1); 
}
bool nb(int x,int y)
{
	if(x<1||x>n-2||y<1||y>m-2||f[x][y]!=1) return 0;
	int hmz=0;
	if(f[x+1][y]!=1) hmz++;
	if(f[x][y+1]!=1) hmz++;
	if(f[x-1][y]!=1) hmz++;
	if(f[x][y-1]!=1) hmz++;
	if(hmz!=1||rand()%10==0) return 0;
	return 1;
}
void dfs(int x,int y,int cnt)
{
	if(cnt>macnt)
	{
		macnt=cnt;
		fx=x;
		fy=y;
	}
	if(rand()%10<1) f[x][y]=2;
	else f[x][y]=0;
	int z=rand()%4,s=0;
	
	if(z==0&&nb(x+1,y)) dfs(x+1,y,cnt+1),s++;
	else if(z<2&&nb(x,y+1)) dfs(x,y+1,cnt+1),s++;
	else if(z<3&&nb(x-1,y)) dfs(x-1,y,cnt+1),s++;
	else if(nb(x,y-1)) dfs(x,y-1,cnt+1),s++;
	if(s==0)
	{
		if(nb(x+1,y)) dfs(x+1,y,cnt+1);
		if(nb(x,y+1)) dfs(x,y+1,cnt+1);
		if(nb(x-1,y)) dfs(x-1,y,cnt+1);
		if(nb(x,y-1)) dfs(x,y-1,cnt+1);
	}
	else
	{
		if(nb(x+1,y)&&rand()%5==0) dfs(x+1,y,cnt+1);
		if(nb(x,y+1)&&rand()%5==0) dfs(x,y+1,cnt+1);
		if(nb(x-1,y)&&rand()%5==0) dfs(x-1,y,cnt+1);
		if(nb(x,y-1)&&rand()%5==0) dfs(x,y-1,cnt+1);	
	}
}

void Build()
{
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			f[i][j]=1;
			
	f[1][1]=0;
	dfs(1,2,1);
	for(int i=1;i<n-1;i++)
		for(int j=1;j<m-1;j++)
			if(nb(i,j)) dfs(i,j,1);
	f[fx][fy]=0;
}

//------------------------------------
//Code By naijil2013
void First_Step() {
	printf("\n\n    请输入您的代号，不超过15个字符：");
	scanf("%s",name);
	system("cls");
	printf("\n\n    请按下任意键，开始您的RGP生涯。");
	getch();
	system("cls");
} 
void Loading() {
	system("mode con: cols=50 lines=5");
	system("color f0");
	system("cls");
	Sleep(1000);
	printf("\n\n    干员，您的行动时间很短。");
	getch(); system("cls");
	printf("\n\n    只有%d秒，逾时迷宫将崩塌。",wait_time=n*m);
	getch(); system("cls");
	printf("\n\n    请尽可能地带出钻石，它们很重要。"); 
	getch(); system("cls");
	printf("\n\n    祝您好运。");
	getch(); system("cls");
	system("color f2"); printf("\n\n    好的，长官。"); Color(0); 
	system("mode con: cols=100 lines=50");
	Hide(); Set(1,1);
}
void Welcome(){
	Hide();
	system("mode con: cols=50 lines=5");
	system("color f0");
	printf("\n\n    呼叫干员%s!",name);
	getch(); system("cls");
	printf("\n\n    总部传来了紧急任务！");
	getch(); system("cls");
	printf("\n\n    请立即动身！"); 
	getch(); system("cls");
	system("color f2"); printf("\n\n    %s收到！",name);
	getch(); system("cls"); 
	n=level_n[level]; 
	m=level_m[level];
	level++;
	printf("\n\n    请按下确定按钮，直升机将起飞。");
	srand((int)(getch()));
	Build();
	system("cls");
	system("color 0f");
	Sleep(3000);
	Loading();
}
void print(){
	system("color 0f");
	Hide(); Set(0,0);
	for(int i=x-11;i<x+10;i++) {
		for(int j=y-11;j<y+10;j++) {
			if(i<x-4 || i>x+3 || j<y-4 || j>y+3) printf("  ");
			else if (i == fx && j == fy) Color(2),printf("索");//
			else if (i == x && j == y) Color(1),printf("我");//
			else {
				if (f[i][j] == 1) Color(5),printf("墙");//
				else if (f[i][j] == 2) Color(3),printf("钻");//
				else cout << "  ";
			}
		}
		cout << endl;
	} 
	Color(0),printf("\n已收集钻石：%d个",val);//
	printf("\n\n手炮存储量：|");
	for(int i=1;i<=cnt_boom;i++) printf("_");
	printf("|");
}

void Ending(bool f) {
	system("cls");
	if(f){
		system("color f0");
		system("mode con cols=50 lines=5");
		system("cls");
		Sleep(500);
		printf("\n\n    快！抓住绳索!!!");
		getch(); system("cls");
		Sleep(3000);
		printf("\n\n    太好了！您回来了！");
		getch(); system("cls");
		printf("\n\n    您带回来了%d颗钻石！实验材料有了！",val);
		getch(); system("cls");
		printf("\n\n    快去休息一下吧，总部会给您足够多的假期。"); 
		getch(); system("cls");
		system("color f2"); printf("\n\n    那我走了，长官。");
		getch();
		Color(0);
		system("cls");
	}
	else {
		system("color 0f");
		system("mode con: cols=50 lines=5");
		Sleep(1000);
		printf("\n\n    %s!呼叫干员%s!",name,name);
		Sleep(3000); system("cls"); Color(2);
		printf("\n\n    %s，卒于第%d次迷雾行动",name,level);
		system("cls");
		Sleep(50000);
		Color(-1);
	}
}

void W() {
	if (f[x - 1][y] == 1) return;
	x--; flag=4;
}
void S() {
	if (f[x + 1][y] == 1) return;
	x++; flag=2;
}
void A() {
	if (f[x][y - 1] == 1) return;
	y--; flag=3;
}
void D() {
	if (f[x][y + 1] == 1) return;
	y++; flag=1;
}
//--------------------
// code by naijil
void Break_wall() {
	if(cnt_boom==0) return ;
	cnt_boom--; nx=x,ny=y;
	Color(2); printf("\n\n 发射手炮！"); 
	while(f[nx][ny]!=1) {
		nx+=dx[flag-1];
		ny+=dy[flag-1];
	}
	if(nx!=0 && nx!=n && ny!=0 && ny!=m) {
		printf("   _已破坏目标_");
		Sleep(1000); f[nx][ny]=0;
		system("cls");
		print();
	}
	else {
		system("cls");
		print();
	}
	Sleep(1000);
	
}
void Get_Boom() {
	if(val<=1) return;
	if(cnt_boom==3) return;
	val-=2; cnt_boom++;
	print();
}
void THEEND(bool is_win) {
	system("cls"); 
	system("mode con: cols=50 lines=5");
	system("color f0");
	if(is_win) {
		Color(0); system("cls");
		printf("\n\n    干员%s，过来一下",name);
		getch(); Color(1); system("cls");
		printf("\n\n    怎么了，长官？");
		getch(); Color(2); system("cls");
		system("color 0f"); Color(2);
		printf("\n\n    砰！！！");
		getch(); Color(1); system("cls");
		printf("\n\n    你！噗……呃……你居然……");
		getch(); Color(0); system("cls");
		printf("\n\n    感谢您，干员%s。",name);
		getch(); system("cls");
		printf("\n\n    另一个世界再见。");
		Sleep(5000); system("cls");
		printf("\n\n    %s，卒",name);
		system("cls");
	}
	Color(2);
	printf("\n\n    %s已死亡，请重开",name);
	Sleep(3000);
}
//---------------------------
// Code By naijil2013 & zhaolt2012
int main() {
	First_Step();
	is_win=true;
	while(level<5 && is_win) {
		cnt_boom=max(3,cnt_boom);
		Welcome();
		x = 1, y = 1;
		flag = 1;
		print();
		start = time(0) ;
		while (true) {
			if(_kbhit()){
				k = getch();
				if (k == 'w') W();
				else if (k == 'a') A();
				else if (k == 's') S();
				else if (k == 'd') D();
				else if (k == ' ') Break_wall();
				else if (k == 'r') Get_Boom();
				if (f[x][y] == 2) val++, f[x][y] = 0;
				print(); 
				if (x == fx && y== fy) {
					system("cls");
					break;
				}
			}
			now = time(0) ;
			if(now-start>wait_time) {
				is_win=0;
				break;
			}
		}
		Ending(is_win);
	}
	THEEND(is_win);
	return 0;
}

// ----The End---
// 欢迎投稿 

