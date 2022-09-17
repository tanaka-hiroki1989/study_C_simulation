/**********************************************/
/*　　　　   randwalk.cプログラム             */
/**********************************************/

/* ランダムウォークシミュレーション           */
/* 擬似乱数を使って2次元平面を酔歩します      */
/*使い方  $./randwalk (試行回数n）(乱数の種)  */


#include <stdio.h>
#include <stdlib.h>

/*関数のプロトタイプの宣言*/
double frand(void) ;/*実数乱数*/

/*********************/
/*     main()関数    */
/*********************/
int main(int argc,char *argv[])
{
 int n ;  /*試行回数n*/
 int i ;  /*繰り返し制御の変数*/
 int seed ;/*乱数の種*/
 double x=0,y=0 ;/*点の座標*/


 /*試行回数nの初期化*/
 if(argc<3){/*引数の指定がない*/
  fprintf(stderr,"使い方　randwalk (試行回数n）(乱数の種)\n") ;
  exit(1) ;
 }
 if((n=atoi(argv[1]))<=0){
  fprintf(stderr,"試行回数nが不正です(%d)\n",n) ;
  exit(1) ;
 } 
 if((seed=atoi(argv[2]))<=0){
  fprintf(stderr,"乱数の種が不正です(%d)\n",seed) ;
  exit(1) ;
 } 

 /*乱数の初期化*/
 srand(seed) ;
 printf("%lf %lf\n",x,y) ;

 /*ランダムウォーク*/
 for(i=0;i<n;++i){
   x+=(frand()-0.5)*2 ;
   y+=(frand()-0.5)*2 ;

  /*結果の出力*/
  printf("%lf %lf\n",x,y) ;
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
