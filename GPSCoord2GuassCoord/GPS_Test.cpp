#include "math.h"
#include "CoorTrans.h"
#include <iostream>
#include <stdio.h>

using   namespace   std; 

int   main(int   argc,   char*   argv[]) 
{ 
  double   MyL0  =   108;			//中央子午线 
  double   MyB   =   33.44556666;   //33   du   44   fen   55.6666   miao 
  double   MyL   =   109.22334444;  //3度带，109   d   22   m   33.4444   s 
  
  PrjPoint_Krasovsky   MyPrj; 
  MyPrj.SetL0(MyL0); 
  MyPrj.SetBL(MyB,   MyL); 
  double   OutMyX;               //结果应该大致是:3736714.783,   627497.303 
  double   OutMyY; 
  OutMyX   =   MyPrj.x;          //正算结果:   北坐标x 
  OutMyY   =   MyPrj.y;          //结果：东坐标y 

  printf("x: %f\n", OutMyX);
  printf("y: %f\n", OutMyY);
  
  //////////////////反算//////////////////////////////////////// 
  double   InputMyX   =   3736714.783;    //如果是独立计算，应该给出中央子午线L0 
  double   InputMyY   =   627497.303; 
  MyPrj.Setxy(InputMyX,   InputMyY); 
  MyPrj.GetBL(&MyPrj.B,   &MyPrj.L);   //把计算出的BL的弧度值换算为dms形式 
  double   OutputMyB; 
  double   OutputMyL; 
  OutputMyB   =   MyPrj.B;     //反算结果：B 
  OutputMyL   =   MyPrj.L;     //反算结果：L 

  printf("B: %f\n", OutputMyB);
  printf("L: %f\n", OutputMyL);

  return 0;
} 


  
