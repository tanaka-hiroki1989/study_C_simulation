/******************************************/
/*　　　　       traffic.cプログラム      */
/******************************************/

/* セルオートマトンに基づく交通流シミュレーション        */
/* ルールと初期状態から，時間発展を計算します            */
/*　使い方   $./traffic (流入率）　< (初期状態ファイル名)*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 50 /*セルの最大個数*/
#define R 8 /*ルール表の大きさ*/
#define MAXT 50 /*繰り返しの回数*/
#define BUFSIZE 1024 /*入力バッファ用配列の長さ*/
#define RULE "184" /*ルール番号(184に固定)*/
#define VEHICLE "-" /*自動車を表す記号*/

/*関数のプロトタイプの宣言*/
void setrule(char *arg,int rule[]) ;/*ルール表の初期化*/
void initca(int ca[]) ;/*初期値の読み込み*/
int cvalue(char ch) ;/*1文字の0/1への変換*/
void putca(int ca[]) ;/*caの状態の出力*/
void nextt(int ca[],int rule[]) ;/*次の時刻に更新*/

/*********************/
/*     main()関数    */
/*********************/
int main(int argc,char *argv[])
{
 int t  ;/*時刻を表す，反復回数のカウンタ*/
 int ca[N]={0} ;/*セルの並び*/
 int rule[R] ;/*ルール表*/
 int flowrate=MAXT ;/*流入率*/

 /*流入率の初期化*/
 if(argc<2){/*流入率の指定がない*/
  fprintf(stderr,"使い方　traffic (流入率）　< (初期状態ファイル名)\n") ;
  exit(1) ;
 }
 flowrate=atoi(argv[1]) ;
 if(flowrate<=0){/*流入率が不正*/
  fprintf(stderr,"流入率が正しくありません（%d）\n",flowrate) ;
  exit(1) ;
 }

 /*ルール表をセット*/
 setrule(RULE,rule) ;
 
 /*ca[]への初期値の読み込み*/
 initca(ca) ;
 printf("t=  0 ") ;
 putca(ca) ;/*ca[]の状態の出力*/

 /*時間発展の計算*/
 for(t=1;t<MAXT;++t){
  nextt(ca,rule) ;/*次の時刻に更新*/
  if((t%flowrate)==0) ca[N-2]=1 ;/*自動車の流入*/
  printf("t=%3d ",t) ;
  putca(ca) ;/*ca[]の状態の出力*/
 }

 return 0 ;
}

/*************************/
/*   nextt()関数         */
/*   caの状態の更新      */
/*************************/

void nextt(int ca[],int rule[])
{
 int nextca[N]={0} ;/*次世代のca[]*/
 int i ;

 /*ルールの適用*/
 for(i=1;i<N-1;++i)
  nextca[i]=rule[ca[i+1]*4+ca[i]*2+ca[i-1]] ;

 /*caの更新*/
 for(i=0;i<N;++i)
  ca[i]=nextca[i] ;
}


/*************************/
/*   putca()関数         */
/*   caの状態の出力      */
/*************************/
void putca(int ca[])
{
 int  i;
 for(i=N-1;i>=0;--i){
  if(ca[i]==1) printf(VEHICLE) ;
  else printf(" ") ;
 }
 printf("\n") ;
}

/*************************/
/*  initca()関数         */
/*  初期値の読み込み     */
/*************************/
void  initca(int ca[])
{
 char linebuf[BUFSIZE] ; /*1行入力用の文字配列*/
 int i=0 ;

 /*初期値を読み込む*/
 if(fgets(linebuf,BUFSIZE,stdin)==NULL){/*読み取り失敗*/
  fprintf(stderr,"初期値の読み取りに失敗しました\n") ;
  exit(1) ;
 }

 /*初期値の設定*/
 for(i=0;linebuf[i]!='\0';++i)
  ca[N-1-i]=cvalue(linebuf[i]) ;/*左詰で代入*/
}


/*************************/
/*  cvalue()関数         */
/*  1文字の0/1への変換   */
/*************************/
int cvalue(char ch)
{
 if(ch=='1') return 1 ;
 else return 0 ;
}


/*************************/
/*  setrule()関数        */
/*  ルール表の初期化     */
/*************************/
void setrule(char *arg,int rule[])
{
 int ruleno ;/*ルール番号*/
 int i ;

 /*ルール番号を取得*/
 ruleno=atoi(arg) ;
 if((ruleno<0)||(255<ruleno)){/*ルール番号が不正*/
  fprintf(stderr,"ルール番号が正しくありません（%d）\n",ruleno) ;
  exit(1) ;
 }
 printf("ルール番号 %d :",ruleno) ;
 /*ルール表の書き込み*/
 for(i=0;i<R;++i){
  rule[i]=ruleno%2 ;/*2進数での１の位の値を取り出す*/
  ruleno/=2 ;/*左シフト*/
 }
 /*ルールの出力*/
 for(i=R-1;i>=0;--i)
  printf("%1d",rule[i]) ;
 printf("\n") ;
}
