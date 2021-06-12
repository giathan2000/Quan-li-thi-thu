#pragma once
#include"ctdl.h"
#include"tum_lum.h"
#include"doc_ghi_file.h"
#include"AVL.h"
#define MAX_MONHOC 200
MON_HOC* ds_monhoc[MAX_MONHOC];
int sl_monhoc = 0;
int sl_cauhoi = 0;
/////////khai bao//////////////
void DeleteArrPointer(MON_HOC* ds_monhoc[MAX_MONHOC], int sl_monhoc);
void luuMonHoc(MonHoc* ds_monhoc[MAX_MONHOC], int sl_monhoc);
void DemCauHoi(AVLTree root, string MAMH, int ds[10000], int &i);
int DsCauHoiCuaMonHoc(AVLTree root, string MAMH, int ds[10000]);
int TimMonHoc(MonHoc* ds_monhoc[MAX_MONHOC], int sl_monhoc, int flag, char input[15]);
void Sua_MMH_Tren_Cay(AVLTree &root, string mamh, string premamh);
bool Kiem_tra_trung_mon(MonHoc* ds_monhoc[MAX_MONHOC], string mamonhoc);
//void UserGV(DANH_SACH_LOP &dsl);
////////// cac ham co toa do///////////////
void Plus_Form_quan_ly_mon_hoc(int x, int y, AVLTree &root);
void Plus_Them_mon_hoc(int x, int y, MonHoc* ds_monhoc[MAX_MONHOC], int& sl_monhoc);
void Plus_Xuat_mon_hoc(int x, int y, int vt, MonHoc* ds_monhoc[MAX_MONHOC]);
void Plus_Nhap_thong_tin_cau_hoi(CauHoi& key, int x, int y, bool &exit);
void Plus_them_cau_hoi_vao_mon_hoc(AVLTree &root, int &sl_cauhoi,  int x, int y);
void Plus_Xuat_danh_sach_cau_hoi_thi(AVLTree root, string tenmonhoc, int x, int y);
void Plus_Sua_Mon_Hoc(MonHoc* ds_monhoc[], int& sl_monhoc, int x, int y, AVLTree &root);
void Plus_Xuat_1_Cau_Hoi(int pos, AVLTree root, int ds[1000], int x, int y);
void Plus_Xoa_Mon_Hoc(MonHoc * ds_monhoc[], int &sl_monhoc, int x, int y, AVLTree &root);
/////////////ket thuc khai bao//////////////
/////////////cac ham thuong/////////////
void DemCauHoi(AVLTree root, string MAMH, int ds[1000], int &i)
{
	if (root != NULL)
	{
		DemCauHoi(root->pLeft, MAMH, ds, i);
		if (root->key.MAMH == MAMH)
		{
			ds[i] = root->key.id;
			i++;
		}
		DemCauHoi(root->pRight, MAMH, ds, i);
	}
}
int Dem_so_cau_hoi_cua_mon_hoc(AVLTree root, string mamh)
{
	int dem = 0;
	if (root != NULL)
	{
		Dem_so_cau_hoi_cua_mon_hoc(root->pLeft, mamh);
		if (root->key.MAMH == mamh)
			dem++;
		Dem_so_cau_hoi_cua_mon_hoc(root->pRight, mamh);
	}
	return dem;
}
int Danh_Sach_Cau_Hoi(AVLTree root, string MAMH, int ds[1000])
{
	int i = 0;
	DemCauHoi(root, MAMH, ds, i);
	return i;
}
AVLTree timCauHoi(AVLTree root, int id)
{
	AVLTree p = root;
	while (p != NULL)
	{
		if (p->key.id > id)
		{
			p = p->pLeft;
			continue;
		}

		if (p->key.id < id)
		{
			p = p->pRight;
			continue;
		}

		if (p->key.id = id)
		{
			return p;
			break;
		}
	}
	return NULL;
}
void DeleteArrPointer(MON_HOC* ds_monhoc[MAX_MONHOC], int sl_monhoc)
{
	for (int i = 0; i < sl_monhoc; i++)
	{
		delete ds_monhoc[i];
	}
}
int TimMonHoc(MonHoc* ds_monhoc[MAX_MONHOC], int sl_monhoc, int flag, char input[15])
{
	//flag == 1 : tim theo ma mon hoc
	//flag == 0 : tim theo ten mon hoc
	char* str;

	for (int i = 0; i < sl_monhoc; i++)
	{
		str = (flag == 1) ? ds_monhoc[i]->MAMH : ds_monhoc[i]->TENMH;
		if (strcmp(str, input) == 0)
		{
			return i;
		}
	}
	return -1;
}
bool Kiem_tra_trung_mon(MonHoc* ds_monhoc[MAX_MONHOC], string mamonhoc)
{
	for (int i = 0; i < sl_monhoc; i++)
	{
		if (mamonhoc == ds_monhoc[i]->MAMH)
		{
			return true;
			break;
		}
	}
	return false;
}
void Sua_MMH_Tren_Cay(AVLTree &root, string mamh, string premamh)
{
	if (root != NULL)
	{
		Sua_MMH_Tren_Cay(root->pLeft, mamh,premamh);
		//do some thing
		if (root->key.MAMH == premamh)
			root->key.MAMH = mamh;
		Sua_MMH_Tren_Cay(root->pRight, mamh,premamh);
	}
}
void Xoa_Mon_Hoc_Tren_Cay(AVLTree &root, string mamh, int &sl_cauhoi)
{
	if (root != NULL)
	{
		Xoa_Mon_Hoc_Tren_Cay(root->pLeft, mamh, sl_cauhoi);
		Xoa_Mon_Hoc_Tren_Cay(root->pRight, mamh, sl_cauhoi);
		if (root->key.MAMH == mamh)
		{
			DelNode(root, root->key);
			sl_cauhoi--;
		}

	}
}
//////////cac ham gan toa do///////////////////
void Plus_Form_quan_ly_mon_hoc(int x, int y, AVLTree &root)
{
	khungquanlymonhoc(x, y);
	gotoxy(x + 16, y + 2);
	string a;
	string s[200]; //mang luu ten mon hoc
	string ma[200]; // mang luu ma mon hoc
	int count = 0;
	int tam = 0;
	for (int i = 0; i < sl_monhoc; i++)
	{
		if (tam < 16)
		{
			gotoxy(x + 5, y + 7 + tam);
			cout << ds_monhoc[i]->MAMH;
			gotoxy(x + 20, y + 7 + tam);
			cout << rut_gon_text(ds_monhoc[i]->TENMH,20);
		}
		s[tam] = ds_monhoc[i]->TENMH;//gan ten lop cho chuoi s
		ma[tam] = ds_monhoc[i]->MAMH;
		tam++;
		count = tam;
	}
	if (tam > 16)
	{
		gotoxy(x + 20, y + 7 + 16);
		cout << "(And " << tam - 16 << " more...)";
	}
	while (true)
	{
	find:
		XoaManHinh(x + 49, y + 28, 55, 5);//xoa man hinh khung chuc nang//xoa man hinh khung chuc nang
		gotoxy(x + 50, y + 28);
		cout << "F1: Nhap moc hoc";
		gotoxy(x + 80, y + 28);
		cout << "F2: Luu du lieu ";
		gotoxy(x + 50, y + 29);
		cout << "F11: Xuat danh sach mon hoc";
		gotoxy(x + 80, y + 29);
		cout << "F4: Nhap cau hoi thi";
		gotoxy(x + 50, y + 30);
		cout << "F5: Sua mon hoc";
		gotoxy(x + 80, y + 30);
		cout << "F6: Xoa mon hoc";
		gotoxy(x + 50, y + 31);
		cout << "ESC: THOAT";
		XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
		gotoxy(x + 16 + a.length(), y + 2);// dua con tro chi vi ve thanh tim kiem
		hidecur(false);
		char k = _getch();
		while (k == 72 || k == -32)
		{
			k = _getch();
		}
		if (k == 64)// phim f6 -> Xoa mon hoc
		{
			Plus_Xoa_Mon_Hoc(ds_monhoc, sl_monhoc, x, y, root);
			XoaManHinh(x + 110, y + 25, 45, 9);//xoa man hinh khung nhap thong tin
			XoaManHinh(x + 49, y + 28, 55, 5);//xoa man hinh khung chuc nang
			XoaManHinh(x + 52, y + 7, 102, 16);//xoa man hinh o danh sach sinh vien
			Sleep(1500);
		}
		if (k == 63)// f5. sua mon hoc
		{
			Plus_Sua_Mon_Hoc(ds_monhoc, sl_monhoc, x, y, root);
			XoaManHinh(x + 110, y + 25, 45, 9);//xoa man hinh khung nhap thong tin
			XoaManHinh(x + 49, y + 28, 55, 5);//xoa man hinh khung chuc nang
			XoaManHinh(x + 52, y + 7, 102, 16);//xoa man hinh o danh sach sinh vien
			Sleep(1500);
		}
		if (k == 27)// esc -> return
		{
			system("cls");
			return;
		}
		if (k == -123)//Nhan f11 de show toan bo lop
		{
			XoaManHinh(x + 5, y + 7, 40, 17);//xoa man hinh o danh sach lop
			XoaManHinh(x + 49, y + 28, 55, 5);//xoa man hinh khung chuc nang
			gotoxy(x + 60, y + 30);
			cout << "ESC: Quay lai khung tim kiem";
			int vt = 0;
			gotoxy(x + 3, y + 30);
			cout << "Dung phim mui ten trai/phai de xem danh sach";
			while (true)
			{
				Plus_Xuat_mon_hoc(x, y, vt, ds_monhoc);															// todo(1) viet ham xuat mon hoc (done)
				char k = _getch();
				hidecur(false);
				if (k == 77)
				{
					if (vt <= sl_monhoc - 16)
					{
						vt += 16;
						XoaManHinh(x + 10, y + 7, 40, 17);
					}//xoa man hinh o danh sach lop
				}
				if (k == 75)
				{
					if (vt >= 16)
					{
						vt -= 16;
						XoaManHinh(x + 10, y + 7, 40, 15);
					}//xoa man hinh o danh sach lop
				}
				if (k == 27)
				{
					XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
					XoaManHinh(x + 10, y + 7, 40, 17);//xoa man hinh o danh sach lop
					break;
				}
				hidecur(true);
			}
			XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
			gotoxy(x + 10, y + 30);
		}
		if (k == 59)//nhan phim f1 de them lop hoc
		{		
			Plus_Them_mon_hoc(x, y, ds_monhoc, sl_monhoc);
			XoaManHinh(x + 110, y + 25, 45, 9);//xoa man hinh khung nhap thong tin
		}
		if (k == 60)//phim f2. chuc nang luu du lieu ra file
		{
			luuMonHoc(ds_monhoc, sl_monhoc);
			luuCauHoi(root, sl_cauhoi);
			XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
			gotoxy(x + 10, y + 30);
			cout << "LUU DU LIEU THANH CONG";
			Sleep(1000);
		}
		if (k == 62)// phim f4, chuc nang nhap cau hoi thi
		{
			Plus_them_cau_hoi_vao_mon_hoc(root, sl_cauhoi, x, y);
			XoaManHinh(x + 110, y + 25, 45, 9);//xoa man hinh khung nhap thong tin
		}
		if (k == 8)//phim backspace
		{
			if (a.length() >= 1)
			{
				XoaManHinh(x + 15 + a.length(), y + 2, 1, 1);
				a.erase(a.size()-1);
				gotoxy(x + 15 + a.length(), y + 2);
			}
		}
		if (k >= 48 && k <= 57 && a.length() < 40)//hang phim so
		{
			a.push_back(k);
			gotoxy(x + 15 + a.length(), y + 2);
			cout << k;
		}
		if ( a.length() < 14 && (k >= 97 && k <= 122) || k == ' ')//phim ki tu va space
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
			hidecur(true);
			break;
		}
		hidecur(true);
		//chuan hoa chu nhap vao
		string a1 = a;
		ChuanHoaChu(a1);
		string a2 = a;
		In_Hoa(a2);
		XoaManHinh(x + 5, y + 7, 40, 17);//xoa man hinh o danh sach lop
		int temp = 0;
		if (a.length() != 0)// xoa het
		{

			for (int i = 0; i < sl_monhoc; i++)
			{
				if (ahaveb(ds_monhoc[i]->MAMH, a2) || ahaveb(ds_monhoc[i]->TENMH, a1))//kiem tra dieu kien tim kiem
				{
					if (temp < 16)
					{
						gotoxy(x + 5, y + 7 + temp);
						cout << ds_monhoc[i]->MAMH;
						gotoxy(x + 20, y + 7 + temp);
						cout << rut_gon_text(ds_monhoc[i]->TENMH, 20);
					}
					s[temp] = ds_monhoc[i]->TENMH;//gan ten lop cho chuoi s
					ma[temp] = ds_monhoc[i]->MAMH;
					temp++;
					count = temp;
				}
			}
			if (temp > 16)
			{
				gotoxy(x + 20, y + 7 + 16);
				cout << "(And " << temp - 16 << " more...)";
			}
		}
		else // ton tai ki tu
		{
			for (int i = 0; i < sl_monhoc; i++)
			{
				if (temp < 16)
				{
					gotoxy(x + 5, y + 7 + temp);
					cout << ds_monhoc[i]->MAMH;
					gotoxy(x + 20, y + 7 + temp);
					cout << rut_gon_text(ds_monhoc[i]->TENMH, 20);
				}
				s[temp] = ds_monhoc[i]->TENMH;//gan ten lop cho chuoi s
				ma[temp] = ds_monhoc[i]->MAMH;
				temp++;
				count = temp;
			}
			if (temp > 16)
			{
				gotoxy(x + 20, y + 7 + 16);
				cout << "(And " << temp - 16 << " more...)";
			}
		}
		gotoxy(x + 16 + a.length(), y + 2);//dua con tro chi vi ve thanh tim kiem
		hidecur(false);
	}
	XoaManHinh(x + 5, y + 7, 40, 17);//xoa man hinh o danh sach lop
	hidecur(true);
	int vt1 = 0;
	while (true)
	{
		if (count > 16)
		{
			gotoxy(x + 3, y + 30);
			cout << "Dung phim mui ten trai/phai de xem danh sach";
		}
		int cmd = menuadvanced(s, x + 15, y + 7, 0, count);
		if (cmd == 99)
		{
			gotoxy(x + 16 + a.length(), y + 16);//nhan enter vao o "quay lai thanh tim kiem"
			hidecur(false);
			goto find;
		}
		// xuat danh sach cau hoi
		XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
		XoaManHinh(x + 49, y + 28, 55, 5);//xoa man hinh khung chuc nang
		gotoxy(x + 60, y + 30);
		cout << "ESC: Quay lai danh sach lop";
		Plus_Xuat_danh_sach_cau_hoi_thi(root, ma[cmd], x, y);	
	}
}
void Plus_Them_mon_hoc(int x, int y, MonHoc* ds_monhoc[MAX_MONHOC], int& sl_monhoc)
{
	XoaManHinh(x + 49, y + 28, 55, 5);//xoa man hinh khung chuc nang
	gotoxy(x + 60, y + 30);
	cout << "ESC: Quay lai khung tim kiem";
	ds_monhoc[sl_monhoc] = new MonHoc;
	int temp = 0;
	for (int i = 0; i < sl_monhoc; i++)
	{
		if (i < 16)
		{
			gotoxy(x + 5, y + 7 + i);
			cout << ds_monhoc[i]->MAMH;
			gotoxy(x + 20, y + 7 + i);
			cout << rut_gon_text(ds_monhoc[i]->TENMH,20);
			temp++;
		}
	}
	if (temp>15)
	{
		gotoxy(x + 20, y + 7 + 16);
		cout << "(And " << sl_monhoc - temp << " more...)";
	}
	XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
	hidecur(false);
	XoaManHinh(x + 123, y + 28, 28, 1);
	XoaManHinh(x + 123, y + 32, 28, 1);//xoa noi dung cu cua 2 thanh ma lop va ten lop
	Ve_HCN(30, 1, x + 122, y + 27);//tao khung nhap ma lop
	gotoxy(x + 112, y + 28);
	cout << "MA MON: ";//tro toi cho nhap ma lop
	Ve_HCN(30, 1, x + 122, y + 31);//tao khung nhap ten lop
	gotoxy(x + 112, y + 32);
	cout << "TEN MON: ";//tro toi cho nhap ten lop
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
		goto nhapmalop;
	if (Kiem_tra_trung_mon(ds_monhoc, a) == true)//kiem tra trung ma lop														//viet ham kiem tra trung ma mon hoc
	{
		gotoxy(x + 10, y + 30);
		cout << "Mon hoc da ton tai, moi ban nhap lai !";
		XoaManHinh(x + 123, y + 28, 28, 1);
		XoaManHinh(x + 123, y + 32, 28, 1);//xoa noi dung cu cua 2 thanh ma lop va ten lop
		goto nhapmalop;
	}
	strcpy(ds_monhoc[sl_monhoc]->MAMH, a.c_str());
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

		if (b.length() <= 27 && (k >= 32 && k <= 64 || k >= 91 && k <= 126 || k == 95))//phim ki tu va space
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
	strcpy(ds_monhoc[sl_monhoc]->TENMH, b.c_str());//----------------------------------------------------------------------------------
	sl_monhoc++;
	//--------------------tro den cay nhi phan
	XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
	gotoxy(x + 10, y + 30);
	cout << "NHAP THANH CONG! ";//hien thi thong bao thanh cong
	XoaManHinh(x + 110, y + 25, 45, 9);//xoa man hinh khung nhap thong tin
	XoaManHinh(x + 5, y + 7, 40, 17);//xoa man hinh o danh sach lop
	XoaManHinh(x + 49, y + 28, 55, 5);//xoa man hinh khung chuc nang
	Sleep(1000);
}
void Plus_Xuat_mon_hoc(int x, int y, int vt, MonHoc* ds_monhoc[MAX_MONHOC])
{
	for (int i = 0; i < sl_monhoc; i++)
	{
		if (i >= vt &&i < vt + 16)
		{
			gotoxy(x + 10, y + 7 + i % 16);
			cout << ds_monhoc[i]->MAMH;
			gotoxy(x + 20, y + 7 + i % 16);
			cout << rut_gon_text(ds_monhoc[i]->TENMH, 20);
		}
	}

}   
void Plus_them_cau_hoi_vao_mon_hoc(AVLTree &root, int &sl_cauhoi, int x, int y)
{
	XoaManHinh(x + 49, y + 28, 55, 5);//xoa man hinh khung chuc nang
	string a;
	gotoxy(x + 60, y + 30);
	cout << "ESC: Quay lai khung tim kiem";
	Ve_HCN(30, 1, x + 120, y + 25);//tao khung nhap ma lop
	gotoxy(x + 110, y + 26);
	cout << "MA MON: ";//tro toi cho nhap ma lop
	gotoxy(x + 121, y + 26);
	while (true)
	{
		hidecur(false);
		char k = _getch();
		if (k == 27)
		{
			XoaManHinh(x + 110, y + 25, 45, 9);//xoa man hinh khung nhap thong tin
			return;
		}
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
		if ((k >= 97 && k <= 122) && a.length() < 14)//phim ki tu va space
		{
			a.push_back(k);
			gotoxy(x + 120 + a.length(), y + 26);
			cout << k;
		}
		if (k == 13)
			break;
		hidecur(true);
		string a2 = a;
		In_Hoa(a2);
		XoaManHinh(x + 5, y + 7, 40, 17);//xoa man hinh o danh sach lop
		int temp = 0;
		for (int i = 0; i < sl_monhoc; i++)
		{
			if (ahaveb(ds_monhoc[i]->MAMH, a2))//kiem tra dieu kien tim kiem
			{
				if (temp < 16)
				{
					gotoxy(x + 5, y + 7 + temp);
					cout << ds_monhoc[i]->MAMH;			
					gotoxy(x + 20, y + 7 + temp);
					cout << rut_gon_text(ds_monhoc[i]->TENMH, 20);
				}
				temp++;
			}
		}
		if (temp > 16)
		{
			gotoxy(x + 20, y + 7 + 16);
			cout << "(And " << temp - 16 << " more...)";
		}
		gotoxy(x + 121 + a.length(), y + 26);
	}
	In_Hoa(a);
	CauHoi key;
	key.MAMH = a;
	while (true)
	{
		bool tontai = false;
		int stt_monhoc = 0;
		for (int i = 0; i < sl_monhoc; i++)
		{
			
			if (strcmp(key.MAMH.c_str(), ds_monhoc[i]->MAMH) == 0)
			{
				tontai = true;
				break;
			}
			stt_monhoc++;
		}
		bool exit = false;
		if (tontai == true)
		{		
			Plus_Nhap_thong_tin_cau_hoi(key, x, y, exit);
			if (exit == true) return;
			key.id = taoId();
			ds_monhoc[stt_monhoc]->ds_id_cauhoi[ds_monhoc[stt_monhoc]->sl_cauhoi] = key.id;
			ds_monhoc[stt_monhoc]->sl_cauhoi++;
			sl_cauhoi++;
			InsertNode(root, key);
		}
		else
		{
			XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
			gotoxy(x + 10, y + 30);
			cout << "Mon hoc khong ton tai!";
			Sleep(700);
		}
	}
}
void Plus_Nhap_thong_tin_cau_hoi(CauHoi& key, int x, int y, bool &exit)
{
	exit = false;
	string temp[5];
	int count = 0;
	string final;
	Khung_nhap_cau_hoi(x, y);
	int line = 5;
enter:
	string qus;
	int pos = qus.length();
	gotoxy(x + 68, y + 3+ line);
	if (qus.length() != 0);
	cout << qus;
	while (true)
		{
			char k ;
			while (true)
			{
				k = _getch();
				if (k == -32)
				{
					k = _getch();
					if (k==72 || k==75 || k==80 || k== 77)
					{
						continue;
					}									
				}
				else
				{
					//k = _getch();
					break;
				}
			}
			if (k == 8)//phim backspace
			{
				if (qus.length() > 0)
				{
					XoaManHinh(x + 67 + qus.length(), y + 3 + line, 1, 1);
					Delete_pos(qus, pos);
					pos--;
					gotoxy(x + 68, y + 3 + line);
					if (qus.length() != 0)
					{
						cout << qus;
					}
				}
				else
				{
					if (count >= 1)
					{
						line--;
						qus = temp[count - 1];
						count--;
						gotoxy(x + 68, y + 3 + line);
						if (qus.length() != 0)
						{
							cout << qus;
						}
						pos = qus.length();
						Delete_pos(qus, pos);
					}
				}
			}
			if ((k >= 32 && k <= 43 || k >= 91 && k <= 126 || k == 95 || k>=45 && k<=90) && count <=4)//hang phim so
			{
				Insert_string(qus, pos, k);
				pos++;
				gotoxy(x + 68, y + 3 + line);
				cout << qus;
				if (qus.length() >= 78 || qus.length() >= 72 && qus[qus.length()] == ' ')
				{
					temp[count] = qus;
					if (count <=4)
					{
						line++;
						count++;
						goto enter;
					}
				}
			}
			if (k == 27)
			{
				XoaManHinh(x + 52, y + 7, 102, 17);
				exit = true;
				return;
			}
			if (k == 13)
			{
				if (count == 5)
					count--;
				for (int i = 0; i <= count; i++)
				{
					final.append(temp[i]);
				}
				final.append(qus);
				if (final.length() >= 1)
					break;
			}
		}
		key.qus = final;
		gotoxy(x + 63, y + 14);
		key.opt[0] = Nhap_Dap_An(x - 1, y + 10);
		key.opt[1] = Nhap_Dap_An(x + 49, y + 10);
		key.opt[2] = Nhap_Dap_An(x - 1, y + 14);
		key.opt[3] = Nhap_Dap_An(x + 49, y + 14);
		char answer;
		while (true)
		{
		input:
			string answershow;
			XoaManHinh(x + 101, y + 22, 1, 1);
			gotoxy(x + 101, y + 22);
			char k = _getch();
			if (k <= 100 && k >= 97 && answershow.length() < 1)
			{
				answershow.push_back(k);
				gotoxy(x + 101, y + 22);
				cout << answershow;
				char x = _getch();
				if (x == 13) // phim enter
				{
					answer = k;
					break;
				}
				if (x == 27)
				{
					goto input;
				}
			}	
		}
		key.ans = answer - 97;
	//	cout << key.ans;
		XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
		gotoxy(x + 10, y + 30);
		cout << "Nhap cau hoi thanh cong!";
		Sleep(1000);
	gotoxy(x + 96, y + 5);
	cout << "Danh sach cau hoi thi";
	XoaManHinh(x + 52, y + 7, 102, 17);//xoa danh sach cau hoi
}

void Plus_Xuat_1_Cau_Hoi(int pos, AVLTree root, int ds[1000], int x, int y)
{
	string temp[5];
	string cauhoi = timCauHoi(root, ds[pos])->key.qus;
	int n = (cauhoi.length() - cauhoi.length() % 80) / 80 + 1;
	if (n == 1)
	{
		gotoxy(x + 67, y + 8);
		cout << cauhoi;
	}
	else
	{
		for (int i = 1; i < n; i++)
		{
			gotoxy(x + 67, y + (i - 1) + 8);
			stringcopy(80, (i - 1) * 80, cauhoi, temp[i - 1]);
			cout << temp[i - 1];
		}
		gotoxy(x + 67, y + n - 1 + 8);
		stringcopy(cauhoi.length() % 80, (n - 1) * 80, cauhoi, temp[n - 1]);
		cout << temp[n - 1];
	}
	Xuat_Thanh_Phan_Cau_Hoi(timCauHoi(root, ds[pos])->key.opt[0], x - 1, y, 28);
	Xuat_Thanh_Phan_Cau_Hoi(timCauHoi(root, ds[pos])->key.opt[1], x + 49, y, 28);
	Xuat_Thanh_Phan_Cau_Hoi(timCauHoi(root, ds[pos])->key.opt[2], x - 1, y + 4, 28);
	Xuat_Thanh_Phan_Cau_Hoi(timCauHoi(root, ds[pos])->key.opt[3], x + 49, y + 4, 28);
	gotoxy(x + 101, y + 22);
	cout << (char)(timCauHoi(root, ds[pos])->key.ans+65);
}
void Plus_Xuat_danh_sach_cau_hoi_thi(AVLTree root, string MAMH, int x, int y)
{
	
	int ds[1000];
	int soluong = Danh_Sach_Cau_Hoi(root, MAMH, ds);
	if (soluong>1)
	{
		gotoxy(x + 3, y + 30);
		cout << "Dung phim mui ten trai/phai de xem danh sach";
	}
	int count = 0; 
	//cout << soluong<<"So luong o day neeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee";
	if (soluong > 0)
	{
		
		while (true)
		{
			Khung_nhap_cau_hoi(x, y);
			Plus_Xuat_1_Cau_Hoi(count, root, ds, x, y);
			gotoxy(x + 127, y + 23);
			cout <<"Cau hoi "<< count + 1 << "/" << soluong;
			hidecur(true);
			char k = _getch();
			if (k == 75)
			{
				if (count > 0)
				{
					XoaManHinh(x + 52, y + 7, 102, 17);//xoa man hinh o danh sach sinh vien
					count--;
				}
			}
			if (k == 77)
			{
				if (count < soluong-1)
				{
					XoaManHinh(x + 52, y + 7, 102, 17);//xoa man hinh o danh sach sinh vien
					count++;
				}
			}
			if (k == 27)
			{
				XoaManHinh(x + 49, y + 28, 55, 5);//xoa man hinh khung chuc nang
				XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
				XoaManHinh(x + 52, y + 7, 102, 17);//xoa dssv
				gotoxy(x + 60, y + 30);
				cout << "ESC: Quay lai khung tim kiem";
				break;
			}

		}
	}
	else
	{
		gotoxy(x + 80, y + 13);
		cout << "Mon " << MAMH << " chua co cau hoi nao!";
	}
}
void Plus_Sua_Mon_Hoc(MonHoc* ds_monhoc[], int& sl_monhoc, int x, int y, AVLTree &root)
{
	XoaManHinh(x + 49, y + 28, 55, 5);//xoa man hinh khung chuc nang
	string a;
	Ve_HCN(30, 1, x + 120, y + 25);//tao khung nhap ma lop
	gotoxy(x + 110, y + 26);
	cout << "MA MON: ";//tro toi cho nhap ma lop
	XoaManHinh(x + 49, y + 28, 55, 5);//xoa man hinh khung chuc nang
	gotoxy(x + 121, y + 26);
	while (true)
	{
		hidecur(false);
		char k = _getch();
		if (k == 27)
		{
			XoaManHinh(x + 110, y + 25, 45, 9);//xoa man hinh khung nhap thong tin
			return;
		}
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
		if ((k >= 97 && k <= 122) && a.length() < 14)//phim ki tu va space
		{
			a.push_back(k);
			gotoxy(x + 120 + a.length(), y + 26);
			cout << k;
		}
		if (k == 13)
			break;
		hidecur(true);
		string a2 = a;
		In_Hoa(a2);
		XoaManHinh(x + 5, y + 7, 40, 17);//xoa man hinh o danh sach lop
		//cout << "xoa man hinh o day";
		int temp = 0;
		for (int i = 0; i < sl_monhoc; i++)
		{
			if (ahaveb(ds_monhoc[i]->MAMH, a2))//kiem tra dieu kien tim kiem
			{
				if (temp < 16)
				{
					gotoxy(x + 5, y + 7 + temp);
					cout << ds_monhoc[i]->MAMH;
					gotoxy(x + 20, y + 7 + temp);
					cout << rut_gon_text(ds_monhoc[i]->TENMH, 20);
				}
				temp++;
			}
		}
		if (temp > 16)
		{
			gotoxy(x + 20, y + 7 + 16);
			cout << "(And " << temp - 16 << " more...)";
		}
		gotoxy(x + 121 + a.length(), y + 26);
	}
	In_Hoa(a);
	char mamh[50];
	strcpy(mamh, a.c_str());
	int pos = TimMonHoc(ds_monhoc, sl_monhoc, 1, mamh);
	if (pos >= 0)
	{
		string mamh, tenmh;
		Khung_sua_mon_hoc(x, y);
		mamh = ds_monhoc[pos]->MAMH;
		string premamh = ds_monhoc[pos]->MAMH;
		//cout << "Ma mon hoc o day ne :" << mamh;
		tenmh = ds_monhoc[pos]->TENMH;
		gotoxy(x + 81, y + 16);
		cout << tenmh;
		gotoxy(x + 3, y + 30);
		cout << "   Dung phim mui ten len/ xuong de";
		gotoxy(x + 3, y + 31);
		cout << " thay doi vi tri, nhan enter de luu";
		batdaunhap:
		bool canexit = false;
		while (canexit == false)
		{
			Editable_Infor(mamh, x, y, 14, false, canexit);
			Editable_Infor(tenmh, x, y + 3, 48, true, canexit);
		}
		In_Hoa(mamh);
		ChuanHoaChu(tenmh);
		char kt[50];
		strcpy(kt, mamh.c_str());
		if (TimMonHoc(ds_monhoc, sl_monhoc, 1, kt) >= 0 && TimMonHoc(ds_monhoc, sl_monhoc, 1, kt) != pos)
		{
			XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
			gotoxy(x + 10, y + 30);
			cout << "Ma mon hoc da ton tai!";
			goto batdaunhap;
		}
		else
		{
			strcpy(ds_monhoc[pos]->MAMH, mamh.c_str());
			strcpy(ds_monhoc[pos]->TENMH, tenmh.c_str());
			XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
			gotoxy(x + 10, y + 30);
			Sua_MMH_Tren_Cay(root, mamh,premamh);
			cout << "Sua mon hoc thanh cong!";
		}
	}
	else
	{
		XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
		gotoxy(x + 10, y + 30);
		cout << "Mon hoc khong ton tai!";
	}
}
void Plus_Xoa_Mon_Hoc(MonHoc * ds_monhoc[], int &sl_monhoc, int x, int y, AVLTree &root)
{
	XoaManHinh(x + 49, y + 28, 55, 5);//xoa man hinh khung chuc nang
	string a;//ma mon hoc
	Ve_HCN(30, 1, x + 120, y + 25);//tao khung nhap ma lop
	gotoxy(x + 110, y + 26);
	cout << "MA MON: ";//tro toi cho nhap ma lop
	XoaManHinh(x + 49, y + 28, 55, 5);//xoa man hinh khung chuc nang
	gotoxy(x + 121, y + 26);
	while (true)
	{
		hidecur(false);
		char k = _getch();
		while (k == -32)
		{
			k = _getch();
		}
		if (k == 27)
		{
			XoaManHinh(x + 110, y + 25, 45, 9);//xoa man hinh khung nhap thong tin
			return;
		}
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
		if (((k >= 97 && k <= 122) || k == ' ') &&  a.length() < 14)//phim ki tu va space
		{
			a.push_back(k);
			gotoxy(x + 120 + a.length(), y + 26);
			cout << k;
		}
		if (k == 13)
			break;
		hidecur(true);
		string a2 = a;
		In_Hoa(a2);
		XoaManHinh(x + 5, y + 7, 40, 17);//xoa man hinh o danh sach lop
		int temp = 0;
		for (int i = 0; i < sl_monhoc; i++)
		{
			if (ahaveb(ds_monhoc[i]->MAMH, a2))//kiem tra dieu kien tim kiem
			{
				if (temp < 16)
				{
					gotoxy(x + 5, y + 7 + temp);
					cout << ds_monhoc[i]->MAMH;
					//s[temp] = ds_monhoc[i]->MAMH;//gan ten lop cho chuoi s
					gotoxy(x + 20, y + 7 + temp);
					cout << rut_gon_text(ds_monhoc[i]->TENMH, 20);
				}
				temp++;
			}
		}
		if (temp > 16)
		{
			gotoxy(x + 20, y + 7 + 16);
			cout << "(And " << temp - 16 << " more...)";
		}
		gotoxy(x + 121 + a.length(), y + 26);
	}
	In_Hoa(a);
	char mamh[50];
	strcpy(mamh, a.c_str());
	int pos = TimMonHoc(ds_monhoc, sl_monhoc, 1, mamh);
	if (pos < 0)
	{
		XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
		gotoxy(x + 10, y + 30);
		cout << "Khong tim thay mon hoc can xoa";
		Sleep(1000);
	}
	else
	{
		//delete ds_monhoc[pos];
		for (int i = pos; i < sl_monhoc - 1; i++)
		{
			ds_monhoc[i] = ds_monhoc[i + 1];
		}
		sl_monhoc--;
		Xoa_Mon_Hoc_Tren_Cay(root, a,sl_cauhoi);
		XoaManHinh(x + 2, y + 28, 46, 7);//XOA MAN HINH KHUNG NOTI
		gotoxy(x + 10, y + 30);
		cout << "Xoa mon hoc thanh cong!";
		Sleep(1000);
	}
}
