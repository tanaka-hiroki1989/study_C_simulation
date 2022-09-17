/**********************************************/
/*　　　　      trape.cプログラム             */
/**********************************************/

/* 数値積分プログラム                         */
/* 台形公式を使って数値積分を行います         */
/*　使い方    $./trape (区間分割数N）　 　    */
/*  区間は0～1に固定してあります              */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*関数のプロトタイプの宣言*/
double fx(double x) ;/*積分対象の関数*/

/*********************/
/*     main()関数    */
/*********************/
int main(int argc,char *argv[])
{
 double h  ;/*刻み幅h*/
 double integral ;/*積分値*/
 int n ;  /*区間分割数N*/
 int i ;  /*繰り返し制御の変数*/

 /*分割数Nの初期化*/
 if(argc<2){/*区間分割数Nの指定がない*/
  fprintf(stderr,"使い方　trape (区間分割数N）\n") ;
  exit(1) ;
 }
 /*刻み幅hの計算*/
 if((n=atoi(argv[1]))<=0){
  fprintf(stderr,"区間分割数Nが不正です(%d)\n",n) ;
  exit(1) ;
 } 
 h=1.0/n ;

 /*積分値の計算*/
 integral=fx(0.0)/2.0 ;
 for(i=1;i<n;++i){
  integral+=fx((double)i/n) ;
 }
 integral+=fx(1.0)/2.0 ;
 integral*=h ;

 /*結果の出力*/
 printf("積分値I　%.9lf    4I  %.9lf\n",integral,integral*4.0) ;

 return 0 ;
}

/*************************/
/*   fx()関数            */
/*   積分対象の関数      */
/*************************/
double fx(double x)
{
 return sqrt(1.0-x*x) ;
}
