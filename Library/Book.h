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
	char* GetName();					//��ȡͼ������
	void SetName(char *cName);			//����ͼ������
	char* GetIsbn();					//��ȡͼ����
	void SetIsbn(char *cIsbn);			//����ͼ����
	char* GetPrice();
	void SetPrice(char *cPrice);
	char* GetAuthor();
	void SetAuthor(char *cAuthor);

	void WriteData();								//��������
	void DeleteData(int iCount);					//ɾ������
	void GetBookFromFile(int iCount);				//��ȡ����

protected:
	char m_cName[NUM1];
	char m_cIsbn[NUM1];
	char m_cPrice[NUM2];
	char m_cAuthor[NUM2];
		
};

