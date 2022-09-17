/**********************************************/
/*　　　　   laplace.cプログラム              */
/**********************************************/

/* 反復法によるラプラス方程式の解法プログラム */
/* 標準入力からuijの初期値を読み込み計算します*/

#include <stdio.h>
#include <stdlib.h>
#define LIMIT 10000 /*反復回数の上限*/
#define N 101 /*x軸方向の分割数*/
#define M 101 /*y軸方向の分割数*/
#define BUFSIZE 256 /*入力バッファ用配列の長さ*/
#define ERROR -1 /*入力時のエラーコード*/

/*関数のプロトタイプの宣言*/
int getuij(double u[][M]) ;/*行列の初期値の読み込み */
void putuij(double u[][M]) ;/*行列の値の出力 */
void iteration(double u[][M]) ;/*1回分の反復計算*/
int getdouble(double *x) ;/*実数の読み込み */

/*********************/
/*     main()関数    */
/*********************/
int main()
{
 int i  ;/*反復回数のカウンタ*/
 double u[N][M] ;/*uij*/

 /*行列の初期値の読み込み*/
 if(getuij(u)!=0){/*読み込み失敗*/
  fprintf(stderr,"初期値の読み込み失敗\n") ;
  exit(1); /*異常終了*/
 }

 /*反復法の計算*/
 for(i=0;i<LIMIT;++i){
  iteration(u) ;
  if((i%(LIMIT/10))==0){/*途中経過を(LIMIT/10)回出力*/
   printf("i=%d\n",i) ;
   putuij(u) ;
   printf("\n") ;
  }
 }

 /*結果の出力*/
 putuij(u) ;

 return 0 ;
}

/*************************/
/*   iteration関数       */
/*  1回分の反復計算      */
/*************************/
void iteration(double u[][M])
{
 double u_next[N][M] ;/*次ステップのuij*/
 int i,j ;

 /*次ステップの値を計算*/
 for(i=1;i<N-1;++i)
  for(j=1;j<M-1;++j)
   u_next[i][j]
    =(u[i][j-1]+u[i-1][j]+u[i+1][j]+u[i][j+1])/4 ;
 /*uijの更新*/
 for(i=1;i<N-1;++i)
  for(j=1;j<M-1;++j)
   u[i][j]=u_next[i][j] ;
}

/*************************/
/*    putuij()関数       */
/* 行列の値の出力        */
/*************************/
void putuij(double u[][M])
{
 int i,j ;

 for(i=0;i<N;++i){
  for(j=0;j<M;++j)
   printf("%lf ",u[i][j]) ;
  printf("\n") ;
 }
}

/*************************/
/*    getuij()関数       */
/* 行列の初期値の読み込み*/
/*************************/
int getuij(double u[][M])
{
 int i,j ;

 for(i=0;i<N;++i)
  for(j=0;j<M;++j){
   if(getdouble(&u[i][j])==EOF){/*読み込みエラー*/
    fprintf(stderr,"%d %d",i,j) ;
    return ERROR ;
   }
  }
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
