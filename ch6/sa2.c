/**********************************************/
/*　　　　       sa2.cプログラム              */
/**********************************************/

/*    シンプルなエージェントシミュレーション  */
/*    2次元平面内で動作するエージェント群     */
/*    2種類のエージェントが相互作用します     */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define BUFSIZE 256 /*入力バッファ用配列の長さ*/
#define N 30       /*エージェントの個数*/
#define N_OF_A 2       /*エージェントの属性値の個数*/
#define TIMELIMIT 100 /*シミュレーション打ち切り時刻*/
#define SEED  RAND_MAX-1  /*乱数の種*/
#define R 0.1 /*近隣を規定する数値*/
/*カテゴリ1のエージェントの速度*/
#define DX 0.1 
#define DY 0.1

/*座標値（2次元ベクトル)の表現*/
struct coordinate {
 double x ;/*x座標*/
 double y ;/*y座標*/
} ;

/*エージェントの表現*/
struct agent {
 int category ;/*エージェントの種類*/
 struct coordinate coord ;/*座標*/
 double dattribute[N_OF_A] ;/*属性値(実数）*/
 int iattribute[N_OF_A] ;/*属性値(整数）*/
} ;



/*関数のプロトタイプの宣言*/
void calcnext(struct agent a[]) ;/*次時刻の状態を計算 */
void putstate(struct agent a[],int t) ;/*状態を出力*/
double frand(void) ;/*実数乱数*/
void cat0(struct agent *cat0agent,struct agent a[]) ;/*カテゴリ0の計算メソッド*/
void cat1(struct agent *cat1agent) ;/*カテゴリ1の計算メソッド*/

/*********************/
/*     main()関数    */
/*********************/
int main()
{
 struct agent a[N]={0} ; /*エージェント*/
 int t ;
 
 /*初期化*/
 srand(SEED) ;/*乱数の初期化*/

 /*カテゴリ1のエージェントの設定*/
 a[0].category=1 ;
 a[0].coord.x=-2 ;
 a[0].coord.y=-2 ;

 putstate(a,0) ;

 /*エージェントシミュレーション*/
 for(t=1;t<=TIMELIMIT;++t){/*打ち切り時間まで計算*/
  calcnext(a) ;/*次時刻の状態を計算 */
  putstate(a,t) ;/*状態を出力*/
 }

 
 return 0 ;
}

/*************************/
/*     calcnext()関数    */
/*   次時刻の状態を計算  */
/*************************/
void calcnext(struct agent a[])
{
 int i ;
 for(i=0;i<N;++i){ /*各エージェントの計算*/
  if(a[i].category==0)/*カテゴリ0*/cat0(&a[i],a) ;
  else if(a[i].category==1)/*カテゴリ1*/cat1(&a[i]) ;
  else/*合致するカテゴリがない*/ 
   fprintf(stderr,"ERROR カテゴリがありません(%d)\n",i) ;
 }
}
/*************************/
/*      cat0()関数       */
/*カテゴリ0の計算メソッド*/
/*************************/
void cat0(struct agent *cat0agent,struct agent a[])
{
 int i ;

 double c0x,c0y,ax,ay ; /*距離の計算に使う変数*/
 for(i=0;i<N;++i){
  if(a[i].category==1){
   /*カテゴリ1のエージェントとの距離を調べる*/
   c0x=(*cat0agent).coord.x ;
   c0y=(*cat0agent).coord.y ;
   ax=a[i].coord.x ;
   ay=a[i].coord.y ;
   if(((c0x-ax)*(c0x-ax)+(c0y-ay)*(c0y-ay))<R){
    /*隣接してカテゴリ1のエージェントがいる*/
    (*cat0agent).category=1 ;/*カテゴリ１に変身*/
    return  ;
   }
  }
 }
 /*カテゴリ1は近隣にはいない*/
 (*cat0agent).coord.x+=(frand()-0.5) ;
 (*cat0agent).coord.y+=(frand()-0.5) ;
}

/*************************/
/*      cat1()関数       */
/*カテゴリ1の計算メソッド*/
/*************************/
void cat1(struct agent *cat1agent)
{
 (*cat1agent).coord.x+=DX ;
 (*cat1agent).coord.y+=DY ;
}

/*************************/
/*     putstate()関数    */
/*      状態を出力       */
/*************************/
void putstate(struct agent a[],int t)
{
 int i ;
 printf("t=%d\n",t) ;/*時刻の出力*/
 for(i=0;i<N;++i) /*カテゴリと座標の出力*/
  printf("%d\t%lf\t%lf\n",a[i].category
                       ,a[i].coord.x,a[i].coord.y) ;
}

/*************************/
/*   frand()関数         */
/*   実数乱数            */
/*************************/
double frand(void)
{
 return (double)rand()/RAND_MAX ;
}

