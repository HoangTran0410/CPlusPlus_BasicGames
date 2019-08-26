#include<iostream>
#include<conio.h>
#include<time.h>
#include<math.h>

#define _WIN32_WINNT 0x0500
#include<windows.h>
using namespace std;


#define Sl_HQ 3

enum TrangThai {Up,Down,Left,Right,Not};

struct DotRan
{
	int x;
	int y;
	int mau;
	char kitu;
};

struct ConRan
{
	DotRan Dot[500];
	int Dai;
	int Diem;
	int Nangluong;
	int Color;
	int m[31][81];
	int vtrimau;
	int vtrikitu;
	TrangThai tt;
};

struct  HoaQua
{
	int x;
	int y;
	int hd;
};

void Chuongtrinhchinh();

int main()
{
	Chuongtrinhchinh();
	return 0;
}
//Di chuyen con tro toi vi tri x y
void gotoxy(int x, int y)
{
  static HANDLE h = NULL;
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };
  SetConsoleCursorPosition(h,c);
}
//Mau chu
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
//An hien con tro console
void ShowCur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = {1, CursorVisibility};
    SetConsoleCursorInfo(handle, &cursor);
}
//Ham hien thi ran len man hinh
void HienThiR(ConRan &R)
{
	for(int i = 1; i < R.Dai ;++i)
	{
		if(R.vtrimau > 0)
			SetColor(R.Dot[i % R.vtrimau + 1].mau);
		else SetColor(7);
		gotoxy(R.Dot[i].x ,R.Dot[i].y);
		if(R.vtrikitu > 0)
			cout << R.Dot[i % R.vtrikitu + 1].kitu;
		else cout << R.Dot[0].kitu;

	}
	SetColor(R.Color);
	gotoxy(R.Dot[0].x ,R.Dot[0].y);
	cout << R.Dot[0].kitu;	
}
//Hien thi diem va nang luong len man hinh
void Diem(ConRan &R,int toadox, int toadoy)
{
	//So diem + toa do
	SetColor(R.Color);
	gotoxy(toadox,toadoy); cout << "          ";

	//Hien thi Diem
	gotoxy(toadox,toadoy);
	cout << R.Diem;
	//Hien thi chieu dai
	gotoxy(toadox + 4,toadoy);
	cout << R.Dai;

	//Hien thi thanh nang luong
	if(R.Nangluong > 10) R.Nangluong = 10;
	gotoxy(toadox - 13,toadoy);
	SetColor(7);
	cout << char(222);
	SetColor(R.Color);
	if(R.Nangluong != 0)
		for(int i = 1 ; i <= R.Nangluong ; ++i )
			cout << char(219);
	else
		for(int i = 1 ; i <= 10 ; ++i )
			cout << " ";
	SetColor(7);
	gotoxy(toadox - 2,toadoy);
	cout << char(221);
}
//Xoa ran da hien thi
void XoaRan(ConRan &R)
{
	gotoxy(R.Dot[R.Dai-1].x ,R.Dot[R.Dai-1].y);
	cout << " ";
}
//Dich chuyen gia tri cac dot ran
void DichuyenRan(ConRan &R)
{
	for(int i = R.Dai-1 ; i > 0; --i)
	{
		R.Dot[i].x = R.Dot[i-1].x;
		R.Dot[i].y = R.Dot[i-1].y;
		if(i == R.Dai-1)
			R.m[R.Dot[i].y][R.Dot[i].x] = 0;
		else R.m[R.Dot[i].y][R.Dot[i].x] = 1;
	}
	R.m[R.Dot[0].y][R.Dot[0].x] = 1;
}
//Dich chuyen vi tri dau ran
void DichchuyenDau(ConRan &R)
{
	if(R.tt == Left)
		R.Dot[0].x--;
	else if(R.tt == Right)
		R.Dot[0].x++;
	else if(R.tt == Down)
		R.Dot[0].y++;
	else if(R.tt == Up)
		R.Dot[0].y--;
}
//Dich chuyen vi tri , huong di chuyen ran may
void DichchuyenRanmay(ConRan &Ranmay,int luachon, HoaQua Hq[])
{
	if(luachon <= 12)
	{
		//Chon hoa qua gan nhat
		int tam = abs(Ranmay.Dot[0].x - Hq[0].x) + abs(Ranmay.Dot[0].y - Hq[0].y);
		int hqso = 0;
		for(int i = 1; i < Sl_HQ; ++i)
		{
			int kc = abs(Ranmay.Dot[0].x - Hq[i].x) + abs(Ranmay.Dot[0].y - Hq[0].y);
			if( kc < tam )
			{
				tam = kc;
				hqso = i;
			}
		}

		//Di chuyen toi hoa qua
		if(Ranmay.Dot[0].x > Hq[hqso].x)
			Ranmay.Dot[0].x--;
		else if(Ranmay.Dot[0].x < Hq[hqso].x)
			Ranmay.Dot[0].x++;
		else if(Ranmay.Dot[0].y > Hq[hqso].y)
			Ranmay.Dot[0].y--;
		else if(Ranmay.Dot[0].y < Hq[hqso].y)
			Ranmay.Dot[0].y++;
	}
}
//Xu ly khi ran cham bien tren, duoi , phai , trai
void Xulychambien(ConRan &R)
{
	if(R.Dot[0].x > 79)
		R.Dot[0].x = 0;
	else if(R.Dot[0].x < 0)
		R.Dot[0].x = 79;
	else if(R.Dot[0].y > 30)
		R.Dot[0].y = 0;
	else if(R.Dot[0].y < 0)
		R.Dot[0].y = 30;	
}
//Xu ly tang diem khi ran an hoa qua
void Xuly_anHoaqua(ConRan &R,ConRan &R2 ,ConRan &R3, HoaQua Hq[])
{
	for(int i = 0; i < Sl_HQ ; ++i)
		if(R.Dot[0].x == Hq[i].x && R.Dot[0].y == Hq[i].y)
		{
			R.Dai++;
			R.Dot[R.Dai-1].x = R.Dot[0].x;
			R.Dot[R.Dai-1].y = R.Dot[0].y;
			R.Diem++;
			R.Nangluong++;
			Hq[i].x = rand()%80;
			Hq[i].y = rand()%29+1;
		}
	if(R3.m[R.Dot[0].y][R.Dot[0].x] == 2 || R2.m[R.Dot[0].y][R.Dot[0].x] == 2 || R.m[R.Dot[0].y][R.Dot[0].x] == 2)
	{
		R.Dai++;
		R.Dot[R.Dai-1].x = R.Dot[0].x;
		R.Dot[R.Dai-1].y = R.Dot[0].y;
		R.Diem++;
		R.Nangluong++;
		if(R3.m[R.Dot[0].y][R.Dot[0].x] == 2)
			R3.m[R.Dot[0].y][R.Dot[0].x] = 0;
		if(R2.m[R.Dot[0].y][R.Dot[0].x] == 2)
			R2.m[R.Dot[0].y][R.Dot[0].x] = 0;
		if(R.m[R.Dot[0].y][R.Dot[0].x] == 2)
			R.m[R.Dot[0].y][R.Dot[0].x] = 0;
	}
}
//Xu ly khi 2 ran cham nhau (che do choi 1)
void XulyChamRan(ConRan &Rc,ConRan &Rbc)// c : cham ,bc : bi cham
{
	if(Rbc.m[Rc.Dot[0].y][Rc.Dot[0].x] == 1)
	{
		for(int i = Rc.Dai-1 ; i >= 0; --i)
		{
			if(rand()%3 == 0)
			{
				gotoxy(Rc.Dot[i].x,Rc.Dot[i].y);
				cout << "$";
				Rc.m[Rc.Dot[i].y][Rc.Dot[i].x] = 2;
			}else
			{
				gotoxy(Rc.Dot[i].x,Rc.Dot[i].y);
				cout << " ";
				Rc.m[Rc.Dot[i].y][Rc.Dot[i].x] = 0;					
			}
			Sleep(10);
		}			
		Rc.Dai = 3;
		Rc.Diem = 0;
		Rc.Nangluong = 0;

		Rbc.Diem +=2;
		Rbc.Nangluong += 2;

		for(int i = 0; i < Rc.Dai; ++i)
		{
			Rc.Dot[i].x = i ;
			Rc.Dot[i].y = 0;
		}
	}
}
//Xu ly khi 2 ran cham nhau (che do choi 2)
void XulyChamRan2(ConRan &Rc,ConRan &Rbc)// c : cham ,bc : bi cham
{
	if(Rbc.m[Rc.Dot[0].y][Rc.Dot[0].x] == 1)
	{
		//Xac dinh vi tri
		int vitri = 1;
		for(int i = 1 ; i < Rbc.Dai; ++i)
		{
			if(Rbc.Dot[i].x == Rc.Dot[0].x && Rbc.Dot[i].y == Rc.Dot[0].y)
				break;
			vitri++ ;
		}

		//Xoa cac dot thua
		for(int i = vitri ; i < Rbc.Dai ; ++i)
		{
			gotoxy(Rbc.Dot[i].x,Rbc.Dot[i].y);
			cout << " ";
			Rbc.m[Rbc.Dot[i].y][Rbc.Dot[i].x] = 0;
			//Tang diem cho ran cham
			Rc.Nangluong++;
			if(i%2 == 0)
			{
				Rc.Dai++;
				Rc.Diem++;
				Rc.Dot[Rc.Dai-1].x = 	Rc.Dot[0].x;
				Rc.Dot[Rc.Dai-1].y = 	Rc.Dot[0].y;
			}
			Sleep(10);
		}

		//Gan gia tri
		Rbc.Diem -= (Rbc.Dai - vitri);
		if(Rbc.Diem < 0) Rbc.Diem = 0;
		Rbc.Dai = vitri;


	}
}
//Kha nang dac biet 1
void Special(ConRan &R)
{
	gotoxy(R.Dot[0].x,R.Dot[0].y);
	cout << " ";
	switch(R.tt)
	{
		case Up   :R.Dot[0].y -= 5;break;
		case Down :R.Dot[0].y += 5;break;
		case Left :R.Dot[0].x -= 10;break;
		case Right:R.Dot[0].x += 10;break;
	}
	if(R.Nangluong > 10) R.Nangluong = 10;
	R.Nangluong -- ;
	switch(R.Color)
	{
		case 12:{gotoxy(58,32);for(int i = 0;i < 10;++i) cout << " ";break;}
		case 9 :{gotoxy(58,33);for(int i = 0;i < 10;++i) cout << " ";break;}
		case 11:{gotoxy(58,34);for(int i = 0;i < 10;++i) cout << " ";break;}
	}
	Xulychambien(R);
}
//Kha nang dac biet 2
void Special2(ConRan &R)
{
	SetColor(14);
	for (int i = 0; i < 5; ++i)
	{
		int x = rand()%80;
		int y = rand()%30;
		R.m[y][x] = 2;
		gotoxy(x,y);
		cout << "$";
	}
	R.Nangluong = 0;
}
//Ham hien thi Menu game
void Menu(int &luachon,int &chedochoi,ConRan &R,ConRan &R2,ConRan &Rm)
{
//Menu chinh
	SetColor(15);
	luachon = 10;
	Menu:
	system("cls");
	gotoxy(30,5);
	cout << "~GAME RAN SAN MOI~";
	gotoxy(30,6);
	cout << "       v1.5";
	SetColor(7);
	gotoxy(30,10);
	cout << "   Nguoi vs May ";
	gotoxy(30,12);
	cout << "  2Nguoi vs  May";
	gotoxy(30,14);
	cout << "  Nguoi vs Nguoi";
	gotoxy(30,16);
	cout << "   Che do  choi ";
	gotoxy(30,18);
	cout << "   Create Snake ";
	gotoxy(30,20);
	cout << "    Huong  Dan  ";
	gotoxy(30,22);
	cout << "      Thoat";
	gotoxy(28,30);
	cout << "W S : Thay doi lua chon";
	gotoxy(28,32);
	cout << "      Enter : Chon";
	gotoxy(27,34);
	cout<<".Made by Van Hoang @2017.";
	gotoxy(30,luachon); cout <<">>";
	gotoxy(46,luachon); cout <<"<<";

	while(true)
	{
		if(_kbhit())
		{
			char key = _getch();

			gotoxy(30,luachon); cout <<"  ";
			gotoxy(46,luachon); cout <<"  ";

			if(key == 'w'||key == 'W') luachon-=2;
			else if(key == 's'|| key == 'S') luachon+=2;
			else if(key == 13) break;
			if(luachon > 22) luachon = 10;
			else if(luachon < 10) luachon = 22;

			gotoxy(30,luachon); cout <<">>";
			gotoxy(46,luachon); cout <<"<<";
		}
	}

//Che do choi
	if(luachon == 16)
	{
		system("cls");
		gotoxy(23,10);
		cout << "            Che do choi";
		gotoxy(23,14);
		cout << "    Bi chan dau => Mat het diem";
		gotoxy(23,16);
		cout << "Cham vao duoi ran khac => Cuop diem";
		gotoxy(23,24);
		cout << "            Enter : Chon";
		gotoxy(23,26);
		cout << "             ESC : back";
		luachon = 14;
		gotoxy(21,luachon); cout <<">>";
		gotoxy(58,luachon); cout <<"<<";
		while(true)
			if(_kbhit())
			{
				char key = _getch();

				gotoxy(21,luachon); cout <<"  ";
				gotoxy(58,luachon); cout <<"  ";

				if(key == 'w' || key =='W')
					luachon-=2;
				else if(key == 's' || key =='S')
					luachon+=2;
				else if(key == 13)
				{
					if(luachon == 14)
						chedochoi = 1;
					else if(luachon == 16)
						chedochoi = 2;
					luachon = 16;
					goto Menu;
				}
				else if(key == 27) {luachon = 16; goto Menu;}

				if(luachon > 16) luachon = 14;
				else if(luachon < 14) luachon = 16;
				gotoxy(21,luachon); cout <<">>";
				gotoxy(58,luachon); cout <<"<<";
			}
	}

//Create Snake
	else if(luachon == 18)
	{
		luachon = 14;
		Create:
		SetColor(7);
		system("cls");
		gotoxy(32,10);
		cout << "  Create Snake";
		gotoxy(32,14);
		cout << "  Thay doi mau";
		gotoxy(30,16);
	    cout << " Thay doi hinh dang";
		gotoxy(30,24);
		cout << "    Enter : Chon";
		gotoxy(30,26);
		cout << "     ESC : back";
	    gotoxy(29,luachon);cout << ">>";
	    gotoxy(49,luachon);cout << "<<";
	    while(true)
	    {
	    	if(_kbhit())
	    	{
	    		char key = _getch();

	    		gotoxy(29,luachon);cout << "  ";
			    gotoxy(49,luachon);cout << "  ";

			    if(key == 'w' || key == 'W')
			    	luachon-=2;
			    else if(key == 's' || key == 'S')
			    	luachon+=2;
			    else if(key == 27) {luachon = 18;goto Menu;}
			    else if(key == 13) 
			    {
			    	if(luachon == 14) goto Thaydoimau;
			    	else if(luachon == 16) goto Thaydoihinhdang;
			    }

			    if(luachon < 14) luachon = 16;
			    else if(luachon > 16) luachon = 14;

				gotoxy(29,luachon);cout << ">>";
				gotoxy(49,luachon);cout << "<<";	
	    	}
	    }
	//Thay doi mau
	    if(false)
		{
			Thaydoimau:
			system("cls");
			string ran;

			//Nhap ten ran
			gotoxy(30,25);
			cout << " Nhap 'back' de thoat";
			gotoxy(0,1);
			Chonran:
			cout << "Chon Ran (1/2/may) :";cin >> ran;
			if(ran != "1"&&ran != "2"&&ran != "may"&&ran != "back") 
				{cout << "\nLua chon khong dung\n";goto Chonran;}

			//Back
			if(ran == "back") goto Create;
			switch(ran[0])
			{
				case '1': R.vtrimau = 0;break;
				case '2': R2.vtrimau = 0;break;
				case 'm': Rm.vtrimau = 0;break;
			}
			system("cls");
			gotoxy(30,22);
			cout << "A D :Thay doi lua chon";
			gotoxy(30,24);
			cout << "    Enter :  Chon";
			gotoxy(30,26);
			cout << "      ESC : Luu";

			//Chon mau
			gotoxy(0,1);
			cout << "Ran " << ran;
			for(int i = 1 ;i < 16 ; ++i)//Bang mau
				{gotoxy(i+5,5);SetColor(i);cout << char(219);}
			SetColor(15);
			gotoxy(6,6); cout << "^";
			int chon = 6,dot = 1;
			while(true)
			{
				if(_kbhit())
				{
					char key = _getch();
					char kitu;
					gotoxy(chon,6);cout << " ";

					if(key == 'a'||key == 'A') chon--;
					else if(key == 'd' ||key =='D') chon++;
					else if(key == 13) 
					{
						switch(ran[0])
						{
							case '1':{R.Dot[dot].mau = chon-5;R.vtrimau++;break;}
							case '2':{R2.Dot[dot].mau = chon-5;R2.vtrimau++;break;}
							case 'm':{Rm.Dot[dot].mau = chon-5;Rm.vtrimau++;break;}
						}
						dot++;
						gotoxy(dot,10);
						SetColor(chon - 5);
						switch(ran[0])
						{
							case '1':{if(R.vtrikitu > 0) kitu = R.Dot[dot % R.vtrikitu + 1].kitu; else kitu = char(219);break;}
							case '2':{if(R2.vtrikitu > 0) kitu = R2.Dot[dot % R2.vtrikitu + 1].kitu; else kitu = char(219);break;}
							case 'm':{if(Rm.vtrikitu > 0) kitu = Rm.Dot[dot % Rm.vtrikitu + 1].kitu; else kitu = char(219);break;}
						}
						cout << kitu;
					}
					else if(key == 27) goto Create;

					if(chon > 20) chon = 6;
					else if(chon < 6) chon = 20;
					SetColor(15);
					gotoxy(chon,6);cout << "^";
				}
			}
	    }
	//Thay doi ki tu
	    if(false)
	    {
	    	Thaydoihinhdang:
	    	system("cls");
			string ran;

			//Nhap ten ran
			gotoxy(30,25);
			cout << " Nhap 'back' de thoat";
			gotoxy(0,1);
			Chonran2:
			cout << "Chon Ran (1/2/may) :";cin >> ran;
			if(ran != "1"&&ran != "2"&&ran != "may"&&ran != "back")
				{cout << "\nLua chon khong dung\n";goto Chonran2;}

			//Back
			if(ran == "back") goto Create;
			switch(ran[0])
			{
				case '1': R.vtrikitu = 0;break;
				case '2': R2.vtrikitu = 0;break;
				case 'm': Rm.vtrikitu = 0;break;
			}
			system("cls");
			//Ve bang ma Acsii
			for(int i=1;i<=255;i++)
			{
				if(i > 6 && i < 14)
				{ 
					i++; continue;
				}
				SetColor(8);
				if(i<100)
					 cout<<i<<" :";
				else cout<<i<<":";
				SetColor(6);
				cout<<char(i)<<"\t";
			}
			SetColor(7);
			gotoxy(22,30);
			cout << "Nhap So tuong ung ki tu muon chon roi Enter";
			gotoxy(22,32);
			cout << "        Nhap so 0 khi hoan thanh";
			int kitu,vitri = 2;

			Nhapkitu:
			gotoxy(0,25);
			cout << "                       ";
			gotoxy(0,25);
			SetColor(7);
			cout << "Nhap so muon chon: ";
			cin >> kitu;
			if(kitu == 0) goto Create;
			else
			{
				switch(ran[0])
				{
					case '1':{ R.vtrikitu++; R.Dot[R.vtrikitu].kitu = char(kitu);break;}
					case '2':{ R2.vtrikitu++;R2.Dot[R2.vtrikitu].kitu = char(kitu);break;}
					case 'm':{ Rm.vtrikitu++;Rm.Dot[Rm.vtrikitu].kitu = char(kitu);break;}
				}
				gotoxy(vitri,27);
				switch(ran[0])
				{
					case '1':{if(R.vtrimau > 0) SetColor(R.Dot[R.vtrikitu % R.vtrimau + 1].mau); else SetColor(7);break;}
					case '2':{if(R2.vtrimau > 0) SetColor(R2.Dot[R.vtrikitu % R2.vtrimau + 1].mau); else SetColor(7);break;}
					case 'm':{if(Rm.vtrimau > 0) SetColor(Rm.Dot[R.vtrikitu % Rm.vtrimau + 1].mau); else SetColor(7);break;}
				}
				cout << char(kitu);
				vitri++;
				goto Nhapkitu;
			}
		}
	}

//Huong dan
	else if(luachon == 20)
	{
		system("cls");
		gotoxy(10,4);
		cout << "A S D W / I J K L :Di chuyen (nguoi choi 1 , nguoi choi 2)";
		gotoxy(10,6);
		cout << "  Q-E   /   U-O   :Special (Khi thanh nang luong full) ";
		gotoxy(10,8);
		cout << "       ESC        :Menu";
		gotoxy(10,14);
		cout << "Thu thap $ hoac vat pham, Giup tang diem va nang luong";
		gotoxy(10,18);
		cout << "================= Gom 2 che do choi =======================";
		gotoxy(10,20);
		cout << "        Che do 1: Chan dau ran khac de giet chung";
		gotoxy(10,22);
		cout << "   Che do 2: Cham vao duoi ran khac de cuop diem cua chung";
		gotoxy(10,26);
		cout << "=========== Gom 2 ki nang dac biet (special) ==============";
		gotoxy(10,28);
		cout << "     Special 1 (E/O): Tao ngau nhien 5 $ (create coin)";
		gotoxy(10,30);
		cout << "  Special 2 (Q/U): Dich chuyen toi truoc 1 khoang (portal)";
		gotoxy(10,33);
		cout << "           Nhan phim bat ki de quay lai Menu";
		getch();
		system("cls");
		goto Menu;
	}
	system("cls");
}
//Ham chay game chinh
void Chuongtrinhchinh()
{
//Khoi tao
	//Chinh do rong console
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 1000, 700, TRUE);

	ShowCur(false);//Tat hien thi con tro
	int chedochoi = 1;
	//Khai bao
	srand(time(NULL));
	ConRan Ran, Ran2, Ranmay;
	HoaQua Hq[Sl_HQ];

	Ran.Dot[0].kitu = char(219);
	Ranmay.Dot[0].kitu = char(177);
	Ran2.Dot[0].kitu = char(178);
	Ran.vtrimau = 0; Ran.vtrikitu = 0;
	Ran2.vtrimau = 0; Ran2.vtrikitu = 0;
	Ranmay.vtrimau = 0; Ranmay.vtrikitu = 0;


	KhoiTao:
	int luachon;
	Menu(luachon,chedochoi,Ran,Ran2,Ranmay);
	if(luachon == 22) goto Quit;

	//Gan gia tri
	for(int i = 0; i < 3; ++i)//Khoi tao vi tri ban dau
	{
		Ran.Dot[i].x = i;
		Ran.Dot[i].y = 10;
		if(luachon >= 12)
		{
			Ran2.Dot[i].x = i;
			Ran2.Dot[i].y = 15;
		}
		if(luachon <= 12)
		{
			Ranmay.Dot[i].x = 79-i;
			Ranmay.Dot[i].y = 13;
		}
	}
	//Khoi tao ran
	//Ran 1 
	Ran.tt = Not;
	Ran.Diem = 0;
	Ran.Nangluong = 0;
	Ran.Dai = 3;
	Ran.Color = 12;
	
	//Ran may
	if(luachon <= 12)
	{		
		Ranmay.Diem = 0;
		Ranmay.Nangluong = 0;
		Ranmay.Dai = 3;
		Ranmay.Color = 11;
	}
	//Ran 2
	if(luachon >= 12)
	{
		Ran2.tt = Not;
		Ran2.Diem = 0;
		Ran2.Nangluong = 0;
		Ran2.Dai = 3;
		Ran2.Color = 9;
	}
	//Khoi tao vi tri hoa qua ban dau
	for(int i = 0; i < Sl_HQ ;++i) 
	{
		Hq[i].hd = rand()%9;
		Hq[i].x = rand()%80;
		Hq[i].y = rand()%31;
	}
	//Khoi tao Ran.m Ran2.m Ranmay.m
	for(int i = 0; i <= 80 ; ++i)
		for(int j = 0; j <= 30 ;++j)
		{
			Ran.m[j][i] = 0;
			if(luachon >= 12)
				Ran2.m[j][i] = 0;
			if(luachon <= 12)
				Ranmay.m[j][i] = 0;
		}

//Ve khung
	SetColor(7);
	for(int i = 0;i < 80; ++i)
	{
		gotoxy(i,31);
		cout << char(219);
		if(i < 32)
		{
			gotoxy(80,i);
			cout << char(219);
		}
	}
	gotoxy(0,32);
	cout << "Che do choi : " << chedochoi;
	gotoxy(57,36);cout << " Nang luong  | Chieu Dai";
	gotoxy(57,37);cout << "             v";
	gotoxy(57,38);cout << "           Diem "; 

//Start Game
	while(true)
	{
	//Hien Thi 

		//Hien thi ran
		HienThiR(Ran);//Ran 1
		if(luachon >= 12 )
			HienThiR(Ran2);//Ran 2
		if(luachon <= 12)
			HienThiR(Ranmay);//Ran may

		//Hien thi Hoa Qua
		for(int i = 0;i < Sl_HQ; ++i)
		{
			gotoxy(Hq[i].x,Hq[i].y);
			SetColor(10);
			switch(Hq[i].hd)
			{
				case 0: cout << "|";break;
				case 2: cout << "/";break;
				case 4: cout << "-";break;
				case 6: cout << "\\";break;
				case 8: Hq[i].hd = -1;
			}
			Hq[i].hd++;
		}

		//Hien thi diem
		Diem(Ran,70,32);//Diem ran 1
		if(luachon >= 12)
			Diem(Ran2,70,33);//Diem ran 2
		if(luachon <= 12)
			Diem(Ranmay,70,34);//Diem ran may

		//Tam ngung
		Sleep(50);

		//Xoa vi tri cu
		XoaRan(Ran);//Ran 1
		if(luachon >= 12)
			XoaRan(Ran2);//Ran 2
		if(luachon <= 12)
			XoaRan(Ranmay);//Ran may

	//Dieu Khien
		if(_kbhit())
		{
			char key = _getch();
			if(key == 'a'|| key == 'A')
				Ran.tt = Left;
			else if(key == 'd'|| key == 'D')
				Ran.tt = Right;
			else if(key == 's'|| key == 'S')
				Ran.tt = Down;
			else if(key == 'w'|| key == 'W')
				Ran.tt = Up;
			else if((key == 'q'|| key == 'Q') && Ran.Nangluong >= 1)
				Special(Ran);
			else if((key == 'e'|| key == 'E') && Ran.Nangluong >= 10)
				Special2(Ran);

			else if(key == 'i' || key == 'I')
				Ran2.tt = Up;
			else if(key == 'j' || key == 'J')
				Ran2.tt = Left;
			else if(key == 'k' || key == 'K')
				Ran2.tt = Down;
			else if(key == 'l' || key == 'L')
				Ran2.tt = Right;
			else if((key == 'u'|| key == 'U') && Ran2.Nangluong >= 1)
				Special(Ran2);
			else if((key == 'o'|| key == 'O') && Ran2.Nangluong >= 10)
				Special2(Ran2);

			else if(key == 27)
			{
				gotoxy(15,15);
				cout << "Ban co chac chan muon thoat ra giao dien Menu";
				gotoxy(15,17);
				cout << "Moi du lieu dang choi se bi xoa (yes:y / no:n)";
				char thoat = _getch();
				if(thoat == 'y' || thoat == 'Y')
					{system("cls");goto KhoiTao;}
				else
				{
					gotoxy(15,15);
					cout << "                                              ";
					gotoxy(15,17);
					cout << "                                              ";
				}
			}
		}
		
	//Xu ly
		//Di chuyen + An hoa qua
		//Ran 1
		DichuyenRan(Ran);
		DichchuyenDau(Ran);
		Xulychambien(Ran);
		Xuly_anHoaqua(Ran,Ran2,Ranmay,Hq);
		//Ran 2
		if(luachon >= 12)
		{
			DichuyenRan(Ran2);
			DichchuyenDau(Ran2);
			Xulychambien(Ran2);
			Xuly_anHoaqua(Ran2,Ran,Ranmay,Hq);
		}
		//Ran may
		if(luachon <= 12)
		{
			DichuyenRan(Ranmay);
			DichchuyenRanmay(Ranmay,luachon,Hq);
			Xuly_anHoaqua(Ranmay,Ran,Ran2,Hq);
		}			

		//Xu ly cham ran
		if(chedochoi == 1)
		{
			SetColor(14);
			if(luachon <= 12)
			{
				XulyChamRan(Ranmay,Ran);//Ran may cham ran 1
				XulyChamRan(Ran,Ranmay);//Ran 1 cham Ran may
			}
			if(luachon == 12)
			{
				XulyChamRan(Ranmay,Ran2);//Ran may cham ran 2
				XulyChamRan(Ran2,Ranmay);//Ran 2 cham ran may
			}
			if(luachon == 14)
			{
				XulyChamRan(Ran,Ran2);//Ran 1 cham ran 2
				XulyChamRan(Ran2,Ran);//Ran 2 cham ran 1
			}
		}else if(chedochoi == 2)
		{
			SetColor(14);
			if(luachon <= 12)
			{
				XulyChamRan2(Ranmay,Ran);//Ran may cham ran 1
				XulyChamRan2(Ran,Ranmay);//Ran 1 cham Ran may
			}
			if(luachon == 12)
			{
				XulyChamRan2(Ranmay,Ran2);//Ran may cham ran 2
				XulyChamRan2(Ran2,Ranmay);//Ran 2 cham ran may
			}
			if(luachon == 14)
			{
				XulyChamRan2(Ran,Ran2);//Ran 1 cham ran 2
				XulyChamRan2(Ran2,Ran);//Ran 2 cham ran 1
			}			
		}
	}

//Quit Game
	Quit:
	system("cls");
}
