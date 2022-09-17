/**********************************************/
/*　　　　 freefall.cプログラム               */
/**********************************************/

/*    自由落下のシミュレーション　　    　    */
/*  自由落下の運動法方程式を数値的に解きます  */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define BUFSIZE 256 /*入力バッファ用配列の長さ*/
#define DT 0.01 /*時刻の刻み幅*/
#define G  9.80665 /*重力加速度*/

/*関数のプロトタイプの宣言*/
int getdouble(double *x) ;/*実数の読み込み */

/*********************/
/*     main()関数    */
/*********************/
int main()
{
 double v,x ; /*速度と位置*/
 double t=0  ;/*時刻*/
 double h=DT ;/*時刻の刻み幅*/


 /*係数の入力*/
 fprintf(stderr,"初速度v0を入力してください\n") ;
 if(getdouble(&v)==EOF) exit(1) ;
 fprintf(stderr,"初期高度x0を入力してください\n") ;
 if(getdouble(&x)==EOF) exit(1) ;

 printf("%f\t%f\t%f\n",t,x,v) ;/*現在時刻と現在の位置*/

 /*自由落下の計算*/
 while(x>0){/*地面に達するまで計算*/
  t+=h ;/*時刻の更新*/
  v+=G*h ;/*速度の計算*/
  x-=v*h ;/*位置の計算*/
  printf("%f\t%f\t%f\n",t,x,v) ;/*現在時刻と現在の位置*/
 }

 /*結果の判定*/
 
 return 0 ;
}

/*************************/
/*    getdouble()関数    */
/*    実数の読み込み     */
/*************************/
int getdouble(double *x)
{
 char linebuf[BUFSIZE] ; /*1行入力用の文字配列*/
 int result=0 ;/*入力結果のコード*/

 if(fgets(linebuf,BUFSIZE,stdin)!=NULL){/*行の読み取りが可能*/
  if(sscanf(linebuf,"%lf",x)<=0)/*変換できなければ*/
    result=EOF ;/*エラー*/
 } else {/*行が読めない*/
  result=EOF ;/*ファイルの終わり*/
 }
 return result ;
}
