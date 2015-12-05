#include "Book.h"
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

CBook::CBook()
{

}
CBook::CBook(char *cName, char *cIsbn, char *cPrice, char *cAuthor)
{
	strcpy_s(m_cName,cName);
	strcpy_s(m_cIsbn, cIsbn);
	strcpy_s(m_cPrice, cPrice);
	strcpy_s(m_cAuthor, cAuthor); 
}


CBook::~CBook()
{

}
char* CBook::GetName()
{
	return m_cName;
}
void CBook::SetName(char *cName)
{
	strcpy_s(m_cName, cName);
}
char* CBook::GetIsbn()
{
	return m_cIsbn;
}
void CBook::SetIsbn(char *cIsbn)
{
	strcpy_s(m_cIsbn, cIsbn);
}
char* CBook::GetPrice()
{
	return m_cPrice;
}
void CBook::SetPrice(char *cPrice)
{
	strcpy_s(m_cPrice, cPrice);
}
char* CBook::GetAuthor()
{
	return m_cAuthor;
}
void CBook::SetAuthor(char *cAuthor)
{
	strcpy_s(m_cAuthor, cAuthor);
}
//��ͼ�����д���ļ�
void CBook::WriteData()
{
	ofstream ofile;
	ofile.open("book.dat", ios::binary | ios::app);//�������ļ�
	try
	{
		ofile.write(m_cName, NUM1);
		ofile.write(m_cIsbn, NUM1);
		ofile.write(m_cPrice, NUM2);
		ofile.write(m_cAuthor, NUM2);

	}
	catch (...)
	{
		throw "file error occurred";
		ofile.close();
	}
	ofile.close();
}
//���ļ��ж�ȡͼ�����
void CBook::GetBookFromFile(int iCount)
{
	char cName[NUM1];
	char cIsbn[NUM1];
	char cPrice[NUM2];
	char cAuthor[NUM2];

	ifstream ifile;
	ifile.open("book.dat", ios::binary);
	try
	{
		//���ļ�ָ�����ڿ�ʼλ��
		ifile.seekg(iCount*(NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
		ifile.read(cName, NUM1);
		if (ifile.tellg() > 0)
			strcpy_s(m_cName, cName);
		ifile.read(cIsbn, NUM1);
		if (ifile.tellg() > 0)
			strcpy_s(m_cIsbn, cIsbn);
		ifile.read(cAuthor, NUM2);
		if (ifile.tellg() > 0)
			strcpy_s(m_cAuthor, cAuthor);
		ifile.read(cPrice, NUM2);
		if (ifile.tellg() > 0)
			strcpy_s(m_cPrice, cPrice);
	}
	catch (...)
	{
		throw  "file error occurred";
		ifile.close();
	}
	ifile.close();

}
//ɾ��ͼ����Ϣ
void CBook::DeleteData(int iCount)
{
	long respos;
	int iDataCount = 0;
	fstream file;
	fstream tmpfile;
	ofstream ofile;
	char cTempBuf[NUM1 + NUM1 + NUM2 + NUM2];
	file.open("book.dat", ios::binary | ios::in | ios::out);
	tmpfile.open("temp.dat", ios::binary | ios::out | ios::trunc);//��ʱɾ��֮ǰ������
	file.seekg(0, ios::end);//�ļ���ָ�������ļ�β
	respos = file.tellg();//�ļ���ָ�뵱ǰλ��
	iDataCount = respos / (NUM1 + NUM2 + NUM1 + NUM2);//�����ļ���ͼ��������
	if (iCount<0 && iCount>iDataCount)
	{
		cout << "Input number error";
	}
	else
	{
		file.seekg((iCount)*(NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
		for (int j = 0; j < (iDataCount - iCount); j++)
		{
			memset(cTempBuf, 0, NUM1 + NUM1 + NUM2 + NUM2);//���cTempBuf
			file.read(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
			tmpfile.write(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);

		}
		file.close();
		tmpfile.seekg(0, ios::beg);
		ofile.open("book.dat");
		ofile.seekp((iCount)*(NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
		for (int i=0; i < (iDataCount - iCount); i++)
		{
			memset(cTempBuf, 0, NUM1 + NUM1 + NUM2 + NUM2);
			tmpfile.read(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
			ofile.write(cTempBuf, NUM1 + NUM1 + NUM2 + NUM2);
		}

	}
	tmpfile.close();
	ofile.close();
	remove("temp.dat");
}

