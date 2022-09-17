/**********************************************/
/*�@�@�@�@   laplace.c�v���O����              */
/**********************************************/

/* �����@�ɂ�郉�v���X�������̉�@�v���O���� */
/* �W�����͂���uij�̏����l��ǂݍ��݌v�Z���܂�*/

#include <stdio.h>
#include <stdlib.h>
#define LIMIT 10000 /*�����񐔂̏��*/
#define N 101 /*x�������̕�����*/
#define M 101 /*y�������̕�����*/
#define BUFSIZE 256 /*���̓o�b�t�@�p�z��̒���*/
#define ERROR -1 /*���͎��̃G���[�R�[�h*/

/*�֐��̃v���g�^�C�v�̐錾*/
int getuij(double u[][M]) ;/*�s��̏����l�̓ǂݍ��� */
void putuij(double u[][M]) ;/*�s��̒l�̏o�� */
void iteration(double u[][M]) ;/*1�񕪂̔����v�Z*/
int getdouble(double *x) ;/*�����̓ǂݍ��� */

/*********************/
/*     main()�֐�    */
/*********************/
int main()
{
 int i  ;/*�����񐔂̃J�E���^*/
 double u[N][M] ;/*uij*/

 /*�s��̏����l�̓ǂݍ���*/
 if(getuij(u)!=0){/*�ǂݍ��ݎ��s*/
  fprintf(stderr,"�����l�̓ǂݍ��ݎ��s\n") ;
  exit(1); /*�ُ�I��*/
 }

 /*�����@�̌v�Z*/
 for(i=0;i<LIMIT;++i){
  iteration(u) ;
  if((i%(LIMIT/10))==0){/*�r���o�߂�(LIMIT/10)��o��*/
   printf("i=%d\n",i) ;
   putuij(u) ;
   printf("\n") ;
  }
 }

 /*���ʂ̏o��*/
 putuij(u) ;

 return 0 ;
}

/*************************/
/*   iteration�֐�       */
/*  1�񕪂̔����v�Z      */
/*************************/
void iteration(double u[][M])
{
 double u_next[N][M] ;/*���X�e�b�v��uij*/
 int i,j ;

 /*���X�e�b�v�̒l���v�Z*/
 for(i=1;i<N-1;++i)
  for(j=1;j<M-1;++j)
   u_next[i][j]
    =(u[i][j-1]+u[i-1][j]+u[i+1][j]+u[i][j+1])/4 ;
 /*uij�̍X�V*/
 for(i=1;i<N-1;++i)
  for(j=1;j<M-1;++j)
   u[i][j]=u_next[i][j] ;
}

/*************************/
/*    putuij()�֐�       */
/* �s��̒l�̏o��        */
/*************************/
void putuij(double u[][M])
{
 int i,j ;

 for(i=0;i<N;++i){
  for(j=0;j<M;++j)
   printf("%lf ",u[i][j]) ;
  printf("\n") ;
 }
}

/*************************/
/*    getuij()�֐�       */
/* �s��̏����l�̓ǂݍ���*/
/*************************/
int getuij(double u[][M])
{
 int i,j ;

 for(i=0;i<N;++i)
  for(j=0;j<M;++j){
   if(getdouble(&u[i][j])==EOF){/*�ǂݍ��݃G���[*/
    fprintf(stderr,"%d %d",i,j) ;
    return ERROR ;
   }
  }
 return 0 ;
}

/*************************/
/*    getdouble()�֐�    */
/*    �����̓ǂݍ���     */
/*************************/
int getdouble(double *x)
{
 char linebuf[BUFSIZE] ; /*1�s���͗p�̕����z��*/
 int result=0 ;/*���͌��ʂ̃R�[�h*/

 if(fgets(linebuf,BUFSIZE,stdin)!=NULL){/*�s�̓ǂݎ�肪�\*/
  if(sscanf(linebuf,"%lf",x)<=0)/*�ϊ��ł��Ȃ����*/
    result=EOF ;/*�G���[*/
 } else {/*�s���ǂ߂Ȃ�*/
  result=EOF ;/*�t�@�C���̏I���*/
 }
 return result ;
}
