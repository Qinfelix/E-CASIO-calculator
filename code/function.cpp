#include<iostream>
#include<cmath>
#include<graphics.h>
#include<conio.h>
#include<string.h>
#include"function.h"
using namespace std;


function::function(double a,double b)
{
	if(a<b)
	{x1=a;x2=b;}
}

//定义加减乘除得到的函数
double add_function::getf(double x)
{
	return (ptrf1->getf(x)+ptrf2->getf(x));
};

double minus_function::getf(double x)
{
	return (ptrf1->getf(x)-ptrf2->getf(x));
};
double multipy_function::getf(double x)
{
	return (ptrf1->getf(x)*ptrf2->getf(x));
};
double divide_function::getf(double x)
{
	return (ptrf1->getf(x)/ptrf2->getf(x));
};



//常函数的返回函数值函数
double constant_function::getf(double x)
{
	return num;
}

double linear_function::getf(double x)
{
	return x;
}

double sin_function::getf(double x)
{
	return sin(ptr->getf(x));
}

double cos_function::getf(double x)
{
	return cos(ptr->getf(x));
}
double tan_function::getf(double x)
{
	return tan(ptr->getf(x));
}
double misin_function::getf(double x)
{
	return asin(ptr->getf(x));
}
double micos_function::getf(double x)
{
	return acos(ptr->getf(x));
}
double mitan_function::getf(double x)
{
	return atan(ptr->getf(x));
}
double power_function::getf(double x)
{
	return pow(x,ptr->getf(x));
}
double exp_function::getf(double x)
{
	return pow(ptr->getf(x),x);
}
double log_function::getf(double x)
{
	return (log(x)/log(ptr->getf(x)));
}





