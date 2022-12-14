/**********************************************/
/*　　　　    sa1.cプログラム                 */
/**********************************************/

/* シンプルなエージェントシミュレーション     */
/* 2次元平面内で動作するエージェント群        */
/* 複数のエージェントがランダムウォークします */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define BUFSIZE 256 /*入力バッファ用配列の長さ*/
#define N 30       /*エージェントの個数*/
#define N_OF_A 2       /*エージェントの属性値の個数*/
#define TIMELIMIT 100 /*シミュレーション打ち切り時刻*/
#define SEED  RAND_MAX-1  /*乱数の種*/

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
void cat0(struct agent *cat0agent) ;/*カテゴリ0の計算メソッド*/
double frand(void) ;/*実数乱数*/

/*********************/
/*     main()関数    */
/*********************/
int main()
{
 struct agent a[N]={0} ; /*エージェント*/
 int t ;
 
 /*初期化*/
 srand(SEED) ;/*乱数の初期化*/
 putstate(a,0) ;

 /*エージェントシミュレーション*/
 for(t=0;t<=TIMELIMIT;++t){/*打ち切り時間まで計算*/
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
  if(a[i].category==0)/*カテゴリ0*/cat0(&a[i]) ;
  else/*合致するカテゴリがない*/ 
   fprintf(stderr,"ERROR カテゴリがありません(%d)\n",i) ;
 }
}

/*************************/
/*      cat0()関数       */
/*カテゴリ0の計算メソッド*/
/*************************/
void cat0(struct agent *cat0agent)
{
 (*cat0agent).coord.x+=(frand()-0.5) ;
 (*cat0agent).coord.y+=(frand()-0.5) ;
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

