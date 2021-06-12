#pragma once

#include <iostream>
#include <string.h>
#include <iostream>
#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h>
#include <fstream>
#include <cstdlib>// rand , srand
#include <ctime>
#include <iomanip>
#include <ctype.h>
#define MAX_MONHOC 200

using namespace std;
const int MAX_SL_CAU_HOI_KT = 60;
const int MAX_LOP_HOC = 100;
const char FOLDER_NAME_BAITAP[15] = "dulieubaitap/";
const char FILENAME_DSCAUHOI[15] = "dscauhoi.dat";
const char FILENAME_DSMONHOC[20] = "dsmonhoc.dat";

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
struct MonHoc
{
	char MAMH[15];
	char TENMH[255];
	int sl_cauhoi = 0;
	int ds_id_cauhoi[10000];
	MonHoc()
	{
		for (int i = 0; i < 10000; i++)
		{
			ds_id_cauhoi[10000] = 0;
		}
	}
};
typedef struct MonHoc MON_HOC;
struct CauHoiKT
{
	int id;
	int tl=-1;
};
struct BaiKT
{
	string MAMH;
	float diem;
	int sl_cauhoiKT;
	CauHoiKT ds_cahuhoiKT[MAX_SL_CAU_HOI_KT];
};
struct node_BaiKT
{
	BaiKT bkt;
	struct node_BaiKT *next = NULL;
};
typedef node_BaiKT* PTR_BaiKT;
struct CauHoi
{
	int id;
	string MAMH;
	string qus;
	string opt[4];
	int ans;

};
struct AVLNode
{
	CauHoi key;
	char CSCB;
	AVLNode *pLeft;
	AVLNode *pRight;
};
typedef AVLNode * AVLTree;
//------------------------------------

struct sinhvien
{
	string MASV;
	string ho;
	string ten;
	string phai;
	string password;
	PTR_BaiKT ds_bkt = NULL;
};
typedef struct sinhvien SINHVIEN;
struct node_sinh_vien
{

	SINHVIEN data;
	/*contro*/
	node_sinh_vien* pnext;
};
typedef struct node_sinh_vien NODESINHVIEN;
struct danh_sach_sinh_vien
{
	NODESINHVIEN* phead = NULL;

	//int so_luong = 0;

};
typedef struct danh_sach_sinh_vien DANH_SACH_SINH_VIEN;
struct lop
{
	string ma_lop;
	string ten_lop;
	int soluongsv = 0;
	bool isnotempty = 0;
	//con tro dssv
	DANH_SACH_SINH_VIEN dssv;
};
typedef struct lop LOP;
struct danh_sach_lop
{
	LOP lop[MAX_LOP_HOC];
	int sl = 0;
};
typedef struct danh_sach_lop DANH_SACH_LOP;

