/**********************************************/
/*　　　　   bignum.cプログラム               */
/**********************************************/

/*多倍長整数の例題プログラム        　　    　*/
/*３の累乗を計算します                        */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 8 /*解を格納する配列の要素数*/
#define ULIMIT 99 /*累乗の繰り返し回数*/
#define RESLIMIT 10000000UL /*7桁の符号なし整数の最大値+1*/

/*関数のプロトタイプの宣言*/
void printresult(unsigned long result[]) ;/*結果の出力*/
void power3(unsigned long result[]) ;/*３を掛ける*/

int main()
{
 unsigned long result[N]={0} ; /*計算結果*/
 int i ;/*繰り返しのカウンタ*/

 /*初期値の設定*/
 result[0]=1 ;/*3の0乗*/

 /*累乗の計算*/
 for(i=1;i<=ULIMIT;++i){
  power3(result) ;/*３を掛ける*/
  printf("n=%3d: ",i) ;
  printresult(result) ;/*結果の出力*/
 }

 return 0 ;
}

/*************************/
/*   printresul()関数    */
/*    結果の出力         */
/*************************/
void printresult(unsigned long result[])
{
 int j ;/*繰り返しのカウンタ*/
 
 for(j=N-1;j>=0;--j){
  if(result[j]==0) printf("        ") ;/*空白を8桁分出力*/
  else  printf("%8lu",result[j]) ;
 }
 printf("\n") ;
}

/*************************/
/*   power3()関数        */
/*   ３を掛ける          */
/*************************/
void power3(unsigned long result[])
{
 int i ;/*繰り返しのカウンタ*/
 unsigned long midres[N]={0} ;/*３倍の計算結果*/

 for(i=0;i<N;++i){
  midres[i]+=result[i]*3 ;
  if(midres[i]>=RESLIMIT){/*桁あふれ*/
   if(i!=N-1){midres[i+1]+=midres[i]/RESLIMIT ;}
   else{/*多倍長整数が桁あふれ*/
    fprintf(stderr,"多倍長整数が桁あふれしました\n") ;
    exit(1) ;/*異常終了*/
   }
   midres[i]=midres[i]%RESLIMIT ;
  }
 }
 /*結果のresult[]への格納*/
 for(i=0;i<N;++i)
  result[i]=midres[i] ;
}


