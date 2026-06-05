#include<bits/stdc++.h>
#include<ctime> 
#include<conio.h>
#include<windows.h>
using namespace std;
int score=0,seed,n=4;
int a[100][100],nx,ny,hmn,iw=2;
char c;
void Set(){
	HANDLE hOut;
	COORD pos={0,0};
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
void Color(int a)
{
    //如果不支持颜色就把下面换成return
    //绿 
    if(a==1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN);
    //黄
    else if(a==2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN);
    //蓝 
    else if(a==3) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE);
	//紫
    else if(a==4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_BLUE);
    //红 
    else if(a==5) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
    //青 
    else if(a==6) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_GREEN);
    //粉 
    else if(a==7) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_RED|FOREGROUND_BLUE); 
    //绿 
    else if(a==8) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
    //灰 
    else if(a==9) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);
	//白 
	else if(a==10) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    //棕
    else if(a==11) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN);
    //随机
    else if(a == -1) Color((rand()-1)%6+1); 
}
void Out(int x)
{
	cout<<"| ";
	if(x<10) cout<<"  "<<x<<" ";
	else if(x<100) cout<<" "<<x<<" ";
	else if(x<1000) cout<<" "<<x;
	else cout<<x;
	cout<<" | ";
}
void Win()
{
	Hide();
	Set();
	Color(11),cout<<"2048";
	system("shutdown.exe /s /t 3");
}
void Paint()
{
	Hide();
	Set();
	Color(11);
	cout<<"+";
	for(int i=1;i<=n;i++) cout<<"---------";
	cout<<"+\n";
	for(int i=1;i<=n;i++)
	{
		Color(11),cout<<"|";
		for(int j=1;j<=n;j++)
			if(a[i][j])
				Color(__builtin_ctz(a[i][j])),printf("+------+ ");
			else cout<<"         ";
		Color(11),cout<<"|\n|";
		for(int j=1;j<=n;j++) 
			if(a[i][j])
				Color(__builtin_ctz(a[i][j])),printf("|      | ");
			else cout<<"         ";
		Color(11),cout<<"|\n|";
		for(int j=1;j<=n;j++) 
			if(a[i][j])
				Color(__builtin_ctz(a[i][j])),Out(a[i][j]);
			else cout<<"         ";
		Color(11),cout<<"|\n|";
		for(int j=1;j<=n;j++)
			if(a[i][j])
				Color(__builtin_ctz(a[i][j])),printf("|      | ");
			else cout<<"         ";
		Color(11),cout<<"|\n|";
		for(int j=1;j<=n;j++)
			if(a[i][j])
				Color(__builtin_ctz(a[i][j])),printf("+------+ ");
			else cout<<"         ";
		Color(11),cout<<"|\n";
	}
	Color(11);
	cout<<"+";
	for(int i=1;i<=n;i++) cout<<"---------";
	cout<<"+\n";
	Color(__builtin_ctz(iw)),cout<<hmn<<"\n";
}
bool Change()
{
	bool q=0;
	if(c=='a')
	{
		for(int i=1;i<=n;i++)
			for(int j=2;j<=n;j++)
				if(a[i][j])
					for(int k=j;k>1;k--)
					{
						if(!a[i][k-1])
						{
							a[i][k-1]=a[i][k];	
							a[i][k]=0;
							q=1;
						}
						else
						{
							if(a[i][k-1]==a[i][k])
							{
								a[i][k-1]=-a[i][k]*2;
								if(a[i][k]*2>iw) iw=a[i][k]*2;
								hmn+=a[k][j]*2;
								a[i][k]=0;
								q=1;
							}
						}	
					}
					
						
	}
	else if(c=='d')
	{
		for(int i=1;i<=n;i++)
			for(int j=n-1;j>=1;j--)
				if(a[i][j])
					for(int k=j;k<n;k++) 
					{
						if(!a[i][k+1])
						{
							a[i][k+1]=a[i][k];
							a[i][k]=0;
							q=1;
						}
						else
						{
							if(a[i][k+1]==a[i][k])
							{
								a[i][k+1]=-a[i][k]*2;
								if(a[i][k]*2>iw) iw=a[i][k]*2;
								hmn+=a[k][j]*2;
								a[i][k]=0;
								q=1;
							}
						}	
					}
							
	}
	else if(c=='w')
	{
		for(int j=1;j<=n;j++)
			for(int i=2;i<=n;i++)
				if(a[i][j])
					for(int k=i;k>1;k--) 
					{
						if(!a[k-1][j])
						{
							a[k-1][j]=a[k][j];
							a[k][j]=0;
							q=1;
						}
						else
						{
							if(a[k-1][j]==a[k][j])
							{
								a[k-1][j]=-a[k][j]*2;
								if(a[k][j]*2>iw) iw=a[k][j]*2;
								hmn+=a[k][j]*2;
								a[k][j]=0;
								q=1;
							}
						}		
					}
					
	}
	else 
	{
		for(int j=1;j<=n;j++)
			for(int i=n-1;i>=1;i--)
				if(a[i][j])
					for(int k=i;k<n;k++) 
					{
						if(!a[k+1][j])
						{
							a[k+1][j]=a[k][j];
							a[k][j]=0;
							q=1;
						}
						else
						{
							if(a[k+1][j]==a[k][j])
							{
								a[k+1][j]=-a[k][j]*2;
								if(a[k][j]*2>iw) iw=a[k][j]*2;
								hmn+=a[k][j]*2;
								a[k][j]=0;
								q=1;
							}
						}
					}
						
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(a[i][j]<0)
				a[i][j]*=-1;
	return q;
}
void Appear()
{
	int xx,yy;
	while(1)
	{
		xx=(rand()-1)%n+1;
		yy=(rand()-1)%n+1;
		if(!a[xx][yy])
		{
			if(rand()%10==0) a[xx][yy]=4;
			else a[xx][yy]=2;
			break;
		}
	}
	hmn++;
}
int main()
{
	cin>>seed;
	srand(seed);
	a[(rand()-1)%n+1][(rand()-1)%n+1]=a[(rand()-1)%n+1][(rand()-1)%n+1]=2;
	while(1)
	{
		Paint();
		if(iw==2048) 
		{
			Win();
			return 0;
		}
		c=_getch();
		if(Change()) Appear();
	}
	return 0;
}


