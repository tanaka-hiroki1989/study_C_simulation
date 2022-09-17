/*******************************************/
/*�@�@�@�@      glife.c�v���O����          */
/*******************************************/

/* ���C�t�Q�[���v�Z�v���O���� �ignuplot���g����GUI��)               */
/* �Q�����Z���I�[�g�}�g���̈��ł��郉�C�t�Q�[���̃v���O�����ł�   */
/*�@�g����    $./glife �@< (������ԃt�@�C����)�@                   */
/*�@�@�@�o�͂�gnuplot���g���ăO���t�B�J���ɕ\�����܂�               */
/*�@������ԃt�@�C���ɂ́C�����z�u�̍��W���Q�s��g�ŋL�q���܂�      */
/*    �ix,y�̏��ɋL�q���܂��j                                       */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 100 /*���C�t�Q�[���̐��E�̑傫��*/
#define MAXT 500 /*�J��Ԃ��̉�*/
#define BUFSIZE 256 /*���̓o�b�t�@�p�z��̒���*/
#define TMPFILE "tempfile.tmp" /*�ꎞ�t�@�C���̃t�@�C����*/
#define GNUPLOT "/bin/gnuplot" /*gnuplot�̃p�X���w��*/

/*�֐��̃v���g�^�C�v�̐錾*/
void initworld(int world[][N]) ;/*�����l�̓ǂݍ���*/
void fputworld(int world[][N]) ;/*world[][]�̏�Ԃ̃t�@�C���o��*/
void nextt(int world[][N]) ;/*���̎����ɍX�V*/
int calcnext(int world[][N],int i,int j) ;
                           /*   �P�Z���̏�Ԃ̍X�V  */

/*********************/
/*     main()�֐�    */
/*********************/
int main(int argc,char *argv[])
{
 int t  ;/*������\���C�����񐔂̃J�E���^*/
 int world[N][N]={0} ;/*���C�t�Q�[���̐��E*/
 FILE *pipe ;/*gnuplot�Ƃ̒ʐM�p�p�C�v*/

 /*world[][]�ւ̏����l�̓ǂݍ���*/
 initworld(world) ;
 printf("t=0\n") ;/*���������̏o��*/
 fputworld(world) ;/*world[][]�̏�Ԃ̏o��*/

 /*�p�C�v���J��*/
 if((pipe=popen(GNUPLOT " -persist","w"))==NULL){
  /*pipe���J���Ȃ�*/
  fprintf(stderr,"�p�C�v���J���܂���D\n") ;
  exit(1) ;
 } 
 /*gnuplot�̏����ݒ�*/
 fprintf(pipe,"set xrange [0:%d]\n",N) ;
 fprintf(pipe,"set yrange [0:%d]\n",N) ;

 /*���Ԕ��W�̌v�Z*/
 for(t=1;t<MAXT;++t){
  nextt(world);/*���̎����ɍX�V*/
  printf("t=%d\n",t) ;/*�����̏o��*/
  fputworld(world) ;/*world[][]�̏�Ԃ̃t�@�C���o��*/
  /*gnuplot�ŕ`��*/
  fprintf(pipe,"plot \"" TMPFILE "\" with points pt 4\n") ; 
  fflush(pipe) ;
  sleep(1) ; /*�\���̑҂����킹*/
 }

 return 0 ;
}

/*************************/
/*   nextt()�֐�         */
/*   world�̏�Ԃ̍X�V   */
/*************************/
void nextt(int world[][N])
{
 int nextworld[N][N]={0} ;/*������world[][]*/
 int i,j ;

 /*���[���̓K�p*/
 for(i=1;i<N-1;++i)
  for(j=1;j<N-1;++j)
   nextworld[i][j]=calcnext(world,i,j) ;

 /*world�̍X�V*/
 for(i=0;i<N;++i)
  for(j=0;j<N;++j)
   world[i][j]=nextworld[i][j] ;
}

/*************************/
/*   calcnext()�֐�      */
/*   �P�Z���̏�Ԃ̍X�V  */
/*************************/
int calcnext(int world[][N],int i,int j)
{
 int no_of_one=0 ;/*���͂ɂ����ԂP�̃Z���̐�*/
 int x,y ;

 /*��ԂP�̃Z���𐔂���*/
 for(x=i-1;x<=i+1;++x)
  for(y=j-1;y<=j+1;++y)
   no_of_one+=world[x][y] ;
 no_of_one-=world[i][j] ;/*�������g�̓J�E���g���Ȃ�*/

 /*��Ԃ̍X�V*/
 if(no_of_one==3) return 1 ;/*�a��*/
 else if(no_of_one==2) return world[i][j] ;/*����*/
      
 return 0 ;/*��L�ȊO*/
}

/**************************/
/*   fputworld()�֐�      */
/*   world[][]�̏�Ԃ̏o��*/
/**************************/
void fputworld(int world[][N])
{
 int  i,j;
 FILE *fp ;  /*�ꎞ�t�@�C���̃t�@�C���|�C���^*/

 /*�ꎞ�t�@�C�����J��*/
 if((fp=fopen(TMPFILE,"w"))==NULL){/*�ꎞ�t�@�C�����J���Ȃ�*/
  fprintf(stderr,"�ꎞ�t�@�C�����J���܂���\n") ;
  exit(1) ;
 } 

 /*world[][]���t�@�C���ɏ����o��*/
 for(i=0;i<N;++i)
  for(j=0;j<N;++j)
   if(world[i][j]==1){/*����������*/
    fprintf(fp,"%d %d\n",i,j) ;/*���W���o��*/
   }
 fclose(fp) ;/*�ꎞ�t�@�C�������*/

}

/*************************/
/*  initworld()�֐�      */
/*  �����l�̓ǂݍ���     */
/*************************/
void  initworld(int world[][N])
{
 char linebuf[BUFSIZE] ; /*1�s���͗p�̕����z��*/
 int x,y ;/*���W�l���i�[*/

 /*�����l��ǂݍ���*/
 while(fgets(linebuf,BUFSIZE,stdin)!=NULL){
  if(sscanf(linebuf,"%d",&x)<1) break ;
  if(fgets(linebuf,BUFSIZE,stdin)==NULL) break ;
  if(sscanf(linebuf,"%d",&y)<1) break ;
  if((x>=0)&&(x<N)&&(y>=0)&&(y<N)) world[x][y]=1 ;
 }
}



