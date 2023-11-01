#define _USE_MATH_DEFINES 
#include <iostream>
#include<graphics.h>
#include<string.h>
#include<conio.h>
#include"button.h"
#include"function.h"
#include<vector>
#include<fstream>
using namespace std;
extern bool ifover;
static ofstream output("MaP_log",ios_base::out);

     incom_functionbutton sin_bu(0,50,_T("sin"),1);
	 incom_functionbutton cos_bu(120,50,_T("cos"),2);
	 incom_functionbutton tan_bu(240,50,_T("tan"),3);
	 incom_functionbutton misin_bu(0,100,_T("sin-1"),4);
	 incom_functionbutton micos_bu(120,100,_T("cos-1"),5);
	 incom_functionbutton mitan_bu(240,100,_T("tan-1"),6);
	 incom_functionbutton power_bu(120,150,_T("x^"),7);
	 incom_functionbutton exp_bu(240,150,_T("a^x"),8);
	 incom_functionbutton log_bu(0,200,_T("loga x"),9);
	incom_functionbutton incom_fun_bu[9]={sin_bu,cos_bu,tan_bu,misin_bu,micos_bu,mitan_bu,power_bu,exp_bu,log_bu};//函数区域按钮
	//线性函数
	linear_functionbutton x_bu(0,150,_T("x"));
	//常函数按钮
	 constant_functionbutton zero_bu(360,200,_T("0"),0);
	 constant_functionbutton one_bu(360,50,_T("1"),1);
	 constant_functionbutton two_bu(480,50,_T("2"),2);
	 constant_functionbutton three_bu(600,50,_T("3"),3);
	 constant_functionbutton four_bu(360,100,_T("4"),4);
	 constant_functionbutton five_bu(480,100,_T("5"),5);
	 constant_functionbutton six_bu(600,100,_T("6"),6);
	 constant_functionbutton seven_bu(360,150,_T("7"),7);
	 constant_functionbutton eight_bu(480,150,_T("8"),8);
	 constant_functionbutton nine_bu(600,150,_T("9"),9);
	 constant_functionbutton E_bu(480,200,_T("e"),M_E);
	 constant_functionbutton PI_bu(600,200,_T("Π"),M_PI);
	constant_functionbutton num_bu[12]={zero_bu,one_bu,two_bu,three_bu,four_bu,five_bu,six_bu,seven_bu,eight_bu,nine_bu,E_bu,PI_bu};
	//四则运算按钮
	 fourrulesbutton add_bu(720,50,_T("+"),ADD);
	 fourrulesbutton minus_bu(720,100,_T("-"),MINUS);
	 fourrulesbutton multipy_bu(720,150,_T("*"),MULTIPY);
	 fourrulesbutton divide_bu(720,200,_T("/"),DIVIDE);
	fourrulesbutton rules_bu[4]={add_bu,minus_bu,multipy_bu,divide_bu};
	//括号按钮
	bracketbutton left_bu(600,250,_T("("),LEFT);
	 bracketbutton right_bu(660,250,_T(")"),RIGHT);
	bracketbutton bra_bu[2]={left_bu,right_bu};
	//结束按钮
	 overbutton over_bu(720,250,_T("OK"));

	 	bool ifover=0;//初始化是否结束的判断依据

    //储存全局变量
	linear_function linear_fun;
	sin_function sin_out[50];
	cos_function cos_out[50];
	tan_function tan_out[50];
	misin_function misin_out[50];
	micos_function micos_out[50];
    mitan_function mitan_out[50];
	power_function power_out[50];
	exp_function exp_out[50];
	log_function log_out[50];
	constant_function constant_out[50];
	add_function add_out[50];
	minus_function minus_out[50];
	multipy_function multipy_out[50];
	divide_function divide_out[50];

	int several=0;

//初始化界面
void iniwindow()
{
	initgraph(780,300);
	settextstyle(20,12,_T("宋体"));
	rectangle(0,0,780,50);
	outtextxy(2,15,_T("f(x)="));
	for(int i=0;i<=8;i++)
	{
		incom_fun_bu[i].graph();
	};
	for(int i=0;i<=11;i++)
	{
		num_bu[i].graph();
	}
	for(int i=0;i<=3;i++)
	{
		rules_bu[i].graph();
	};
	for(int i=0;i<=1;i++)
	{
		bra_bu[i].graph();
	};
	over_bu.graph();//绘制
	x_bu.graph();
};

//检测鼠标落在了哪里
button* wheredown(MOUSEMSG m)//处理鼠标信息
{
	for(int i=0;i<=8;i++)
	{
		if(incom_fun_bu[i].buttondown(m)==1)
		{
			return &incom_fun_bu[i];
			break;
		}
	};
	for(int i=0;i<=11;i++)
	{
		if(num_bu[i].buttondown(m)==1)
		{
			return &num_bu[i];
			break;
		}
	};
	for(int i=0;i<=3;i++)
	{
		if(rules_bu[i].buttondown(m)==1)
		{
			return &rules_bu[i];
			break;
		}
	};
	for(int i=0;i<=1;i++)
	{
		if(bra_bu[i].buttondown(m)==1)
		{
			return &bra_bu[i];
			break;
		}
	};
	if(over_bu.buttondown(m)==1)
		return &over_bu;
	if(x_bu.buttondown(m)==1)
		return &x_bu;
};

//输出按下按钮的字符
void outbutton(button* ptr)//输出按钮字符
{
	ptr->outbutton();
}

//获得常函数按钮组成的数字,从数组的【i】到【j】全是数字
double getnumber(vector<button*> some_bu,int begin_num,int over_num)
{
	double sum=0;
	for(int i=begin_num;i<=over_num;i++)
	{
		sum+=some_bu[i]->getnumber()*pow(10,over_num-i);
	};
	return sum;
}

//对函数式解析做一个声明
function* express_button(vector<button*> some_bu);

//给我一个button数组与开始的序号读取紧接着的一个完整函数
function* getcom_fun(vector<button*>some_bu,int &begin_read)
{
	output<<"调用getcom_fun函数读取一个完整函数，读取起点为"<<begin_read<<endl;
	function* ptr;
	int length=static_cast<int>(some_bu.size());
 	switch (some_bu[begin_read]->bu_type)
	{
	   case FUNCTION:
		    switch(some_bu[begin_read]->getfunction_type())
			{
			case COM:
				switch (some_bu[begin_read]->getcom_fun_type())
				{
				case 1:
					output<<"读取第一个按钮为“x“，返回线性函数指针"<<endl;
					ptr=&linear_fun;
					begin_read+=1;
					break;
				case 0:
					int i=begin_read;
					while(some_bu[i]->getcom_fun_type()==0)
					{
						i++;
						if(i==length)
						{goto part2;};
					};
					part2:
					double nu=getnumber(some_bu,begin_read,i-1);
					constant_function n(getnumber(some_bu,begin_read,i-1));
					constant_out[several]=n;
					ptr=constant_out+several;
					output<<"读取第一个按钮代表常函数，最终返回常函数"<<nu<<endl;
					begin_read=i;
					break;
				};
				break;
			case INCOM:
				output<<"读取的第一个按钮代表该完整函数为复合函数"<<endl;
				if(some_bu[begin_read+1]->getbracket_type()==LEFT)
				{
					//获取该函数的参数括号中内容组成一个新的数组
					int i=1;//用来记录括号是否抵消
					int j=begin_read+2;//用来记录读取到了哪里
					while(i!=0)
					{
						switch(some_bu[j]->getbracket_type())
						{
						case LEFT:
							i++;
							break;
						case RIGHT:
							i--;
							break;
						case NO:
							break;
						};
						j++;
					};
					vector<button*> some_bu_part(j-begin_read-3);
					for(int i=0;i<j-begin_read-3;i++)
					{
						some_bu_part[i]=some_bu[begin_read+2+i];
					};
					output<<"该函数要复合的函数的按钮重新组成一个按钮数组进行解析，且该数组长度为"<<j-begin_read-3<<endl;
					//对这个数组进行解析
					function* f_in=express_button(some_bu_part);
					output<<"对括号内的函数解析完毕，回到复合函数的解析"<<endl;
					//构造相关复合函数并返回值
					sin_function sin_out1(f_in);
					sin_out[several]=sin_out1;
					cos_function cos_out1(f_in);
					cos_out[several]=cos_out1;
					tan_function tan_out1(f_in);
					tan_out[several]=tan_out1;
					misin_function misin_out1(f_in);
					misin_out[several]=misin_out1;
				    micos_function micos_out1(f_in);
					micos_out[several]=micos_out1;
					 mitan_function mitan_out1(f_in);
					mitan_out[several]=mitan_out1;
					 power_function power_out1(f_in);
					 power_out[several]=power_out1;
					 exp_function exp_out1(f_in);
					 exp_out[several]=exp_out1;
					 log_function log_out1(f_in);
					 log_out[several]=log_out1;
					switch(some_bu[begin_read]->getsequence())
					{
					case 0:
						abort();
					case 1:
						ptr=sin_out+several;
						output<<"该复合函数的外函数是sin"<<endl;
						break;
					case 2:
						ptr=cos_out+several;
						output<<"该复合函数的外函数是cos"<<endl;
						break;
					case 3:
						ptr=tan_out+several;
						output<<"该复合函数的外函数是tan"<<endl;
						break;
					case 4:
						ptr=misin_out+several;
						output<<"该复合函数的外函数是sin-1"<<endl;
						break;
					case 5:
						ptr=micos_out+several;
						output<<"该复合函数的外函数是cos-1"<<endl;
						break;
					case 6:
						ptr=mitan_out+several;
						output<<"该复合函数的外函数是tan-1"<<endl;
						break;
					case 7:
						ptr=power_out+several;
						output<<"该复合函数的外函数是x^"<<endl;
						break;
					case 8:
						ptr=exp_out+several;
						output<<"该复合函数的外函数是a^x"<<endl;
						break;
					case 9:
						ptr=log_out+several;
						output<<"该复合函数的外函数是loga x"<<endl;
						break;
					};
					begin_read=j;
					output<<"返回该复合函数"<<endl;
				}
				else abort();
			};
			break;
		case BRACKET:
			output<<"读取的第一个按钮为括号类按钮"<<endl;
			if(some_bu[begin_read]->getbracket_type()==LEFT)
			{
				//获取该函数的参数括号中内容组成一个新的数组
					int i=1;//记录括号抵消次数
					int j=begin_read+1;//读取的模块
					while(i!=0)
					{
						switch(some_bu[j]->getbracket_type())
						{
						case LEFT:
							i++;
							break;
						case RIGHT:
							i--;
							break;
						case NO:
							break;
						};
						j++;
					};
					vector<button*> some_bu_part(j-2-begin_read);
					for(int i=0;i<j-2-begin_read;i++)
					{
						some_bu_part[i]=some_bu[begin_read+1+i];
					};
					output<<"括号里的按钮重新组成一个按钮数组进行解析，且该数组长度为"<<j-begin_read-2<<endl;
					//对这个数组进行解析
					begin_read=j;
					function* f=express_button(some_bu_part);
					output<<"括号内的函数解析完毕,并将之返回"<<endl;
					ptr=f;
			}
			else abort();
			break;
		default:
			abort();
	};
	several++;
	output<<"getcom_fun函数执行完毕，并得到一个完整函数"<<endl;
	return ptr;
	};

//表达式解析
function* express_button(vector<button*> some_bu)
{
	//用来储存函数信息的指针
	function* ptr;
	//来记录读到了数组的哪个部分
	int begin_read=0;
	output<<"调用express_button函数进行表达式解析,解析的起点为"<<begin_read<<endl;
	//获得数组长度
	int length=static_cast<int>(some_bu.size());
	//获得了第一个函数块
	ptr=getcom_fun(some_bu,begin_read);
	
	//判断是否要继续解析
	output<<"判断是否之后还有函数要进行解析"<<endl;
	while(begin_read<length)
	{
		output<<"经过判断，后面还有函数需要解析"<<endl;
	RULES_TYPE rule1;//定义紧跟着的四则运算

	if(some_bu[begin_read]->bu_type==RULES)
	{
		rule1=some_bu[begin_read]->getrules_type();
		begin_read+=1;
	}
	else abort();
	output<<"检测到四则运算"<<rule1;

	//进入下一个函数模块的判断读取
	function* ptr_2;
	output<<"进入对下一个完整函数的获取"<<endl;
	ptr_2=getcom_fun(some_bu,begin_read);
	output<<"得到四则运算之后的函数指针"<<endl;
	//static定义之后不能两次初始化
	add_function ad(ptr,ptr_2);
	minus_function mi(ptr,ptr_2);
	multipy_function mu(ptr,ptr_2);
	divide_function di(ptr,ptr_2);
	add_out[several]=ad;
	minus_out[several]=mi;
	multipy_out[several]=mu;
	divide_out[several]=di;
	switch (rule1)
	{  case ADD:
	        ptr=add_out+several;
			break;
	   case MINUS:
		   ptr=minus_out+several;
			break;
	   case MULTIPY:
		   ptr=multipy_out+several;
		   break;
	   case DIVIDE:
		   ptr=divide_out+several;
		   break;
	};
	output<<"这两个函数的四则运算执行完毕，并返回相应函数"<<endl;
	};//while语句结束
	output<<"经过判断，后面没有函数进行解析了，表达式解析完成"<<endl;
	return ptr;
	};



int main()
{
	iniwindow();
	MOUSEMSG m;
	int bu_num=-1;//按键个数除了over键外
	function* last_function;
	button* all_bu_house[500];
	while(ifover==0)
	{
		m=GetMouseMsg();
		switch(m.uMsg)
		{
		case WM_LBUTTONDOWN:
			button* bu=wheredown(m);
			outbutton(bu);
			//连续储存button信息到暂时的数组
			all_bu_house[bu_num+1]=bu;
			bu_num+=1;
			break;
		}
	};
	//log
	output<<"输入结束"<<endl;
	//精简出函数部分到另一个数组
	vector<button*> all_bu(bu_num);
	for(int i=0;i<bu_num;i++)
	{
		all_bu[i]=all_bu_house[i];
	};
	//log
	output<<"得到一个按钮数组，长度为"<<bu_num<<endl;
	//开始对all_bu数组的信息进行处理
     last_function=express_button(all_bu);
	 closegraph();
	 double x;
	 while(true)
	 {
	cout<<"x=";
	cin>>x;
	cout<<"f(x)="<<last_function->getf(x)<<endl;
	 };
	return 0;
};

