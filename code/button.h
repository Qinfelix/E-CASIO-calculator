#ifndef BUTTON_H
#define BUTTON_H

#include<iostream>
#include<cmath>
#include<graphics.h>
#include<conio.h>
#include<string.h>
#include"function.h"
#include<fstream>
#include<atlstr.h>

using namespace std;

enum BUTTONTYPE{FUNCTION,RULES,BRACKET,OVER};
enum FUNCTION_BUTTONTYPE{COM,INCOM};
enum BRACKET_TYPE{LEFT,RIGHT,NO};
enum RULES_TYPE{ADD,MINUS,MULTIPY,DIVIDE};



extern bool ifover;

class button//��ť����
{
protected:
	int x1,y1,x2,y2;
	LPCTSTR str;
public:
	button(int a,int b,int c,int d,BUTTONTYPE t,LPCTSTR e);//���캯��
	void graph();//���ư�ť
	bool buttondown(MOUSEMSG m);//�жϰ�ť�Ƿ���
	virtual void outbutton();//���������ť������
	BUTTONTYPE bu_type;//���button������
	CString getstr();//�ַ������ⲿ�ӿ�
	virtual FUNCTION_BUTTONTYPE getfunction_type(){abort();};//���Ϊ�����ఴť�������壬������ȡ��������Ϊ�������Ƿ�����
	virtual BRACKET_TYPE getbracket_type();//Ϊ�����ఴť׼������ȡ��������
	virtual RULES_TYPE getrules_type(){abort();};//Ϊ��������׼����ȡ������������
	virtual double getnumber(){abort();};//Ϊ��������ť����
	virtual int getcom_fun_type();//Ϊ��������׼�����ж������Ժ������ǳ�����
	virtual int getsequence();//Ϊ����������׼����������ĺ������
};


class functionbutton:public button//��������ť����
{
public:
	FUNCTION_BUTTONTYPE fun_type;//����������
	functionbutton(int a,int b,LPCTSTR e,FUNCTION_BUTTONTYPE t):button(a,b,a+120,b+50,FUNCTION,e),fun_type(t){};
	virtual FUNCTION_BUTTONTYPE getfunction_type();
};
//������������ť
class fourrulesbutton:public button
{
private:
	RULES_TYPE rulestype;
public:
	fourrulesbutton(int a,int b,LPCTSTR e,RULES_TYPE t):button(a,b,a+60,b+50,RULES,e),rulestype(t){};
	virtual RULES_TYPE getrules_type();

};
class bracketbutton:public button//���Ű�ť
{
private:
	BRACKET_TYPE brackettype;
public:
	bracketbutton(int a,int b,LPCTSTR e,BRACKET_TYPE t):button(a,b,a+60,b+50,BRACKET,e),brackettype(t){};
	virtual BRACKET_TYPE getbracket_type();
	virtual FUNCTION_BUTTONTYPE getfunction_type(){abort();};
	virtual RULES_TYPE getrules_type(){abort();};
	virtual double getnumber(){abort();};
};

class overbutton:public button//������ť
{
public:
	overbutton(int a,int b,LPCTSTR e):button(a,b,a+60,b+50,OVER,e){};
	virtual void outbutton();
	virtual FUNCTION_BUTTONTYPE getfunction_type(){abort();};
	virtual BRACKET_TYPE getbracket_type(){abort();};
	virtual RULES_TYPE getrules_type(){abort();};
	virtual double getnumber(){abort();};
	virtual int getcom_fun_type(){abort();};
};

//����������ť��
class com_functionbutton:public functionbutton
{
private:
	int com_fun_type;
public:
	virtual int getcom_fun_type();
	com_functionbutton(int a,int b,LPCTSTR e,int t):functionbutton(a,b,e,COM),com_fun_type(t){};
};
//��������ť��-�꺯������Ϊ0
class constant_functionbutton:public com_functionbutton
{
public:
	double number;
	virtual double getnumber();
	constant_functionbutton(int a,int b,LPCTSTR e,double num):com_functionbutton(a,b,e,0),number(num){};
};
//һ�κ�����ť-������������Ϊ1
class linear_functionbutton:public com_functionbutton
{
public:
	linear_functionbutton(int a,int b,LPCTSTR e):com_functionbutton(a,b,e,1){};
};
//������������ť
class incom_functionbutton:public functionbutton
{
private:
	int sequence;
public:
	virtual int getsequence();
	incom_functionbutton(int a,int b,LPCTSTR e,int i):functionbutton(a,b,e,INCOM),sequence(i){};
};


#endif