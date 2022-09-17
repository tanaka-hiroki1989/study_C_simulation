/**********************************************/
/*　　　　       gsa1.cプログラム             */
/**********************************************/

/*    シンプルなエージェントシミュレーション  */
/*    2次元平面内で動作するエージェント       */
/* 複数のエージェントがランダムウォークします */
/*    gnuplotで1秒ごとに出力します            */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define BUFSIZE 256 /*入力バッファ用配列の長さ*/
#define N 30      /*エージェントの個数*/
#define N_OF_A 2       /*エージェントの属性値の個数*/
#define TIMELIMIT 100 /*シミュレーション打ち切り時刻*/
#define SEED  RAND_MAX-1  /*乱数の種*/
/*以下はgnuplot利用のための定義*/
#define TMPFILE "tempfile.tmp" /*一時ファイルのファイル名*/
#define GNUPLOT "/bin/gnuplot" /*gnuplotのパスを指定*/
#define RANGE 10 /*gnuplotの出力領域*/

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
void fputstate(struct agent a[],int t) ;/*状態を出力*/
void cat0(struct agent *cat0agent) ;/*カテゴリ0の計算メソッド*/
double frand(void) ;/*実数乱数*/

/*********************/
/*     main()関数    */
/*********************/
int main()
{
 struct agent a[N]={0} ; /*エージェント*/
 int t ;
 FILE *pipe ;/*gnuplotとの通信用パイプ*/
 
 /*パイプを開く*/
 if((pipe=popen(GNUPLOT " -persist","w"))==NULL){
  /*pipeが開けない*/
  fprintf(stderr,"パイプが開けません．\n") ;
  exit(1) ;
 } 
 /*gnuplotの初期設定*/
 fprintf(pipe,"set xrange [-%d:%d]\n",RANGE,RANGE) ;
 fprintf(pipe,"set yrange [-%d:%d]\n",RANGE,RANGE) ;

 /*初期化*/
  srand(SEED) ;/*乱数の初期化*/

 /*エージェントシミュレーション*/
 for(t=0;t<=TIMELIMIT;++t){/*打ち切り時間まで計算*/
  printf("t=%d\n",t) ;
  calcnext(a) ;/*次時刻の状態を計算 */
  fputstate(a,t) ;/*状態をファイル出力*/
  /*gnuplotで描画*/
  fprintf(pipe,"plot \"" TMPFILE "\" with points pt 4\n") ; 
  fflush(pipe) ;
  sleep(1) ; /*表示の待ち合わせ*/
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
/*   frand()関数         */
/*   実数乱数            */
/*************************/
double frand(void)
{
 return (double)rand()/RAND_MAX ;
}

/*************************/
/*    fputstate()関数    */
/*      状態を出力       */
/*************************/
void fputstate(struct agent a[],int t)
{
 int i ;
 FILE *fp ;  /*一時ファイルのファイルポインタ*/

 /*一時ファイルを開く*/
 if((fp=fopen(TMPFILE,"w"))==NULL){/*一時ファイルが開けない*/
  fprintf(stderr,"一時ファイルが開けません\n") ;
  exit(1) ;
 } 

 for(i=0;i<N;++i) /*カテゴリと座標の出力*/
  fprintf(fp,"%lf %lf\n",a[i].coord.x,a[i].coord.y) ;
 fclose(fp) ;/*一時ファイルを閉じる*/
}

