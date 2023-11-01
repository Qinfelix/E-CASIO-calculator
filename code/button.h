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

class button//按钮基类
{
protected:
	int x1,y1,x2,y2;
	LPCTSTR str;
public:
	button(int a,int b,int c,int d,BUTTONTYPE t,LPCTSTR e);//构造函数
	void graph();//绘制按钮
	bool buttondown(MOUSEMSG m);//判断按钮是否按下
	virtual void outbutton();//文字输出按钮代表含义
	BUTTONTYPE bu_type;//获得button的类型
	CString getstr();//字符串的外部接口
	virtual FUNCTION_BUTTONTYPE getfunction_type(){abort();};//如果为函数类按钮才有意义，用来获取函数类型为完整还是非完整
	virtual BRACKET_TYPE getbracket_type();//为括号类按钮准备，获取括号类型
	virtual RULES_TYPE getrules_type(){abort();};//为四则运算准备获取四则运算类型
	virtual double getnumber(){abort();};//为常函数按钮设置
	virtual int getcom_fun_type();//为完整函数准备，判断是线性函数还是常函数
	virtual int getsequence();//为非完整函数准备，获得他的函数编号
};


class functionbutton:public button//函数区域按钮基类
{
public:
	FUNCTION_BUTTONTYPE fun_type;//函数的类型
	functionbutton(int a,int b,LPCTSTR e,FUNCTION_BUTTONTYPE t):button(a,b,a+120,b+50,FUNCTION,e),fun_type(t){};
	virtual FUNCTION_BUTTONTYPE getfunction_type();
};
//四则运算区域按钮
class fourrulesbutton:public button
{
private:
	RULES_TYPE rulestype;
public:
	fourrulesbutton(int a,int b,LPCTSTR e,RULES_TYPE t):button(a,b,a+60,b+50,RULES,e),rulestype(t){};
	virtual RULES_TYPE getrules_type();

};
class bracketbutton:public button//括号按钮
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

class overbutton:public button//结束按钮
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

//完整函数按钮类
class com_functionbutton:public functionbutton
{
private:
	int com_fun_type;
public:
	virtual int getcom_fun_type();
	com_functionbutton(int a,int b,LPCTSTR e,int t):functionbutton(a,b,e,COM),com_fun_type(t){};
};
//常函数按钮类-完函数类型为0
class constant_functionbutton:public com_functionbutton
{
public:
	double number;
	virtual double getnumber();
	constant_functionbutton(int a,int b,LPCTSTR e,double num):com_functionbutton(a,b,e,0),number(num){};
};
//一次函数按钮-完整函数类型为1
class linear_functionbutton:public com_functionbutton
{
public:
	linear_functionbutton(int a,int b,LPCTSTR e):com_functionbutton(a,b,e,1){};
};
//非完整函数按钮
class incom_functionbutton:public functionbutton
{
private:
	int sequence;
public:
	virtual int getsequence();
	incom_functionbutton(int a,int b,LPCTSTR e,int i):functionbutton(a,b,e,INCOM),sequence(i){};
};


#endif