#pragma once
#include"xulylophoc.h"
//#include"xulymonhoc.h"
#include"AVL.h"
void Them_Vao_Cuoi(DANH_SACH_SINH_VIEN& l, NODESINHVIEN* p);
void luuMonHoc(MonHoc* ds_monhoc[MAX_MONHOC], int sl_monhoc);
NODESINHVIEN* KhoiTaoSinhVien(SINHVIEN sv);
#define MAX_MONHOC 200
#define true 1
#define false 0
void DeleteArrPointer(MON_HOC* ds_monhoc[MAX_MONHOC], int sl_monhoc);
void luuBaiTap(string, PTR_BaiKT);
void loadBaiTap(string mssv, PTR_BaiKT&);
void insert_first(PTR_BaiKT& first, BaiKT bkt);
int insert_after(PTR_BaiKT, BaiKT);
int reccount(PTR_BaiKT);
PTR_BaiKT get_last(PTR_BaiKT);
int xoanode_first(PTR_BaiKT&);
int xoanode_after(PTR_BaiKT&);
void delete_list(PTR_BaiKT&);
PTR_BaiKT newnode();
void Ghi_file_danh_sach_lop(DANH_SACH_LOP dsl);
void Ghi_file_danh_sach_lop(DANH_SACH_LOP dsl)
{
	ofstream f;
	f.open("danh_sach_lop.txt",ios::out);
	for (int i = 0; i < dsl.sl; i++)
	{
		f << dsl.lop[i].ma_lop;
		f << ',';
		f << dsl.lop[i].ten_lop;
		f << ',';
		f << dsl.lop[i].isnotempty;
		f << "\n";
	}
	f.close();
}
void Doc_file_danh_sach_lop(DANH_SACH_LOP& dsl)
{
	ifstream f;
	f.open("danh_sach_lop.txt", ios::in);
	while (f.eof() != true)
	{
		getline(f, dsl.lop[dsl.sl].ma_lop,',');
		getline(f, dsl.lop[dsl.sl].ten_lop,',');
		f >> dsl.lop[dsl.sl].isnotempty;
		f.ignore();
		dsl.sl++;
	}
	dsl.sl--;
	f.close();
}
void Ghi_file_dssv(DANH_SACH_LOP dsl)
{
	for (int i = 0; i < dsl.sl; i++)
	{
		ofstream f;
		string tenfile = dsl.lop[i].ma_lop;
		tenfile.append(".txt");
		if (dsl.lop[i].isnotempty==1)
		{
			f.open(tenfile.c_str(), ios::out);
			for (NODESINHVIEN* k = dsl.lop[i].dssv.phead; k != NULL;k = k->pnext)
			{
				if (k->data.MASV.length() != 0)
				{
					f << k->data.MASV;
					//cout << k->sv.MASV;
					f << ",";
					f << k->data.ho;
					f << ",";
					f << k->data.ten;
					f << ",";
					f << k->data.phai;
					f << ",";
					f << k->data.password;
					f << endl;
					/*cout << "\nBan vua them " << k->data.MASV << " vao file! " << endl;*/
				}
			}
			f.close();
		}
	}
}
void Doc_file_dssv(DANH_SACH_LOP &dsl)
{
	for (int i = 0; i < dsl.sl; i++)
	{
		if (dsl.lop[i].isnotempty == 1)
		{
			ifstream f;
			string tenfile = dsl.lop[i].ma_lop;
			tenfile.append(".txt");
			f.open(tenfile.c_str(), ios::in);
			while (f.eof() != true)
			{
				SINHVIEN sv;
				getline(f, sv.MASV, ',');
				getline(f, sv.ho, ',');
				getline(f, sv.ten, ',');
				getline(f, sv.phai, ',');
				getline(f, sv.password,'\n');
				f.ignore(0, '\n');
				NODESINHVIEN* p = KhoiTaoSinhVien(sv);
				loadBaiTap(sv.MASV, p->data.ds_bkt);
				Them_Vao_Cuoi(dsl.lop[i].dssv, p);
				if (sv.MASV.length() != 0)
				{
					dsl.lop[i].soluongsv++;
				}
			}
			f.close();
		}
	}
}
void loadMonHoc(MonHoc *ds_monhoc[MAX_MONHOC], int &sl_monhoc)
{
	DeleteArrPointer(ds_monhoc, sl_monhoc);
	fstream f;
	f.open(FILENAME_DSMONHOC, ofstream::in);
	if (f.is_open())
	{
		f >> sl_monhoc;
		f.ignore();
		for (int i = 0; i < sl_monhoc; i++)
		{
			ds_monhoc[i] = new MonHoc;
			f.get(ds_monhoc[i]->MAMH, 15, ',');
			f.ignore();
			f.get(ds_monhoc[i]->TENMH, 255, ',');
			f.ignore();
			f >> ds_monhoc[i]->sl_cauhoi;
			f.ignore();
			for (int j = 0; j < ds_monhoc[i]->sl_cauhoi; j++)
			{
				f >> ds_monhoc[i]->ds_id_cauhoi[j];
				f.ignore();
			}
		}
	}

	f.close();

}
void luuMonHoc(MonHoc *ds_monhoc[MAX_MONHOC], int sl_monhoc)
{
	fstream f;
	f.open(FILENAME_DSMONHOC, ofstream::out | ofstream::trunc);

	f << sl_monhoc;
	f << ",";

	for (int i = 0; i < sl_monhoc; i++)
	{
		f << ds_monhoc[i]->MAMH;
		f << ",";
		f << ds_monhoc[i]->TENMH;
		f << ",";
		f << ds_monhoc[i]->sl_cauhoi;
		f << ",";
		for (int j = 0; j < ds_monhoc[i]->sl_cauhoi; j++)
		{
			f << ds_monhoc[i]->ds_id_cauhoi[j];
			f << ",";
		}
	}

	f.close();
}
void SaveNode(fstream &f, AVLTree &root)
{
	if (root != NULL)
	{
		SaveNode(f, root->pLeft);
		f << root->key.id;
		f << ",";
		f << root->key.MAMH;
		f << ",";
		f << root->key.qus;
		f << ",";
		f << root->key.opt[0];
		f << ",";
		f << root->key.opt[1];
		f << ",";
		f << root->key.opt[2];
		f << ",";
		f << root->key.opt[3];
		f << ",";
		f << root->key.ans;
		f << ",";
		SaveNode(f, root->pRight);
	}
}
void luuCauHoi(AVLTree root, int sl_cauhoi)
{
	fstream f;
	f.open(FILENAME_DSCAUHOI, ofstream::out | ofstream::trunc);
	f << sl_cauhoi;
	f << ",";
	SaveNode(f, root);
	f.close();
}
void loadCauHoi(AVLTree &root, int &sl_cauhoi)
{
	CauHoi key;
	DelTree(root);
	fstream f;
	f.open(FILENAME_DSCAUHOI, ofstream::in);

	f >> sl_cauhoi;
	f.ignore();


	while (f)
	{
		f >> key.id;
		f.ignore();
		getline(f, key.MAMH, ',');
		getline(f, key.qus, ',');
		getline(f, key.opt[0], ',');
		getline(f, key.opt[1], ',');
		getline(f, key.opt[2], ',');
		getline(f, key.opt[3], ',');
		f >> key.ans;
		f.ignore();
		InsertNode(root, key);
		if (f.eof()) break;
	}

	f.close();
}
void luuBaiTap(string mssv, PTR_BaiKT p_bkt)
{
	string fname = FOLDER_NAME_BAITAP + mssv + ".dat";
	fstream file;
	file.open(fname.c_str(), ios::out | ios::trunc);

	while (p_bkt != NULL)
	{
		file << p_bkt->bkt.MAMH;
		file << ",";
		file << p_bkt->bkt.diem;
		file << ",";
		file << p_bkt->bkt.sl_cauhoiKT;
		file << ",";
		for (int i = 0; i < p_bkt->bkt.sl_cauhoiKT; i++)
		{
			file << p_bkt->bkt.ds_cahuhoiKT[i].id;
			file << ",";
			file << p_bkt->bkt.ds_cahuhoiKT[i].tl;
			file << ",";
		}

		p_bkt = p_bkt->next;
	}
	file.close();
}
void loadBaiTap(string mssv, PTR_BaiKT& p)
{
	string fname = FOLDER_NAME_BAITAP + mssv + ".dat";
	fstream file;
	file.open(fname.c_str(), ios::in);

	BaiKT bkt;
	if (file.is_open())
	{
		while (true)
		{
			//	file.getline( bkt.MAMH.c_str(),)
			getline(file, bkt.MAMH, ',');
			if (file.eof()) break;
			file >> bkt.diem;
			file.ignore();

			file >> bkt.sl_cauhoiKT;
			file.ignore();

			for (int i = 0; i < bkt.sl_cauhoiKT; i++)
			{
				file >> bkt.ds_cahuhoiKT[i].id;
				file.ignore();
				file >> bkt.ds_cahuhoiKT[i].tl;
				file.ignore();
			}

			if (p == NULL)
			{
				insert_first(p, bkt);
			}
			else
			{
				insert_after(p, bkt);
			}
		}
	}
	file.close();
}
void insert_first(PTR_BaiKT& first, BaiKT bkt)
{
	PTR_BaiKT p = newnode();
	p->bkt = bkt;
	p->next = first;
	first = p;
}
PTR_BaiKT newnode()
{
	PTR_BaiKT p = new node_BaiKT;
	p->bkt.diem = 0;
	p->bkt.MAMH = "";
	p->bkt.sl_cauhoiKT = 0;
	for (int i = 0; i < MAX_SL_CAU_HOI_KT; i++)
	{
		p->bkt.ds_cahuhoiKT[i].id = i;
		p->bkt.ds_cahuhoiKT[i].tl = MAX_SL_CAU_HOI_KT - i;
	}

	p->next = NULL;
	return p;
}
int insert_after(PTR_BaiKT p, BaiKT bkt)
{
	if (p == NULL)
	{
		return 0;
	}
	else
	{
		PTR_BaiKT q = newnode();
		q->bkt = bkt;
		q->next = p->next;
		p->next = q;
	}
}

int reccount(PTR_BaiKT first)
{
	int i = 0;
	if (first == NULL)
	{
		return 0;
	}
	else
	{
		PTR_BaiKT p = first;
		while (p != NULL)
		{
			i++;
			//cout << i;
			p = p->next;
		}
	}
	return i;
}
PTR_BaiKT get_last(PTR_BaiKT first)
{
	PTR_BaiKT p = first;
	while (p->next != NULL)
	{
		p = p->next;
	}
	return p;
}
int delete_first(PTR_BaiKT& first)
{
	PTR_BaiKT p;
	if (first == NULL) return 0;
	p = first;
	first = p->next;
	delete p;
	cout << "Thanh cong ! (nhan phim bat ki de tro lai menu)";
	_getch();

}
int delete_after(PTR_BaiKT& p)
{
	PTR_BaiKT q;
	if (p == NULL || p->next == NULL) return 0;
	q = p->next;
	p->next = q->next;
	delete q;
	cout << "Thanh cong ! (nhan phim bat ki de tro lai menu)";
	_getch();
}
void delete_list(PTR_BaiKT& first)
{
	PTR_BaiKT p;
	while (first != NULL)
	{
		p = first;
		first = first->next;
		delete p;
	}
}

