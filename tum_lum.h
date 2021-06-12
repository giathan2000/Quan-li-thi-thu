#pragma once
#include"ctdl.h"


void XoaManHinh(int x, int y, int w, int h);
void ChuanHoaChu (string &a)
{
	while (a[0] == ' ')
	{
		a.erase(a.begin()+0);
	}
	while (a[a.length()] == ' ')
	{
		a.erase(a.begin() + a.length());
	}
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] == ' ')
		{
			if (a[i + 1] == ' ')
			{
				a.erase(a.begin()+i+1);
				i--;
			}
		}
	}
	if (a[0] >= 97 && a[0] <= 132)
		a[0] -= 32;
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] == ' ')
		{
			if (a[i + 1] >= 97 && a[i + 1] <= 132)
				a[i + 1] -= 32;
		}
		else
			if (a[i + 1] >= 65 && a[i + 1] <= 90)
			{
				a[i + 1] += 32;
			}
	}
}
void In_Hoa(string &a)
{
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] >= 97 && a[i] <= 132)
			a[i] -= 32;
		if (a[i] == ' ')
		{
			a.erase(a.begin() + i);
			i--;
		}
	}
}
string Lay_ma_lop_tu_ma_sinh_vien(string a)
{
	a.erase(a.size() - 1);
	a.erase(a.size() - 1);
	a.erase(a.size() - 1);
	a.erase(a.size() - 1);
	a.erase(a.size() - 1);
	return a;
}
void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void vebang4cot(int x, int y, int w, int h)
{
	//dong dau
	gotoxy(x, y);
	for (int i = 0; i < w;i++)
	{
		if (i == 0)
			cout << (char(201));
		else if (i == w - 1)
			cout << char(187);
		else if (i == w / 4 || i == 3 * w / 5 || i == 3 * w / 4)
			cout << (char)203;
		else
			cout << (char)205;
	}
	//cout << endl;
	gotoxy(x, y + 1);
	//doan giua
	for (int i = 0;i < h;i++)
	{
		if (i == 1)
		{
			for (int j = 0;j < w;j++)
			{
				if (j == 0)
					cout << (char)204;
				else if (j == w - 1)
					cout << (char)185;
				else if (j == w / 4 || j == 3 * w / 5 || j == 3 * w / 4)
				{
					cout << (char)206;
				}
				else cout << (char)205;
			}
			
		}
		else
		{
			for (int j = 0;j < w;j++)
			{
				if (j == 0 || j == w - 1)
					cout << (char)186;
				else if (j == w / 4 || j == 3 * w / 5 || j == 3 * w / 4)
				{
					cout << (char)186;
				}
				else cout << " ";
			}
			//cout << endl;
			
		}
		gotoxy(x, y + i + 2);
	}
	//dong cuoi
	gotoxy(x, y + h + 1);
	for (int i = 0; i < w;i++)
	{
		if (i == 0)
			cout << char(200);
		else if (i == w - 1)
			cout << (char(188));
		else if (i == w / 4 || i == 3 * w / 5 || i == 3 * w / 4)
			cout << (char)202;
		else
			cout << (char)205;
	}
	
}
void vebang2cot(int w, int h,int x, int y)
{
	//dong dau
	gotoxy(x, y);
	for (int i = 0; i < w;i++)
	{
		if (i == 0)
			cout << (char(201));
		else if (i == w - 1)
			cout << char(187);
		else if (i == w / 3 )
			cout << (char)203;
		else
			cout << (char)205;
	}
	//cout << endl;
	gotoxy(x, y + 1);
	//doan giua
	for (int i = 0;i < h;i++)
	{
		if (i == 1)
		{
			for (int j = 0;j < w;j++)
			{
				if (j == 0)
					cout << (char)204;
				else if (j == w - 1)
					cout << (char)185;
				else if (j == w / 3 )
				{
					cout << (char)206;
				}
				else cout << (char)205;
			}
			//cout << endl;
			
		}
		else
		{
			for (int j = 0;j < w;j++)
			{
				if (j == 0 || j == w - 1)
					cout << (char)186;
				else if (j == w / 3 )
				{
					cout << (char)186;
				}
				else cout << " ";
			}
			//cout << endl;
			
		}
		gotoxy(x, y + i + 2);
	}
	//dong cuoi
	gotoxy(x, y + h + 1);
	for (int i = 0; i < w;i++)
	{
		if (i == 0)
			cout << char(200);
		else if (i == w - 1)
			cout << char(188);
		else if (i == w - 1)
			cout << (char(188));
		else if (i == w / 3 )
			cout << (char)202;
		else
			cout << (char)205;
	}

}
void hidecur(bool flag)
{
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConCurInf.dwSize = 10;
	if (!flag)
	{
		ConCurInf.bVisible = TRUE;
	}
	else
	{
		ConCurInf.bVisible = FALSE;
	}

	SetConsoleCursorInfo(hOut, &ConCurInf);
}
int menu(string s[10], int n, int x, int y, int cmd)
{
	hidecur(true);
	int now = cmd;
	int prenow = -1;
	char key;
	for (int i = 0; i < n; i++)
	{
		gotoxy(x, y + i);
		if (i == now)
		{
			SetConsoleTextAttribute(console, 240);
			cout << s[i];			
			SetConsoleTextAttribute(console, 15);
		}
		else
		{
			cout << s[i];
		}
	}

	while (true)
	{
		for (int i = 0; i < n; i++)
		{
			gotoxy(x, y + i);
			if (i == now)
			{
				SetConsoleTextAttribute(console, 240);
				cout << s[i];	
				SetConsoleTextAttribute(console, 15);
			}
			if (i == prenow)
			{
				SetConsoleTextAttribute(console, 15);
				cout << s[i];			
			}
		}
		key = _getch();
		while (key == -32)
		{
			key = _getch();
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
			return now;
		}
		if (key == 27)
		{
			
			return 99;
		}
	}
}

int menuadvanced(string s[] , int x, int y,  int cmd,int max)
{
	int vt = 0;
start:
	XoaManHinh(x-10, y, 40, 16);
	hidecur(true);
	int n = 16;
	int now = cmd;
	int prenow = -1;
	char key;
	if (n + vt >= max )
		n = max - vt ;
	for (int i = 0 + vt; i < n + vt; i++)
		{
			gotoxy(x, y + i%16);
			if (i%16 == now)
			{

				SetConsoleTextAttribute(console, 240);
				cout << s[i];
				SetConsoleTextAttribute(console, 15);
			}
			else
			{
				cout << s[i];
			}
		}
	
	while (true)
	{		
			for (int i = 0 + vt; i < n + vt; i++)
			{
				gotoxy(x, y + i%16);
				if (i%16 == now)
				{

					SetConsoleTextAttribute(console, 240);
					cout << s[i];				
					SetConsoleTextAttribute(console, 15);
				}
				if (i%16 == prenow)
				{
					SetConsoleTextAttribute(console, 15);
					cout << s[i];					
				}
			}
		key = _getch();
		while (key == -32)
		{
			key = _getch();
		}
		if (key == 72)// phim len
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
		if (key == 80)// xuong
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
				return now + vt;			
		}
		if (key == 27)
		{
			return 99;
		}
	
		// bo sung
		if (key == 77)//sang phai
		{
			if (vt < max - 16)
			{
				vt += 16;
				XoaManHinh(x-10,y, 40, 17);//xoa man hinh o danh sach lop
				goto start;
			}
			
		}
		if (key == 75)//sang trai
		{
			if (vt>= 16)
			{
				vt -= 16;			
				XoaManHinh(x-10, y, 40, 17);
				goto start;
			}
		}	
	}
}
void Ve_HCN(int w, int h,int x, int y)
{
	gotoxy(x, y);
	for (int i = 0; i < w; i++)
	{
		if (i == 0)
			cout << (char(218));
		else if (i == w - 1)
			cout << char(191);
		else
			cout << (char)196;
	}
	cout << endl;
	//doan giua
	gotoxy(x, y + 1);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
			{
				if (j == 0 || j == w - 1)
					cout << (char)179;
				else cout << " ";
			}
			//cout << endl;
		gotoxy(x, y + i + 2);
	}
	//dong cuoi
	gotoxy(x, y + h+1 );
	for (int i = 0; i < w; i++)
	{
		if (i == 0)
			cout << char(192);
		else if (i == w - 1)
			cout << char(217);
		else
			cout << (char)196;
	}
}
void Ke_line(int w, int x, int y)
{
	gotoxy(x, y);
	for (int i = 0; i < w; i++)
	{
		if (i == 0)
			cout << (char)195;
		else if (i == w - 1)
			cout << (char)180;
		else
			cout << (char)196;
	}
}
void Ke_column(int h, int x, int y)
{
	
	for (int i = 0; i < h; i++)
	{
		gotoxy(x, y+i);
		if (i == 0)
			cout << (char)194;
		else if (i == h - 1)
			cout << (char)193;
		else
			cout << (char)179;
	}
}
bool SetWindowSize(size_t width, size_t height)
{
	HANDLE output_handle = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if (output_handle == INVALID_HANDLE_VALUE)
		return false;

	COORD coord = {};
	coord.X = static_cast<SHORT>(width);
	coord.Y = static_cast<SHORT>(height);
	if (::SetConsoleScreenBufferSize(output_handle, coord) == FALSE)
		return false;

	SMALL_RECT rect = {};
	rect.Bottom = coord.X - 1;
	rect.Right = coord.Y - 1;
	return (::SetConsoleWindowInfo(output_handle, TRUE, &rect) != FALSE);
}
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
bool ahaveb(string a, string b)
{
	int pos[10];
	int count = 0;
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] == b[0])
		{
			pos[count] = i;
			count++;
		}
	}
	for (int k = 0; k < count; k++)
	{
		for (int i = 0; i < b.length(); i++)
		{
			if (b[i] != a[pos[k]+i])
				break;			
			if (i == b.length()-1)
				return true;
		}
		
	}
	return false;
}
void kiemtraphim()
{
	char key_press;
	int ascii_value;
	cout << "\n\t\tNhap phim bat ky de kiem tra ma ASCII\n\t\t\An ESC de thoat\n\n\n";
	while (1)
	{
		key_press = _getch();
		ascii_value = key_press;
		if (ascii_value == 27) // For ESC
			break;
		cout << "Ban nhap phim-> \" " << key_press << " \" Gia tri ASCII =  " << ascii_value << "\n";
	}
	
}
void XoaManHinh(int x, int y, int w, int h)
{
	gotoxy(x, y);
	//SetConsoleTextAttribute(console, 135);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
			cout << " ";
		gotoxy(x, y + i + 1);
	}
}
void formlogin(int x, int y)
{
	//SetConsoleTextAttribute(console, 135);
	//gotoxy(10, 10);
	//gotoxy(x, y);
	Ve_HCN(60, 9, x, y);
	Ke_line(60, x, y + 2);
	gotoxy(25+ x, 1 + y);
	cout << "DANG NHAP ";
	gotoxy(3 + x, 4 + y);
	cout << "Username:  ";
	Ve_HCN(43, 1, 13 + x, 3 + y);
	gotoxy(3 + x, 7 + y);
	cout << "Password:  ";
	Ve_HCN(43, 1, 13 + x, 6 + y);
	gotoxy(0 + x, 11 + y);
}
void Khung_nhap_cau_hoi(int x, int y)
{
	XoaManHinh(x + 96, y + 5, 30, 1);
	gotoxy(x + 96, y + 5);
	cout << "Nhap cau hoi thi";
	//gotoxy(x, y);
	gotoxy(x + 52, y + 7);
	cout << "Cau hoi:";
	Ve_HCN(85, 5, x + 65, y + 7);

	gotoxy(x + 55, y + 15);
	cout << "Dap an A:";
	Ve_HCN(30, 2, x + 65, y + 14);// dap an 1

	gotoxy(x + 55, y + 19);
	cout << "Dap an C:";
	Ve_HCN(30, 2, x + 65, y + 18);// dan an 3

	gotoxy(x + 105, y + 15);
	cout << "Dap an B:";
	Ve_HCN(30, 2, x + 115, y + 14);// dap an 2

	gotoxy(x + 105, y + 19);
	cout << "Dap an D:";
	Ve_HCN(30, 2, x + 115, y + 18);// dap an 2

	gotoxy(x + 85, y + 22);
	cout << "Dap an dung: ";
	Ve_HCN(12, 1, x + 100, y + 21);
}
void Khung_Nhap_Sinh_Vien(int x, int y)
{
	XoaManHinh(x + 96, y + 5, 30, 1);
	gotoxy(x + 96, y + 5);
	cout << "Nhap sinh vien";
	gotoxy(x + 70, y + 9);
	cout << "Ma sinh vien: ";
	gotoxy(x + 70, y + 10);
	cout << "(Duoc tao tu dong ";
	gotoxy(x + 66, y + 11);
	cout<<"sau khi nhap thong tin)";
	Ve_HCN(20, 1, x + 90, y + 8);
	gotoxy(x + 55, y + 15);
	cout << "Ho:";
	Ve_HCN(30, 1, x + 65, y + 14);// ho

	gotoxy(x + 55, y + 19);
	cout << "Phai:";
	Ve_HCN(30, 1, x + 65, y + 18);// ten

	gotoxy(x + 105, y + 15);
	cout << "Ten:";
	Ve_HCN(30, 1, x + 115, y + 14);// gioi tinh

	gotoxy(x + 105, y + 19);
	cout << "Password:";
	Ve_HCN(30, 1, x + 115, y + 18);// pass
}
void Insert_string(string &a, int pos, char x)
{

	a.push_back(a[a.length()]);
	for (int i = a.length(); i > pos; i--)
	{
		a[i] = a[i - 1];
	}
	a[pos] = x;

}
void Delete_pos(string &s, int pos)
{
	int n = s.length();

	for (int i = pos - 1; i < n - 1; i++)
	{
		s[i] = s[i + 1];
	}
	s.erase(s.size()-1);
}
string Nhap_thong_tin(int x, int y, bool &exit, int limited)
{
	string infor;
	int pos = infor.length();
	//string hidepass;
	/*XoaManHinh(x + 15, y + 4, 30, 1);
	XoaManHinh(x + 15, y + 7, 30, 1);*/
	gotoxy(x + 15, y + 4);
	if (infor.length() != 0);
	cout << infor;
	while (true)
	{
		gotoxy(x + 15 + pos, y + 4);
		char k = _getch();
		while (k == -32)
		{
			k = _getch();
		}

		if (k == 8)//phim backspace
		{
			if (infor.length() >= 1)
			{
				XoaManHinh(x + 14 + infor.length(), y + 4, 1, 1);
				Delete_pos(infor, pos);
				pos--;
				gotoxy(x + 15, y + 4);
				if (infor.length() != 0)
				{
					cout << infor;
				}
			}
		}
		if ((k >= 32 && k <= 64 || k >= 91 && k <= 126 || k == 95) && infor.length()<=limited)//hang phim so
		{
			Insert_string(infor, pos, k);
			pos++;
			gotoxy(x + 15, y + 4);
			cout << infor;
		}
		
		if (k == 27)
		{
			exit = true;
			return "a";
		}

		if (k == 13)
		{
			if (infor.length() >= 1)
				break;
		}
		if (k == 77)//phim sang phai
		{
			if (pos < infor.length())
			{
				pos++;
				gotoxy(x + 15 + pos, y + 4);
			}
		}
		if (k == 75)//phim sang trai
		{
			if (pos>0)
			{
				pos--;
				gotoxy(x + 15 + pos, y + 4);
			}
		}

	}
	return infor;
}
string Nhap_Dap_An(int x, int y)
{
	string temp[2];
	int count = 0;
	string final;
	int line = 2;
enter:
	string qus;
	int pos = qus.length();
	gotoxy(x + 68, y + 3 + line);
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
					break;
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
					Delete_pos(qus,pos);
				}
			}
		}
		if ((k >= 32 && k <= 43 || k >= 91 && k <= 126 || k == 95 || k >= 45 && k <= 90) && count <= 1)//hang phim so
		{
			Insert_string(qus, pos, k);
			pos++;
			gotoxy(x + 68, y + 3 + line);
			cout << qus;
			if (qus.length() >= 25 )
			{
				temp[count] = qus;
				if (count <= 1)
				{
					line++;
					count++;
					goto enter;
				}
			}
		}	
		if (k == 13)
		{
			for (int i = 0; i <= count; i++)
			{
				
				final.append(temp[i]);
				
			}
			final.append(qus);
			if (final.length() >= 1)
			{
				//canexit = true;
				return final;
			}
		}
	}
}
string getlastname(string a)
{
	string result;
	int i = a.length();
	while (i >=0 )
	{
		if (a[i] == ' ')
		{
		//	result.pop_back();
			result.erase(result.size()-1);
			return result;
		}
		else
		{
			Insert_string(result, 0, a[i]);
			if (i>=0)
				i--;
		}
	}
	//result.pop_back();
	result.erase(result.size()-1);
	return result;
}
void khungquanlylophoc(int x, int y)
{
	//SetConsoleTextAttribute(console, 135);
	gotoxy(x, y);
	Ve_HCN(156, 35, x, y);
	gotoxy(x + 3, y + 2);
	cout << "Tim kiem: ";
	Ve_HCN(70, 1, x + 14, y + 1);//khung tim kiem
	Ve_HCN(50, 19, x + 1, y + 4);//khung danh sach lop
	Ke_line(50, x + 1, y + 6);
	Ve_HCN(104, 19, x + 51, y + 4);//khung danh sach sinh vien
	Ke_line(104, x + 51, y + 6);
	gotoxy(x + 18, y + 5);
	cout << "Danh sach lop hoc";
	gotoxy(x + 96, y + 5);
	cout << "Danh sach sinh vien";
	Ve_HCN(107, 9, x + 1, y + 25);//khung thong bao
	Ke_column(11, x + 48, y + 25);
	Ke_line(48, x + 1, y + 27);
	gotoxy(x + 20, y + 26);
	cout << "Thong bao";
	//gotoxy(x, y + 37);
	gotoxy(x + 65, y + 26);
	cout << "Phim tat kha dung";


}
int toInt(string s)
{
	int res = 0;
	for (int i = 0; i < s.length(); i++)
	{
		res = res * 10 + s[i] - 48;
	}
	return res;
}
int so_sanh_string(string s1, string s2)
{
	int a = s1.length();
	int b = s2.length();
	int max;
	if (a > b)
		max = a;
	else
		max = b;
	for (int i = 0; i < max; i++)
	{
		if (s1[i] > s2[i])
		{
			return 1;
			break;
			//Chuoi dau lon hon
		}
		if (s1[i]<s2[i])
		{
			return 2;
			break;
			//Chuoi sau lon hon
		}
		if (s1[i] == s2[i] && i == max - 1)
			return 0;
		//hai chuoi bang nhau
	}
}
int so_sanh_ho_ten(string t1, string t2, string h1, string h2)
{
	if (so_sanh_string(getlastname(t1), getlastname(t2)) == 0)
	{
		if (so_sanh_string(h1, h2) == 1)
			return 1;
		else if (so_sanh_string(h1, h2) == 2)
			return 2;
		else if (so_sanh_string(h1, h2) == 0)
			return 0;
	}
	else if (so_sanh_string(getlastname(t1), getlastname(t2)) == 1)
		return 1;
	else if (so_sanh_string(getlastname(t1), getlastname(t2)) == 2)
		return 2;
}
void Swap_lop(LOP &a, LOP&b)
{
	LOP temp;
	temp = a;
	a = b;
	b = temp;
}
void Swap_sv(SINHVIEN &a, SINHVIEN &b)
{
	SINHVIEN temp;
	temp = a;
	a = b;
	b = temp;
}
void Sap_xep_ho_ten_tang_dan(DANH_SACH_SINH_VIEN& dssv)
{
	for (NODESINHVIEN* k = dssv.phead; k != NULL; k = k->pnext)
	{
		for (NODESINHVIEN* i = dssv.phead; i != NULL; i = i->pnext)
		{
			if (so_sanh_ho_ten(k->data.ten, i->data.ten, k->data.ho, i->data.ho) == 2)
				Swap_sv(k->data, i->data);
		}
	}
}
void Khung_sua_mon_hoc(int x, int y)
{
	/*int x = a - 45;
	int y = b - 16;*/
	gotoxy(x + 107-45, y + 29-16);
	cout << "Ma mon hoc:";
	Ve_HCN(30, 1, x + 125-45, y + 28-16);
	gotoxy(x + 107-45, y + 32-16);
	cout << "Ten mon hoc:";
	Ve_HCN(50, 1,x + 125-45, y + 31-16 );
	
}
void khungquanlymonhoc(int x, int y)
{
	//SetConsoleTextAttribute(console, 135);
	gotoxy(x, y);
	Ve_HCN(156, 35, x, y);
	gotoxy(x + 3, y + 2);
	cout << "Tim kiem: ";
	Ve_HCN(70, 1, x + 14, y + 1);//khung tim kiem
	Ve_HCN(50, 19, x + 1, y + 4);//khung danh sach lop
	Ke_line(50, x + 1, y + 6);
	Ve_HCN(104, 19, x + 51, y + 4);//khung danh sach sinh vien
	Ke_line(104, x + 51, y + 6);
	gotoxy(x + 18, y + 5);
	cout << "Danh sach moc hoc";
	gotoxy(x + 96, y + 5);
	cout << "Danh sach cau hoi thi";
	Ve_HCN(107, 9, x + 1, y + 25);//khung thong bao
	Ke_column(11, x + 48, y + 25);
	Ke_line(48, x + 1, y + 27);
	gotoxy(x + 20, y + 26);
	cout << "Thong bao";
	//gotoxy(x, y + 37);
	gotoxy(x + 65, y + 26);
	cout << "Phim tat kha dung";
}
void Editable_Infor(string &a, int x, int y, int w, bool space, bool &canexit)
{
	y = y + 1;
	x++;
	int pos = a.length();
	XoaManHinh(x + 80, y + 12, w, 1);
	gotoxy(x + 80, y + 12);
	if (a.length() != 0)
		cout << a;
	while (true)
	{
		gotoxy(x + 80 + pos, y + 12);
		char k = _getch();
		while (k == -32)
		{
			k = _getch();
		}

		if (k == 8)//phim backspace
		{
			if (a.length() >= 1 && pos > 0)
			{
				XoaManHinh(x + 80-1 + a.length(), y + 12, 1, 1);
				Delete_pos(a, pos);
				pos--;
				gotoxy(x + 80, y + 12);
				if (a.length() != 0)
				{
					cout << a;
				}
			}
		}
		if ((k >= 32 && k <= 64 || k >= 91 && k <= 126 || k == 95) && a.length() <= w - 1 )//hang phim so
		{
			if (space == true )
			{
				Insert_string(a, pos, k);
				pos++;
				gotoxy(x + 80, y + 12);
				cout << a;
			}
			else
			{
				if (k != ' ')
				{
					Insert_string(a, pos, k);
					pos++;
					gotoxy(x + 80, y + 12);
					cout << a;
				}
			}
		}
		
		if (k == 13)//enter
		{
			if (a.length() >= 1)
			{
				canexit = true;
				break;
			}
		}
		if (k == 77)//phim sang phai
		{
			if (pos < a.length())
			{
				pos++;
				gotoxy(x + 80 + pos, y + 12);
			}
		}
		if (k == 75)//phim sang trai
		{
			if (pos>0)
			{
				pos--;
				gotoxy(x + 80 + pos, y + 12);
			}
		}
		if (k == 80 || k == 72)// phim len xuong
		{	
			canexit = false;
			break;		
		}

	}
}
void stringcopy(int size, int pos, string original, string &result)
{
	//string result;
	for (int i = pos; i < pos + size; i++)
	{
		//result[i - pos] = original[pos];
		Insert_string(result, result.length(), original[i]);
	}
}
void Xuat_Thanh_Phan_Cau_Hoi(string cauhoi, int x, int y, int max)
{
	string temp[5];
	//xsmax[0].copy()
	//string cauhoi = timCauHoi(root, ds[i])->key.qus;
	int n = (cauhoi.length() - cauhoi.length() % max) / max + 1;
	if (n == 1)
	{
		gotoxy(x + 67, y + 15);
		cout << cauhoi;
	}
	else
	{
		for (int i = 1; i < n; i++)
		{
			gotoxy(x + 67, y + (i - 1) + 15);
			stringcopy(max, (i - 1) * max, cauhoi, temp[i - 1]);
			//temp[i-1], 78, (i-1) * 79);
			cout << temp[i - 1];
		}
		gotoxy(x + 67, y + n - 1 + 15);
		stringcopy(cauhoi.length() % max, (n - 1) * max, cauhoi, temp[n - 1]);
		cout << temp[n - 1];
	}
}
string rut_gon_text(string a, int sl)
{

	string rs;
	if (sl >= a.length())
		return a;
	else
	{
		for (int i = 0; i < sl; i++)
		{
			Insert_string(rs, rs.length(), a[i]);
		}
		rs.append("...");
		return rs;
	}
}
void Khung_Nhap_Thong_Tin_Bai_Thi(int x, int y)
{
	Ve_HCN(75, 11, x, y);
	gotoxy(x + 10, y + 3);
	cout << "Mon thi";
	Ve_HCN(30,1,x+33,y+2);
	gotoxy(x + 10, y + 6);
	cout << "Thoi gian thi (phut)";
	Ve_HCN(30, 1, x + 33, y + 5);
	gotoxy(x + 10, y + 9);
	cout << "So cau hoi thi";
	Ve_HCN(30, 1, x + 33, y + 8);

}
int Kiem_Tra_Ma_Mon_Hoc_Tren_Cay(AVLTree root, string mamh, int &dem1)
{
	if (root != NULL)
	{
		
		Kiem_Tra_Ma_Mon_Hoc_Tren_Cay(root->pLeft, mamh, dem1);
		if (root->key.MAMH == mamh)
			dem1++;
		Kiem_Tra_Ma_Mon_Hoc_Tren_Cay(root->pRight, mamh, dem1);		
	}
	return dem1;
}
int Dem_Sl_Cau_Hoi_Co_MaMHH_Tren_Cay(AVLTree root, string mamh, int &count)
{
	if (root != NULL)
	{
		Dem_Sl_Cau_Hoi_Co_MaMHH_Tren_Cay(root->pLeft, mamh,count);
		//do some thing
		if (root->key.MAMH == mamh)
			count++;
		Dem_Sl_Cau_Hoi_Co_MaMHH_Tren_Cay(root->pRight, mamh,count);
	}
	return count;
}
void Khung_Thi_Trac_Nghiem(int x, int y)
{
	
	XoaManHinh(x + 96, y + 5, 30, 1);
	Ve_HCN(120, 24, x + 45, y + 2);
	gotoxy(x + 96, y + 5);
	cout << "ID cau hoi: ";
	//gotoxy(x, y);
	gotoxy(x + 52, y + 7);
	cout << "Cau hoi:";
	Ve_HCN(85, 5, x + 65, y + 7);

	gotoxy(x + 55, y + 15);
	cout << "Dap an 1:";
	Ve_HCN(30, 2, x + 65, y + 14);// dap an 1

	gotoxy(x + 55, y + 19);
	cout << "Dap an 3:";
	Ve_HCN(30, 2, x + 65, y + 18);// dan an 3

	gotoxy(x + 105, y + 15);
	cout << "Dap an 2:";
	Ve_HCN(30, 2, x + 115, y + 14);// dap an 2

	gotoxy(x + 105, y + 19);
	cout << "Dap an 4:";
	Ve_HCN(30, 2, x + 115, y + 18);// dap an 2

	gotoxy(x + 85, y + 22);
	cout << "Nhap dap an: ";
	Ve_HCN(12, 1, x + 100, y + 21);
}
void Swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}
void Tron_Mang_Ngau_Nhien(int arr[],int n)
{
	srand(time(NULL));

	int minPosition;
	int maxPosition = n - 1;
	int swapPosition;

	int i = 0;
	while (i < n - 1)
	{
		minPosition = i + 1;
		swapPosition = rand() % (maxPosition - minPosition + 1) + minPosition;

		Swap(arr[i], arr[swapPosition]);
		i++;
	}
}
void khungChonMonHoc(int flag)
{
	gotoxy(47, 1);
	cout << "---CHON MON THI---";
	gotoxy(40, 3);
	cout << "Ma mon";
	gotoxy(57, 3);
	cout << "Ten mon hoc ";

	gotoxy(36, 2);
	cout << (char)201;
	gotoxy(80, 2);
	cout << (char)187;
	gotoxy(36, 16);
	cout << (char)200;
	gotoxy(80, 16);
	cout << (char)188;

	if (flag == -1)
	{
		gotoxy(55, 16);
		cout << "...<<";
	}
	if (flag == 1)
	{
		gotoxy(55, 16);
		cout << ">>...";
	}
	if (flag == 0)
	{
		gotoxy(51, 16);
		cout << "...<<..>>...";
	}


}
void clr_xy(int x, int y, int _x, int _y)
{
	string emp = "";
	for (int i = 0; i < _x - x; i++)
	{
		emp.insert(0, " ");
	}

	for (int i = 0; i <= _y - y; i++)
	{
		gotoxy(x, y + i);
		cout << emp;
	}
}
void khungCauHoiRong(int sl_cauhoiKT)
{
	int x = 26;
	int y = 18;

	gotoxy(0, y - 1);
	cout << "---------------------------------------------------------------------------------------------";

	gotoxy(x - 13, y);
	cout << "Answer sheet: ";

	for (int i = 0; i < sl_cauhoiKT; i++)
	{
		gotoxy(x, y);
		cout << i + 1;
		x += 4;

		if (i % 10 == 9)
		{
			x = 26;
			y++;
		}
	}
}
int getNumber(int x, int y)
{
	//	int max, int x, int y
	string num = "";
	hidecur(false);
	int key = 0;
	while (true)
	{
		do{
			key = getch();
		} while (!((key > 47 && key < 58) || key == 13 || key == 27 || key == 8));

		if (key == 13) break;
		if (key == 27) return -1;
		if (key == 8)
		{
			if (num.length() > 0)
			{
				num.erase(num.size() - 1);
			}
		}
		else
		{
			if (num.size() < 3)
			{
				num.push_back((char)key);
			}
		}

		gotoxy(x, y);
		cout << "    ";
		gotoxy(x, y);
		cout << num;
	}

	return toInt(num);
}
void khungquanlydiemthi1sv(int x, int y)
{
	//SetConsoleTextAttribute(console, 135);
	gotoxy(x, y);
	Ve_HCN(102, 35, x, y);
	gotoxy(x + 3, y + 2);
	cout << "Tim kiem: ";
	Ve_HCN(70, 1, x + 14, y + 1);//khung tim kiem
	Ve_HCN(50, 19, x + 1, y + 4);//khung danh sach lop
	Ke_line(50, x + 1, y + 6);
	Ve_HCN(50, 19, x + 51, y + 4);//khung danh sach sinh vien
	Ke_line(50, x + 51, y + 6);
	//Ve_HCN(50, 19, x + 101, y + 4);// khung danh sach cau hoi da thi
	//Ke_line(50, x + 101, y + 6);
	gotoxy(x + 18, y + 5);
	cout << "Danh sach sinh vien";
	gotoxy(x + 65, y + 5);
	cout << "Danh sach mon hoc";
	Ve_HCN(100, 9, x + 1, y + 25);//khung thong bao
	/*gotoxy(x + 111, y + 5);
	cout << "Danh sach cau hoi da thi";*/
	Ke_column(11, x + 48, y + 25);
	Ke_line(48, x + 1, y + 27);
	gotoxy(x + 20, y + 26);
	cout << "Thong bao";
	//gotoxy(x, y + 37);
	gotoxy(x + 65, y + 26);
	cout << "Phim tat kha dung";
}
void khungquanlydiemthi1lop(int x, int y)
{
	//SetConsoleTextAttribute(console, 135);
	gotoxy(x, y);
	Ve_HCN(102, 35, x, y);
	gotoxy(x + 3, y + 2);
	cout << "Tim kiem: ";
	Ve_HCN(70, 1, x + 14, y + 1);//khung tim kiem
	Ve_HCN(50, 19, x + 1, y + 4);//khung danh sach lop
	Ke_line(50, x + 1, y + 6);
	Ve_HCN(50, 19, x + 51, y + 4);//khung danh sach sinh vien
	Ke_line(50, x + 51, y + 6);
	//Ve_HCN(50, 19, x + 101, y + 4);// khung danh sach cau hoi da thi
	//Ke_line(50, x + 101, y + 6);
	gotoxy(x + 18, y + 5);
	cout << "Danh sach lop";
	gotoxy(x + 65, y + 5);
	cout << "Danh sach mon hoc";
	Ve_HCN(100, 9, x + 1, y + 25);//khung thong bao
	/*gotoxy(x + 111, y + 5);
	cout << "Danh sach cau hoi da thi";*/
	Ke_column(11, x + 48, y + 25);
	Ke_line(48, x + 1, y + 27);
	gotoxy(x + 20, y + 26);
	cout << "Thong bao";
	//gotoxy(x, y + 37);
	gotoxy(x + 65, y + 26);
	cout << "Phim tat kha dung";
}
void Khung_Tim_Lop_Hoc(int x, int y)
{
	gotoxy(x, y);
	Ve_HCN(85, 25, x-5, y);
	gotoxy(x + 3 -5, y + 2);
	cout << "Ten/Ma lop: ";
	Ve_HCN(55, 1, x + 13, y + 1);//khung tim kiem
	//Ve_HCN(35, 19, x + 14, y + 4);//khung danh sach lop
	//Ke_line(35, x + 14, y + 6);
}
void Giai_Phong_Danh_Sach_Sinh_Vien(danh_sach_sinh_vien &l)
{

	node_sinh_vien *k = NULL;
	while (l.phead != NULL)
	{
			PTR_BaiKT p = l.phead->data.ds_bkt, temp;
			while(p != NULL)
			{
				temp = p;
				p = p->next;
				delete temp;
			}
			
		k = l.phead;
		l.phead = l.phead->pnext;
		delete k;
	}
}

void Giai_Phong_Tat_Ca_Danh_Sach_Sinh_Vien(DANH_SACH_LOP &dsl)
{
	for (int i = 0; i< dsl.sl;i++)
	{
		Giai_Phong_Danh_Sach_Sinh_Vien(dsl.lop[i].dssv);
	}
}

void giaiPhongDanhSachMonHoc(MON_HOC* ds_monhoc[MAX_MONHOC], int sl_monhoc)
{
	for(int i = 0; i< sl_monhoc; i++)
	{
		delete ds_monhoc[i];
	}
}
