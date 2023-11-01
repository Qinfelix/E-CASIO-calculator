#include<iostream>
#include<cmath>
#include<graphics.h>
#include<conio.h>
#include<string.h>
#include"button.h"
#include"function.h"
#include<fstream>
#include<atlstr.h>
using namespace std;

button::button(int a,int b,int c,int d,BUTTONTYPE t,LPCTSTR e)
{
	if((a<c)&(b<d))
	{
	x1=a;
	y1=b;
	x2=c;
	y2=d;
	str=e;
	};
	bu_type=t;
}
void button::graph()
{
	rectangle(x1,y1,x2,y2);
	int width=textwidth(str);
	outtextxy(x1/2+x2/2-width/2,y1+15,str);
}

bool button::buttondown(MOUSEMSG m)
{
	bool a=(x1<=m.x)&(m.x<=x2);
	bool b=(y1<=m.y)&(m.y<=y2);
	return a&b;
};

void button::outbutton()
{
	static int initialx=textwidth(_T("f(x)="))+2;
	outtextxy(initialx,15,str);
	initialx+=textwidth(str);
};

CString button::getstr()
{
	CString str1=str;
	return str1;
};

FUNCTION_BUTTONTYPE functionbutton::getfunction_type()
{
	return fun_type;
};

BRACKET_TYPE bracketbutton::getbracket_type()
{
	return brackettype;
};
RULES_TYPE fourrulesbutton::getrules_type()
{
	return rulestype;
};

void overbutton::outbutton()
{
	ifover=1;
}

int com_functionbutton::getcom_fun_type()
{
	return com_fun_type;
}

double constant_functionbutton::getnumber()
{return number;};

int incom_functionbutton::getsequence()
{
	return sequence;
};

 BRACKET_TYPE button::getbracket_type()
 {return NO;};


  int button::getsequence()
  {
	  return 0;
  }

   int button::getcom_fun_type()
  {
	  return 2;
  }