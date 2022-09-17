/**********************************************/
/*　　 ginfection.cプログラム                 */
/**********************************************/

/*    ”感染”のエージェントシミュレーション  */
/*    2次元平面内で動作するエージェント群     */
/*    2種類のエージェントが相互作用します     */
/*    gnuplotで1秒ごとに出力します*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define BUFSIZE 256 /*入力バッファ用配列の長さ*/
#define N 50       /*エージェントの個数*/
#define N_OF_A 2       /*エージェントの属性値の個数*/
#define TIMELIMIT 100 /*シミュレーション打ち切り時刻*/
#define SEED  RAND_MAX-1  /*乱数の種*/
#define R 0.1 /*近隣を規定する数値*/

/*カテゴリ1のエージェントの速度*/
#define DX 0.1 
#define DY 0.1


/*以下はgnuplot利用のための定義*/
#define ATMPFILE "atempfile.tmp" /*一時ファイルのファイル名*/
#define BTMPFILE "btempfile.tmp" /*一時ファイルのファイル名*/
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
double frand(void) ;/*実数乱数*/
void cat0(struct agent *cat0agent,struct agent a[]) ;
                                   /*カテゴリ0の計算メソッド*/
void cat1(struct agent *cat1agent) ;/*カテゴリ1の計算メソッド*/

/*大域変数*/
double factor=1.0 ;/*カテゴリ１のエージェントの歩幅*/

/*********************/
/*     main()関数    */
/*********************/
int main(int argc,char *argv[])
{
 struct agent a[N]={0} ; /*エージェント*/
 int t ;
 FILE *pipe ;/*gnuplotとの通信用パイプ*/

 /*factorの初期化*/
 if(argc>=2){/*factorの指定がある*/
  factor=atof(argv[1]) ;
 }
 printf("factor : %lf\n",factor) ;
 
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
 /*エージェントの設定*/
 a[0].category=1 ;
 a[0].coord.x=-2 ;
 a[0].coord.y=-2 ;

 /*エージェントシミュレーション*/
 for(t=1;t<=TIMELIMIT;++t){/*打ち切り時間まで計算*/
  printf("t=%d\n",t) ;
  calcnext(a) ;/*次時刻の状態を計算 */
  fputstate(a,t) ;/*状態をファイル出力*/
  /*gnuplotで描画*/
  fprintf(pipe,"plot \"" ATMPFILE "\" , \"" BTMPFILE "\"with points pt 4\n") ; 
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
 (*cat1agent).coord.x+=(frand()-0.5)*factor ;
 (*cat1agent).coord.y+=(frand()-0.5)*factor ;
}

/*************************/
/*    fputstate()関数    */
/*      状態を出力       */
/*************************/
void fputstate(struct agent a[],int t)
{
 int i ;
 FILE *fpa,*fpb ;  /*一時ファイルのファイルポインタ*/

 /*一時ファイルを開く*/
 if((fpa=fopen(ATMPFILE,"w"))==NULL){/*一時ファイルが開けない*/
  fprintf(stderr,"一時ファイルAが開けません\n") ;
  exit(1) ;
 } 
 if((fpb=fopen(BTMPFILE,"w"))==NULL){/*一時ファイルが開けない*/
  fprintf(stderr,"一時ファイルBが開けません\n") ;
  exit(1) ;
 } 

 for(i=0;i<N;++i){ /*カテゴリと座標の出力*/
  if(a[i].category==0)
   fprintf(fpa,"%lf %lf\n",a[i].coord.x,a[i].coord.y) ;
  else
   fprintf(fpb,"%lf %lf\n",a[i].coord.x,a[i].coord.y) ;
 }
 fclose(fpa) ;/*一時ファイルを閉じる*/
 fclose(fpb) ;/*一時ファイルを閉じる*/
}

/*************************/
/*   frand()関数         */
/*   実数乱数            */
/*************************/
double frand(void)
{
 return (double)rand()/RAND_MAX ;
}

