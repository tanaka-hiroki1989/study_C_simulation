/**********************************************/
/*　　　　      qe.cプログラム                */
/**********************************************/

/*暗黙の型変換に関する例題プログラム　　    　*/
/*２次方程式を解公式を使って解きます          */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define BUFSIZE 256 /*入力バッファ用配列の長さ*/

/*関数のプロトタイプの宣言*/
int getdouble(double *x) ;/*実数の読み込み */

int main()
{
 double a,b,c ; /*２次方程式の係数*/
 double d ;/*判別式の値*/

 /*係数の入力*/
 printf("係数aを入力してください\n") ;
 if(getdouble(&a)==EOF) exit(1) ;
 if(a==0) exit(1) ;/*２次方程式ではない*/
 printf("係数bを入力してください\n") ;
 if(getdouble(&b)==EOF) exit(1) ;
 printf("係数cを入力してください\n") ;
 if(getdouble(&c)==EOF) exit(1) ;

 /*判別式の計算*/
 d=b*b-4*a*c ;
 /*解の公式の計算*/
 if(d==0)/*重解*/
  printf("x=%lf\n",-b/2/a) ;
 else if(d<0)/*虚解*/
  printf("x=%lf+%lfi,%lf-%lfi\n",-b/2/a,sqrt(-d)/2/a,-b/2/a,sqrt(-d)/2/a) ;
 else /*実解*/
  printf("x=%lf,%lf\n",-b/2/a+sqrt(d)/2/a,-b/2/a-sqrt(d)/2/a) ;

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
