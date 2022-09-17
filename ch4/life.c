/**********************************************/
/*�@�@�@�@      life.c�v���O����              */
/**********************************************/

/* ���C�t�Q�[���v�Z�v���O����                 */
/* �Q�����Z���I�[�g�}�g���̈��ł��郉�C�t�Q�[���̃v���O�����ł� */
/*�@�g����    $./life �@< (������ԃt�@�C����)*/
/*�@�@�@�o�͍͂s��`���ł�                    */
/*�@������ԃt�@�C���ɂ́C�����z�u�̍��W���Q�s��g�ŋL�q���܂�     */
/*    �ix,y�̏��ɋL�q���܂��j                 */

#include <stdio.h>
#include <stdlib.h>

#define N 50 /*���C�t�Q�[���̐��E�̑傫��*/
#define MAXT 50 /*�J��Ԃ��̉�*/
#define BUFSIZE 256 /*���̓o�b�t�@�p�z��̒���*/

/*�֐��̃v���g�^�C�v�̐錾*/
void initworld(int world[][N]) ;/*�����l�̓ǂݍ���*/
void putworld(int world[][N]) ;/*world[][]�̏�Ԃ̏o��*/
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

 /*world[][]�ւ̏����l�̓ǂݍ���*/
 initworld(world) ;
 printf("t=0\n") ;/*���������̏o��*/
 putworld(world) ;/*world[][]�̏�Ԃ̏o��*/

 /*���Ԕ��W�̌v�Z*/
 for(t=1;t<MAXT;++t){
  nextt(world);/*���̎����ɍX�V*/
  printf("t=%d\n",t) ;/*�����̏o��*/
  putworld(world) ;/*world[][]�̏�Ԃ̏o��*/
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

/*************************/
/*   putworld()�֐�      */
/*  world[][]�̏�Ԃ̏o��*/
/*************************/
void putworld(int world[][N])
{
 int  i,j;

 for(j=N-1;j>=0;--j){
  for(i=0;i<N;++i)
    printf("%1d",world[i][j]) ;/*�o��*/
  printf("\n") ;
 }
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



