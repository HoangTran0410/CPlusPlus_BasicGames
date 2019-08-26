#include<iostream>//Nhap lieu co ban + cac ham can thiet
#include<string.h>//Tao chuoi , cac ham ve chuoi
#include<conio.h>//Dung cho SetColor, gotoxy ....
#include<windows.h>
#include<time.h>//Dung de khoi tao ngau nhien
using namespace std; //Danh cho DEV C

enum TrangThai {UP,DOWN,LEFT,RIGHT};

struct ChuChay
{
	int x,y;
	int xhq,yhq;	
	int xe,ye;
	TrangThai tt;
};
void gotoxy(int x, int y);//Di chuyen con tro toi vi tri (x,y) tren man hinh
void SetColor(WORD color);//Ham tao mau sac
void KhoiTao(ChuChay &A);//Khoi tao gia tri ban dau cho vi tri
void Huong_Dan();//Hien thi huong dan len man hinh
void CheDochoi(ChuChay &A,int chedo,char vatpham[]);//Cach di chuyen cua vatpham qua tung che do khac nhau >=2
void xoamanhinh();//Xoa man hinh (xoa tu dau cho toi het dong 23)
void XoaMenu();//Xoa khung Menu
void Khoitao_Hieuung(int a[20][2],char achuoi[3]);//Hieu ung tuyet roi
void Hieuung(int a[20][2],char achuoi[3]);//Ve hieu ung tuyet roi
void Reset_Hieuung(int a[20][2]);//Xoa va tao moi hieu ung
void Ban_sung(ChuChay A,char ten[],char key);
void Tao_Kedich(ChuChay &A,char kedich[],int maukedich);
void NgauNhien_dich(ChuChay &A);//Khoi tao ke dich ngau nhien
void Kedich_boom(ChuChay A);//Ve cam giac vu no sau khi ban trung ke dich
void Ban_chet(ChuChay &A,char key,char ten[],char kedich[], int &diem,int &dieme);
void Tao_acsii();//Tao bang ma ki tu ACSII
void Menu(int &bien_return);//Hien thi Menu
void SelectColor(int y,int &maukitu,int &maukedich,int &mauvatpham,int &bien_return);//Ham chon mau cho Menu ChangeColor
void ChangeColor(int &maukitu,int &maukedich,int &mauvatpham,int &bien_return);// Hien thi Menu thay doi mau sac
void Nhaptenmap(char filename[]);
void VeMap(char filename[]);

// LET'S GO
int main()
{
//Khoi tao mang 2 chieu dung cho hieu ung tuyet roi
	int a[20][2];
	char hoi;
do
{	srand(time(NULL));//Khoi tao bo sinh so ngau nhien

//Khai bao bien
	ChuChay A;
	int chedo=1,diem=0,diem2=0,dieme=0,delay=150,tam_hieuung=1,bien_return=0,maukitu=3,mauvatpham=10,maukedich=13,hienkd,hienkedich,acsii;
	char ten[10],vatpham[10],dich,kedich[10],achuoi[3],filename[20],aichoi;
	
//Nhap thong tin
	SetColor(7);
	do//Nhap ten
	{
		gotoxy(0,0);
		for(int i=1;i<=80;i++)
			cout<<" ";
		gotoxy(0,0);
		cout<<"Your charater:";cin>>ten;
		//Truong hop ACSII
		if(ten[0]=='?'&&strlen(ten)==1) 
		{	
			Tao_acsii();
			cout<<"Enter ACSII code (?=63):";
			cin>>acsii;ten[0]=char(acsii);
		}
		if(strlen(ten)>5) 
		{
			gotoxy(0,0);
			cout<<"String length must < 6!!";
			getch();		//Gioi han do dai ten

		}
	}while(strlen(ten)>5);

	cout<<"Items:";cin>>vatpham;
	//Vat pham la ki tu lay tu bang ma ACSII
	if(vatpham[0]=='?'&&strlen(vatpham)==1) 
	{	
		Tao_acsii();
		cout<<"Enter ACSII code (?=63):";
		cin>>acsii;vatpham[0]=char(acsii);
	}

	cout<<"Do you want Enemy ? (y/n): ";cin>>dich;

//Khoi tao vi tri ban dau cho ke dich +hinh dang ke dich
	if(dich=='y'||dich=='Y')
	{
		hienkd=1;
		hienkedich=1;
		NgauNhien_dich(A);
		cout<<"Enemy character: ";
		cin>>kedich;
		if(kedich[0]=='?'&&strlen(kedich)==1) 
		{	
			Tao_acsii();
			cout<<"Enter ACSII code (?=63):";
			cin>>acsii;kedich[0]=char(acsii);	
		}
	}
	else {//Tranh truong hop toa do ten trung voi toa do ke dich
		hienkedich=0;
		hienkd=-1;
		kedich[0]='H';
		A.xe=0;
		A.ye=25;
	}

//Khoi tao hieu ung tuyet roi = 0
	char hieu_ung='n';
	Khoitao_Hieuung(a,achuoi);
		
//Khoi tao chuong trinh
	system("cls");
	KhoiTao(A);	
	xoamanhinh();
	Huong_Dan();
	getch();
	xoamanhinh();
	aichoi='1';//Khoi tao aichoi= nguoi choi

//Ve bien duoi
	SetColor(8);
	gotoxy(0,23);
	for(int i=0;i<=80-1;i++)
		cout<<char(176);

do
{	
VONGLAP:while(1)
	{

	//Ve che do 
		char chedotext[7];
		if(chedo==1) strcpy(chedotext,"EASY");
		else if(chedo==2) strcpy(chedotext,"HARD");
		else if(chedo==3) strcpy(chedotext,"VERY HARD");
		else itoa(chedo,chedotext,10);
		SetColor(8);
		gotoxy(0,0);
		cout<<"Mode: "<<chedotext;
		if(aichoi=='2') cout<<"(auto)";
		else 			cout<<"         ";
		
	//Ve diem so
		SetColor(8);
		gotoxy(0,1);
		cout<<"Collected: ";
		SetColor(15);
		gotoxy(11,1);
		cout<<"  ";
		gotoxy(11,1);
		cout<<diem;
		gotoxy(14,1);
		SetColor(8);
		cout<<"/20 "<<"'"<<vatpham<<"'";

	//Ve toc do
		SetColor(8);
		gotoxy(8,2);//Xoa toc do cu
		cout<<"    ";
		gotoxy(0,2);
		cout<<"Speed: ";
		if(delay<=10) delay=10;
		if(150-delay>90) SetColor(12);
		cout<<150-delay;//Ve toc do moi

	//Co vu
		SetColor(6);
		gotoxy(0,3);
		if(diem2<=6)
		{	
			switch(diem2)
			{
				case 0:cout<<"Let's collect green items ";break;
				case 1:cout<<"Be careful and stay away from monsters!";break;
				case 2:cout<<"They are pink and will steal your items!";break;
				case 3:cout<<"Use your gun to shoot the monsters      ";break;
				case 4:cout<<"Or maybe use your gun to clean up the way";break;
				case 5:cout<<"Collect enough items and WIN             ";break;
				case 6:cout<<"Good Luck !                  ";break;
			}
		}

	//Ve ke dich
		if(hienkedich==1)
		{
			SetColor(maukedich);
			gotoxy(A.xe,A.ye);
			cout<<kedich;
		}
		
	//Ve vat pham
		SetColor(mauvatpham);
		if(chedo==1)
		{
			gotoxy(A.xhq,A.yhq);
			cout<<vatpham;
		}
		else if(chedo>=2)
 		CheDochoi(A,chedo-1,vatpham);		

	//Ve ki tu 
	 	SetColor(maukitu);
	 	gotoxy(A.x, A.y);
		cout<<ten;

	//Ve hieu ung (neu co)
		if(hieu_ung=='y')
		Hieuung(a,achuoi);
		
	//Thang -thua
		int e=0;
		if((A.y==A.ye)&&hienkedich==1)//vi tri Ke dich trung Ten => tru diem
			for(int i=A.x;i<A.x+strlen(ten);i++)
				for(int j=A.xe;j<A.xe+strlen(kedich);j++)
					if(i==j)
						e=1;
		if(e) 
		{
			SetColor(12);
			gotoxy(11,1);
			cout<<diem;
			Sleep(200);
			SetColor(15);
			gotoxy(11,1);
			cout<<diem;
			diem--;
			dieme++;
		}

		if(diem<0)//LOSE
		{
			SetColor(11);
			gotoxy(33,12);
			cout<<"<==LOSER==>";
			diem++;
			break;
		}

		else if(diem>=20&&chedo>=3)//Win
		{
			SetColor(10);
			gotoxy(35,12);
			cout<<"'-_WINER_-'\n\n";
			break;
		}else
		if(diem>=20)//Win 1 man
		{	
			SetColor(10);
			gotoxy(35,11);
			cout<<" -----------";
			gotoxy(35,12);
			cout<<"|WIN State "<<chedo<<"|";
			gotoxy(35,13);
			cout<<" -----------";
		//Hieu ung sau khi thang 1 man
			SetColor(15);
			for(int i=4;i>=1;i--)
			{
				gotoxy(40,15);
				cout<<i;
				for(int j=41;j<=44;j++)
				{
					gotoxy(j,15);
					cout<<".";
					Sleep(100);
				}
				Sleep(600);
				gotoxy(40,15);
				cout<<"       ";
			}
		//Reset + qua man choi moi
			xoamanhinh();
			delay=150;
			chedo++;
			diem=0;
			diem2=0;//diem2 Dung cho Co vu
			dieme=0;
		} 
		

	//An vat pham
	 	int vitri;
		 for(int i=0;i<strlen(ten);i++)
	 	{
	 		vitri=A.x+i;
	 		if((vitri>=A.xhq)&&(vitri<=A.xhq+strlen(vatpham)-1)&&(A.y==A.yhq))
			{
				gotoxy(A.xhq,A.yhq);
				for(int i=1;i<=strlen(vatpham);i++)
					cout<<" ";
				A.xhq=rand()%77+1;
				A.yhq=rand()%23;
				diem++;
				diem2++;
		//Tang toc khi an duoc vat pham (tuy chon)
				delay-=10;
			}
		}
				
//Dieu khien 
	//Nguoi choi
		if (aichoi=='1')
		{	
			if (kbhit())
			{
				char key=getch();
				if(key=='a'||key=='A')
				A.tt=LEFT;
				else if(key=='w'||key=='W')
				A.tt=UP;
				else if(key=='s'||key=='S')
				A.tt=DOWN;
				else if(key=='d'||key=='D')
				A.tt=RIGHT;
				else if((key=='c'||key=='C')) {hienkd=-hienkd;if(hienkd==-1) hienkedich=0;else hienkedich=1;}
				else if(key=='z'||key=='Z') //Bat/Tat hieu ung 
				{
					tam_hieuung=-tam_hieuung;
					if(tam_hieuung==-1)
						hieu_ung='y';
					else hieu_ung='n';
				}
				else if(key=='f'||key=='F') delay+=10;//Tang toc
				else if(key=='g'||key=='G') delay-=10;//Giam toc
				else if(key=='x'||key=='X') //Chuyen che do choi 
				{
					SetColor(8);
					gotoxy(0,0);
					cout<<"Mode: "<<chedotext;
					SetColor(12);
					cout<<"(auto)";
					Sleep(100);
					cout<<"         ";
					aichoi='2';
				}
				else if(key==13)//Enter de tam dung
				break;
				else if(key=='r'||key=='R') xoamanhinh();
				else if(key=='h'||key=='H') Huong_Dan();
				else if(key=='m'||key=='M') 
VONGMenun:		{	Menu(bien_return);
					if(bien_return==1) {XoaMenu();goto VONGLAP;}
					else if(bien_return==2) 
					{
						gotoxy(40,13);
						cout<<"Enter State: ";cin>>chedo;
						xoamanhinh();
						goto VONGLAP;
					}
					else if(bien_return==3)
					{
						ChangeColor(maukitu,maukedich,mauvatpham,bien_return);
						if(bien_return==4) goto VONGMenun;
						else goto VONGLAP;
					}	
					else if(bien_return==5) {gotoxy(15,15);goto Quit;}
					else if(bien_return==6) {Nhaptenmap(filename);VeMap(filename);}						
				}
				else Ban_chet(A,key,ten,kedich,diem,dieme);
				
			}
		}
		
	//May choi
		else if(aichoi=='2')
		{
		//Nhap phim
			if (kbhit())
			{
				char key=getch();
				if(key==13)
				break;//ENTER de tam dung
				else if(key=='f'||key=='F') delay+=10;//Tang toc
				else if(key=='g'||key=='G') delay-=10;//Giam toc
				else if(key=='x'||key=='X') aichoi='1';//Chuyen che do choi
				else if(key==13) break;// Tam dung
				else if(key=='r'||key=='R') xoamanhinh();
				else if(key=='h'||key=='H') Huong_Dan();
				else if((key=='c'||key=='C')) {hienkd=-hienkd;if(hienkd==-1) hienkedich=0;else hienkedich=1;}
				else if(key=='z'||key=='Z') //Bat/Tat hieu ung 
				{
					tam_hieuung=-tam_hieuung;
					if(tam_hieuung==-1)
						hieu_ung='y';
					else hieu_ung='n';
				}				
				else if(key=='m'||key=='M') 
VONGMenum:		{	
					Menu(bien_return);
					if(bien_return==1) {XoaMenu();goto VONGLAP;}
					else if(bien_return==2) 
					{
						gotoxy(40,13);
						cout<<"Enter State:";cin>>chedo;
						xoamanhinh();
						goto VONGLAP;
					}
					else if(bien_return==3)
					{
						ChangeColor(maukitu,maukedich,mauvatpham,bien_return);
						if(bien_return==4) goto VONGMenum;
						else goto VONGLAP;
					}	
					else if(bien_return==5) {gotoxy(15,15);goto Quit;}
					else if(bien_return==6) {Nhaptenmap(filename);VeMap(filename);}						
				}
				else Ban_chet(A,key,ten,kedich,diem,dieme);

			}

		//Cac truong hop di an vat pham
			if(A.yhq>A.y) A.tt=DOWN;
			else if(A.yhq<A.y) A.tt=UP;
			else if(A.xhq>A.x) A.tt=RIGHT;
			else if(A.xhq<A.x) A.tt=LEFT;

		//Cac truong hop gap ke dich
			if(A.y>=A.ye-10&&A.y<A.ye&&A.x==A.xe) 	   Ban_chet(A,'k',ten,kedich,diem,dieme);
			else if(A.y<=A.ye+10&&A.y>A.ye&&A.x==A.xe) Ban_chet(A,'i',ten,kedich,diem,dieme);
			else if(A.x<=A.xe+15&&A.x>A.xe&&A.y==A.ye) Ban_chet(A,'j',ten,kedich,diem,dieme);
			else if(A.x>=A.xe-15&&A.x<A.xe&&A.y==A.ye) Ban_chet(A,'l',ten,kedich,diem,dieme);
		}

	//Tam dung , tao hieu ung chuyen dong
		Sleep(delay);

	//Reset hieu ung
		if(hieu_ung=='y')
		 Reset_Hieuung(a);

	//Xoa du lieu cu cua ki tu
		gotoxy(A.x,A.y);
		for(int i=0;i<strlen(ten);i++)
		cout<<" ";
		
	//Di chuyen ki tu
		if(A.tt==DOWN)
		A.y++;
		else if(A.tt==UP)
		A.y--;
		else if(A.tt==RIGHT)
		A.x++;
		else if(A.tt==LEFT)
		A.x--;

	//xu ly cham bien ki tu
		if(A.y>25-3)
		A.y=0;
	 	else if(A.y<0)
	 	A.y=25-3;
		else if(A.x<0)
	 	A.x=80-strlen(ten);
	 	else if(A.x>80-strlen(ten))
	 	A.x=0;		
	 
	//Tao vi tri ke dich moi
		if(hienkedich==1)
			Tao_Kedich(A,kedich,maukedich);	
	}
//Hien thi goi y + nhan lenh tu ban phim
	SetColor(7);
	gotoxy(22,10);
	cout<<"Continue / Reset / Stop (t/r/d): ";
	gotoxy(58,10);
	cout<<" ";
	cin>>hoi;
	if(hoi=='t'||hoi=='T') 
	{
		xoamanhinh();
		if(diem==0)
			NgauNhien_dich(A);
	}
	
}while(hoi=='c'||hoi=='C');	
//Xoa man hinh de nhap lai du lieu
	xoamanhinh();
}while(hoi=='d'||hoi=='D');
Quit:	return 0;
}
//Ham di chuyen con tro toi mot vi tri toa do (x,y) tren man hinh
void gotoxy(int x, int y)
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
}
//Ham tao mau sac
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
//Khoi tao gia tri ban dau cho vi tri cua kitu va vatpham
void KhoiTao(ChuChay &A)
{
	A.y=4;
	A.x=1;
	A.xhq=rand()%77+1;
	A.yhq=rand()%23;
}
//Hien thi huong dan
void Huong_Dan()
{
	SetColor(8);
	gotoxy(0,13);
	cout<<"      ~FLY AND FIGHT~\n";
	cout<<" ~Made by VAN HOANG @2017~\n";
	cout<<"===================================\n";
	cout<<"A S D W  :Move\n";
	cout<<"J K L I  :Shoot\n";
	cout<<"   X     :Control/Auto\n";
	cout<<"   Z     :On/Off snow\n";
	cout<<" F / G   :Speep up/Slow down game\n";
	cout<<"   C     :On/Off enemy\n";
	cout<<"ENTER / R:Pause/Refresh screen.\n\n";
	SetColor(8);
	cout<<"   H    : Help                M     : Menu";
}
//Cach di chuyen cua vatpham qua tung che do khac nhau >=2
void CheDochoi(ChuChay &A,int chedo,char vatpham[])
{
	//Di chuyen vat pham
	 	//Xoa vat pham cu
	 	gotoxy(A.xhq,A.yhq);
	 	for(int i=1;i<=strlen(vatpham);i++)
	 	cout<<" ";
 		//Tao vi tri vat pham moi
	 	int ran=rand()%5+1;
	 	if(ran==1) A.xhq-=chedo;
	 	else if(ran==2) A.xhq+=chedo;
	 	else if(ran==3) A.yhq-=chedo;
	 	else if(ran==4) A.yhq+=chedo;
 	//Xu ly cham bien vat pham
	 	if(A.yhq>25-3)
		A.yhq=0;
	 	else if(A.yhq<0)
	 	A.yhq=25-3;
		else if(A.xhq<0)
	 	A.xhq=80-strlen(vatpham);
	 	else if(A.xhq>80-strlen(vatpham))
	 	A.xhq=0;
	//Ve vat pham
		gotoxy(A.xhq,A.yhq);
		cout<<vatpham;		
}
//Ham xoa man hinh 1 lan
void xoamanhinh()
{
	for(int i=0;i<=22;i++)
	{
		gotoxy(0,i);
		for(int j=0;j<=79;j++)
		cout<<" ";
		cout<<"\n";
	}
}
void XoaMenu()
{
	for(int i=17;i<=21;i++)
	{
		gotoxy(62,i);
		cout<<"                 ";
	}
}
//Khoi tao hieu ung tuyet roi
void Khoitao_Hieuung(int a[20][2],char achuoi[3])
{
	for(int i=0;i<20;i++)
	{	
		a[i][0]=rand()%78+1;
		a[i][1]=rand()%23;
	}
	achuoi[0]=',';
	achuoi[1]='.';
	achuoi[2]='*';
}
//Ve hieu ung tuyet roi
void Hieuung(int a[20][2],char achuoi[3])
{
	for( int i=0;i<20;i++)
	{	
		gotoxy(a[i][0],a[i][1]);
		SetColor(7);
		cout<<achuoi[i%3];
	}
}
//Tao cam giac chuyen dong cho tuyet
void Reset_Hieuung(int a[20][2])
{
	for(int i=0;i<20;i++)
	{
		gotoxy(a[i][0],a[i][1]);
		cout<<" ";
		if((a[i][0]>=78)||a[i][1]>=21)
		{
			a[i][0]=rand()%78+1;
			a[i][1]=rand()%21;
		}
		else
		{
			a[i][0]++;
			a[i][1]++;
		}	
	}	
}
//Ve duong dan khi ban sung
void Ban_sung(ChuChay A,char ten[],char key)
{
		
	SetColor(15);
	//Ban sung theo chieu ngang qua phai
	if((key=='l'||key=='L')&&A.x>=0&&A.x+strlen(ten)<80)
	{
		gotoxy(A.x+strlen(ten),A.y);
		for(int i=1;i<=(79-A.x-strlen(ten))/2;i++)
			cout<<char(16)<<" ";
		Sleep(15);
		gotoxy(A.x+strlen(ten),A.y);
		for(int i=1;i<=(79-A.x-strlen(ten));i++)
			cout<<" ";
	}
	//Ban sung theo chieu ngang qua trai
	else if(key=='j'||key=='J')
	{
		gotoxy(0,A.y);
		for(int i=1;i<A.x/2;i++)
			cout<<char(17)<<" ";
		Sleep(15);
		gotoxy(0,A.y);
		for(int i=1;i<A.x;i++)
			cout<<" ";
	}
	//Ban sung len tren
	else if(key=='i'||key=='I')
	{
		for(int i=0;i<A.y;i++)
		{	
			gotoxy(A.x,i);
			if(i%2)
			cout<<char(30);
		}
		Sleep(15);
		for(int i=0;i<A.y;i++)
		{	
			gotoxy(A.x,i);
			cout<<" ";
		}
	}
	//Ban sung xuong duoi
	else if(key=='k'||key=='K')
	{
		for(int i=A.y+1;i<23;i++)
		{	
			gotoxy(A.x,i);
			if(i%2)
			cout<<char(31);
		}
		Sleep(15);
		for(int i=A.y+1;i<23;i++)
		{	
			gotoxy(A.x,i);
			cout<<" ";
		}
	}	
}
//Tao ra ke dich
void Tao_Kedich(ChuChay &A,char kedich[],int maukedich)
{
	//Di chuyen vi tri ke dich
	 	//Xoa vi tri cu
	 	gotoxy(A.xe,A.ye);
	 	for(int i=1;i<=strlen(kedich);i++)
	 	cout<<" ";
 		//Tao vi tri ke dich moi+Xu ly cham bien
 		int a=rand()%2;
 		while(A.ye<=0||A.xe<=0) {A.ye++;A.xe++;}
 		while(A.ye>=22||A.xe>=80) {A.ye--;A.xe--;}
	 	if(A.x>A.xe&&A.y>A.ye) {if(a) A.xe++;else A.ye++;}
	 	else if(A.x>A.xe&&A.y<=A.ye) {if(a) A.xe++; else A.ye--;}
	 	else if(A.x<A.xe&&A.y<=A.ye) {if(a) A.ye--; else A.xe--;}
	 	else if(A.x<=A.xe&&A.y>A.ye) {if(a) A.ye++; else A.xe--;}
	//Ve ke dich
	SetColor(maukedich);
	gotoxy(A.xe,A.ye);
	cout<<kedich;	
}
//Khoi tao ke dich ngau nhien
void NgauNhien_dich(ChuChay &A)
{
	A.xe=rand()%77+1;
	A.ye=rand()%23;
	if(A.xe==A.x&&A.ye==A.y)
	{
		A.xe+=5;
		A.ye+=5;
	}
}
//Ve cam giac vu no sau khi ban trung ke dich
void Kedich_boom(ChuChay A)
{
	gotoxy(A.xe,A.ye);cout<<"O";
	gotoxy(A.xe-1,A.ye);cout<<"@";
	gotoxy(A.xe+1,A.ye);cout<<"@";
	gotoxy(A.xe,A.ye+1);cout<<"@";
	gotoxy(A.xe,A.ye-1);cout<<"@";
	Sleep(10);
	gotoxy(A.xe-1,A.ye+1);cout<<"@";
	gotoxy(A.xe+1,A.ye-1);cout<<"@";
	gotoxy(A.xe+1,A.ye+1);cout<<"@";
	gotoxy(A.xe-1,A.ye-1);cout<<"@";

	gotoxy(A.xe-2,A.ye);cout<<"@";
	gotoxy(A.xe+2,A.ye);cout<<"@";
	gotoxy(A.xe,A.ye+2);cout<<"@";
	gotoxy(A.xe,A.ye-2);cout<<"@";
	Sleep(10);
	gotoxy(A.xe,A.ye);cout<<" ";
	gotoxy(A.xe-1,A.ye);cout<<" ";
	gotoxy(A.xe+1,A.ye);cout<<" ";
	gotoxy(A.xe,A.ye+1);cout<<" ";
	gotoxy(A.xe,A.ye-1);cout<<" ";
	Sleep(20);
	gotoxy(A.xe-2,A.ye);cout<<" ";
	gotoxy(A.xe+2,A.ye);cout<<" ";
	gotoxy(A.xe,A.ye+2);cout<<" ";
	gotoxy(A.xe,A.ye-2);cout<<" ";
	gotoxy(A.xe-1,A.ye+1);cout<<" ";
	gotoxy(A.xe+1,A.ye-1);cout<<" ";
	gotoxy(A.xe+1,A.ye+1);cout<<" ";
	gotoxy(A.xe-1,A.ye-1);cout<<" ";
}
//Ke dich chet
void Ban_chet(ChuChay &A,char key,char ten[],char kedich[], int &diem,int &dieme)
{
	if(key=='l'||key=='L'||key=='j'||key=='J'||key=='i'||key=='I'||key=='k'||key=='K')
	{
		Ban_sung(A,ten,key);
		if(((key=='l'||key=='L')&&(A.y==A.ye)&&(A.xe>A.x))||((key=='j'||key=='J')&&(A.y==A.ye)&&(A.xe<A.x))||((key=='i'||key=='I')&&(A.y>A.ye)&&(A.xe==A.x))||((key=='i'||key=='I')&&(A.y>A.ye)&&(A.xe==A.x))||((key=='k'||key=='K')&&(A.y<A.ye)&&(A.xe==A.x))) 		
			{
				Kedich_boom(A);
				diem+=dieme; 
				dieme=0;
				gotoxy(A.xe,A.ye); 
				for(int i=1;i<=strlen(kedich);i++) 
					cout<<" "; NgauNhien_dich(A);
			}
	}
};
//Tao bang ma ki tu Acsii
void Tao_acsii()
{
	for(int i=1;i<=255;i++)
		{
			SetColor(8);
			if(i<100)
				 cout<<i<<" :";
			else cout<<i<<":";
			SetColor(6);
			cout<<char(i)<<"\t";
		}
		SetColor(7);
	cout<<"\n";
}  
//Tra ve gia tri khi an Enter trong Menu
int Luachon(int y)
{
	switch(y)
	{
		case  21:return 1;break;//Back
		case  20:return 5;break;//Quit game
		case  19:return 2;break;//Select Level//Select Level
		case  18:return 3;break;//Select Level	
		case  17:return 6;break;//Select Map
	}
}
//Ham hien thi Menu 
void Menu(int &bien_return)
{
	int x=77,y=21;
	//Khoi tao
	SetColor(8);
	gotoxy(62,17); cout<<"     Select Map  ";
	gotoxy(62,18); cout<<"   Change Color  ";
	gotoxy(62,19); cout<<"   Select Level  ";
	gotoxy(62,20); cout<<"      Quit Game  ";
	gotoxy(62,21); cout<<"           Back  ";
	gotoxy(63,21); cout<<"=>";
	gotoxy(77,21);cout<<"<=";
	while(1)
	{
	//Nhan phim
		if(kbhit())	
		{
			char key=getch();
			if(key=='w') 
			{
				gotoxy(x,y); cout<<"  ";gotoxy(x-14,y);cout<<"  ";//Xoa vi tri con tro cu
				y--;
				if(y<17) y=21;//Xu ly cham bien
				gotoxy(x,y);cout<<"<=";gotoxy(x-14,y);cout<<"=>";//Ve vi tri moi
			}
			else if(key=='s')
			{
				gotoxy(x,y); cout<<"  ";gotoxy(x-14,y);cout<<"  ";
				y++;
				if(y>21) y=17;
				gotoxy(x,y);cout<<"<=";gotoxy(x-14,y);cout<<"=>";
			}
			else if(key==13) {bien_return=Luachon(y);break;}
		}
	}
}
//Hien thi bang mau
void BangMau()
{
	gotoxy(30,10);
	for(int i=1;i<=15;i++)
	{
		SetColor(i);
		cout<<i<<" ";
	}
	SetColor(15);
}
//Xoa Bang mau
void XoaBangmau()
{
	gotoxy(30,10);
	for(int i=1;i<=35;i++)
		cout<<" ";
	gotoxy(40,13);cout<<"                  ";
}
//Ham chon mau Color cho ki tu , vat pham , ke dich
void SelectColor(int y,int &maukitu,int &maukedich,int &mauvatpham,int &bien_return)
{
	switch(y)
	{
		case  21:{	bien_return=4;break;}//Back
		case  20:{	
					BangMau();
					gotoxy(40,13);
					cout<<"Color(1->15):";cin>>maukedich;
					XoaMenu();XoaBangmau(); break;}
		case  19:{	
					BangMau();
					gotoxy(40,13);
					cout<<"Color(1->15):";cin>>mauvatpham;
					XoaMenu();XoaBangmau();break;}
		case  18:{	
					BangMau();
					gotoxy(40,13);
					cout<<"Color(1->15):";cin>>maukitu;
					XoaMenu();XoaBangmau();break;}

	}
}
//Ham hien thi Menu ChangeColor -Thay doi mau sac
void ChangeColor(int &maukitu,int &maukedich,int &mauvatpham,int &bien_return)
{
	int x=77,y=21;
	//Khoi tao
	SetColor(8);
	gotoxy(62,17); cout<<"                 ";
	gotoxy(62,18); cout<<"    Ships Color  ";
	gotoxy(62,19); cout<<"    Items Color  ";
	gotoxy(62,20); cout<<"    Enemy Color  ";
	gotoxy(62,21); cout<<"           Back  ";
	gotoxy(63,21); cout<<"=>";
	gotoxy(77,21);cout<<"<=";
	while(1)
	{
	//Nhan phim
		if(kbhit())	
		{
			char key=getch();
			if(key=='w') 
			{
				gotoxy(x,y); cout<<"  ";gotoxy(x-14,y);cout<<"  ";//Xoa vi tri con tro cu
				y--;
				if(y<18) y=21;//Xu ly cham bien
				gotoxy(x,y);cout<<"<=";gotoxy(x-14,y);cout<<"=>";//Ve vi tri moi
			}
			else if(key=='s')
			{
				gotoxy(x,y); cout<<"  ";gotoxy(x-14,y);cout<<"  ";
				y++;
				if(y>21) y=18;
				gotoxy(x,y);cout<<"<=";gotoxy(x-14,y);cout<<"=>";
			}
			else if(key==13) {SelectColor(y,maukitu,maukedich,mauvatpham,bien_return);break;}
		}
	}
}
//Nhap ten map
void Nhaptenmap(char filename[])
{
	while(1)
	{
		SetColor(8);
		gotoxy(40,13);
		cout<<"Nhap ten map:";cin>>filename;
		FILE *f=fopen(filename,"rt");
		if(f==NULL) 
		{	
			gotoxy(40,14);
			cout<<"Khong ton tai file Map nay";
			gotoxy(40,15);
			cout<<"Dung chuong trinh PaintACSII de ve Map.";
			getch();
			gotoxy(40,14);
			cout<<"                           ";
			gotoxy(40,15);
			cout<<"                                        ";
			gotoxy(40,13);
			cout<<"                                        ";
		}
		fclose(f);
		break;
	}
	XoaMenu();
	gotoxy(40,13);
	cout<<"                                        ";
}
//Ve map
void VeMap(char filename[])
{
	FILE *f=fopen(filename,"rt");
	int x,y,k,c;
	while(!feof(f))
	{
		fscanf(f,"%d",&x);
		fscanf(f,"%d",&y);
		fscanf(f,"%d",&k);
		fscanf(f,"%d",&c);
		if(x<80&&y<23)
		{	
			gotoxy(x,y);
			SetColor(c);
			cout<<char(k);
		}
	}
	fclose(f);
}

