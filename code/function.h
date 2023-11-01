#ifndef FUNCTION_H
#define FUNCTION_H

#include<iostream>
#include<cmath>
#include<graphics.h>
#include<conio.h>
#include<string.h>

using namespace std;

//独立函数的抽象类
class function
{
protected:
	double x1;
	double x2;//函数的定义域
public:
	function(double a,double b);//默认构造函数
	double getx1()const
	{return x1;};
	double getx2() const
	{return x2;};
	virtual double getf(double x)=0;//获得函数值 
};

//加减乘除得到的函数类
class add_function:public function
{
protected:
	function* ptrf1;
	function* ptrf2;
public:
	add_function(function* ptr1=NULL,function* ptr2=NULL,double a=1,double b=2):function(a,b),ptrf1(ptr1),ptrf2(ptr2){};
	virtual double getf(double x);
};
class minus_function:public function
{
protected:
	function* ptrf1;
	function* ptrf2;
public:
	minus_function(function* ptr1=NULL,function* ptr2=NULL,double a=1,double b=2):function(a,b),ptrf1(ptr1),ptrf2(ptr2){};
	virtual double getf(double x);
};
class multipy_function:public function
{
protected:
	function* ptrf1;
	function* ptrf2;
public:
	multipy_function(function* ptr1=NULL,function* ptr2=NULL,double a=1,double b=2):function(a,b),ptrf1(ptr1),ptrf2(ptr2){};
	virtual double getf(double x);
};
class divide_function:public function
{
protected:
	function* ptrf1;
	function* ptrf2;
public:
	divide_function(function* ptr1=NULL,function* ptr2=NULL,double a=1,double b=2):function(a,b),ptrf1(ptr1),ptrf2(ptr2){};
	virtual double getf(double x);
};



//独立函数类中的常函数
class constant_function:public function
{
private:
	double num;
public:
	constant_function(double number=0,double a=1,double b=2):function(a,b),num(number){};
	virtual double getf(double x);
};

//独立函数类的一次函数
class linear_function:public function
{
public:
	linear_function(double a=1,double b=2):function(a,b){};
	virtual double getf(double x);
};


//非独立函数的复合函数的抽象类
class complex_function:public function
{
protected:
	function* ptr;
public:
	complex_function(function* ptr1,double a,double b):function(a,b),ptr(ptr1){};
	virtual double getf(double x)=0;
};

//复合函数的各种函数子类
class sin_function:public complex_function
{
public:
	sin_function(function* ptr1=NULL,double a=1,double b=2):complex_function(ptr1,a,b){};
	virtual double getf(double x);
};

class cos_function:public complex_function
{
public:
	cos_function(function* ptr1=NULL,double a=1,double b=2):complex_function(ptr1,a,b){};
	virtual double getf(double x);
};

class tan_function:public complex_function
{
public:
	tan_function(function* ptr1=NULL,double a=1,double b=2):complex_function(ptr1,a,b){};
	virtual double getf(double x);
};
class misin_function:public complex_function
{
public:
	misin_function(function* ptr1=NULL,double a=1,double b=2):complex_function(ptr1,a,b){};
	virtual double getf(double x);
};
class micos_function:public complex_function
{
public:
	micos_function(function* ptr1=NULL,double a=1,double b=2):complex_function(ptr1,a,b){};
	virtual double getf(double x);
};
class mitan_function:public complex_function
{
public:
	mitan_function(function* ptr1=NULL,double a=1,double b=2):complex_function(ptr1,a,b){};
	virtual double getf(double x);
};

class power_function:public complex_function
{
public:
	power_function(function* ptr1=NULL,double a=1,double b=2):complex_function(ptr1,a,b){};
	virtual double getf(double x);
};

class exp_function:public complex_function
{
public:
	exp_function(function* ptr1=NULL,double a=1,double b=2):complex_function(ptr1,a,b){};
	virtual double getf(double x);
};

class log_function:public complex_function
{
public:
	log_function(function* ptr1=NULL,double a=1,double b=2):complex_function(ptr1,a,b){};
	virtual double getf(double x);
};


#endif