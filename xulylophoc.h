#pragma once
#include"ctdl.h"
#include"tum_lum.h"
#include"doc_ghi_file.h"
DANH_SACH_LOP dsl;
// CAC HAM KHONG TOA DO
void Them_Vao_Cuoi(DANH_SACH_SINH_VIEN& l, NODESINHVIEN*p);
void Sap_xep_ten_lop_tang_dan(DANH_SACH_LOP &dsl);
bool Kiem_tra_trung_lop(DANH_SACH_LOP dsl, string malop);
int Check_so_luong_sv(DANH_SACH_LOP dsl, string tenlop);
int Check_so_luong_sv_ma(DANH_SACH_LOP dsl, string malop);
string Tao_Ma_Sinh_Vien_Tu_Ma_Lop(LOP lop);
NODESINHVIEN* KhoiTaoSinhVien(SINHVIEN sv);
NODESINHVIEN* Tim_sinh_vien_theo_ma_sv(DANH_SACH_LOP dsl, string masv);
// CAC HAM CO TOA DO

void Plus_Form_quan_ly_lop_hoc(int x, int y, DANH_SACH_LOP &dsl);
void Plus_Them_lop_hoc(int x, int y, DANH_SACH_LOP &dsl);
void Plus_Xuat_lop_hoc(int x, int y, int vt, DANH_SACH_LOP dsl);
void Plus_Nhap_thong_tin_sinh_vien(SINHVIEN &sv, int x, int y, bool &exit);
void Plus_Nhap_Sv_Vao_Lop(DANH_SACH_LOP &dsl, int x, int y);
void Plus_Xuat_danh_sach_sinh_vien(DANH_SACH_LOP dsl, string tenlop, int x, int y, int vt);
////////////////////////////KET THUC KHAI BAO NGUYEN MAU HAM///////////////////////////////
bool Kiem_tra_trung_lop(DANH_SACH_LOP dsl, string malop)
{
	for (int i = 0; i < dsl.sl; i++)
	{
		if (malop == dsl.lop[i].ma_lop)
		{
			return true;
			break;
		}
	}
	return false;
}
NODESINHVIEN* KhoiTaoSinhVien(SINHVIEN sv)
{
	NODESINHVIEN* p = new NODESINHVIEN;
	if (p == NULL)
	{
		//cout << "Khong du bo nho, cap phat that bai!";
		return NULL;
	}
	p->data = sv;
	p->pnext = NULL;
	return p;

}
NODESINHVIEN* Tim_sinh_vien_theo_ma_sv(DANH_SACH_LOP dsl, string masv)
{
	for (int i = 0; i <= dsl.sl; i++)
	{
		if (Lay_ma_lop_tu_ma_sinh_vien(masv) == dsl.lop[i].ma_lop)
		{
			for (NODESINHVIEN* k = dsl.lop[i].dssv.phead; k != NULL; k = k->pnext)
			{
				if (masv == k->data.MASV)
					return k;
			}
		}
	}
}
string Tao_Ma_Sinh_Vien_Tu_Ma_Lop(LOP lop)
{
	srand(time(NULL));
	
	string a = "_0000";
	for (int i = 1; i < 5; i++)
	{
		a[i] = rand() % (57 - 48 + 1) + 48;
	}
	lop.ma_lop.append(a);
	
	return lop.ma_lop;
}
int Check_so_luong_sv(DANH_SACH_LOP dsl, string tenlop)
{
	int count = 0;
	ChuanHoaChu(tenlop);
	for (int i = 0; i < dsl.sl; i++)
	{
		if (dsl.lop[i].ten_lop == tenlop)
		{
			for (NODESINHVIEN* k = dsl.lop[i].dssv.phead; k != NULL; k = k->pnext)
			{
				count++;
			}
		}
	}
	return count;
}
int Check_so_luong_sv_ma(DANH_SACH_LOP dsl, string malop)
{
	int count = 0;
	In_Hoa(malop);
	for (int i = 0; i < dsl.sl; i++)
	{
		if (dsl.lop[i].ma_lop == malop)
		{
			for (NODESINHVIEN* k = dsl.lop[i].dssv.phead; k != NULL; k = k->pnext)
			{
				count++;
			}
		}
	}
	return count;
}
void Them_Vao_Cuoi(DANH_SACH_SINH_VIEN &l, NODESINHVIEN *p)
{
	if (l.phead == NULL)
	{
		l.phead = p;
	}
	else
	{
		for (NODESINHVIEN* k = l.phead; k != NULL; k = k->pnext)
		{
			if (k->pnext == NULL)
			{
				k->pnext = p;
				p->pnext = NULL;
			}
		}
	}
}
void Sap_xep_ten_lop_tang_dan(DANH_SACH_LOP &dsl)
{
	for (int i = 0; i < dsl.sl; i++)
	{
		for (int j = 0; j < dsl.sl; j++)
		{
			if (so_sanh_string(dsl.lop[i].ten_lop, dsl.lop[j].ten_lop) == 2)
				Swap_lop(dsl.lop[i], dsl.lop[j]);
		}
	}
}
// CAC HAM GAN TOA DO//////////
void Plus_Nhap_Sv_Vao_Lop(DANH_SACH_LOP &dsl, int x, int y)
{
	XoaManHinh(x + 49, y + 28, 55, 5);//xoa man hinh khung chuc nang
	string a;
	gotoxy(x + 60, y + 30);
	cout << "ESC: Quay lai khung tim kiem";
	Ve_HCN(30, 1, x + 120, y + 25);//tao khung nhap ma lop
	gotoxy(x + 110, y + 26);
	cout << "MA LOP: ";//tro toi cho nhap ma lop
	gotoxy(x + 121, y + 26);
	while (true)
	{
		hidecur(false);
		char k = _getch();
		if (k == 8)//phim backspace
		{
			if (a.length() >= 1)
			{
				XoaManHinh(x + 120 + a.length(), y + 26, 1, 1);
				a.erase(a.size() - 1);
				gotoxy(x + 120 + a.length(), y + 26);
			}
		}
		if (k >= 48 && k <= 57 && a.length() < 14)//hang phim so
		{
			a.push_back(k);
			gotoxy(x + 120 + a.length(), y + 26);
			cout << k;
		}
		if (k >= 97 && k <= 122 && a.length() < 14)//phim ki tu va space
		{
			a.push_back(k);
			gotoxy(x + 120 + a.length(), y + 26);
			cout << k;
		}
		if (k == 13)
			break;
		if (k == 27)
		{
			XoaManHinh(x + 110, y + 25, 45, 9);//xoa man hinh khung nhap thong tin
			 return;
		}
		hidecur(true);
		string a2 = a;
		In_Hoa(a2);
		XoaManHinh(x + 5, y + 7, 37, 17);//xoa man hinh o danh sach lop
		int temp = 0;
		for (int i = 0; i < dsl.sl; i++)
		{
			if (ahaveb(dsl.lop[i].ma_lop, a2))//kiem tra dieu kien tim kiem
			{
				if (temp < 16)
				{
					gotoxy(x + 10, y + 7 + temp);
					cout << dsl.lop[i].ma_lop;
					//s[temp] = dsl.lop[i].ten_lop;//gan ten lop cho chuoi s
					gotoxy(x + 20, y + 7 + temp);
					cout << rut_gon_text(dsl.lop[i].ten_lop, 20);

				}
				temp++;
			}
		}
		if (temp > 16)
		{
			gotoxy(x + 20, y + 7 + 16);
			cout << "(And " << temp - 16 << " more...)";
		}
		//gotoxy(x + 16 + a.length(), y + 2);//dua con tro chi vi ve thanh tim kiem
		gotoxy(x + 121 + a.length(), y + 26);
		hidecur(false);
	}
	int dem = 0;
	In_Hoa(a);
	// nhap xong ma lop
	for (int i = 0; i < dsl.sl; i++)
	{
		if (a == dsl.lop[i].ma_lop)
		{
			while (true)
			{
				bool exit = false;
				SINHVIEN sv;
				//cout << "NHAP THONG TIN SINH VIEN: ";
			createstring:
				string a = Tao_Ma_Sinh_Vien_Tu_Ma_Lop(dsl.lop[i]);
				for (NODESINHVIEN* k = dsl.lop[i].dssv.phead; k != NULL; k = k->pnext)
				{
					if (a == k->data.MASV)
						goto createstring;
				}
				sv.MASV = a;

				Plus_Nhap_thong_tin_sinh_vien(sv, x, y, exit);
				if (exit == true)
					return;
				gotoxy(x + 95, y + 9);
				cout << sv.MASV;
				NODESINHVIEN* p = KhoiTaoSinhVien(sv);
				Them_Vao_Cuoi(dsl.lop[i].dssv, p);
				dsl.lop[i].soluongsv++;
				dsl.lop[i].isnotempty = 1;
				//delete p;
				XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
				XoaManHinh(x + 96, y + 5, 30, 1);
				gotoxy(x + 96, y + 5);
				cout << "Danh sach sinh vien";
				gotoxy(x + 3, y + 30);
				cout << "THEM SINH VIEN " << sv.MASV << " VAO LOP " << dsl.lop[i].ma_lop;
				gotoxy(x + 13, y + 31);
				cout << " THANH CONG!";
				dem++;
				Sap_xep_ho_ten_tang_dan(dsl.lop[i].dssv);
				Sleep(1000);
			}
		}
	}
	if (dem == 0)
	{
		XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
		gotoxy(x + 10, y + 30);
		cout << "Lop khong ton tai!";
		Sleep(1000);
	}
	
}
void Plus_Nhap_thong_tin_sinh_vien(SINHVIEN &sv, int x, int y, bool &exit)
{
	exit = false;
	Khung_Nhap_Sinh_Vien(x, y);
	sv.ho = Nhap_thong_tin(x-15 + 66, y-3 + 14, exit,7);
	if (exit == true)
		return;
	ChuanHoaChu(sv.ho);
	sv.ten = Nhap_thong_tin(x-14 + 115, y-3 + 14, exit,15);
	if (exit == true)
		return;
	ChuanHoaChu(sv.ten);

	while (true)
	{
		XoaManHinh(x +66, y +19, 27, 1);
		sv.phai = Nhap_thong_tin(x - 15 + 66, y - 3 + 18,exit,3);
		if (exit == true)
			return;
		ChuanHoaChu(sv.phai);
		if (sv.phai == "Nam" || sv.phai == "Nu")
		break;
	}
	sv.password = Nhap_thong_tin(x-14 + 115, y-3 + 18,exit,18);
	if (exit == true)
		return;
}
void Plus_Xuat_danh_sach_sinh_vien(DANH_SACH_LOP dsl, string tenlop, int x, int y,int vt)
{
	ChuanHoaChu(tenlop);
	bool lopkhongtontai = true;
	for (int i = 0; i < dsl.sl; i++)
	{
		if (dsl.lop[i].ten_lop == tenlop)
		{
			lopkhongtontai = false;
			if (dsl.lop[i].soluongsv != 0)
			{
				{
					//system("cls");
					vebang4cot(x, y, 100, 12);
					gotoxy(2 + x, 1 + y);
					cout << "Ma sinh vien";
					gotoxy(27 + x, 1 + y);
					cout << "Ho ten";
					gotoxy(64 + x, 1 + y);
					cout << "Phai";
					gotoxy(77 + x, 1 + y);
					cout << "Password";
					int counter = 0;
					for (NODESINHVIEN* k = dsl.lop[i].dssv.phead; k != NULL; k = k->pnext)
					{
						if (k->data.MASV.length() != 0)
						{
							if (counter >= vt && counter < vt + 10)
							{
								gotoxy(2 + x, y + counter % 10 + 3);
								cout << k->data.MASV;
								gotoxy(27 + x, y + counter % 10 + 3);
								cout << k->data.ho << " " << k->data.ten;
								gotoxy(64 + x, y + counter % 10 + 3);
								cout << k->data.phai;
								gotoxy(77 + x, y + counter % 10 + 3);
								cout << k->data.password;
							}
							counter++;
						}
					}				
				}
			}
			else
			{
				gotoxy(x + 37, 8 + y);
				cout << "Lop " << dsl.lop[i].ma_lop << " khong co sinh vien nao! ";
			}
		}
	}
}
void Plus_Them_lop_hoc(int x, int y, DANH_SACH_LOP &dsl)
{
	int temp = 0;
	for (int i = 0; i < dsl.sl; i++)
	{
		if (i < 16)
		{
			gotoxy(x + 5, y + 7 + i);
			cout << dsl.lop[i].ma_lop;
			gotoxy(x + 20, y + 7 + i);
			cout << dsl.lop[i].ten_lop;
			temp++;
		}
	}
	if (temp>15)
	{
		gotoxy(x + 10, y + 7 + 16);
		cout << "(And " << dsl.sl - temp << " more...)";
	}
	XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
	hidecur(false);
	XoaManHinh(x + 123, y + 28, 28, 1);
	XoaManHinh(x + 123, y + 32, 28, 1);//xoa noi dung cu cua 2 thanh ma lop va ten lop
	Ve_HCN(30, 1, x + 122, y + 27);//tao khung nhap ma lop
	gotoxy(x + 112, y + 28);
	cout << "MA LOP: ";//tro toi cho nhap ma lop
	Ve_HCN(30, 1, x + 122, y + 31);//tao khung nhap ten lop
	gotoxy(x + 112, y + 32);
	cout << "TEN LOP: ";//tro toi cho nhap ten lop
nhapmalop:
	string a;//ma lop
	string b;//ten lop
	gotoxy(x + 123, y + 28);
	while (true)
	{
		char k = _getch();
		gotoxy(x + 123 + a.length(), y + 28);
		if (k == 8)//phim backspace
		{
			if (a.length() >= 1)
			{
				XoaManHinh(x + 122 + a.length(), y + 28, 1, 1);
				a.erase(a.size()-1);
				gotoxy(x + 122 + a.length(), y + 28);
			}
		}
		if (k >= 48 && k <= 57 && a.length() < 14)//hang phim so
		{
			a.push_back(k);
			gotoxy(x + 122 + a.length(), y + 28);
			cout << k;
		}
		if ((k >= 97 && k <= 122) && a.length() < 14)//phim ki tu va space
		{
			a.push_back(k);
			gotoxy(x + 122 + a.length(), y + 28);
			cout << k;
		}
		if (k == 27)
			return;
		if (k == 13)
			break;
	}
	In_Hoa(a);//chuan hoa ma lop

	if (a.length() == 0)
	{
		goto nhapmalop;
	}
	LOP p;
	if (Kiem_tra_trung_lop(dsl, a) == true)//kiem tra trung ma lop
	{
		gotoxy(x + 10, y + 30);
		cout << "Lop da ton tai, moi ban nhap lai !";
		XoaManHinh(x + 123, y + 28, 28, 1);
		XoaManHinh(x + 123, y + 32, 28, 1);//xoa noi dung cu cua 2 thanh ma lop va ten lop
		goto nhapmalop;
	}
	p.ma_lop = a;
nhapten:
	gotoxy(x + 123, y + 32);
	while (true)
	{
		gotoxy(x + 123 + b.length(), y + 32);
		char k = _getch();
		if (k == 8)//phim backspace
		{
			if (b.length() >= 1)
			{
				XoaManHinh(x + 122 + b.length(), y + 32, 1, 1);
				b.erase(b.size()-1);
				gotoxy(x + 122 + b.length(), y + 32);
			}
		}
		if (k >= 48 && k <= 57 && b.length() < 27)//hang phim so
		{
			b.push_back(k);
			gotoxy(x + 122 + b.length(), y + 32);
			cout << k;
		}
		if (b.length() < 27 && (k >= 97 && k <= 122) || k == ' ')//phim ki tu va space
		{
			b.push_back(k);
			gotoxy(x + 122 + b.length(), y + 32);
			cout << k;
		}
		if (k == 27)
			return;
		if (k == 13)
			break;
	}
	ChuanHoaChu(b);
	if (b.length() == 0)
		goto nhapten;
	p.ten_lop = b;
	dsl.lop[dsl.sl] = p;
//	KhoiTaoList(dsl.lop[dsl.sl].dssv);
	dsl.sl++;
	XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
	gotoxy(x + 5, y + 30);
	cout << "NHAP THANH CONG! ";//hien thi thong bao thanh cong
	Sap_xep_ten_lop_tang_dan(dsl);
	XoaManHinh(x + 110, y + 25, 45, 9);//xoa man hinh khung nhap thong tin
	XoaManHinh(x + 5, y + 7, 40, 17);//xoa man hinh o danh sach lop
	XoaManHinh(x + 49, y + 28, 55, 5);//xoa man hinh khung chuc nang
	Sleep(1500);
}
void Plus_Form_quan_ly_lop_hoc(int x, int y,DANH_SACH_LOP &dsl)
{
	khungquanlylophoc(x, y);
	gotoxy(x + 16, y + 2);
	string a;
	string s[200];
	int count=0;
	int tam = 0;
	for (int i = 0; i < dsl.sl; i++)
	{
		if (tam < 16)
		{
			gotoxy(x + 5, y + 7 + tam);
			cout << dsl.lop[i].ma_lop;
			gotoxy(x + 20, y + 7 + tam);
			cout << dsl.lop[i].ten_lop;
		}
		s[tam] = dsl.lop[i].ten_lop;//gan ten lop cho chuoi s
		
		tam++;
		count = tam;
		
	}
	if (tam > 16)
	{
		gotoxy(x + 10, y + 7 + 16);
		cout << "(And " << tam- 16 << " more...)";
	}
	while (true)
	{
	find:
		XoaManHinh(x + 49, y + 28, 55, 5);//xoa man hinh khung chuc nang//xoa man hinh khung chuc nang
		gotoxy(x + 50, y + 28);
		cout << "F1: Them lop";
		gotoxy(x + 80, y + 28);
		cout << "F2: Luu du lieu ";
		gotoxy(x + 50, y + 29);
		cout << "F11: Xem danh sach lop";
		gotoxy(x + 80, y + 29);
		cout << "F4: Them sinh vien";
		gotoxy(x + 50, y + 30);
		cout << "ESC: Thoat";
		XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
		gotoxy(x + 16 + a.length(), y + 2);// dua con tro chi vi ve thanh tim kiem
		hidecur(false);
		char k = _getch();
		while (k == 72 || k == -32)
		{
			k=_getch();
		}
		
		if (k == 27)
		{
			system("cls");
			return;
		}
		if (k == -123)//Nhan f11 de show toan bo lop
		{
			XoaManHinh(x + 49, y + 28, 55, 5);//xoa man hinh khung chuc nang
			XoaManHinh(x + 5, y + 7, 40, 17);//xoa man hinh o danh sach lop
			gotoxy(x + 60, y + 30);
			cout << "ESC: Quay lai khung tim kiem";
			int vt = 0;
			gotoxy(x + 3, y + 30);
			cout << "Dung phim mui ten trai/phai de xem danh sach";
			while (true)
			{
				Plus_Xuat_lop_hoc(x, y, vt, dsl);
				char k = _getch();
				hidecur(false);
				if (k == 77)
				{
					if (vt <= dsl.sl - 16)
						vt += 16;
						XoaManHinh(x + 5, y + 7, 40, 17);//xoa man hinh o danh sach lop
				}
				if (k == 75)
				{
					if (vt >= 16)
						vt -= 16;
					XoaManHinh(x + 5, y + 7, 40, 17);//xoa man hinh o danh sach lop
				}
				if (k == 27)
				{
					XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
					XoaManHinh(x + 5, y + 7, 40, 17);//xoa man hinh o danh sach lop
					break;
				}
				
				hidecur(true);
			}
			XoaManHinh(x + 5, y + 7, 45, 17);//xoa man hinh o danh sach lop
			XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
			gotoxy(x + 10, y + 30);
		}
		if (k == 59)//nhan phim f1 de them lop hoc
		{
			XoaManHinh(x + 49, y + 28, 55, 5);//xoa man hinh khung chuc nang
			gotoxy(x + 60, y + 30);
			cout << "ESC: Quay lai khung tim kiem";
			Plus_Them_lop_hoc(x, y, dsl);
			XoaManHinh(x + 110, y + 25, 45, 9);//xoa man hinh khung nhap thong tin
		}
		if (k == 60)//phim f2. chuc nang luu du lieu ra file
		{
			Ghi_file_danh_sach_lop(dsl);
			Ghi_file_dssv(dsl);
			XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
			gotoxy(x + 10, y + 30);
			cout << "LUU DU LIEU THANH CONG";
			Sleep(1000);
		}

		if (k == 62)// phim f4, chuc nang nhap hoc sinh vao lop
		{
			
			Plus_Nhap_Sv_Vao_Lop(dsl, x, y);
			XoaManHinh(x + 110, y + 25, 45, 9);//xoa man hinh khung nhap thong tin	
			XoaManHinh(x + 52, y + 7, 102, 17);//xoa dssv
		}
		// het chuc nang f4
		if (k == 8)//phim backspace
		{
			if (a.length() >= 1)
			{
				XoaManHinh(x + 15 + a.length(), y + 2, 1, 1);
				a.erase(a.size()-1);
				gotoxy(x + 15 + a.length(), y + 2);
			}
		}
		if (k >= 48 && k <= 57 && a.length() <= 40)//hang phim so
		{
			a.push_back(k);
			gotoxy(x + 15 + a.length(), y + 2);
			cout << k;
		}
		if (a.length() <= 40 && (k >= 97 && k <= 122) || k == ' ')//phim ki tu va space
		{
			a.push_back(k);
			gotoxy(x + 15 + a.length(), y + 2);
			cout << k;
		}
		if (k == 80 && count != 0)//phim xuong
		{
			XoaManHinh(x + 49, y + 28, 55, 5);//xoa man hinh khung chuc nang
			gotoxy(x + 60, y + 30);
			cout << "ESC: Quay lai khung tim kiem";
			break;
		}
		hidecur(true);
		//chuan hoa chu nhap vao
		string a1 = a;
		ChuanHoaChu(a1);
		string a2 = a;
		In_Hoa(a2);
		XoaManHinh(x + 5, y + 7, 45, 17);//xoa man hinh o danh sach lop
		int temp = 0;
		if (a.length() != 0)// xoa het
		{
			for (int i = 0; i < dsl.sl; i++)
			{
				if (ahaveb(dsl.lop[i].ma_lop, a2) || ahaveb(dsl.lop[i].ten_lop, a1))//kiem tra dieu kien tim kiem
				{
					if (temp < 16)
					{
						gotoxy(x + 5, y + 7 + temp);
						cout << dsl.lop[i].ma_lop;
						gotoxy(x + 20, y + 7 + temp);
						cout << rut_gon_text(dsl.lop[i].ten_lop, 20);
					}
					s[temp] = dsl.lop[i].ten_lop;//gan ten lop cho chuoi s
					temp++;
					count = temp;
				}
			}
		if (temp > 16)
			{
				gotoxy(x + 10, y + 7 + 16);
				cout << "(And " << temp - 16 << " more...)";
			}
		}
		else // ton tai ki tu
		{
			for (int i = 0; i < dsl.sl; i++)
			{				
				if (temp < 16)
					{
						gotoxy(x + 5, y + 7 + temp);
						cout << dsl.lop[i].ma_lop;
						gotoxy(x + 20, y + 7 + temp);
						cout << rut_gon_text(dsl.lop[i].ten_lop, 20);
					}
					s[temp] = dsl.lop[i].ten_lop;//gan ten lop cho chuoi s
					temp++;
					count = temp;
				}
			if (temp > 16)
			{
				gotoxy(x + 10, y + 7 + 16);
				cout << "(And " << temp - 16 << " more...)";
			}
		}
		gotoxy(x + 16 + a.length(), y + 2);//dua con tro chi vi ve thanh tim kiem
		//hidecur(false);		
	}
		XoaManHinh(x + 5, y + 7, 45, 17);//xoa man hinh o danh sach lop
		hidecur(true);	
		int vt1 = 0;
		while (true)
		{
			if (count > 15)
			{
				gotoxy(x + 3, y + 30);
				cout << "Dung phim mui ten trai/phai de xem danh sach";
			}
			
			//cmd = menu(s, 15, x + 16, y + 7, 0, cmd);
			int cmd = menuadvanced(s, x + 15, y + 7, 0, count);
			if (cmd == 99)
			{
				gotoxy(x + 16 + a.length(), y + 16);//nhan enter vao o "quay lai thanh tim kiem"
				goto find;
			}
			// xuat danh sach sinh vien	
				XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
				XoaManHinh(x + 49, y + 28, 55, 5);//xoa man hinh khung chuc nang
				gotoxy(x + 60, y + 30);
				cout << "ESC: Quay lai danh sach lop";
				int vt = 0;
				XoaManHinh(x + 52, y + 7, 102, 16);//xoa man hinh o danh sach sinh vien
				/*if (check_so_luong_sv(dsl,s[cmd]) <= 10)*/
				if (Check_so_luong_sv(dsl, s[cmd]) >= 10)
				{
					gotoxy(x + 3, y + 30);
					cout << "Dung phim mui ten trai/phai de xem danh sach";	
				}
				
				while (true)
				{
					Plus_Xuat_danh_sach_sinh_vien(dsl, s[cmd], x + 53, y + 7, vt);
					char k = _getch();
					if (k == 77)
					{
						if (vt <= Check_so_luong_sv(dsl, s[cmd]) - 10)
						{
							vt += 10;
							XoaManHinh(x + 52, y + 7, 102, 16);//xoa dssv
						}
					}
					if (k == 75)
					{
						if (vt >= 10)
						{
							vt -= 10;
							XoaManHinh(x + 52, y + 7, 102, 16);//xoa dssv
						}
					}
					if (k == 27)
					{				
						XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
						XoaManHinh(x + 52, y + 7, 102, 16);//xoa dssv
						XoaManHinh(x + 49, y + 28, 55, 5);//xoa man hinh khung chuc nang
						gotoxy(x + 60, y + 30);
						cout << "ESC: Quay lai khung tim kiem";
						break;
					}
				}				
	}		
}
void Plus_Xuat_lop_hoc(int x, int y, int vt, DANH_SACH_LOP dsl)
	{
	hidecur(true);
		for (int i = 0; i < dsl.sl; i++)
		{
			if (i >= vt &&i < vt + 16)
			{
				gotoxy(x + 5, y + 7 + i % 16);
				cout << dsl.lop[i].ma_lop;
				gotoxy(x + 20, y + 7 + i%16);
				cout << rut_gon_text(dsl.lop[i].ten_lop, 20);
			}
		}
		
		gotoxy(x + 45, y + 7 + 16);
		cout << (vt - vt % 16) / 16 + 1  << "/" << (dsl.sl - dsl.sl % 16) / 16 + 1;
		
	}

