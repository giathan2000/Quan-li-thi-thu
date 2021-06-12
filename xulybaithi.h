//
#include"ctdl.h"
#include <pthread.h>
#include"doc_ghi_file.h"
#include"AVL.h"
#include"xulylophoc.h"
#include"xulymonhoc.h"
#include"tum_lum.h"
#include<math.h>
#pragma once
////Khai bao
void hdsd(int flag);
void taoDeKT(int ds_cauhoikt[60], MonHoc *ds_monhoc[MAX_MONHOC], int stt_monhoc, int sl_cauhoiKT);
void setDirection(int stt, int sl_cauhoiKT);
int chonMonHoc(MonHoc *ds_monhoc[MAX_MONHOC], PTR_BaiKT p, int sl_monhoc);
void* tinhGio(void* unused);
int thiTracNghiem(string mssv);
bool timeout();
int menu_cauhoi(string s[4], int n, int x, int y, int flag, int cmd);
//
int thoigianKT = 0;
void hdsd(int flag)
{
	//flag == 1 hdsd menu chon mon thi
	//flag == 0 hdsd menu thi trac nghiem

	gotoxy(10, 0);
	cout << "                                                                                                           ";
	gotoxy(10, 0);
	if (flag == 1)
	{
		cout << "ESC : thoat | ";
		cout << "UP/DOWN : chon mon thi | ";
		cout << "LEFT/RIGHT : chuyen trang ";
	}
	else
	{
		cout << "ESC/F3 : nop bai | ";
		cout << "UP/DOWN/ENTER : chon dap an | ";
		cout << "LEFT/RIGHT : doi cau hoi ";
	}
}
void taoDeKT(int ds_cauhoikt[60], MonHoc *ds_monhoc[MAX_MONHOC], int stt_monhoc, int sl_cauhoiKT)
{
	int temp_ds_id_cauhoi[10000];

	for (int i = 0; i < ds_monhoc[stt_monhoc]->sl_cauhoi; i++)
	{
		temp_ds_id_cauhoi[i] = ds_monhoc[stt_monhoc]->ds_id_cauhoi[i];
	}

	srand(time(NULL));
	int  minN = 0;
	int j = 0;
	for (int i = ds_monhoc[stt_monhoc]->sl_cauhoi - 1; i >= 0; i--)
	{
		int r = minN + (rand()) % (i + 1 - minN);
		int t = temp_ds_id_cauhoi[r];

		temp_ds_id_cauhoi[r] = temp_ds_id_cauhoi[i];
		temp_ds_id_cauhoi[i] = t;
		ds_cauhoikt[j] = t;
		j++;
		if (j == sl_cauhoiKT) break;
	}
}
void setAnswer(int stt, int ans, int sl_cauhoiKT)
{
	int x = 26 + ((stt) % 10) * 4;
	int y = 18 + (stt - (stt % 10)) / 10;
	gotoxy(x, y);
	cout << stt + 1 << (char)(65 + ans);
}
void setDirection(int stt, int sl_cauhoiKT)
{
	sl_cauhoiKT--;
	if (stt == 0 && sl_cauhoiKT >0)
	{
		gotoxy(37, 16);
		cout << "                                ";
		gotoxy(44, 16);
		cout << ">>...";

	}
	else if (stt > 0 && stt < sl_cauhoiKT)
	{
		gotoxy(37, 16);
		cout << "                                ";
		gotoxy(37, 16);
		cout << "...<<  >>...";
	}
	else if (stt == sl_cauhoiKT)
	{
		gotoxy(37, 16);
		cout << "                                ";
		gotoxy(37, 16);
		cout << "...<<";
	}
}
int chonMonHoc(MonHoc *ds_monhoc[MAX_MONHOC], PTR_BaiKT p, int sl_monhoc)
{
	//	system("cls");
	hidecur(true);
	int now = 0;
	int x = 40;
	int x_y = 17;
	int y = 5;
	int page_number = 1;
	int prenow = -1;
	int key = 0;
	system("cls");
	hdsd(1);
	khungChonMonHoc(1);
	for (int i = 0; i < sl_monhoc; i++)
	{
		gotoxy(x, y + i);
		if (i == now)
		{
			SetConsoleTextAttribute(console, 240);
			cout << ds_monhoc[i]->MAMH;
			gotoxy(x + x_y, y + i);
			cout << ds_monhoc[i]->TENMH;
			SetConsoleTextAttribute(console, 15);
		}
		else
		{
			SetConsoleTextAttribute(console, 15);
			cout << ds_monhoc[i]->MAMH;
			gotoxy(x + x_y, y + i);
			cout << ds_monhoc[i]->TENMH;
			//gotoxy(x,y+i+1);	
		}
	}

	while (true){
		//system("cls");
		int max_row_page = page_number * 10 > sl_monhoc ? sl_monhoc : page_number * 10;
		//			gotoxy(0,30);
		//			cout << now << "  " << page_number << "   "<<max_row_page;


		key = getch();
		int get_now = max_row_page % 10 == 0 ? 9 : max_row_page % 10 - 1;
		while (key == -32)
		{
			key = getch();
		}
		if (key == 72)
		{
			if (now <= 0)
			{
				prenow = now;
				now = get_now;
			}
			else
			{
				prenow = now--;
			}
		}

		if (key == 77)
		{
			if (page_number * 10 < sl_monhoc)
			{
				clr_xy(36, 2, 120, 16);
				page_number++;
				max_row_page = page_number * 10 > sl_monhoc ? sl_monhoc : page_number * 10;
				get_now = max_row_page % 10 == 0 ? 9 : max_row_page % 10 - 1;
				now = now >= get_now ? get_now : now;
				prenow = -1;
				if (page_number <= 1) khungChonMonHoc(1);
				else if (page_number * 10 >= sl_monhoc) khungChonMonHoc(-1);
				else khungChonMonHoc(0);

				for (int i = page_number * 10 - 10; i < max_row_page; i++)
				{

					gotoxy(x, y + i - page_number * 10 + 10);
					if (i - page_number * 10 + 10 == now)
					{
						SetConsoleTextAttribute(console, 240);
						cout << ds_monhoc[i]->MAMH;
						gotoxy(x + x_y, y + i - page_number * 10 + 10);
						cout << ds_monhoc[i]->TENMH;
						SetConsoleTextAttribute(console, 15);
					}
					else
					{
						SetConsoleTextAttribute(console, 15);
						cout << ds_monhoc[i]->MAMH;
						gotoxy(x + x_y, y + i - page_number * 10 + 10);
						cout << ds_monhoc[i]->TENMH;
						//gotoxy(x,y+i+1);	
					}
				}
			}
		}

		if (key == 75)
		{
			if (page_number > 1)
			{
				clr_xy(36, 2, 120, 16);
				page_number--;
				max_row_page = page_number * 10 > sl_monhoc ? sl_monhoc : page_number * 10;


				if (page_number <= 1) khungChonMonHoc(1);
				else if (page_number * 10 >= sl_monhoc) khungChonMonHoc(-1);
				else khungChonMonHoc(0);

				for (int i = page_number * 10 - 10; i < max_row_page; i++)
				{

					gotoxy(x, y + i - page_number * 10 + 10);
					if (i - page_number * 10 + 10 == now)
					{
						SetConsoleTextAttribute(console, 240);
						cout << ds_monhoc[i]->MAMH;
						gotoxy(x + x_y, y + i - page_number * 10 + 10);
						cout << ds_monhoc[i]->TENMH;
						SetConsoleTextAttribute(console, 15);
					}
					else
					{
						SetConsoleTextAttribute(console, 15);
						cout << ds_monhoc[i]->MAMH;
						gotoxy(x + x_y, y + i - page_number * 10 + 10);
						cout << ds_monhoc[i]->TENMH;
						//gotoxy(x,y+i+1);	
					}
				}
			}
		}

		if (key == 80)
		{
			if (now >= get_now)
			{
				prenow = now;
				now = 0;
			}
			else
			{
				prenow = now++;
			}
		}

		if (key == 27)
		{
			return -1;
		}

		if (key == 13)
		{
			string temp = ds_monhoc[page_number * 10 - 10 + now]->MAMH;

			if (kiemTraDaThiMonHoc(p, temp))
			{
				gotoxy(40, 18);
				cout << "BAN DA THI MON NAY ROI!!!";
			}
			else return (page_number * 10 - 10 + now);
		}

		for (int i = (page_number * 10) - 10; i < max_row_page; i++)
		{

			gotoxy(x, y + i - page_number * 10 + 10);
			if (i - page_number * 10 + 10 == now)
			{

				SetConsoleTextAttribute(console, 240);
				cout << ds_monhoc[i]->MAMH;
				gotoxy(x + x_y, y + i - page_number * 10 + 10);
				cout << ds_monhoc[i]->TENMH;
				SetConsoleTextAttribute(console, 15);
			}
			if (i - page_number * 10 + 10 == prenow)
			{

				SetConsoleTextAttribute(console, 15);
				cout << ds_monhoc[i]->MAMH;
				gotoxy(x + x_y, y + i - page_number * 10 + 10);
				cout << ds_monhoc[i]->TENMH;
				//gotoxy(x,y+i+1);	
			}
		}

	}
}

void* tinhGio(void* unused)
{
	gotoxy(22, 6);

	for (int i = thoigianKT; i >= 0; i--)
	{
		gotoxy(33, 6);
		cout << "                                              ";
		gotoxy(22, 6);
		cout << "Thoi gian: " << (i - (i % 60)) / 60 << ':' << i % 60;
		if (timeout()) pthread_exit(NULL);
		Sleep(999);
	}
	gotoxy(40, 6);
	cout << "HET GIO!!! nhan phim bat ky...";
	thoigianKT = 0;
	pthread_exit(NULL);
	return NULL;
}

bool timeout()
{
	if (thoigianKT == 0) return true;
	else return false;
}
int menu_cauhoi(string s[4], int n, int x, int y, int flag, int cmd)
{
	//cout << s[1];
	hidecur(true);
	int now = cmd;
	int prenow = -1;
	char key;

	if (flag == 1)
	{
		system("cls");
	}

	for (int i = 0; i < n; i++)
	{
		gotoxy(x, y + i);
		if (i == now)
		{

			SetConsoleTextAttribute(console, 240);
			cout << "Dap an " << (char)(65 + i) << ": " << s[i];
			//gotoxy(x,y+i+1);
			SetConsoleTextAttribute(console, 15);
		}
		else
		{
			cout << "Dap an " << (char)(65 + i) << ": " << s[i];
		}
	}
	int i = 0;
	while (true)
	{
		//system("cls");

		for (int i = 0; i < n; i++)
		{
			gotoxy(x, y + i);
			if (i == now)
			{

				SetConsoleTextAttribute(console, 240);
				cout << "Dap an " << (char)(65 + i) << ": " << s[i];
				//gotoxy(x,y+i+1);
				SetConsoleTextAttribute(console, 15);
			}
			if (i == prenow)
			{

				SetConsoleTextAttribute(console, 15);
				cout << "Dap an " << (char)(65 + i) << ": " << s[i];
				//gotoxy(x,y+i+1);	
			}
		}

		if (timeout() || key == 61)
		{
			thoigianKT = 0;
			return -2;
		}

		key = _getch();
		while (key == -32 && key == 0)
		{
			key = _getch();
		}

		if (key == 61)
		{
			thoigianKT = 0;
			return -2;
		}

		if (key == 72)
		{
			if (now == 0)
			{
				prenow = now;
				now = n - 1;
			}
			else
			{
				prenow = now--;
			}
		}
		if (key == 80)
		{
			if (now == n - 1)
			{
				prenow = now;
				now = 0;
			}
			else
			{
				prenow = now++;
			}
		}
		if (key == 13)
		{
			//			gotoxy(20,20);
			//			cout << now;
			//			getch();
			return now;
		}

		if (key == 77 || key == 75 || key == 61)
		{
			return key;
		}

		if (key == 27)
		{
			return  -2;
		}
	}
}

int thiTracNghiem(string mssv)
{
	DANH_SACH_LOP dsl;
	Doc_file_danh_sach_lop(dsl);
	Doc_file_dssv(dsl);

	AVLTree root;
	CreateAVLTree(root);
	int sl_cauhoi = 0;
	loadCauHoi(root, sl_cauhoi);

	NODESINHVIEN* nodesv = Tim_sinh_vien_theo_ma_sv(dsl, mssv);
	PTR_BaiKT p = nodesv->data.ds_bkt;
	MonHoc *ds_monhoc[MAX_MONHOC];
	int sl_monhoc = 0;
	loadMonHoc(ds_monhoc, sl_monhoc);
	cout << sl_monhoc;
	getch();
	int stt_monhoc = 0;
	do{
		hdsd(1);
		stt_monhoc = chonMonHoc(ds_monhoc, p, sl_monhoc);
		if (stt_monhoc == -1) return 0;
		if (ds_monhoc[stt_monhoc]->sl_cauhoi <= 0)
		{
			gotoxy(36, 18);
			cout << "THONG BAO: MON HOC NAY CHUA CO CAU HOI NAO!!!\n";
			gotoxy(36, 19);
			system("pause");
		}
		else break;
	} while (true);

	gotoxy(36, 20);
	cout << "So luong cau hoi cua mon nay la` : " << ds_monhoc[stt_monhoc]->sl_cauhoi << ". Toi da 60 cau." << endl;
	int sl_cauhoiKT;
	do
	{
		gotoxy(36, 21);
		cout << "Nhap so luong cau hoi :                  ";
		gotoxy(60, 21);
		sl_cauhoiKT = getNumber(60, 21);
		if (sl_cauhoiKT < 0) return 0;
		if (sl_cauhoiKT > ds_monhoc[stt_monhoc]->sl_cauhoi || sl_cauhoiKT < 1 || sl_cauhoiKT > 60)
		{
			gotoxy(36, 18);
			cout << "THONG BAO: Vui long nhap so khac !!!                ";
		}
		else break;
	} while (true);


	gotoxy(36, 22);
	cout << "Nhap thoi gian kiem tra (phut) : ";
	thoigianKT = getNumber(69, 22);
	if (thoigianKT == 0) thoigianKT = 5;
	if (thoigianKT < 0) return -1;
	thoigianKT = thoigianKT * 60;

	int ds_cauhoikt[60];
	taoDeKT(ds_cauhoikt, ds_monhoc, stt_monhoc, sl_cauhoiKT);



	BaiKT bkt;
	AVLTree ptr = NULL;
	system("cls");
	float tl_dung = 0;
	int key = 0;
	int i = 0, pre_i = 0;
	khungCauHoiRong(sl_cauhoiKT);

	pthread_t thread;
	pthread_create(&thread, NULL, &tinhGio, NULL);

	while (true)
	{
		clr_xy(33, 9, 150, 16);
		hdsd(2);
		setDirection(i, sl_cauhoiKT);
		ptr = timCauHoi(root, ds_cauhoikt[i]);
		gotoxy(33, 9);
		cout << "Cau hoi " << i + 1 << ": " << ptr->key.qus;
		int temp = menu_cauhoi(ptr->key.opt, 4, 36, 11, 0, 0);

		if (timeout() || temp == -2)
		{
			thoigianKT = 0;
			break;
		}

		if (temp == 75 && i > 0)
		{
			pre_i = i;
			i--;
			continue;
		}
		if (temp == 77 && i < sl_cauhoiKT - 1)
		{
			pre_i = i;
			i++;
			continue;
		}
		if (temp != 77 && temp != 75)
		{
			bkt.ds_cahuhoiKT[i].tl = temp;
			setAnswer(i, temp, sl_cauhoiKT);
		}

	}

	for (int i = 0; i < sl_cauhoiKT; i++)
	{
		ptr = timCauHoi(root, ds_cauhoikt[i]);
		bkt.ds_cahuhoiKT[i].id = ptr->key.id;
		if (ptr->key.ans == bkt.ds_cahuhoiKT[i].tl)
		{
			tl_dung++;
		}
	}

	bkt.sl_cauhoiKT = sl_cauhoiKT;
	bkt.MAMH = ds_monhoc[stt_monhoc]->MAMH;
	bkt.diem = (float)(tl_dung / (sl_cauhoiKT)) * 10;
	bkt.diem = roundf(bkt.diem * 10) / 10;

	gotoxy(35, 4);
	cout << "Diem cua ban la : " << bkt.diem ;
	gotoxy(35, 5);
	cout << "  An phim bat ki de thoat...";


	if (p == NULL)
	{
		insert_first(p, bkt);
	}
	else
	{
		insert_after(p, bkt);
	}

	luuBaiTap(mssv, p);	
	_getch();
	system("cls");
	

}
void inBangDiemSV(string MAMH, NODESINHVIEN* sv)
{
	int x = 120, y = 4;
	PTR_BaiKT temp_p = sv->data.ds_bkt;
	while (temp_p != NULL)
	{
		if (temp_p->bkt.MAMH == MAMH)
		{
			break;
		}
		temp_p = temp_p->next;
	}
	if (temp_p == NULL)
	{
		gotoxy(x, y + 1);
		cout << "CHUA THI !!!";
		gotoxy(x, y + 2);
		system("pause");

	}
	else
	{
		gotoxy(x + 10, y - 4);
		cout << "LEFT/RIGHT: chuyen trang | ESC : thoat ";
		gotoxy(x + 20, y - 2);
		cout << "DIEM : " << temp_p->bkt.diem;
		AVLTree root = NULL, p_cauhoi = NULL;
		int sl_cauhoi = 0;
		loadCauHoi(root, sl_cauhoi);
		int key = -1, n_page = 1;
		while (true)
		{
			x = 120; y = 4;
			clr_xy(x, y, x + 90, y + 37);
			int max_row = n_page * 5 > temp_p->bkt.sl_cauhoiKT ? temp_p->bkt.sl_cauhoiKT : n_page * 5;
			
			for (int i = n_page * 5 - 5; i < max_row; i++)
			{
				p_cauhoi = timCauHoi(root, temp_p->bkt.ds_cahuhoiKT[i].id);
				if (p_cauhoi == NULL)
				{
					gotoxy(x, y);
					cout << "Cau hoi da bi xoa .";
				}
				else
				{
					gotoxy(x, y);
					cout << "Cau " << i + 1 << ": " << p_cauhoi->key.qus;
					gotoxy(x, y + 1);
					cout << "A : " << p_cauhoi->key.opt[0];
					gotoxy(x, y + 2);
					cout << "B : " << p_cauhoi->key.opt[1];
					gotoxy(x, y + 3);
					cout << "C : " << p_cauhoi->key.opt[2];
					gotoxy(x, y + 4);
					cout << "D : " << p_cauhoi->key.opt[3];
					gotoxy(x, y + 5);
					if (p_cauhoi->key.ans == temp_p->bkt.ds_cahuhoiKT[i].tl)
					{
						SetConsoleTextAttribute(console, 240);
						gotoxy(x, y + p_cauhoi->key.ans + 1);
						cout << (char)(p_cauhoi->key.ans + 65);
						SetConsoleTextAttribute(console, 15);
						gotoxy(x, y + 5);
						cout << "Dung!. D/a: " << (char)(p_cauhoi->key.ans + 65) << ". ";

					}
					else
					{

						SetConsoleTextAttribute(console, 240);
						gotoxy(x, y + p_cauhoi->key.ans + 1);
						cout << (char)(p_cauhoi->key.ans + 65);

						if (temp_p->bkt.ds_cahuhoiKT[i].tl >= 0)
						{
							SetConsoleTextAttribute(console, 192);
							gotoxy(x, y + temp_p->bkt.ds_cahuhoiKT[i].tl + 1);
							cout << (char)(temp_p->bkt.ds_cahuhoiKT[i].tl + 65);
						}

						SetConsoleTextAttribute(console, 15);
						gotoxy(x, y + 5);
						cout << "Sai!. Tra loi: " << (char)(temp_p->bkt.ds_cahuhoiKT[i].tl + 65) << ", d/a: " << (char)(p_cauhoi->key.ans + 65) << ". ";
					}
				}
				y += 7;
			}
			gotoxy(x + 75, y + 2);
			cout << max_row << "/" << temp_p->bkt.sl_cauhoiKT << "   ";

			do{
				key = getch();
			} while (!(key == 77 || key == 75 || key == 27));
			
			switch (key)
			{
			case 77:
			{
					   if (n_page * 5 < temp_p->bkt.sl_cauhoiKT)
					   {
						   n_page++;
					   }
					   break;
			}
			case 75:
			{
					   if (n_page > 1)
					   {
						   n_page--;
					   }
					   break;
			}

			case 27:
			{
					   return;
					   break;
			}
			}
		}

	}
	return;
}

PTR_BaiKT timBaiKiemTraDaThi(string MAMH, PTR_BaiKT p_dsBKT)
{
	PTR_BaiKT p = p_dsBKT;
	while (p != NULL)
	{
		if (p->bkt.MAMH == MAMH)
		{
			return p;
		}
		p = p->next;
	}
	return NULL;
}

void inBangDiemLop(string MAMH, LOP &lophoc)
{
	int x = 110, y = 4;
	if (lophoc.isnotempty == false || lophoc.dssv.phead == NULL)
	{
		gotoxy(x + 20, y + 1);
		cout << "Lop chua co sinh vien nao!!";
		gotoxy(x + 20, y + 2);
		system("pause");
	}
	else
	{
		gotoxy(x + 10, 0);
		cout << "LEFT/RIGHT: chuyen trang | ESC : thoat ";
		gotoxy(x, y - 2);
		cout << "MSSV";
		gotoxy(x + 16, y - 2);
		cout << "Ho va ten";
		gotoxy(x + 16 + 30, y - 2);
		cout << "Diem ";
		NODESINHVIEN* arr_sv[1000];
		NODESINHVIEN* p = lophoc.dssv.phead;
		int sl_sv = 0;
		do
		{
			arr_sv[sl_sv] = p;
			p = p->pnext;
			sl_sv++;
		} while (p != NULL);
		
		int n_page = 1;
		while (true)
		{
			clr_xy(x, y, 200, y + 21);
			int max_row = n_page * 20 > sl_sv ? sl_sv : n_page * 20;
			max_row--;
			for (int i = n_page * 20 - 20; i < max_row ; i++)
			{
				gotoxy(x, y + (i % 20));
				cout << arr_sv[i]->data.MASV;
				gotoxy(x + 16, y + (i % 20));
				cout << arr_sv[i]->data.ho <<" "<< arr_sv[i]->data.ten;
				gotoxy(x + 16 + 30, y + (i % 20));
				PTR_BaiKT nodeBKT = timBaiKiemTraDaThi(MAMH, arr_sv[i]->data.ds_bkt);
				if (nodeBKT == NULL)
				{
					cout << "Chua thi";
				}
				else
				{
					cout << nodeBKT->bkt.diem;
				}
			}

			gotoxy(x + 40, y + 20 + 2);
			cout << max_row << "/" << sl_sv - 1<< "   ";
			int key;
			do{
				key = getch();
			} while (!(key == 77 || key == 75 || key == 27));

			switch (key)
			{
			case 77:
			{
					   if (n_page * 20 < sl_sv)
					   {
						   n_page++;
					   }
					   break;
			}
			case 75:
			{
					   if (n_page > 1)
					   {
						   n_page--;
					   }
					   break;
			}

			case 27:
			{
					   return;
					   break;
			}
			}
		}
	}
}

void Plus_Tim_Lop_Hoc(int x, int y, DANH_SACH_LOP dsl, string &malop, bool &exit)
{
	
	string a;
	string s[200];
	string ma[200];
	int count = 0;
	int tam = 0;
	for (int i = 0; i < dsl.sl; i++)
	{
		if (tam < 16)
		{
			gotoxy(x + 13, y + 7 + tam);
			cout << dsl.lop[i].ma_lop;
			gotoxy(x + 23, y + 7 + tam);
			cout << dsl.lop[i].ten_lop;
		}
		s[tam] = dsl.lop[i].ten_lop;//gan ten lop cho chuoi s
		ma[tam] = dsl.lop[i].ma_lop;
		tam++;
		count = tam;
	}
	if (tam > 16)
	{
		gotoxy(x + 20, y + 7 + 16);
		cout << "(And " << tam - 16 << " more...)";
	}
	//x = x + 3;
	gotoxy(x + 16 + a.length(), y + 2);
	while (true)
	{
	find:
		XoaManHinh(x + 49, y + 28, 45, 7);//xoa man hinh khung chuc nang
		gotoxy(x + 65, y + 30);
		cout << "ESC: Quay lai";
		gotoxy(x + 16 + a.length(), y + 2);
		hidecur(false);
		char k = _getch();
		while (k == 72 || k == -32)
		{
			k = _getch();
		}

		if (k == 27)
		{
			exit = true;
			//UserGV(dsl);
			return;
		}
		if (k == 8)//phim backspace
		{
			if (a.length() >= 1)
			{
				XoaManHinh(x + 15 + a.length(), y + 2, 1, 1);
				a.erase(a.size() - 1);
				gotoxy(x + 15 + a.length(), y + 2);
			}
		}
		if (k >= 48 && k <= 57)//hang phim so
		{
			a.push_back(k);
			gotoxy(x + 15 + a.length(), y + 2);
			cout << k;
		}
		if ((k >= 97 && k <= 122) || k == ' ')//phim ki tu va space
		{
			a.push_back(k);
			gotoxy(x + 15 + a.length(), y + 2);
			cout << k;
		}
		if (k == 80 && count != 0)//phim xuong
		{

			XoaManHinh(x + 49, y + 28, 45, 5);//xoa man hinh khung chuc nang
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
		XoaManHinh(x + 5, y + 7, 37, 17);//xoa man hinh o danh sach lop
		int temp = 0;
		if (a.length() != 0)// xoa het
		{
			for (int i = 0; i < dsl.sl; i++)
			{
				if (ahaveb(dsl.lop[i].ma_lop, a2) || ahaveb(dsl.lop[i].ten_lop, a1))//kiem tra dieu kien tim kiem
				{
					if (temp < 16)
					{
						gotoxy(x + 10, y + 7 + temp);
						cout << dsl.lop[i].ma_lop;
						gotoxy(x + 20, y + 7 + temp);
						cout << rut_gon_text(dsl.lop[i].ten_lop, 20);
					}
					s[temp] = dsl.lop[i].ten_lop;//gan ten lop cho chuoi s
					ma[temp] = dsl.lop[i].ma_lop;
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
			for (int i = 0; i < dsl.sl; i++)
			{
				if (temp < 16)
				{
					gotoxy(x + 10, y + 7 + temp);
					cout << dsl.lop[i].ma_lop;
					gotoxy(x + 20, y + 7 + temp);
					cout << rut_gon_text(dsl.lop[i].ten_lop, 20);
				}
				s[temp] = dsl.lop[i].ten_lop;//gan ten lop cho chuoi s
				ma[temp] = dsl.lop[i].ma_lop;
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
	XoaManHinh(x + 5, y + 7, 37, 17);//xoa man hinh o danh sach lop
	hidecur(true);
	int vt1 = 0;
	while (true)
	{
		int cmd = menuadvanced(s, x + 15, y + 7, 0, count);
		exit = false;
		if (cmd == 99)
			goto find;
		malop = ma[cmd];
		break;
	}
}
void Plus_Tim_Sinh_Vien(int x, int y, DANH_SACH_LOP dsl, string malop, string &masv, bool &exit)
{
	XoaManHinh(x + 2, y + 7, 45, 17);//xoa man hinh o danh sach lop
	string s[200];
	string ma[200];
	int n = Check_so_luong_sv_ma(dsl, malop);//dem so sinh vien cua lop 
	string *temp = new string[n];// cap phat vung nho masv
	string *temp1 = new string[n];// cap phat vung nho tensv
	string *tempho = new string[n];

	int dem = 0;
	for (int i = 0; i < dsl.sl; i++)
	{
		if (dsl.lop[i].ma_lop == malop)
		{
			for (NODESINHVIEN* k = dsl.lop[i].dssv.phead; k != NULL; k = k->pnext)
			{
				temp[dem] = k->data.MASV;//gan ma sv vao mang temp
				temp1[dem] = k->data.ten;//gan ten sv vao mang temp1
				tempho[dem] = k->data.ho;// gan ho sv vao tempho
				tempho[dem].append(" ");
				tempho[dem].append(temp1[dem]);
				dem++;
			}
		}
	}
	dem--;
	string a;	
	int count = 0;
	int tam = 0;
	for (int i = 0; i < n; i++)
	{
		if (tam < 16)
		{
			if (i == 0)
			{
				SetConsoleTextAttribute(console, 240);
				gotoxy(x + 5, y + 7 + tam);
				cout << temp[i];
				gotoxy(x + 20, y + 7 + tam);
				cout << tempho[i];
				SetConsoleTextAttribute(console, 15);
			}
			else
			{
				gotoxy(x + 5, y + 7 + tam);
				cout << temp[i];
				gotoxy(x + 20, y + 7 + tam);
				cout << tempho[i];
			}
		}
		s[tam] = tempho[i];//gan ten lop cho chuoi s
		ma[tam] = temp[i];
		if (i < n - 1)
		{
			tam++;
			count = tam;
		}
	}
	
	
	if (tam > 16)
	{
		gotoxy(x + 20, y + 7 + 16);
		cout << "(And " << tam - 16 << " more...)";
	}
	//x = x + 3;
	gotoxy(x + 16 + a.length(), y + 2);
	while (true)
	{
	find:
		XoaManHinh(x + 49, y + 28, 50, 5);//xoa man hinh khung chuc nang
		gotoxy(x + 65, y + 30);
		cout << "ESC: Quay lai ";
		gotoxy(x + 16 + a.length(), y + 2);
		hidecur(false);
		char k = _getch();
		while (k == -32)
		{
			k = _getch();
		}

		if (k == 27)
		{
			//system("cls");
			exit = true;
			
			//UserGV(dsl);
			return;
		}
		if (k == 8)//phim backspace
		{
			if (a.length() >= 1)
			{
				XoaManHinh(x + 15 + a.length(), y + 2, 1, 1);
				a.erase(a.size() - 1);
				gotoxy(x + 15 + a.length(), y + 2);
			}
		}
		if (k >= 48 && k <= 57)//hang phim so
		{
			a.push_back(k);
			gotoxy(x + 15 + a.length(), y + 2);
			cout << k;
		}
		if ((k >= 97 && k <= 122) || k == ' ')//phim ki tu va space
		{
			a.push_back(k);
			gotoxy(x + 15 + a.length(), y + 2);
			cout << k;
		}
		if (k == 80 && count != 0)//phim xuong
		{

			XoaManHinh(x + 49, y + 28, 50, 5);//xoa man hinh khung chuc nang
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
		XoaManHinh(x + 5, y + 7, 37, 17);//xoa man hinh o danh sach lop
		int temp2 = 0;
		if (a.length() != 0)// xoa het
		{
			for (int i = 0; i < n; i++)
			{
				if (ahaveb(temp[i], a2) || ahaveb(tempho[i], a1))//kiem tra dieu kien tim kiem
				{
					if (temp2 < 16)
					{
						gotoxy(x + 5, y + 7 + temp2);
						cout << temp[i];
						gotoxy(x + 20, y + 7 + temp2);
						cout << rut_gon_text(tempho[i], 20);
					}
					s[temp2] = tempho[i];//gan ten lop cho chuoi s
					ma[temp2] = temp[i];
					temp2++;
					count = temp2;
				}
			}
			if (temp2 > 16)
			{
				gotoxy(x + 20, y + 7 + 16);
				cout << "(And " << temp2 - 16 << " more...)";
			}
		}
		else // ton tai ki tu
		{
			for (int i = 0; i < n; i++)
			{
				if (temp2 < 16)
				{
					gotoxy(x + 5, y + 7 + temp2);
					cout << temp[i];
					gotoxy(x + 20, y + 7 + temp2);
					cout << rut_gon_text(tempho[i], 20);
				}
				s[temp2] = tempho[i];//gan ten lop cho chuoi s
				ma[temp2] = temp[i];
				temp2++;
				count = temp2;
			}
			if (temp2 > 16)
			{
				gotoxy(x + 20, y + 7 + 16);
				cout << "(And " << temp2 - 16 << " more...)";
			}
		}
		gotoxy(x + 16 + a.length(), y + 2);//dua con tro chi vi ve thanh tim kiem
		hidecur(false);
	}
	XoaManHinh(x + 5, y + 7, 37, 17);//xoa man hinh o danh sach lop
	hidecur(true);
	int vt1 = 0;
	while (true)
	{
		int cmd = menuadvanced(s, x + 15, y + 7, 0,  count);
		exit = false;
		if (cmd == 99)
			goto find;
		masv = ma[cmd];
		break;
	}
	
	delete[] temp;
	delete[] temp1;
	delete[] tempho;
	
}
void Plus_Tim_Mon_Hoc(int x, int y, string &mamh, string &tenmh, bool &exit)
{
	XoaManHinh(x + 3, y + 7, 45, 17);//xoa man hinh o danh sach lop
	string a;
	string s[200]; //mang luu ten mon hoc
	string ma[200]; // mang luu ma mon hoc
	int count = 0;
	int tam = 0;
	for (int i = 0; i < sl_monhoc; i++)
	{
		if (tam < 16)
		{
			if (i == 0)
			{
				SetConsoleTextAttribute(console, 240);
				gotoxy(x + 5, y + 7 + tam);
				cout << ds_monhoc[i]->MAMH;
				gotoxy(x + 20, y + 7 + tam);
				cout << rut_gon_text(ds_monhoc[i]->TENMH, 20);
				SetConsoleTextAttribute(console, 15);
			}
			else
			{
				gotoxy(x + 5, y + 7 + tam);
				cout << ds_monhoc[i]->MAMH;
				gotoxy(x + 20, y + 7 + tam);
				cout << rut_gon_text(ds_monhoc[i]->TENMH, 20);
			}
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
		XoaManHinh(x + 49 - 50, y + 28, 50, 5);//xoa man hinh khung chuc nang
		gotoxy(x + 65 - 50, y + 30);
		cout << "ESC: Quay lai";
		gotoxy(x + 16 - 50 + a.length(),y+2);
		hidecur(false);
		char k = _getch();
		while (k == -32)
		{
			k = _getch();
		}
		while (k == 72)
		{
			k = _getch();
		}
		if (k == 27)
		{			
			exit = true;
			return;
		}
		if (k == 8)//phim backspace
		{
			if (a.length() >= 1)
			{
				XoaManHinh(x + 15 - 50 + a.length(), y + 2, 1, 1);
				a.erase(a.size() - 1);
				gotoxy(x + 15 - 50 + a.length(), y + 2);
			}
		}
		if (k >= 48 && k <= 57)//hang phim so
		{
			a.push_back(k);
			gotoxy(x + 15 - 50 + a.length(), y + 2);
			cout << k;
		}
		if ((k >= 97 && k <= 122) || k == ' ')//phim ki tu va space
		{
			a.push_back(k);
			gotoxy(x + 15 - 50 + a.length(), y + 2);
			cout << k;
		}
		if (k == 80 && count != 0)//phim xuong
		{
			XoaManHinh(x + 49 -50, y + 28, 50, 5);//xoa man hinh khung chuc nang
			gotoxy(x + 60 - 50 , y + 30);
			cout << "ESC: Quay lai khung tim kiem";
			hidecur(true);
			break;
		}
		//////////////// giai doan tim kiem//////////////////////
		
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
		exit = false;
		mamh = ma[cmd];
		tenmh = s[cmd];
		if (cmd == 99)
		{
			gotoxy(x + 16 + a.length(), y + 16);//nhan enter vao o "quay lai thanh tim kiem"
			hidecur(false);
			goto find;
		}
		break;
	}
}
void Plus_Xem_Bai_Thi_Sinh_Vien(DANH_SACH_LOP dsl, int x, int y)
{
	// viet ham nhap mon hoc
	string malop;
	string masv;
	string mamh;
	string tenmh;
	NODESINHVIEN *k;
	while (true)
	{
		system("cls");
		gotoxy(10, 0);
		cout << "UP/DOWN/LEFT/RIGHT: xem danh sach lop || ENTER : chon ";
		gotoxy(20, 1);
		cout << "CHON LOP CO SINH VIEN CAN TIM ";
		Khung_Tim_Lop_Hoc(x, y);
		bool exit = false;
		Plus_Tim_Lop_Hoc(x, y, dsl, malop, exit);
		if (exit == true)
		{
			system("cls");
			return;
		}
		system("cls");
		khungquanlydiemthi1sv(x, y);
		while (true)
		{
			gotoxy(20, 0);
			cout << "UP/DOWN/LEFT/RIGHT: xem danh sach lop || ENTER : chon ";
			gotoxy(30, 1);
			cout << "CHON SINH VIEN CAN TIM                     ";
			Plus_Tim_Sinh_Vien(x, y, dsl, malop, masv, exit);
			if (exit == true)
			{

				break;
			}
			while (true)
			{
				clr_xy(120, 0, 200, 46);
				Plus_Tim_Mon_Hoc(x + 50, y, mamh, tenmh, exit);
				if (exit == true)
				{
					break;
				}
				else
				{
					k = Tim_sinh_vien_theo_ma_sv(dsl, masv);

					gotoxy(130, 41);
					cout << "Ma lop: " << malop << endl;
					gotoxy(130, 42);
					cout << "Ma sinh vien: " << masv << endl;
					gotoxy(130, 43);
					cout << "Ten sinh vien: " << k->data.ho << k->data.ten << endl;
					gotoxy(130, 44);
					cout << "Ma mon hoc: " << mamh << endl;
					gotoxy(130, 45);
					cout << "Ten mon hoc: " << tenmh << endl;
					inBangDiemSV(mamh, k);
				}

			}
		}
	}

}
int timLopTheoMa(DANH_SACH_LOP dsl, string malop)
{
	for (int i = 0; i<dsl.sl; i++)
	{
		if (dsl.lop[i].ma_lop == malop) return i;
	}
	return -1;
}
void Plus_Xem_Bai_Thi_1_Lop(DANH_SACH_LOP dsl, int x, int y)
{
	string malop;
	string mamh;
	string tenmh;
	while (true)
	{
		gotoxy(10, 0);
		cout << "UP/DOWN/LEFT/RIGHT: xem danh sach lop | ENTER : chon ";
		khungquanlydiemthi1lop(x, y);
		bool exit = false;
		Plus_Tim_Lop_Hoc(x, y, dsl, malop, exit);
		if (exit == true)
		{
			system("cls");
			return;
		}
		while (true)
		{
			clr_xy(110, 0, 200, 30);
			Plus_Tim_Mon_Hoc(x + 50, y, mamh, tenmh, exit);
			if (exit == true)
			{
				break;
			}
			else
			{
				int stt = -1;
				stt = timLopTheoMa(dsl, malop);
				if (stt == -1) return;
				gotoxy(120, 27);
				cout << "Ma lop: " << malop << endl;
				gotoxy(120, 28);
				cout << "Ma mon hoc: " << mamh << endl;
				gotoxy(120, 29);
				cout << "Ten mon hoc: " << tenmh << endl;
				inBangDiemLop(mamh, dsl.lop[stt]);
			}
		}
	}
}
void Plus_Quan_Ly_Bai_Kiem_Tra(DANH_SACH_LOP dsl, int x, int y)
{
	Ve_HCN(33, 5, x - 1, y - 3);
	Ke_line(33, x - 1, y - 1);
	gotoxy(x + 7, y - 2);
	cout << "Quan ly bai thi";
	string s[] = { "    Xem bai thi 1 sinh vien    ",
		"    Xem bai thi 1 lop          " };
	int cmd = menu(s, 2, x, y,  0);
	if (cmd == 99)
	{
		XoaManHinh(x - 1, y - 3, 33, 7);
		return;
	}
	bool exit = false;
	if (cmd == 0)
	{
		system("cls");
		Plus_Xem_Bai_Thi_Sinh_Vien(dsl, x-35, y-4);
	}
	else
	{
		system("cls");
		Plus_Xem_Bai_Thi_1_Lop(dsl, x-40, y-5);
	}
}

