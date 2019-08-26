#include<iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdio.h>

using namespace std;

#define cot 81
#define dong 26
#define luongnuocmax 600

enum TrangThaiB {LEFT,RIGHT};
struct DICHUYEN
{
 	int x,y;
 	int xb,yb;
 	TrangThaiB ttb;
};
void gotoxy(int x, int y);
void SetColor(WORD color);
void Huongdan();
void Khoitaonuoc(int nuoc[3][luongnuocmax],int luongnuoc);
void KhoitaoMau(int mau[cot][dong]);
void Taomap(char a[cot][dong]);
void Vemap(char a[cot][dong],int mau[cot][dong]);
void Dieukhien(DICHUYEN &A,char a[cot][dong],int boom[2][20],int &demboom,char &infi,int nuoc[3][luongnuocmax],int &luongnuoc,char &mua,char &godmode,int mau[cot][dong],int &color);

int main()
{
//Khai bao bien
	srand(time(NULL));
	DICHUYEN A;
	char a[cot][dong],infi='y',mua='n',godmode='n';
	int boom[2][20],demboom=0,nuoc[3][luongnuocmax],luongnuoc=1,mau[cot][dong],color=7;
	//khoi tao gia tri vi tri dau tien
	A.x=10;A.y=2;
	A.xb=20;A.yb=2;
//Khoi tao 
	SetColor(7);
	gotoxy(32,12);cout<<"     ~PIXEL CRAFT~      ";
	gotoxy(32,13);cout<<".Create your own Worlds.";
	gotoxy(60,27);cout<<"   Made By Hoang Tran";
	Huongdan();
	getch();
	KhoitaoMau(mau);
	Taomap(a);
	Vemap(a,mau);
	Khoitaonuoc(nuoc,luongnuoc);
//Start Game
	while(1)
	{
		Dieukhien(A,a,boom,demboom,infi,nuoc,luongnuoc,mua,godmode,mau,color);
	}
}
//Di chuyen con tro
void gotoxy(int x, int y)
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
}
//Ham tao mau
void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
 
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
 
    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;
 
    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void KhoitaoMau(int mau[cot][dong])
{
	for(int i=0;i<cot;i++)
		for(int j=0;j<dong;j++)
			mau[i][j]=7;
}
void Taomap(char a[cot][dong])
{ 
	int b[82];
	b[0]=rand()%10+15;
	for(int i=0;i<cot;i++)
	{ 
		b[i+1]=b[i]+rand()%3-rand()%3;
		if (b[i+1]<9) b[i+1]+=3;

		for(int j=0;j<dong;j++)
			if(j>=b[i])
				a[i][j]=char(178);
			else a[i][j]=' ';
	}
}
//Ve map tu mang a ra man hinh
void Vemap(char a[cot][dong],int mau[cot][dong])
{
	for(int i=0;i<cot;i++)
	{
	//Ve nui
		for(int j=0;j<dong;j++)
		{
			if(a[i][j]!=' ')
				SetColor(mau[i][j]);
			gotoxy(i,j);
			cout<<a[i][j];
		}
	}
	//Ve nen xanh ben duoi
	SetColor(9);
	for(int j=0;j<cot;j++)
	{
		gotoxy(j,26);
		cout<<char(223);
	}
}
//Ve lai map khi dich chuyen map
void Velaimap(char a[cot][dong],char huong,int mau[cot][dong])
{
	for(int j=0;j<dong;j++)//hoan vi cot 0 va cot 80
	{	if(huong=='t')
			{if(a[0][j]!=a[80][j])
				{gotoxy(80,j);SetColor(mau[0][j]);cout<<a[0][j];}}
		else if(huong=='p')
			{if(a[80][j]!=a[0][j])
				{gotoxy(0,j);SetColor(mau[80][j]);cout<<a[80][j];}}		
	}

	for(int j=0;j<dong;j++)//Hoan vi nhung cot con lai
		if(huong=='p')
		{
			for(int i=1;i<=80;i++)	
				if(a[i][j]!=a[i-1][j])
				{
					gotoxy(i,j);SetColor(mau[i-1][j]);cout<<a[i-1][j];
				}
				else if(mau[i][j]!=mau[i-1][j])
				{
					SetColor(mau[i-1][j]);
					gotoxy(i,j);cout<<char(178);
				}
		} else if(huong=='t')
		{
			for(int i=79;i>=0;i--)	
				if(a[i][j]!=a[i+1][j])
				{
					gotoxy(i,j);SetColor(mau[i+1][j]);cout<<a[i+1][j];
				}else if(mau[i][j]!=mau[i+1][j])
				{
					SetColor(mau[i+1][j]);
					gotoxy(i,j);cout<<char(178);
				}
		}
}
//Dich chuyen gia tri cua mang a
void DichchuyenMap(char a[cot][dong],char huongdichchuyen,int nuoc[3][luongnuocmax],int luongnuoc,int mau[cot][dong])
{
	SetColor(9);
	if(huongdichchuyen=='p')
	{
		for(int n=0;n<luongnuoc-1;n++)//Dich chuyen nuoc
		{
			gotoxy(nuoc[0][n],nuoc[1][n]);
			cout<<" ";
			nuoc[0][n]++;
			if(nuoc[0][n]>80) nuoc[0][n]=0;
			gotoxy(nuoc[0][n],nuoc[1][n]);
			cout<<char(178);
		}
	}else if(huongdichchuyen=='t')
	{
		for(int n=0;n<luongnuoc-1;n++)//Dich chuyen nuoc
		{
			gotoxy(nuoc[0][n],nuoc[1][n]);
			cout<<" ";
			nuoc[0][n]--;
			if(nuoc[0][n]<0) nuoc[0][n]=80;
			gotoxy(nuoc[0][n],nuoc[1][n]);
			cout<<char(178);
		}
	}
	Velaimap(a,huongdichchuyen,mau);
	char tam[26],mautam[26];
	if(huongdichchuyen=='t')
	{
		//Dich chuyen mau
		for(int cot1=0;cot1<=25;cot1++)
			mautam[cot1]=mau[0][cot1];
		for(int o=0;o<80;o++)
			for(int k=0;k<=25;k++)
				mau[o][k]=mau[o+1][k];
		for(int travemau=0;travemau<=25;travemau++)
			mau[80][travemau]=mautam[travemau];
		//Dich chuyen vat the
		for(int cotmot=0;cotmot<=25;cotmot++)//gan gia tri cot 0 cho mang tam
			tam[cotmot]=a[0][cotmot];
		for(int i=0;i<80;i++)//Dich chuyen gia tri
			for(int j=0;j<=25;j++)
		 		a[i][j]=a[i+1][j];
		for(int trave=0;trave<=25;trave++)//tra lai gia tri cot 0
		 	a[80][trave]=tam[trave];
	}
	else if(huongdichchuyen=='p')
	{
		//Dich chuyen mau
		for(int cotcuoi=0;cotcuoi<=25;cotcuoi++)
			mautam[cotcuoi]=mau[80][cotcuoi];
		for(int o=80;o>0;o--)
			for(int k=0;k<=25;k++)
				mau[o][k]=mau[o-1][k];
		for(int travemau=0;travemau<=25;travemau++)
			mau[0][travemau]=mautam[travemau];
		//Dich chuyen vat the
		for(int cot80=0;cot80<=25;cot80++)//gan gia tri cot 80 cho mang tam
		 	tam[cot80]=a[80][cot80];
		for(int i=80;i>0;i--)//Dich chuyen gia tri
		 	for(int j=0;j<=25;j++)
			a[i][j]=a[i-1][j];
		for(int trave=0;trave<=25;trave++)//tra lai gia tri cot 80
			a[0][trave]=tam[trave];
	}
}
//Danh dau
void Danhdau(DICHUYEN A,int boom[2][20],char huongboom,int &demboom,int color,int mau[cot][dong])
{
	gotoxy(70,0);cout<<"Danhdau:";
	if(19-demboom<10) cout<<" "<<19-demboom;
	else if(19-demboom>=10) cout<<19-demboom;

	int x,y;//Vi tri danh dau
	if(huongboom=='i') { x=A.x; y=A.y-1;}
	else if(huongboom=='j') { x=A.x-1; y=A.y;}
	else if(huongboom=='k') { x=A.x; y=A.y+1;}
	else if(huongboom=='l') { x=A.x+1; y=A.y;}
	if(x>0&&x<80&&y>0&&y<26)
	{
		SetColor(color);
		gotoxy(x,y);cout<<"#";//Danh dau
		boom[0][demboom]=x;//Luu vi tri 
		boom[1][demboom]=y;
		mau[x][y]=color;
		demboom++;
		if(demboom>19) demboom--;
	}
}
//Kich hoat bom tai vi tri danh dau
void Nobom(char a[cot][dong],int boom[2][20],int &demboom,int mau[cot][dong])
{
	for(int i=0;i<demboom;i++)
	{
 	//Ve vu no +gan gia tri " " vao mang a +xoa mau
		//Gan gia tri trong
		a[boom[0][i]][boom[1][i]]=' ';
		a[boom[0][i]+1][boom[1][i]+1]=' ';
		a[boom[0][i]+1][boom[1][i]-1]=' ';
		a[boom[0][i]-1][boom[1][i]-1]=' ';
		a[boom[0][i]-1][boom[1][i]+1]=' ';
		a[boom[0][i]+1][boom[1][i]]=' ';
		a[boom[0][i]-1][boom[1][i]]=' ';
		a[boom[0][i]][boom[1][i]+1]=' ';
		a[boom[0][i]][boom[1][i]-1]=' ';
		//Xoa mau
		mau[boom[0][i]][boom[1][i]]=7;
		mau[boom[0][i]+1][boom[1][i]+1]=7;
		mau[boom[0][i]+1][boom[1][i]-1]=7;
		mau[boom[0][i]-1][boom[1][i]-1]=7;
		mau[boom[0][i]-1][boom[1][i]+1]=7;
		mau[boom[0][i]+1][boom[1][i]]=7;
		mau[boom[0][i]-1][boom[1][i]]=7;
		mau[boom[0][i]][boom[1][i]+1]=7;
		mau[boom[0][i]][boom[1][i]-1]=7;

		gotoxy(boom[0][i]+1,boom[1][i]);
		cout<<"@";
		gotoxy(boom[0][i]-1,boom[1][i]);
		cout<<"@";
		gotoxy(boom[0][i],boom[1][i]+1);
		cout<<"@";
		gotoxy(boom[0][i],boom[1][i]-1);
		cout<<"@";
		//Tam ngung
	 	Sleep(50);
		//Canh hinh vuong
		gotoxy(boom[0][i]+1,boom[1][i]);
		cout<<" ";
		gotoxy(boom[0][i]-1,boom[1][i]);
		cout<<" ";
		gotoxy(boom[0][i],boom[1][i]+1);
		cout<<" ";
		gotoxy(boom[0][i],boom[1][i]-1);
		cout<<" "; 
		gotoxy(boom[0][i],boom[1][i]);
		cout<<" "; 
		//Goc hinh vuong
		gotoxy(boom[0][i]+1,boom[1][i]+1);
		cout<<" ";
		gotoxy(boom[0][i]-1,boom[1][i]+1);
		cout<<" ";
		gotoxy(boom[0][i]+1,boom[1][i]-1);
		cout<<" ";
		gotoxy(boom[0][i]-1,boom[1][i]-1);
		cout<<" "; 
	}
 	//Ve nuoc
	for(int j=0;j<=80;j++)
	{
		SetColor(9); 
		gotoxy(j,26);cout<<char(223);
	}
	SetColor(7);
	demboom=0;
}
//Xoa 1 o
void Xoa1da(char a[cot][dong],int boom[2][20],int &demboom,int mau[cot][dong])
{
	for(int i=0;i<demboom;i++)
	{
		gotoxy(boom[0][i],boom[1][i]);
		cout<<" ";
		a[boom[0][i]][boom[1][i]]=' ';
		mau[boom[0][i]][boom[1][i]]=7;
	}
	demboom=0;
}
//Chuyen nhung vi tri danh dau thanh da
void ThemDa(char a[cot][dong],int boom[2][20],int &demboom,int mau[cot][dong])
{
	for(int i=0;i<demboom;i++)
	{
		//Ve nhung khoi da moi
		SetColor(mau[boom[0][i]][boom[1][i]]);
		gotoxy(boom[0][i],boom[1][i]);
		cout<<char(178);
		//Gan gia tri
		a[boom[0][i]][boom[1][i]]=char(178);
	}
	demboom=0;
}
//Nhay len khi an Q E W
void Nhay(DICHUYEN &A,char a[cot][dong],char huong,char godmode,int mau[cot][dong])
{
	if(godmode=='y')
	{
		if(huong=='w')
		{
			if(A.y>=1&&a[A.x][A.y-1]==' '||mau[A.x][A.y-1]%16-6==0) 
			{	
				gotoxy(A.x,A.y);
				cout<<" ";//Xoa vi tri cu
				A.y--;
				gotoxy(A.x,A.y);
				cout<<"A";//Ve vi tri moi
			}
		}
		else if(huong=='s')
		{
			if(A.y>=0&&a[A.x][A.y+1]==' ') 
			{	
				gotoxy(A.x,A.y);
				cout<<" ";//Xoa vi tri cu
				A.y++;
				gotoxy(A.x,A.y);
				cout<<"A";//Ve vi tri moi
			}
		}
	}else if(godmode=='n')
	{

		gotoxy(A.x,A.y);
		cout<<" ";//Xoa vi tri cu
		//Nhay sang phai
		if(huong=='e')
		{
			for(int i=1;i<=4;i++)
			{
				gotoxy(A.x,A.y);cout<<" ";
				if((a[A.x][A.y-1]==' '||mau[A.x][A.y-1]%16-6==0)&&A.y>0)
					A.y--;
				if(a[A.x+1][A.y]==' '||mau[A.x+1][A.y]%16-6==0)
					A.x++;
				gotoxy(A.x,A.y);cout<<"A";
			}
		}
		//Nhay sang trai
		else if(huong=='q')
		{
			for(int i=1;i<=4;i++)
			{
				gotoxy(A.x,A.y);cout<<" ";
				if((a[A.x][A.y-1]==' '||mau[A.x][A.y-1]%16-6==0)&&A.y>0)
					A.y--;
				if(a[A.x-1][A.y]==' '||mau[A.x-1][A.y]%16-6==0)
					A.x--;
				gotoxy(A.x,A.y);cout<<"A";
			}
		}
		//Nhay len tren
		else if(huong=='w'&&godmode=='n')
		{
			for(int i=1;i<=4;i++)
			{
				if((a[A.x][A.y-1]==' '||mau[A.x][A.y-1]%16-6==0)&&A.y>0)
				A.y--;
			}
		}
		gotoxy(A.x,A.y);
		cout<<"A";//Ve vi tri moi
		Sleep(0);
	}
}
//Khoi tao gia tri cua mang nuoc
void Khoitaonuoc(int nuoc[3][luongnuocmax],int luongnuoc)
{
	for(int i=0;i<luongnuoc-1;i++)
	{
		nuoc[0][i]=40;
		nuoc[1][i]=rand()%8;
		nuoc[2][i]=rand()%3;//xuong_0  trai_1  phai_2
	}
}
//Ham tao hieu ung nuoc tuong tac voi nhau
int Tuongtacnuoc(int nuoc[3][luongnuocmax],int luongnuoc,int x,int y)
{
	for(int i=0;i<luongnuoc-1;i++)
	{
		if(nuoc[0][i]==x&&nuoc[1][i]==y)
			return 1;
	}
	return 0;
}
//Xoa vi tri cu cua nuoc
void Xoanuoccu(int nuoc[3][luongnuocmax],int i)
{
	gotoxy(nuoc[0][i],nuoc[1][i]);
	cout<<" ";
}
//Xet xem tai vi tri (x,y) co vat can gi hay khong
int Empty(DICHUYEN A,char a[cot][dong],int nuoc[3][luongnuocmax],int luongnuoc,int x,int y)
{
	return (!Tuongtacnuoc(nuoc,luongnuoc,x,y)&&a[x][y]==' '&&((x!=A.x)||(y!=A.y))&&((x!=A.xb)||(y!=A.yb)));
}
//Tao hieu ung nuoc chuyen dong
void Nuocchay(DICHUYEN A,char a[cot][dong],int nuoc[3][luongnuocmax],int luongnuoc)
{
	for(int i=0;i<luongnuoc-1;i++)
	{
		if(nuoc[1][i]==25) 
		{
			Xoanuoccu(nuoc,i);
			nuoc[0][i]=40;nuoc[1][i]=rand()%8;
		}
		else if(Empty(A,a,nuoc,luongnuoc,nuoc[0][i],nuoc[1][i]+1))
		{
			nuoc[2][i]=0;
		}
		else if(Empty(A,a,nuoc,luongnuoc,nuoc[0][i]+1,nuoc[1][i])&&!Empty(A,a,nuoc,luongnuoc,nuoc[0][i]-1,nuoc[1][i]))
		{
			nuoc[2][i]=2;
		}else if(Empty(A,a,nuoc,luongnuoc,nuoc[0][i]-1,nuoc[1][i])&&!Empty(A,a,nuoc,luongnuoc,nuoc[0][i]+1,nuoc[1][i]))
		{
			nuoc[2][i]=1;
		}else if(Empty(A,a,nuoc,luongnuoc,nuoc[0][i]-1,nuoc[1][i])&&Empty(A,a,nuoc,luongnuoc,nuoc[0][i]+1,nuoc[1][i])&&!Empty(A,a,nuoc,luongnuoc,nuoc[0][i],nuoc[1][i]+1)&&Empty(A,a,nuoc,luongnuoc,nuoc[0][i]+1,nuoc[1][i]+1))
		{
			nuoc[2][i]=rand()%2+1;
		}

		SetColor(9);

		if(nuoc[2][i]==0&&Empty(A,a,nuoc,luongnuoc,nuoc[0][i],nuoc[1][i]+1)) {Xoanuoccu(nuoc,i);nuoc[1][i]++;}
		else if(nuoc[2][i]==1&&Empty(A,a,nuoc,luongnuoc,nuoc[0][i]-1,nuoc[1][i])) {Xoanuoccu(nuoc,i);nuoc[0][i]--;}
		else if(nuoc[2][i]==2&&Empty(A,a,nuoc,luongnuoc,nuoc[0][i]+1,nuoc[1][i])) {Xoanuoccu(nuoc,i);nuoc[0][i]++;}

		gotoxy(nuoc[0][i],nuoc[1][i]);
 		cout<<char(178);
	}
}
//Luu map hien tai
void LuuMap(char a[cot][dong],char namemap[10],int mau[cot][dong])
{
	FILE *map=fopen(namemap,"wt");
	for(int i=0;i<cot;i++)
		for(int j=0;j<dong;j++)	
			fprintf(map,"%d %d\n",a[i][j],mau[i][j]);
	gotoxy(59,0);cout<<"                     ";
	gotoxy(59,0);cout<<"       Luu thanh cong";
	getch();
	gotoxy(59,0);cout<<"                     ";
	fclose(map);
}
//Mo map da luu
void Loadmap(char a[cot][dong],char namemap[10],int mau[cot][dong])
{
	FILE *map=fopen(namemap,"rt");
	if(map==NULL) 
	{
		fclose(map);
		gotoxy(59,0);cout<<"                     ";
		gotoxy(60,0);cout<<"File not found";getch();
		gotoxy(60,0);cout<<"              ";
	}else
	{
		for(int i=0;i<cot;i++)
			for(int j=0;j<dong;j++)	
				fscanf(map,"%d %d",&a[i][j],&mau[i][j]);
		fclose(map);
		Vemap(a,mau);
	}
}
void Huongdan()
{
	SetColor(7);
	gotoxy(0,0);
	cout<<"  A D  :Move\n";
	cout<<" Q W E :Jump-Left/Up/Right\n";
	cout<<"   M   :Menu\n";
	cout<<"   O   :On-off Loop Map \n";
	cout<<"  X C  :Change Color\n";
	cout<<"I J K L:Marked\n";
	cout<<"   R   :Delete all marker places\n";  
	cout<<"   T   :Add rock to all marker places\n";  
	cout<<"   B   :Activate bombs at all marker places\n";
	cout<<" N < > :On-off water/decrease water/increase water\n";
	cout<<"   G   :Godmode.";
	gotoxy(0,27);
	cout<<"   H   :Huong dan.";
}
//Ham Dieu Khien chinh cua chuong trinh
void Dieukhien(DICHUYEN &A,char a[cot][dong],int boom[2][20],int &demboom,char &infi,int nuoc[3][luongnuocmax],int &luongnuoc,char &mua,char &godmode,int mau[cot][dong],int &color)
{
//Dieu khien nhan vat A + Cac phim nong
	//Ve nhan vat
	SetColor(7);
	gotoxy(A.xb,A.yb);
	cout<<"B";
	gotoxy(A.x,A.y);
	if(godmode=='y')
		SetColor(11);
	cout<<"A";
	SetColor(7);
	//Nhan phim
	if(kbhit())
	{
		char key=getch();
		if(key=='m') //Menu
		{
			gotoxy(59,0);cout<<"New/Save/Open(n/s/o) ";
			char newmap=getch();
			if(newmap=='n')
			{
				A.x=10;A.y=2;
				A.xb=20;A.yb=2;
				KhoitaoMau(mau);
				Taomap(a);
				Vemap(a,mau);
				demboom=0;
				if(mua=='y')
					Khoitaonuoc(nuoc,luongnuoc);
			}
			else if(newmap=='s')//Save map
			{
				char namemap[10];
				gotoxy(59,0);cout<<"                     ";
				gotoxy(59,0);cout<<"Name Map:";cin>>namemap;
				if(namemap[0]!='b'&&strlen(namemap)!=1)
				LuuMap(a,namemap,mau);
				else 
				{
					gotoxy(59,0);cout<<"                     ";
					gotoxy(59,0);cout<<"   Huy luu thanh cong";
					getch();
					gotoxy(59,0);cout<<"                     ";
				}
			}
			else if(newmap=='o')//Open map
			{
				char namemap[10];
				gotoxy(59,0);cout<<"                     ";
				gotoxy(59,0);cout<<"Name Map:";cin>>namemap;
				Loadmap(a,namemap,mau);
				if(mua=='y')
				Khoitaonuoc(nuoc,luongnuoc);
				gotoxy(A.x,A.y);cout<<" ";
				gotoxy(A.xb,A.yb);cout<<" ";
				A.x=10;A.y=2;
				A.xb=20;A.yb=2;
			}
			else {gotoxy(59,0);cout<<"                     ";}
		}
		else if(key=='a')//Di sang trai
		{
			gotoxy(A.x,A.y);cout<<" ";
			if(a[A.x-1][A.y]==' '||mau[A.x-1][A.y]%16-6==0)//Mat dat bang phang
				A.x--;
			else if(a[A.x-1][A.y-1]==' ')//Mat dat nho cao 1 don vi 
			{	A.x--;A.y--;}
			gotoxy(A.x,A.y);cout<<"A"; 
		}
		else if(key=='d')//Di sang phai 
		{
			gotoxy(A.x,A.y);cout<<" ";
			if(a[A.x+1][A.y]==' '||mau[A.x+1][A.y]%16-6==0)//Mat dat bang phang
				A.x++;
			else if(a[A.x+1][A.y-1]==' ')//Mat dat nho cao 1 don vi 
			{	A.x++;A.y--;}
			gotoxy(A.x,A.y);cout<<"A"; 
		}
		else if(key=='e')  Nhay(A,a,'e',godmode,mau);//Nhay sang phai
		else if(key=='q')  Nhay(A,a,'q',godmode,mau);//Nhay sang trai
		else if(key=='w')  Nhay(A,a,'w',godmode,mau);//Nhay len tren
		else if(key=='s')  Nhay(A,a,'s',godmode,mau);//Di xuong _trong che do godmode
		//Dat boom + danh dau
		else if(key=='i')   Danhdau(A,boom,'i',demboom,color,mau);
		else if(key=='j')   Danhdau(A,boom,'j',demboom,color,mau);
		else if(key=='k')   Danhdau(A,boom,'k',demboom,color,mau);
		else if(key=='l')   Danhdau(A,boom,'l',demboom,color,mau);
		//No boom
		else if(key=='b')   Nobom(a,boom,demboom,mau);
		//Xoa 1 da
		else if(key=='r')	Xoa1da(a,boom,demboom,mau);
		//Them da vao map
		else if(key=='t')   ThemDa(a,boom,demboom,mau);
		//Chinh mau
		else if(key=='x')	{color--;SetColor(color);gotoxy(39,27);cout<<"Mau:   ";gotoxy(43,27);cout<<color;}
		else if(key=='c')	{color++;SetColor(color);gotoxy(39,27);cout<<"Mau:   ";gotoxy(43,27);cout<<color;}
		//Vong lap map
		else if(key=='o')   {if(infi=='y') infi='n';else infi='y';gotoxy(70,0);cout<<"LoopMap: "<<infi;}
		//Mua
		else if(key=='n')	{if(mua=='y') mua='n'; else mua='y';}
		else if(key=='.')  	{mua='y';nuoc[0][luongnuoc-1]=A.x;nuoc[1][luongnuoc-1]=A.y-1;luongnuoc++;if(luongnuoc>luongnuocmax) luongnuoc--;}
		else if(key==',')  	{mua='y';luongnuoc--;if(luongnuoc<1) luongnuoc=1; else {gotoxy(nuoc[0][luongnuoc-1],nuoc[1][luongnuoc-1]);cout<<" ";}}
		//Che do godmode
		else if(key=='g') 	{if(godmode=='y') godmode='n'; else godmode='y';gotoxy(70,0);cout<<"Godmode: "<<godmode;}
		//Huong dan
		else if(key=='h') 	{Huongdan();getch();Vemap(a,mau);}
	}
	Sleep(25);
	//Update vi tri roi
	if((a[A.x][A.y+1]==' '||mau[A.x][A.y+1]%16-6==0)&&A.y<=24&&godmode=='n')
	{
		gotoxy(A.x,A.y);cout<<" ";//Xoa vi tri cu cua A
		A.y++;//Hieu ung roi xuong
	}
//Ve lai nhung o co mau
	if(mau[A.x+1][A.y]%16-6==0&&a[A.x+1][A.y]==char(178)) {gotoxy(A.x+1,A.y);SetColor(6);cout<<char(178);}
	if(mau[A.x-1][A.y]%16-6==0&&a[A.x-1][A.y]==char(178)) {gotoxy(A.x-1,A.y);SetColor(6);cout<<char(178);}
	if(mau[A.x][A.y+1]%16-6==0&&a[A.x][A.y+1]==char(178)) {gotoxy(A.x,A.y+1);SetColor(6);cout<<char(178);}
	if(mau[A.x][A.y-1]%16-6==0&&a[A.x][A.y-1]==char(178)) {gotoxy(A.x,A.y-1);SetColor(6);cout<<char(178);}
	
	if(mau[A.x-1][A.y-1]%16-6==0&&a[A.x-1][A.y-1]==char(178)) {gotoxy(A.x-1,A.y-1);SetColor(6);cout<<char(178);}
	if(mau[A.x+1][A.y-1]%16-6==0&&a[A.x+1][A.y-1]==char(178)) {gotoxy(A.x+1,A.y-1);SetColor(6);cout<<char(178);}
	if(mau[A.x-1][A.y+1]%16-6==0&&a[A.x-1][A.y+1]==char(178)) {gotoxy(A.x-1,A.y+1);SetColor(6);cout<<char(178);}
	if(mau[A.x+1][A.y+1]%16-6==0&&a[A.x+1][A.y+1]==char(178)) {gotoxy(A.x+1,A.y+1);SetColor(6);cout<<char(178);}
//Phan Dieu khien nhan vat B
	//Xu ly cham bien
	if(A.xb<0) {gotoxy(A.xb,A.yb);cout<<" ";A.xb=80;}
	else if(A.xb>80) {gotoxy(A.xb,A.yb);cout<<" ";A.xb=0;}
	//Hieu ung roi B
	else if(a[A.xb][A.yb+1]==' '&&A.yb<=24)
	{
		gotoxy(A.xb,A.yb);cout<<" ";
		A.yb++;
	}
	//Nhay
	else if(rand()%10==5)
	{
		gotoxy(A.xb,A.yb);cout<<" ";
		//Xac dinh huong di cua b
		if(A.xb<A.x) A.ttb=RIGHT;
		else if(A.xb>A.x) A.ttb=LEFT;
		//Di chuyen b
		if(A.ttb==LEFT)
		{
			if(a[A.xb-1][A.yb]==' ')
				A.xb--;
			else for(int i=1;i<=4;i++)
					{
						gotoxy(A.xb,A.yb);cout<<" ";
						if(a[A.xb][A.yb-1]==' ')
							A.yb--;
						if(a[A.xb-1][A.yb]==' ')
							A.xb--;
						gotoxy(A.xb,A.yb);cout<<"B";
					}
		}
		else if(A.ttb==RIGHT)
		{
			if(a[A.xb+1][A.yb]==' ')
				A.xb++;
			else for(int i=1;i<=4;i++)
					{
						Sleep(2);
						gotoxy(A.xb,A.yb);cout<<" ";
						if(a[A.xb][A.yb-1]==' ')
							A.yb--;
						if(a[A.xb+1][A.yb]==' ')
							A.xb++;
						gotoxy(A.xb,A.yb);cout<<"B";
					}
		}
	}
//Hieu ung
	//Dich chuyen map
	if(infi=='y')
	{
		if(A.x>=79) 
		{
			gotoxy(A.x,A.y);cout<<" ";
			gotoxy(A.xb,A.yb);cout<<" ";
			DichchuyenMap(a,'t',nuoc,luongnuoc,mau);
			A.x--;A.xb--;
		}
		else if(A.x<=1) 
		{
			gotoxy(A.x,A.y);cout<<" ";
			gotoxy(A.xb,A.yb);cout<<" ";
			DichchuyenMap(a,'p',nuoc,luongnuoc,mau);
			A.x++;A.xb++;
		}
	}
	//Hieu ung nuoc
	if(mua=='y')
		Nuocchay(A,a,nuoc,luongnuoc);
}

