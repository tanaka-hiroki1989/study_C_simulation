/**********************************************/
/*　　　　      life.cプログラム              */
/**********************************************/

/* ライフゲーム計算プログラム                 */
/* ２次元セルオートマトンの一種であるライフゲームのプログラムです */
/*　使い方    $./life 　< (初期状態ファイル名)*/
/*　　　出力は行列形式です                    */
/*　初期状態ファイルには，初期配置の座標を２行一組で記述します     */
/*    （x,yの順に記述します）                 */

#include <stdio.h>
#include <stdlib.h>

#define N 50 /*ライフゲームの世界の大きさ*/
#define MAXT 50 /*繰り返しの回数*/
#define BUFSIZE 256 /*入力バッファ用配列の長さ*/

/*関数のプロトタイプの宣言*/
void initworld(int world[][N]) ;/*初期値の読み込み*/
void putworld(int world[][N]) ;/*world[][]の状態の出力*/
void nextt(int world[][N]) ;/*次の時刻に更新*/
int calcnext(int world[][N],int i,int j) ;
                           /*   １セルの状態の更新  */

/*********************/
/*     main()関数    */
/*********************/
int main(int argc,char *argv[])
{
 int t  ;/*時刻を表す，反復回数のカウンタ*/
 int world[N][N]={0} ;/*ライフゲームの世界*/

 /*world[][]への初期値の読み込み*/
 initworld(world) ;
 printf("t=0\n") ;/*初期時刻の出力*/
 putworld(world) ;/*world[][]の状態の出力*/

 /*時間発展の計算*/
 for(t=1;t<MAXT;++t){
  nextt(world);/*次の時刻に更新*/
  printf("t=%d\n",t) ;/*時刻の出力*/
  putworld(world) ;/*world[][]の状態の出力*/
 }

 return 0 ;
}

/*************************/
/*   nextt()関数         */
/*   worldの状態の更新   */
/*************************/
void nextt(int world[][N])
{
 int nextworld[N][N]={0} ;/*次世代world[][]*/
 int i,j ;

 /*ルールの適用*/
 for(i=1;i<N-1;++i)
  for(j=1;j<N-1;++j)
   nextworld[i][j]=calcnext(world,i,j) ;

 /*worldの更新*/
 for(i=0;i<N;++i)
  for(j=0;j<N;++j)
   world[i][j]=nextworld[i][j] ;
}

/*************************/
/*   calcnext()関数      */
/*   １セルの状態の更新  */
/*************************/
int calcnext(int world[][N],int i,int j)
{
 int no_of_one=0 ;/*周囲にある状態１のセルの数*/
 int x,y ;

 /*状態１のセルを数える*/
 for(x=i-1;x<=i+1;++x)
  for(y=j-1;y<=j+1;++y)
   no_of_one+=world[x][y] ;
 no_of_one-=world[i][j] ;/*自分自身はカウントしない*/

 /*状態の更新*/
 if(no_of_one==3) return 1 ;/*誕生*/
 else if(no_of_one==2) return world[i][j] ;/*存続*/
      
 return 0 ;/*上記以外*/
}

/*************************/
/*   putworld()関数      */
/*  world[][]の状態の出力*/
/*************************/
void putworld(int world[][N])
{
 int  i,j;

 for(j=N-1;j>=0;--j){
  for(i=0;i<N;++i)
    printf("%1d",world[i][j]) ;/*出力*/
  printf("\n") ;
 }
}

/*************************/
/*  initworld()関数      */
/*  初期値の読み込み     */
/*************************/
void  initworld(int world[][N])
{
 char linebuf[BUFSIZE] ; /*1行入力用の文字配列*/
 int x,y ;/*座標値を格納*/

 /*初期値を読み込む*/
 while(fgets(linebuf,BUFSIZE,stdin)!=NULL){
  if(sscanf(linebuf,"%d",&x)<1) break ;
  if(fgets(linebuf,BUFSIZE,stdin)==NULL) break ;
  if(sscanf(linebuf,"%d",&y)<1) break ;
  if((x>=0)&&(x<N)&&(y>=0)&&(y<N)) world[x][y]=1 ;
 }
}



