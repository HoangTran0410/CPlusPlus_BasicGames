#include<iostream>
using namespace std;
void ngaymai (int ngay, int thang, int nam);
int ngaythumay(int ngay ,int thang,int nam);
int songay(int thang,int nam);
int khoangcachngay(int ngayb,int thangb,int namb,int ngaye,int thange,int namen); 
int kt(int ngay,int thang,int nam );
void kt2(int ngay,int thang,int nam);
int thumay_so(int ngay,int thang,int nam);
void thumay(int ngay,int thang,int nam);
void namgi(int nam);
void vethang(int thang,int nam);
void lehoi(int ngay,int thang);
int main()
	{
	int trl, ngay ,thang ,nam;
	char a;
	do
	{
		system("cls");
		cout<<"Ban muon tinh gi?:\n";
		cout<<"\nHien thi thong tin cua mot ngay bat ki : an phim 1\n";
		cout<<"\nTinh khoang cach giua 2 ngay bat ki : an phim 2\n";
		cin>>trl;
		system("cls");
		if (trl==1)
		{
			cout<<"Nhap vao \"ngay thang nam\" :";
			cin>>ngay>>thang>>nam;
			if (kt(ngay,thang,nam))
			{
				if (songay(2,nam)==29) cout<<"\nNam "<<nam<<" la nam nhuan\n";
				else cout<<"\nNam "<<nam<<" la nam KHONG nhuan\n";
				cout<<"Nam "<<nam<<" la nam ";namgi(nam);cout<<"\n";
				cout<<ngay<<"/"<<thang<<" la ";
				thumay(ngay,thang,nam);cout<<" trong tuan"<<"\n";
				cout<<ngay<<"/"<<thang<<" la ngay thu "<<ngaythumay(ngay,thang,nam)<<" trong nam.";
				ngaymai(ngay,thang,nam);
				vethang(thang,nam);	
				for(int i=1;i<=songay(thang,nam);i++)
				{
					lehoi(i,thang);
				}	
			}
			else
			{
				kt2(ngay,thang,nam);
			}	
		}
		else 
			if(trl==2)
			{
				int ngay2,thang2,nam2;
				cout<<"Nhap vao ngay thang nam bat dau: ";cin>>ngay>>thang>>nam;
				cout<<"\nNhap vao ngay thang nam ket thuc: ";cin>>ngay2>>thang2>>nam2;
				if(kt(ngay,thang,nam)&&(kt(ngay,thang,nam)))
				{	
					cout<<"\nTu "<<ngay<<"/"<<thang<<"/"<<nam<<" toi "<<ngay2<<"/"<<thang2<<"/"<<nam2<<" co: ";
					if(!khoangcachngay(ngay,thang,nam,ngay2,thang2,nam2)) 
						cout<<"\nDu lieu ban nhap sai hoac trung ngay\n";
					else
					{
						int m=khoangcachngay(ngay,thang,nam,ngay2,thang2,nam2);
						if(nam==nam2) 
						{
							cout<<m<<" ngay\n";
							cout<<"\n= "<<m*24<<" gio.";
						}
						else
						{ 
							int sonam,ngaydu;
							if(thang2>=thang) 
							{
								sonam=nam2-nam;
								ngaydu=khoangcachngay(ngay,thang,nam2,ngay2,thang2,nam2);
							}
							else
							{
								sonam=nam2-nam-1;
								ngaydu=khoangcachngay(ngay,thang,nam,ngay2,thang2,nam+1);
							}
							cout<<m<<" ngay\n"<<"= "<<sonam<<" nam + "<<ngaydu<<" ngay";
							cout<<"\n= "<<m*24<<" gio.";
						}
					}
				}
				else
				{
					if (!kt(ngay,thang,nam)) 
						kt2(ngay,thang,nam);
					else 
						kt2(ngay2,thang2,nam2);
				}
			}
			else cout<<"\nLua chon cua ban khong ton tai\n";
			cout<<"\n\nTiep tuc hay dung lai (y/n): ";cin>>a;
			cout<<"________________________________________________________\n";
		
	} while((a=='y')||(a=='Y'));
	return 0;
}
int songay(int thang,int nam) // Tinh so ngay trong thang bat ki cua mot nam bat ki
{
	switch (thang)
	{
		case 1 :
		case 3 :
		case 5 :
		case 7 :
		case 8 :
		case 10 :
		case 12 :return 31;
		case 4 :
		case 6 :
		case 9 :
		case 11 : return 30;
		case 2 : 
		if((!(nam%4)&&(nam%100))||(!(nam%400)))
			return 29;
		else 
			return 28;
	}
}
void ngaymai (int ngay, int thang, int nam)// Tim ngay mai cua (ngay,thang,nam)
{
	if(ngay<songay(thang,nam))
		ngay++;
	else
	{
		ngay=1;
		thang++;
		if(thang>12)
		{
			thang=1;
			nam++;
		}
	}
	cout<<"\nNgay mai la : ";
	cout<<ngay<<"/"<<thang<<"/"<<nam<<"\n";
}
int ngaythumay(int ngay ,int thang,int nam)// Tính toan xem (ngay ,tahng ,nam) la ngay thu may trong nam
{
	int ngaythu=0;
	if(thang==1)	return ngay;
	else
	{
		for(int i=1;i<thang;i++)
		ngaythu+= songay(i,nam);
		return ngaythu+ngay;
	}
}
int khoangcachngay(int ngayb,int thangb,int namb,int ngaye,int thange,int namen) 
//Tinh khoang cach giua 2 (ngay,thang,nam) bat ki
{
	if (namb==namen)
	{
		if (thangb==thange)
		{
			if(ngayb<ngaye)
			return ngaye-ngayb;
			else return 0;
		}
		else
		{
			if(thangb<thange)
			{
				int tong=0;
				if (thangb+1==thange) return (songay(thangb,namb)-ngayb)+ngaye;
				else
				{
					for(int i=thangb+1;i<thange;i++)
					tong+=songay(i,namb);
					return tong+(songay(thangb,namb)-ngayb)+ngaye;
				}
			}
			else return 0;
			
		}
	}
	else
	{
		if(namen>namb)
		{
			int nam,s=0;
			if (songay(2,namb)==29) nam=366;
				else nam=365;
			if(namb+1==namen) 
				return ngaythumay(ngaye,thange,namen)+(nam-ngaythumay(ngayb,thangb,namb));
			else
			{
				for (int i=(namb+1);i<namen;i++)
				if (songay(2,i)==29) 
					s+=366;
				else s+=365;
				return ngaythumay(ngaye,thange,namen)+(nam-ngaythumay(ngayb,thangb,namb))+s;
			}
		}
		else return 0;
	}
}
int kt(int ngay,int thang,int nam )
//Kiem tra xem ngay nhap vao co dung hay khong
{
	if ((ngay<=31)&&(ngay>0)&&(thang<=12)&&(thang>0)&&(nam>=0)&&(ngay<=songay(thang,nam)))
		return 1;
	else return 0;
}
void kt2(int ngay,int thang,int nam)
//Xuat ra man hinh thong bao neu ngay nhap vao khong dung
{
	if(!(ngay<=31)||(ngay<=0)) cout<<"\nNgay khong hop le\n";
	if(!(thang<=12)||(thang<=0)) cout<<"\nThang khong hop le\n";
	if((nam<0)) cout<<"\nNam khong hop le\n";
	if(!(ngay<=songay(thang,nam))) cout<<"\nKhong ton tai ngay \n"<<ngay<<"/"<<thang<<"/"<<nam; 
}
int thumay_so(int ngay,int thang,int nam)
//Tinh xem (ngay,thang,nam) la thu may trong tuan,ket qua xuat ra duoi dang "so int"
{
	switch (khoangcachngay(1,1,0,ngay,thang,nam)%7)
	{
		case 0: return 7;break;
		case 1: return 8;break;
		case 2: return 2;break;
		case 3: return 3;break;
		case 4: return 4;break;
		case 5: return 5;break;
		case 6: return 6;break;
	}
}
void thumay(int ngay,int thang,int nam)
//Tinh xem (ngay,thang,nam) la thu may trong tuan,ket qua xuat ra duoi dang "ki tu"
{
	switch (thumay_so(ngay,thang,nam))
	{
		case 7: cout<<" thu 7 ";break;
		case 8: cout<<" chu nhat ";break;
		case 2: cout<<" thu 2 ";break;
		case 3: cout<<" thu 3 ";break;
		case 4: cout<<" thu 4 ";break;
		case 5: cout<<" thu 5 ";break;
		case 6: cout<<" thu 6 ";break;
	}
}
void namgi(int nam)
//Tinh xem (nam) nhap vao la nam con giap gi
{
	int nam1,nam2;
	nam1=nam%10;
	if ((nam>=2000)&&(nam<3000))
		nam2=(100+(nam%100))%12;
	else  
		if ((nam<2000)&&(nam>=0)) 
			nam2=(nam%100)%12;
	if((nam<3000)&&(nam>=0))
	{
		switch(nam1)
		{
			case 0:cout<<"Canh";break;
			case 1:cout<<"Tan";break;
			case 2:cout<<"Nham";break;
			case 3:cout<<"Quy";break;
			case 4:cout<<"Giap";break;
			case 5:cout<<"At";break;
			case 6:cout<<"Binh";break;
			case 7:cout<<"Dinh";break;
			case 8:cout<<"Mau";break;
			case 9:cout<<"Ky";break;
		}
		switch(nam2)
		{
			case 0:cout<<" Ty";break;
			case 1:cout<<" Suu";break;
			case 2:cout<<" Dan";break;
			case 3:cout<<" Mao";break;
			case 4:cout<<" Thin";break;
			case 5:cout<<" Ti.";break;
			case 6:cout<<" Ngo";break;
			case 7:cout<<" Mui";break;
			case 8:cout<<" Than";break;
			case 9:cout<<" Dau";break;
			case 10:cout<<" Tuat";break;
			case 11:cout<<" Hoi";break;		
		}
	}
	else cout<<"\nChuong trinh chi tinh duoc tu vi cho nhung nam < 3000\n";
}
void vethang(int thang , int nam )
//Ve ra so do cua (thang) nhap vao
{
	cout<<"\nTHANG "<<thang<<"/"<<nam<<"\n===================================================\n";
	cout<<"CN\tThu2\tThu3\tThu4\tThu5\tThu6\tThu7\n\n";
	int j=songay(thang-1,nam);

	switch(thumay_so(1,thang,nam))
	{
		case 8: cout<<"";break;
		case 2: cout<<"("<<j<<")\t";break;
		case 3: cout<<"("<<j-1<<")\t("<<j<<")\t";break;
		case 4: cout<<"("<<j-2<<")\t("<<j-1<<")\t("<<j<<")\t";break;
		case 5: cout<<"("<<j-3<<")\t"<<"("<<j-2<<")\t"<<"("<<j-1<<")\t"<<"("<<j<<")\t";break;
		case 6: cout<<"("<<j-4<<")\t"<<"("<<j-3<<")\t"<<"("<<j-2<<")\t"<<"("<<j-1<<")\t"<<"("<<j<<")\t";break;
		case 7: cout<<"("<<j-5<<")\t"<<"("<<j-4<<")\t"<<"("<<j-3<<")\t"<<"("<<j-2<<")\t"<<"("<<j-1<<")\t"<<"("<<j<<")\t";break;
	}
	for(int i=1;i<=songay(thang,nam);i++)
	{
		if (thumay_so(i,thang,nam)==7)
		{
			cout<<" "<<i<<"\n\n";
		}
		else cout<<" "<<i<<"\t";
	}
	cout<<"\n===================================================\n";
}
void lehoi(int ngay,int thang)
//Chua thong tin cua cac ngay le trong nam
{
	switch(ngay*100+thang)
	{
		case  101: cout<<ngay<<"/"<<thang<<": Tet Duong Lich*\n";break;
		case  901: cout<<ngay<<"/"<<thang<<": Ngay HS-SV Viet Nam\n";break;
		case  302: cout<<ngay<<"/"<<thang<<": Ngay thanh lap Dang Cong San VN\n";break;
		case 1402: cout<<ngay<<"/"<<thang<<": Ngay Le tinh nhan\n";break;
		case 2702: cout<<ngay<<"/"<<thang<<": Ngay thay thuoc VN\n";break;
		case  803: cout<<ngay<<"/"<<thang<<": Ngay quoc te phu nu\n";break;
		case 2003: cout<<ngay<<"/"<<thang<<": Ngay quoc te hanh phuc\n";break;
		case 2203: cout<<ngay<<"/"<<thang<<": Ngay nuoc sach the gioi\n";break;
		case 2603: cout<<ngay<<"/"<<thang<<": Ngay thanh lap Doan Thanh Nien CS HCM\n";break;
		case 2703: cout<<ngay<<"/"<<thang<<": Ngay the thao VN\n";break;
		case  104: cout<<ngay<<"/"<<thang<<": Ngay ca thang tu\n";break;
		case 2104: cout<<ngay<<"/"<<thang<<": Ngay Sach VN\n";break;
		case 2204: cout<<ngay<<"/"<<thang<<": Ngay Trai Dat\n";break;
		case 3004: cout<<ngay<<"/"<<thang<<": Ngay giai phong Mien Nam*\n";break;
		case  105: cout<<ngay<<"/"<<thang<<": Ngay Quoc Te lao dong*\n";break;
		case  705: cout<<ngay<<"/"<<thang<<": Ngay chien thang Dien Bien phu\n";break;
		case 1305: cout<<ngay<<"/"<<thang<<": Ngay cua me\n";break;
		case 1505: cout<<ngay<<"/"<<thang<<": Ngay thanh lap doi thieu nien tien phong\n";break;
		case 1905: cout<<ngay<<"/"<<thang<<": Ngay sinh chu tich Ho Chi Minh\n";break;
		case  106: cout<<ngay<<"/"<<thang<<": Ngay quoc te thieu nhi\n";break;
		case  506: cout<<ngay<<"/"<<thang<<": Ngay moi truong the gioi\n";break;
		case 1706: cout<<ngay<<"/"<<thang<<": Ngay cua cha\n";break;
		case 2106: cout<<ngay<<"/"<<thang<<": Ngay bao chi VN\n";break;
		case 2806: cout<<ngay<<"/"<<thang<<": Ngay gia dinh VN\n";break;
		case 2707: cout<<ngay<<"/"<<thang<<": Ngay thuong binh liet si\n";break;
		case 1107: cout<<ngay<<"/"<<thang<<": Ngay dan so the gioi\n";break;
		case 1908: cout<<ngay<<"/"<<thang<<": Cach mang thang 8 thanh cong\n";break;
		case  209: cout<<ngay<<"/"<<thang<<": Ngay Quoc Khanh*\n";break;
		case  709: cout<<ngay<<"/"<<thang<<": Ngay sinh ra va lon len cua VTV\n";break;
		case 1009: cout<<ngay<<"/"<<thang<<": Ngay thanh lap mat tran to quoc VN\n";break;
		case  110: cout<<ngay<<"/"<<thang<<": Ngay quoc te nguoi cao tuoi\n";break;
		case 1010: cout<<ngay<<"/"<<thang<<": Ngay giai phong thu do Ha Noi\n";break;
		case 1310: cout<<ngay<<"/"<<thang<<": Ngay doanh nhan VN\n";break;
		case 2010: cout<<ngay<<"/"<<thang<<": Ngay thanh lap hoi phu nu VN\n";break;
		case 3110: cout<<ngay<<"/"<<thang<<": Ngay le Haloween\n";break;
		case  911: cout<<ngay<<"/"<<thang<<": Ngay phap luat VN\n";break;
		case 2011: cout<<ngay<<"/"<<thang<<": Ngay nha giao VN\n";break;
		case 2311: cout<<ngay<<"/"<<thang<<": Ngay thanh lap hoi chu thap do VN\n";break;
		case 2212: cout<<ngay<<"/"<<thang<<": Ngay thanh lap quan doi nhan dan VN\n";break;
		case 2512: cout<<ngay<<"/"<<thang<<": Ngay Le Giang sinh\n";break;
	}
}