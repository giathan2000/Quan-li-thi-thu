
#include"FrontE.h"

int main()
{
		CreateAVLTree(root);
		resizeConsole(1800, 900);
		loadMonHoc(ds_monhoc, sl_monhoc);
		loadCauHoi(root, sl_cauhoi);
		Doc_file_danh_sach_lop(dsl);
		Doc_file_dssv(dsl);
		DangNhap(dsl);	
		DelTree(root);
		Giai_Phong_Tat_Ca_Danh_Sach_Sinh_Vien(dsl);
}

