/***********************************************/
/* 　　　        rkp.cプログラム               */
/***********************************************/

/*ナップサック問題をランダム探索で解くプログラムです． */
/*　使い方   $./rkp (荷物の個数) (制限重量)  (試行回数)*/

#include <stdio.h>
#include <stdlib.h>


#define BUFSIZE 256/*入力バッファの大きさ*/
#define MAXP 256/*荷物の個数の最大値*/
#define SEED  RAND_MAX-1  /*乱数の種*/
#define R 10 /*実験の繰り返し回数*/


/*関数のプロトタイプの宣言*/
void initparcel(int parcel[][2]);/*ファイルから荷物の重量と価値を読み込む*/
void prints(int p[],int n);/*解の表示*/
void solve(int parcel[][2],int p[],int weightlimit,long nlimit,int n) ;/*解を求める*/
void rsetp(int p[],int n) ;/*乱数による荷物の詰め合わせ*/
double frand(void) ;/*実数乱数*/
int calcval(int parcel[][2],int p[],int n) ;/*評価値の計算*/
int calcw(int parcel[][2],int p[],int n) ;/*重量の計算*/

/*****************/
/*　main()関数　 */
/*****************/
int main(int argc, char **argv)
{
 int parcel[MAXP][2]={0} ;/*荷物*/
 int p[MAXP]={0} ;/*解*/
 int weightlimit ;/*制限重量*/
 int n ;/*荷物の個数*/
 long nlimit ;/*試行回数*/
 int r ;/*実験の繰り返し制御変数*/

 if(argc!=4){
  fprintf(stderr,"使い方　./rkp (荷物の個数) (制限重量) (試行回数)\n") ;
  exit(1) ;
 }

 n=atoi(argv[1]) ;
 if((n<=0)||(n>MAXP)){/*荷物の個数が不正*/
  fprintf(stderr,"荷物の個数が不正です(%d）\n",n) ;
  exit(1) ;
 }
 printf("荷物の個数:%d\n",n) ;

 if((weightlimit=atoi(argv[2]))<=0){/*制限重量が0以下*/
  fprintf(stderr,"制限重量が不正です(%d）\n",weightlimit) ;
  exit(1) ;
 }
 printf("制限重量　:%d\n",weightlimit) ;

 if((nlimit=atoi(argv[3]))<=0){/*試行回数が0以下*/
  fprintf(stderr,"試行回数が不正です(%d）\n",nlimit) ;
  exit(1) ;
 }
 printf("試行回数　:%ld\n",nlimit) ;

 /*ファイルから荷物の重量と価値を読み込む*/
 initparcel(parcel) ;
 /*問題を解く*/
 srand(SEED) ;
 /*実験の繰り返し*/
 for(r=0;r<R;++r)
  solve(parcel,p,weightlimit,nlimit,n) ;

 return 0 ;
}

/***********************/
/*問題を解く関数solve()*/
/***********************/
void solve(int parcel[][2],int p[],int weightlimit,long nlimit,int n)
{
 int maxvalue=0 ,mweight;/*価値の最大値と，そのときの重量*/
 int value,weight ; /*価値と重量*/
 long i ;
 int bestp[MAXP]={0} ;/*最良解*/
 int j ;

 for(i=0;i<nlimit;++i){
  rsetp(p,n) ;/*乱数による荷物の詰め合わせ*/
  if((weight=calcw(parcel,p,n))<=weightlimit)/*制限重量以内*/
   value=calcval(parcel,p,n) ;/*評価値の計算*/
  else
   value=0 ;/*重量オーバー*/
  if(value>maxvalue){/*最良解を更新*/
   maxvalue=value ;
   mweight=weight ;
   for(j=0;j<n;++j)
    bestp[j]=p[j] ;
  }
 }
 printf("%d  %d ",maxvalue,mweight) ;
 prints(bestp,n) ;
}

/****************************/
/*   　 calcw()関数         */
/*      評価値の計算        */
/****************************/
int calcw(int parcel[][2],int p[],int n)
{
 int i ;
 int w=0 ;/*重量*/

 for(i=0;i<n;++i)
  w+=parcel[i][0]*p[i]  ;

 return w ;
}

/****************************/
/*   　 calcval()関数       */
/*      評価値の計算        */
/****************************/
int calcval(int parcel[][2],int p[],int n)
{
 int i ;
 int v=0 ;/*評価値*/

 for(i=0;i<n;++i)
  v+=parcel[i][1]*p[i]  ;

 return v ;
}

/****************************/
/*   　 rsetp()関数         */
/*乱数による荷物の詰め合わせ*/
/****************************/
void rsetp(int p[],int n)
{
 int i ;

 for(i=0;i<n;++i)
  while((p[i]=frand()*2)>=2)  ;
}

/*************************/
/*   frand()関数         */
/*   実数乱数            */
/*************************/
double frand(void)
{
 return (double)rand()/RAND_MAX ;
}

/**************/
/*prints()関数*/
/*  解の表示  */
/**************/
void prints(int p[],int n)
{
 int i ;
 for(i=0;i<n;++i)
  printf("%1d",p[i]) ;
 printf("\n") ;
}

/****************************************/
/*ファイルから荷物の重量と価値を読み込む*/
/****************************************/
void initparcel(int parcel [MAXP][2])
{
 int i=0 ;
  char linebuf[BUFSIZE] ;/*入力バッファ*/

 while((i<MAXP) && (fgets(linebuf,BUFSIZE,stdin)!=NULL)){
  sscanf(linebuf,"%d %d",&parcel[i][0],&parcel[i][1]) ;
  ++i ;
 }
}
