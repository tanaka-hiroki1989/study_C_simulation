/**********************************************/
/*　　　coord.cプログラム                     */
/**********************************************/

/* 行列形式のデータを座標形式に変換します     */

#include <stdio.h>

#define BUFSIZE 1024 /*入力バッファ用配列の長さ*/

/*********************/
/*     main()関数    */
/*********************/
int main()
{
 int lineno=0 ;/*行番号*/
 char linebuf[BUFSIZE] ; /*1行入力用の文字配列*/
 int i ;

 /*データを読み込む*/
 while(fgets(linebuf,BUFSIZE,stdin)!=NULL){/*読み取れる間繰り返す*/
  if(linebuf[0]=='0'){/*データ領域*/
   for(i=0;linebuf[i]!='\0';++i)
    if(linebuf[i]=='1') printf("%d %d\n",i,-lineno) ;/*座標の出力*/
  ++lineno ;
  }
 }

 return 0 ;
}
