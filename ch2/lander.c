/**********************************************/
/*　　　　   lander.cプログラム               */
/**********************************************/

/*    落下運動のシミュレーション　　    　    */
/*  逆噴射をする，着陸船のシミュレーションです*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define BUFSIZE 256 /*入力バッファ用配列の長さ*/
#define DT 0.001 /*時刻の刻み幅*/
#define F 1.5 /*逆噴射の加速度を決定する係数*/
#define G  9.80665 /*重力加速度*/

/*関数のプロトタイプの宣言*/
int getdouble(double *x) ;/*実数の読み込み */
double retrofire(double t,double tf) ;/*逆噴射の制御*/

/*********************/
/*     main()関数    */
/*********************/
int main()
{
 double v,x ; /*速度と位置*/
 double x0 ; /*初期高度位置*/
 double t=0  ;/*時刻*/
 double h=DT ;/*時刻の刻み幅*/
 double tf=0  ;/*逆噴射開始時刻*/


 /*係数の入力*/
 fprintf(stderr,"初速度v0を入力してください\n") ;
 if(getdouble(&v)==EOF) exit(1) ;
 fprintf(stderr,"初期高度x0を入力してください\n") ;
 if(getdouble(&x0)==EOF) exit(1) ;
 fprintf(stderr,"逆噴射開始時刻tfを入力してください\n") ;
 if(getdouble(&tf)==EOF) exit(1) ;

 x=x0 ;/*初期高度の設定*/
 printf("%f\t%f\t%f\n",t,x,v) ;/*現在時刻と現在の位置*/

 /*落下の計算*/
 while((x>0)&&(x<=x0)){/*地面に達するか初期高度より高くなるまで計算*/
  t+=h ;/*時刻の更新*/
  v+=(G+retrofire(t,tf))*h ;/*速度の計算*/
  x-=v*h ;/*位置の計算*/
  printf("%f\t%f\t%f\n",t,x,v) ;/*現在時刻と現在の位置*/
 }

 /*結果の判定*/
 
 return 0 ;
}

/*************************/
/*    retrofire()関数    */
/*    逆噴射の制御       */
/*************************/
double retrofire(double t,double tf)
{
 double result=0 ;/*逆噴射の加速度*/

 if(t>=tf){/*逆噴射開始時刻以降なら*/
  result=-F*G ;/*逆噴射*/
 }
 return result ;
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
