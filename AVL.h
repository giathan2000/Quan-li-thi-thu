#pragma once
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <windows.h>
#include <fstream>
#include <ctype.h>
#include "tum_lum.h"
using namespace std;
#define LH -1
#define EH 0
#define RH 1 
void CreateAVLTree(AVLTree &root)
{
      root = NULL;
} 
AVLNode *CreateAVLNode(CauHoi key)
{
        AVLNode *p = new AVLNode;
 
        if (!p) exit(1);
 
        p->CSCB = EH;
        p->key = key;
        p->pLeft = NULL;
        p->pRight = NULL;
 
        return p;
}
 //cay con trai lech trai
void Rotate_Left_Left(AVLTree &root)
{
        AVLNode *p;
 
        p = root->pLeft;
        root->pLeft = p->pRight;
        p->pRight = root;
 
        switch (p->CSCB)
        {
        case LH:
                root->CSCB = EH;
                p->CSCB = EH;
                break;
        case EH:
                p->CSCB = RH;
                root->CSCB = LH;
                break;
        }
 
        root = p;
}
 //cay con phai lech phai
void Rotate_Right_Right(AVLTree &root)
{
        AVLNode *p;
 
        p = root->pRight;
        root->pRight = p->pLeft;
        p->pLeft = root;
 
        switch (p->CSCB)
        {
        case EH:
                root->CSCB = RH;
                p->CSCB = EH;
                break;
        case RH:
                p->CSCB = EH;
                root->CSCB = EH;
                break;
        }
 
        root = p;
}
 //cay con phai lech trai
void Rotate_Right_Left(AVLTree &root)
{
        AVLNode *p1, *p2;
 
        p1 = root->pRight;
        p2 = p1->pLeft;
        root->pRight = p2->pLeft;
        p1->pLeft = p2->pRight;
        p2->pLeft = root;
        p2->pRight = p1;
 
        switch (p2->CSCB)
        {
        case LH:
                root->CSCB = EH;
                p1->CSCB = RH;
                break;
        case EH:
                root->CSCB = EH;
                p1->CSCB = EH;
                break;
        case RH:
                root->CSCB = LH;
                p1->CSCB = EH;
                break;
        }
 
        p2->CSCB = EH;
        root = p2;
}
 //cay con trai lech phai
void Rotate_Left_Right(AVLTree &root)
{
        AVLNode *p1, *p2;
 
        p1 = root->pLeft;
        p2 = p1->pRight;
        root->pLeft = p2->pRight;
        p1->pRight = p2->pLeft;
        p2->pRight = root;
        p2->pLeft = p1;
 
        switch (p2->CSCB)
        {
        case LH:
                p1->CSCB = EH;
                root->CSCB = RH;
                break;
        case EH:
                root->CSCB = EH;
                p1->CSCB = EH;
                break;
        case RH:
                root->CSCB = EH;
                p1->CSCB = LH;
                break;
        }
 
        p2->CSCB = EH;
        root = p2;
}
 //Can bang khi cay lech trai
int BalanceLeft(AVLTree &root)
{
        AVLNode *p;
 
        p = root->pLeft;
 
        switch (p->CSCB)
        {
        case LH:
                Rotate_Left_Left(root);
                return 2;
        case EH:
                Rotate_Left_Left(root);
                return 1;
        case RH:
                Rotate_Left_Right(root);
                return 2;
        }
}
 //can bang cay lech phai
int BalanceRight(AVLTree &root)
{
        AVLNode *p;
 
        p = root->pRight;
 
        switch (p->CSCB)
        {
        case RH:
                Rotate_Right_Right(root);
                return 2;
        case EH:
                Rotate_Right_Right(root);
                return 1;
        case LH:
                Rotate_Right_Left(root);
                return 2;
        }
}
 //Chen 1 node vao cay AVL
int InsertNode(AVLTree &root, CauHoi key)
{
        int Res;
        if (root)
        {
                //gia tri da co trong cay
                if (root->key.id == key.id) return 0;
 
                //root->x > x
                //chen vao ben trai
                if (root->key.id > key.id)
                {
                        Res = InsertNode(root->pLeft, key);
                        if (Res < 2) return Res;
 
                        //Res >= 2
                        switch (root->CSCB)
                        {
                        case RH:
                                root->CSCB = EH;
                                return 1;
                        case EH:
                                root->CSCB = LH;
                                return 2;
                        case LH:
                                BalanceLeft(root);
                                return 1;
                        }
                }
 
                //root->x < x
                //chen vao ben phai
                else
                {
                        Res = InsertNode(root->pRight, key);
 
                        if (Res < 2) return Res;
 
                        //Res >= 2
                        switch (root->CSCB)
                        {
                        case LH:
                                root->CSCB = EH;
                                return 1;
                        case EH:
                                root->CSCB = RH;
                                return 2;
                        case RH:
                                BalanceRight(root);
                                return 1;
                        }
                }
        }
 
        root = CreateAVLNode(key);
        return 2;
}
 //Tim node the mang
int SearchStandFor(AVLTree &root, AVLNode *&p)
{
        int Res;
 
        if (p->pLeft)
        {
                Res = SearchStandFor(root, p->pLeft);
 
                if (Res < 2) return Res;
 
                switch (p->CSCB)
                {
                case LH:
                        p->CSCB = EH;
                        return 1;
                case EH:
                        p->CSCB = RH;
                        return 2;
                case RH:
                        return BalanceRight(root);
                }
        }
 
        root->key = p->key;
        root = p;
        p = p->pRight;
        return 2;
} 
//Xoa 1 node tren cay
int DelNode(AVLTree &root, CauHoi key)
{
        int Res;
 
        //Khong ton tai node nay tren cay
        if (!root) return 0;
 
        //Qua duoc if tren tuc la ton tai
        //root->x > x => Sang ben trai tim xoa
        if (root->key.id > key.id)
        {
                Res = DelNode(root->pLeft, key);
 
                //Neu co xoa thi Res = 1 hoac 2. 2 tuc thay doi chieu cao cay
                if (Res < 2) return Res;
 
                //Chieu cao bi thay doi
                switch (root->CSCB)
                {
                case LH:
                        root->CSCB = EH;
                        return 2;
                case EH:
                        root->CSCB = RH;
                        return 1;
                case RH:
                        return BalanceRight(root);
                }
        }
 
        if (root->key.id < key.id)
        {
                Res = DelNode(root->pRight, key);
 
                if (Res < 2) return Res;
 
                switch (root->CSCB)
                {
                case LH:
                        return BalanceLeft(root);
                case EH:
                        root->CSCB = LH;
                        return 1;
                case RH:
                        root->CSCB = EH;
                        return 2;
                }
        }
        else
        {
                AVLNode *p1 = root;
 
                if (root->pLeft == NULL)
                {
                        root = root->pRight;
                        Res = 2;
                }
                else
                {
                        if (root->pRight == NULL)
                        {
                                root = root->pLeft;
                                Res = 2;
                        }
                        else
                        {
                                Res = SearchStandFor(p1, root->pRight);
 
                                if (Res < 2) return Res;
                                switch (root->CSCB)
                                {
                                case RH:
                                        root->CSCB = EH;
                                        return 2;
                                case EH:
                                        root->CSCB = LH;
                                        return 1;
                                case LH:
                                        return BalanceRight(root);
                                }
                        }
                        delete p1;
                        return Res;
                }
        }
 
}
void DelTree(AVLTree &root)
{
	if(root != NULL)
	{
		DelTree(root->pLeft);
		DelTree(root->pRight);
		delete root;	
	}
	root = NULL;
}
 bool kiemTraDaThiMonHoc(PTR_BaiKT p ,string MAMH)
{
	while(p != NULL)
	{
		if(p->bkt.MAMH == MAMH) return true;
		p = p->next;
	}
	
	return false;
}
int taoId()
{
	
	int a[100001];
	fstream file;
	file.open("ds_id_ngaunhien.config", ios::in );
	
	for(int i=0 ; i <=100000; i++)
	{
		file >> a[i];
		file.ignore();
	}
	file.close();
	
	file.open("ds_id_ngaunhien.config", ios::out | ios::trunc);
	
	for(int i=1 ; i <=100000; i++)
	{
		file << a[i];
		file << ";";

	}
	file.close();
	return a[0];
}

