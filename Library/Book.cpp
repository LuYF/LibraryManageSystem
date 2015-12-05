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
//将图书对象写入文件
void CBook::WriteData()
{
	ofstream ofile;
	ofile.open("book.dat", ios::binary | ios::app);//二进制文件
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
//从文件中读取图书对象
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
		//将文件指针置于开始位置
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
//删除图书信息
void CBook::DeleteData(int iCount)
{
	long respos;
	int iDataCount = 0;
	fstream file;
	fstream tmpfile;
	ofstream ofile;
	char cTempBuf[NUM1 + NUM1 + NUM2 + NUM2];
	file.open("book.dat", ios::binary | ios::in | ios::out);
	tmpfile.open("temp.dat", ios::binary | ios::out | ios::trunc);//打开时删除之前的内容
	file.seekg(0, ios::end);//文件流指针置于文件尾
	respos = file.tellg();//文件流指针当前位置
	iDataCount = respos / (NUM1 + NUM2 + NUM1 + NUM2);//计算文件中图书对象个数
	if (iCount<0 && iCount>iDataCount)
	{
		cout << "Input number error";
	}
	else
	{
		file.seekg((iCount)*(NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
		for (int j = 0; j < (iDataCount - iCount); j++)
		{
			memset(cTempBuf, 0, NUM1 + NUM1 + NUM2 + NUM2);//清空cTempBuf
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

