#pragma once

#define NUM1 128
#define NUM2 50

class CBook
{
public:
	CBook();
	CBook(char *cName, char *cIsbn, char *cPrice, char *cAuthor);
	~CBook();

public:
	char* GetName();					//获取图书名称
	void SetName(char *cName);			//设置图书名称
	char* GetIsbn();					//获取图书编号
	void SetIsbn(char *cIsbn);			//设置图书编号
	char* GetPrice();
	void SetPrice(char *cPrice);
	char* GetAuthor();
	void SetAuthor(char *cAuthor);

	void WriteData();								//增加数据
	void DeleteData(int iCount);					//删除数据
	void GetBookFromFile(int iCount);				//获取数据

protected:
	char m_cName[NUM1];
	char m_cIsbn[NUM1];
	char m_cPrice[NUM2];
	char m_cAuthor[NUM2];
		
};

