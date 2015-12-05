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

//������Ļ��ʾ������������
void SetScreenGrid()
{
	char sysSetBuf[80];
	sprintf_s(sysSetBuf, "mode con cols=%d lines=%d", CMD_COLS, CMD_LINES);
	system(sysSetBuf);
}
//���ÿ���̨��������Ϣ
void SetSysCaption(const char* pText)
{
	char sysSetBuf[80];
	sprintf_s(sysSetBuf, "title %s", pText);
	system(sysSetBuf);
}
//����
void ClearScreen()
{
	system("cls");
}
//��ʾ��ӭ��Ϣ
void ShowWelcome()
{
	for (int i = 0; i < 7; i++)
	{
		cout << endl;
	}
	cout << setw(40);
	cout << "**************" << endl;
	cout << setw(40);
	cout << "ͼ�����ϵͳ" << endl;
	cout << setw(40);
	cout << "**************" << endl;
}
//��ʾϵͳ���˵�
void ShowRootMenu()
{
	cout << setw(40);
	cout << "��ѡ����" << endl;
	cout << endl;
	cout << setw(38);
	cout << "1 �������" << endl;
	cout << endl;
	cout << setw(38);
	cout << "2 ���ȫ��" << endl;
	cout << endl;
	cout << setw(38);
	cout << "3 ɾ��ͼ��" << endl;
}
//�ȴ��û�����
void WaitUser()
{
	int iInputPage = 0;
	cout << "enter �������˵� q �˳�" << endl;
	char buf[256];
	gets_s(buf);
	if (buf[0] = 'q')
		system("exit");
}

//��ȡ�û�ѡ��
int GetSelect()
{
	char buf[256];
	gets_s(buf);
	return atoi(buf);
}
//�������
void GuideInput()
{
	char inName[NUM1];
	char inIsbn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];

	cout << "��������" << endl;
	cin >> inName;
	cout << "����ISBN" << endl;
	cin >> inIsbn;
	cout << "����۸�" << endl;
	cin >> inPrice;
	cout << "��������" << endl;
	cin >> inAuthor;

	CBook book(inName, inIsbn, inPrice, inAuthor);
	book.WriteData();
	cout << "Write Finish" << endl;
	WaitUser();
}
//���ȫ��ͼ����Ϣ
void ViewData(int iSelPage = 1)
{
	int iPage = 0;
	int iCurPage = 0;
	int iDataCount = 0;
	char inName[NUM1];					//�洢ͼ�����Ƶı���
	char inIsbn[NUM1];					//�洢ͼ��ISBN�ı���
	char inPrice[NUM2];
	char inAuthor[NUM2];
	bool bIndex = false;
	int iFileLength;
	iCurPage = iSelPage;
	ifstream ifile;
	ifile.open("book.dat", ios::binary);
	iFileLength = GetFileLength(ifile);

	iDataCount = iFileLength / (NUM1 + NUM1 + NUM2 + NUM2);//�ļ����ܵļ�¼��
	if (iDataCount >= 1)
		bIndex = true;
	iPage = iDataCount / 20 + 1;
	ClearScreen();
	cout << "���м�¼" << iDataCount << " ";
	cout << "����ҳ��" << iPage << " ";
	cout << "��ǰҳ��" << iCurPage << " ";
	cout << "n ��ʾ��һҳ m ����" << endl;

	cout << setw(5) << "Index";
	cout << setw(15) << "Name" << setw(15) << "Isbn";
	cout << setw(15) << "Price" << setw(15) << "Author";
	cout << endl;

	try
	{
		//����ͼ���¼��Ų������ļ��е�λ��
		ifile.seekg((iCurPage - 1) * 20 * (NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
		if (!ifile.fail())
		{
			for (int i = 1; i < 21; i++)
			{
				memset(inName, 0, 128);//����
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
		throw "file error occured";			//�׳��쳣
		ifile.close();						//�쳣��ر��ļ���
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
//��ȡ�ļ���С
long GetFileLength(ifstream &ifs)
{
	long tmppos;
	long respos;
	tmppos = ifs.tellg();				//��ȡ�ļ�ָ��λ��
	ifs.seekg(0, ios::end);				//���ļ�ָ�������ļ�β
	respos = ifs.tellg();				//��ȡ�ļ�ָ��λ�ã����ļ���С
	ifs.seekg(tmppos, ios::beg);		//�ظ��ļ�ָ��ԭ����λ��
	return respos;
}
//ɾ��ͼ��
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