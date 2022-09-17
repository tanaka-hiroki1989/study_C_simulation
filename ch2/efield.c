/**********************************************/
/*　　　　   efield.cプログラム               */
/**********************************************/

/*    2次元運動のシミュレーション　　    　   */
/*  電界中の荷電粒子のシミュレーションです    */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#define DT 0.001 /*時刻の刻み幅*/
#define TIMELIMIT 20.0 /*シミュレーション打ち切り時刻*/
#define R 0.1 /*距離rの最低値*/
#define BUFSIZE 256 /*入力バッファ用配列の長さ*/
#define N 256 /*配置できる電荷の数の最大値*/

/*座標値（2次元ベクトル)の表現*/
struct coordinate {
 double x ;/*x座標*/
 double y ;/*y座標*/
} ;

/*電荷*/
struct charge {
 struct coordinate qxy ;/*電荷の位置*/
 double q ;/*電荷*/
} ;

/*関数のプロトタイプの宣言*/
int getdouble(double *x) ;/*実数の読み込み */
int inputq(struct charge qi[]) ;/*電荷の入力*/

/*********************/
/*     main()関数    */
/*********************/
int main()
{
 struct coordinate v,x ; /*質点の速度と位置*/
 struct charge qi[N] ; /*電荷qi*/
 int nofq ;/*電荷の個数*/
 double t=0  ;/*時刻*/
 double h=DT ;/*時刻の刻み幅*/
 double rx,ry,r,rmin ;/*電荷と質点の距離*/
 int i ;
 
 /*係数の入力*/
 fprintf(stderr,"初速度v0xを入力してください\n") ;
 if(getdouble(&v.x)==EOF) exit(1) ;
 fprintf(stderr,"初速度v0yを入力してください\n") ;
 if(getdouble(&v.y)==EOF) exit(1) ;
 fprintf(stderr,"初期位置x.xを入力してください\n") ;
 if(getdouble(&x.x)==EOF) exit(1) ;
 fprintf(stderr,"初期位置x.yを入力してください\n") ;
 if(getdouble(&x.y)==EOF) exit(1) ;
 nofq=inputq(qi) ;/*電荷の入力*/

 printf("%f\t%f\t%f\t%f\t%f\n",t,x.x,x.y,v.x,v.y) ;/*現在時刻と現在の位置*/

 /*2次元運動の計算*/
 while(t<=TIMELIMIT){/*打ち切り時間まで計算*/
  t+=h ;/*時刻の更新*/
  rmin=DBL_MAX ;/*距離の最小値を初期化*/
  for(i=0;i<nofq;++i){
   rx=qi[i].qxy.x-x.x ;/*距離rxの計算*/
   ry=qi[i].qxy.y-x.y ;/*距離ryの計算*/
   r=sqrt(rx*rx+ry*ry) ;/*距離rの計算*/
   if(r<rmin) rmin=r ;/*距離の最小値を更新*/ 
   v.x+=(rx/r/r/r*qi[i].q)*h ;/*速度vxの計算*/
   v.y+=(ry/r/r/r*qi[i].q)*h ;/*速度vyの計算*/
  }
  x.x+=v.x*h ;/*位置xxの計算*/
  x.y+=v.y*h ;/*位置xyの計算*/
  printf("%f\t%f\t%f\t%f\t%f\n",t,x.x,x.y,v.x,v.y) ;/*現在時刻と現在の位置*/
  if(rmin<R) break ;/*電荷に非常に近づいたら終了*/
 }

 
 return 0 ;
}

/*************************/
/*      inputq()関数    */
/*       電荷の入力      */
/*************************/
int inputq(struct charge qi[])
{
 int i ;

 for(i=0;i<N;++i){
  fprintf(stderr,"電荷%d\n",i) ;
  fprintf(stderr,"電荷の配置場所qxy.xを入力してください\n") ;
  if(getdouble(&qi[i].qxy.x)==EOF) break ;
  fprintf(stderr,"電荷の配置場所qxy.yを入力してください\n") ;
  if(getdouble(&qi[i].qxy.y)==EOF) break ;
  fprintf(stderr,"電荷の値qを入力してください\n") ;
  if(getdouble(&qi[i].q)==EOF) break ;
 }
 return i ;
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
