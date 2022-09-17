/**********************************************/
/*　　　　    sa0.cプログラム                 */
/**********************************************/

/*    シンプルなエージェントシミュレーション  */
/*    2次元平面内で動作するエージェント       */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define BUFSIZE 256 /*入力バッファ用配列の長さ*/
#define N 1       /*エージェントの個数*/
#define N_OF_A 2       /*エージェントの属性値の個数*/
#define TIMELIMIT 100 /*シミュレーション打ち切り時刻*/


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
void reverse(int *i) ;/*cat0()の下請け関数*/

/*********************/
/*     main()関数    */
/*********************/
int main()
{
 struct agent a[N]={0} ; /*エージェント*/
 int t ;
 
 /*初期化*/
 a[0].iattribute[0]=1 ;
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
 /*内部状態の更新*/
 reverse(&((*cat0agent).iattribute[0])) ;
 reverse(&((*cat0agent).iattribute[1])) ;

 /*内部状態によって次の座標を決定*/
 (*cat0agent).coord.x+=(*cat0agent).iattribute[0] ;
 (*cat0agent).coord.y+=(*cat0agent).iattribute[1] ;
}

/*************************/
/*    reverse()関数      */
/*cat0()関数の下請け関数 */
/*************************/
void reverse(int *i)
{
 if(*i==0) *i=1;
 else *i=0 ;
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

