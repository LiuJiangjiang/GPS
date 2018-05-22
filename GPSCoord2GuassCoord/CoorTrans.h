#ifndef   _COORTRANS_H_INCLUDED 
#define   _COORTRANS_H_INCLUDED 
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#define M_PI 3.141592654


double   Dms2Rad(double   Dms); 
double   Rad2Dms(double   Rad); 

class   PrjPoint 
{ 
	public: 
  		double   L0;        //   中央子午线经度 
  		double   B,   L;    //   大地坐标 
  		double   x,   y;    //   高斯投影平面坐标 
	public: 
  		bool   BL2xy(); 
  		bool   xy2BL(); 

	protected: 
  		double   a,   f,   e2,   e12;     //   基本椭球参数 
  		double   A1,   A2,   A3,   A4;    //   用于计算X的椭球参数 

	public: 
  		bool   SetL0(double   dL0); 
  		bool   SetBL(double   dB,   double   dL); 
  		bool   GetBL(double   *dB,  double   *dL); 
  		bool   Setxy(double   dx,   double   dy); 
  		bool   Getxy(double   *dx,  double   *dy); 
}; 

class   PrjPoint_Krasovsky   :   virtual   public   PrjPoint   //类的继承，声明基类是PrjPoint，虚基类 
{ 
	public: 
  		PrjPoint_Krasovsky();   //定义构造函数，用来初始化。(函数名和类名相同) 
  		~PrjPoint_Krasovsky(); 
}; 

class   PrjPoint_IUGG1975   :   virtual   public   PrjPoint 
{ 
	public: 
  		PrjPoint_IUGG1975(); 
  		~PrjPoint_IUGG1975(); 
}; 

double   Dms2Rad(double   Dms) 
{ 
	double   Degree,   Miniute; 
	double   Second; 
	int   Sign; 
	double   Rad; 
	if(Dms   >=   0) 
		Sign   =   1; 
	else 
		Sign   =   -1; 
	Dms     =   fabs(Dms); 
	Degree  =   floor(Dms); 
	Miniute =   floor(fmod(Dms   *   100.0,   100.0)); 
	Second  =   fmod(Dms   *   10000.0,   100.0); 
	Rad     =   Sign   *   (Degree   +   Miniute   /   60.0   +   Second   /   3600.0)   *   M_PI   /   180.0; 
	return   Rad; 
} 
double   Rad2Dms(double   Rad) 
{ 
	double   Degree,   Miniute; 
	double   Second; 
	int   Sign; 
	double   Dms; 
	if(Rad   >=   0) 
	  Sign   =   1; 
	else 
	  Sign   =   -1; 
	Rad     =   fabs(Rad   *   180.0   /   M_PI); 
	Degree  =   floor(Rad); 
	Miniute =   floor(fmod(Rad   *   60.0,   60.0)); 
	Second  =   fmod(Rad   *   3600.0,   60.0); 
	Dms     =   Sign   *   (Degree   +   Miniute   /   100.0   +   Second   /   10000.0); 
	return   Dms; 
} 
/////////////////////////////////////////////////// 
//   Definition   of   PrjPoint 
/////////////////////////////////////////////////// 
bool   PrjPoint::BL2xy() 
{ 
  	double   X,   N,   t,   t2,   m,   m2,   ng2; 
  	double   sinB,   cosB; 
  	X     =  A1   *   B   *   180.0   /   M_PI   +   A2   *   sin(2   *   B)   +   A3   *   sin(4   *   B)   +   A4   *   sin(6   *   B); 
  	sinB  =  sin(B); 
  	cosB  =  cos(B); 
  	t     =  tan(B); 
  	t2    =  t   *   t; 
  	N     =  a   /   sqrt(1   -   e2   *   sinB   *   sinB); 
  	m     =  cosB   *   (L   -   L0); 
  	m2    =  m   *   m; 
  	ng2   =  cosB   *   cosB   *   e2   /   (1   -   e2); 
  	//x,y的计算公式见孔祥元等主编武汉大学出版社2002年出版的《控制测量学》的第72页 
  	//书的的括号有问题，   (   和   [   应该交换 
  	x   =   X   +   N   *   t   *   ((0.5   +   ((5   -   t2   +   9   *   ng2   +   4   *   ng2   *   ng2)   /   24.0   +   (61   -     
			58   *   t2   +   t2   *   t2)   *   m2   /   720.0)   *   m2)   *   m2); 
  	y   =   N   *   m   *   (   1   +   m2   *   (   (1   -   t2   +   ng2)   /   6.0   +   m2   *   (   5   -   18   *   t2   +   t2   *   t2 
			+   14   *   ng2   -   58   *   ng2   *   t2   )   /   120.0)); 
  	y   +=   500000; 
	return   true; 
} 
bool   PrjPoint::xy2BL() 
{ 
  	double   sinB,   cosB,   t,   t2,   N   ,ng2,   V,   yN; 
  	double   preB0,   B0; 
  	double   eta; 
  	y   -=   500000; 
  	B0   =   x   /   A1; 
  	do 
  	{ 
		preB0 =   B0; 
		B0    =   B0   *   M_PI   /   180.0; 
		B0    =   (x   -   (A2   *   sin(2   *   B0)   +   A3   *   sin(4   *   B0)   +   A4   *   sin(6   *   B0)))   /   A1; 
		eta   =   fabs(B0   -   preB0); 
  	}while(eta   >   1e-14); 

  	B0    =   B0   *   M_PI   /   180.0; 
  	B     =   Rad2Dms(B0); 
  	sinB  =   sin(B0); 
  	cosB  =   cos(B0); 
  	t     =   tan(B0); 
  	t2    =   t   *   t; 
  	N     =   a   /   sqrt(1   -   e2   *   sinB   *   sinB); 
  	ng2   =   cosB   *   cosB   *   e2   /   (1   -   e2); 
  	V     =   sqrt(1   +   ng2); 
  	yN    =   y   /   N; 
  	B   =   B0   -   (yN   *   yN   -   (5   +   3   *   t2   +   ng2   -   9   *   ng2   *   t2)   *   yN   *   yN   *   yN   *   yN   / 
			12.0   +   (61   +   90   *   t2   +   45   *   t2   *   t2)   *   yN   *   yN   *   yN   *   yN   *   yN   *   yN   /   360.0) 
			*   V   *   V   *   t   /   2; 
  	L   =   L0   +   (yN   -   (1   +   2   *   t2   +   ng2)   *   yN   *   yN   *   yN   /   6.0   +   (5   +   28   *   t2   +   24 
			*   t2   *   t2   +   6   *   ng2   +   8   *   ng2   *   t2)   *   yN   *   yN   *   yN   *   yN   *   yN   /   120.0)   /   cosB; 
	return   true; 
} 
bool   PrjPoint::SetL0(double   dL0) 
{ 
  	L0   =   Dms2Rad(dL0); 
  	L0 = dL0/180*M_PI;
	return   true; 
} 
bool   PrjPoint::SetBL(double   dB,   double   dL) 
{ 
  	B   =   Dms2Rad(dB); 
  	L   =   Dms2Rad(dL); 
  	B = dB/180*M_PI;
  	L = dL/180*M_PI;
  	BL2xy(); 
	return   true; 
} 

bool   PrjPoint::GetBL(double   *dB,   double   *dL) 
{ 
  	*dB   =   Rad2Dms(B); 
  	*dL   =   Rad2Dms(L); 
  	return   true; 
} 
bool   PrjPoint::Setxy(double   dx,   double   dy) 
{ 
  	x   =   dx; 
  	y   =   dy; 
  	xy2BL(); 
  	return   true; 
} 
bool   PrjPoint::Getxy(double   *dx,   double   *dy) 
{ 
  	*dx   =   x; 
  	*dy   =   y; 
	return   true; 
} 
/////////////////////////////////////////////////// 
//   Definition   of   PrjPoint_IUGG1975  WGS84
/////////////////////////////////////////////////// 
PrjPoint_IUGG1975::PrjPoint_IUGG1975()   //在类外定义构造成员函数，要加上类名和域限定符   :: 
{ 
  	a     =   6378140; 
  	f     =   298.257; 
  	e2    =   1   -   ((f   -   1)   /   f)   *   ((f   -   1)   /   f); 
  	e12   =   (f   /   (f   -   1))   *   (f   /   (f   -   1))   -   1; 
  	A1    =   111133.0047;     //这几个A是什么意思？ 
  	A2    =   -16038.5282; 
  	A3    =   16.8326; 
  	A4    =   -0.0220; 
} 
PrjPoint_IUGG1975::~PrjPoint_IUGG1975()       //析构函数，释放构造函数占用的内存 
{ 
} 
/////////////////////////////////////////////////// 
//   Definition   of   PrjPoint_Krasovsky  beijing 54 
/////////////////////////////////////////////////// 
PrjPoint_Krasovsky::PrjPoint_Krasovsky() 
{ 
  	a     =   6378245; 
  	f     =   298.3; 
  	e2    =   1   -   ((f   -   1)   /   f)   *   ((f   -   1)   /   f); 
  	e12   =   (f   /   (f   -   1))   *   (f   /   (f   -   1))   -   1; 
  	A1    =   111134.8611; 
  	A2    =   -16036.4803; 
  	A3    =   16.8281; 
  	A4    =   -0.0220; 
} 
PrjPoint_Krasovsky::~PrjPoint_Krasovsky() 
{ 
} 

#endif


