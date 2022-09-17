/**********************************************/
/*　　　　       ca1.cプログラム              */
/**********************************************/

/* セルオートマトン（1次元）計算プログラム    */
/* ルールと初期状態から，時間発展を計算します */
/*　使い方    $./ca1 (ルール番号）　< (初期状態ファイル名)　 　  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 65 /*セルの最大個数*/
#define R 8 /*ルール表の大きさ*/
#define MAXT 50 /*繰り返しの回数*/
#define BUFSIZE 256 /*入力バッファ用配列の長さ*/

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

 /*ルール表の初期化*/
 if(argc<2){/*ルールの指定がない*/
  fprintf(stderr,"使い方　ca1 (ルール番号）　< (初期状態ファイル名)\n") ;
  exit(1) ;
 }
 setrule(argv[1],rule) ;/*ルール表をセット*/
 
 /*ca[]への初期値の読み込み*/
 initca(ca) ;
 putca(ca) ;/*ca[]の状態の出力*/

 /*時間発展の計算*/
 for(t=0;t<MAXT;++t){
  nextt(ca,rule) ;/*次の時刻に更新*/
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
 for(i=N-1;i>=0;--i)
  printf("%1d",ca[i]) ;
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
