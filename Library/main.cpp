#include<iostream>
#include<stdlib.h>
#include<iomanip>
#include<string>
#include<fstream>
#include"Book.h"

using namespace std;

#define CMD_COLS 80
#define CMD_LINES 80

void SetScreenGrid();
void ClearScreen();
void SetSysCaption(const char *pText);
void ShowWelcome();
void ShowRootMenu();
void WaitView(int iCurPage);
void WaitUser();
void GuideInput();
int GetSelect();
long GetFileLength(ifstream &ifs);
void ViewData(int iSelPage);
void DeleteBookFromFile();

//设置屏幕显示的行数和列数
void SetScreenGrid()
{
	char sysSetBuf[80];
	sprintf_s(sysSetBuf, "mode con cols=%d lines=%d", CMD_COLS, CMD_LINES);
	system(sysSetBuf);
}
//设置控制台标题栏信息
void SetSysCaption(const char* pText)
{
	char sysSetBuf[80];
	sprintf_s(sysSetBuf, "title %s", pText);
	system(sysSetBuf);
}
//清屏
void ClearScreen()
{
	system("cls");
}
//显示欢迎信息
void ShowWelcome()
{
	for (int i = 0; i < 7; i++)
	{
		cout << endl;
	}
	cout << setw(40);
	cout << "**************" << endl;
	cout << setw(40);
	cout << "图书管理系统" << endl;
	cout << setw(40);
	cout << "**************" << endl;
}
//显示系统主菜单
void ShowRootMenu()
{
	cout << setw(40);
	cout << "请选择功能" << endl;
	cout << endl;
	cout << setw(38);
	cout << "1 添加新书" << endl;
	cout << endl;
	cout << setw(38);
	cout << "2 浏览全部" << endl;
	cout << endl;
	cout << setw(38);
	cout << "3 删除图书" << endl;
}
//等待用户输入
void WaitUser()
{
	int iInputPage = 0;
	cout << "enter 返回主菜单 q 退出" << endl;
	char buf[256];
	gets_s(buf);
	if (buf[0] = 'q')
		system("exit");
}

//获取用户选择
int GetSelect()
{
	char buf[256];
	gets_s(buf);
	return atoi(buf);
}
//添加新书
void GuideInput()
{
	char inName[NUM1];
	char inIsbn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];

	cout << "输入书名" << endl;
	cin >> inName;
	cout << "输入ISBN" << endl;
	cin >> inIsbn;
	cout << "输入价格" << endl;
	cin >> inPrice;
	cout << "输入作者" << endl;
	cin >> inAuthor;

	CBook book(inName, inIsbn, inPrice, inAuthor);
	book.WriteData();
	cout << "Write Finish" << endl;
	WaitUser();
}
//浏览全部图书信息
void ViewData(int iSelPage = 1)
{
	int iPage = 0;
	int iCurPage = 0;
	int iDataCount = 0;
	char inName[NUM1];					//存储图书名称的变量
	char inIsbn[NUM1];					//存储图书ISBN的变量
	char inPrice[NUM2];
	char inAuthor[NUM2];
	bool bIndex = false;
	int iFileLength;
	iCurPage = iSelPage;
	ifstream ifile;
	ifile.open("book.dat", ios::binary);
	iFileLength = GetFileLength(ifile);

	iDataCount = iFileLength / (NUM1 + NUM1 + NUM2 + NUM2);//文件中总的记录数
	if (iDataCount >= 1)
		bIndex = true;
	iPage = iDataCount / 20 + 1;
	ClearScreen();
	cout << "共有记录" << iDataCount << " ";
	cout << "共有页数" << iPage << " ";
	cout << "当前页数" << iCurPage << " ";
	cout << "n 显示下一页 m 返回" << endl;

	cout << setw(5) << "Index";
	cout << setw(15) << "Name" << setw(15) << "Isbn";
	cout << setw(15) << "Price" << setw(15) << "Author";
	cout << endl;

	try
	{
		//根据图书记录编号查找在文件中的位置
		ifile.seekg((iCurPage - 1) * 20 * (NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
		if (!ifile.fail())
		{
			for (int i = 1; i < 21; i++)
			{
				memset(inName, 0, 128);//清零
				memset(inIsbn, 0, 128);
				memset(inAuthor, 0, 50);
				memset(inPrice, 0, 50);

				if (bIndex)
					cout << setw(3) << ((iCurPage - 1) * 20 + i);

				ifile.read(inName, NUM1);
				cout << setw(20) << inName;
				ifile.read(inIsbn, NUM1);
				cout<< setw(12) << inIsbn;
				ifile.read(inPrice, NUM2);
				cout << setw(14) << inPrice;
				ifile.read(inAuthor, NUM2);
				cout << setw(16) << inAuthor;
				cout << endl;

				if (ifile.tellg() < 0)
					bIndex = false;
				else
					bIndex = true;
			}
		}
	}
	catch (...)
	{
		cout << "throw file exception " << endl;
		throw "file error occured";			//抛出异常
		ifile.close();						//异常后关闭文件流
	}
	if (iCurPage < iPage)
	{
		iCurPage = iCurPage + 1;
		WaitView(iCurPage);
	}
	else
	{
		WaitView(iCurPage);
	}
	ifile.close();
}
//获取文件大小
long GetFileLength(ifstream &ifs)
{
	long tmppos;
	long respos;
	tmppos = ifs.tellg();				//获取文件指针位置
	ifs.seekg(0, ios::end);				//将文件指针置于文件尾
	respos = ifs.tellg();				//获取文件指针位置，即文件大小
	ifs.seekg(tmppos, ios::beg);		//回复文件指针原来的位置
	return respos;
}
//删除图书
void DeleteBookFromFile()
{
	int iDelCount;
	cout << "Input delete index" << endl;
	cin >> iDelCount;
	CBook tmpbook;
	tmpbook.DeleteData(iDelCount);
	cout << "Delete Finish" << endl;
	WaitUser();
}
void WaitView(int iCurPage)
{
	char buf[256];
	gets_s(buf);
	if (buf[0] == 'q')
		system("exit");
	if (buf[0] == 'n')
		ViewData(iCurPage);
}

void main()
{
	ShowWelcome();
	while (1)
	{
		ClearScreen();
		ShowWelcome();
		ShowRootMenu();
		switch (GetSelect())
		{
		case 1:
			ClearScreen();
			GuideInput();
			break;
		case 2:
			ClearScreen();
			ViewData(1);
			break;
		case 3:
			ClearScreen();
			DeleteBookFromFile();
			break;

		default:
			break;
		}
	}
	system("pause");
	return;
}