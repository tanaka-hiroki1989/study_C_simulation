/**********************************************/
/*　　　　      ri.cプログラム                */
/**********************************************/

/* 乱数による数値積分プログラム               */
/* 擬似乱数を使って数値積分を行います         */
/*　使い方    $./ri (試行回数n）　      　    */
/*  区間は0～1に固定してあります              */

#include <stdio.h>
#include <stdlib.h>

#define SEED  RAND_MAX-1  /*乱数の種*/
#define R 10 /*実験の繰り返し回数*/

/*関数のプロトタイプの宣言*/
double frand(void) ;/*実数乱数*/

/*********************/
/*     main()関数    */
/*********************/
int main(int argc,char *argv[])
{
 int integral ;/*積分値*/
 int n ;  /*試行回数n*/
 int i,r ;  /*繰り返し制御の変数*/
 double x,y ;/*点の座標*/

 /*試行回数nの初期化*/
 if(argc<2){/*試行回数nの指定がない*/
  fprintf(stderr,"使い方　ri (試行回数n）\n") ;
  exit(1) ;
 }
 if((n=atoi(argv[1]))<=0){
  fprintf(stderr,"試行回数nが不正です(%d)\n",n) ;
  exit(1) ;
 } 

 /*乱数の初期化*/
 srand(SEED) ;

 /*積分実験の繰り返し*/
 for(r=0;r<R;++r){
  integral=0 ;
  /*積分値の計算*/
  for(i=0;i<n;++i){
   x=frand() ; y=frand() ;
   if((x*x+y*y)<=1)/*円の内部*/
    ++integral ;
  }
  /*結果の出力*/
  printf("積分値I　%.9lf    4I  %.9lf\n"
        ,(double)integral/n,(double)integral/n*4.0) ;
 }
 return 0 ;
}

/*************************/
/*   frand()関数         */
/*   実数乱数            */
/*************************/
double frand(void)
{
 return (double)rand()/RAND_MAX ;
}
