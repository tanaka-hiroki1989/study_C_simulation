/**********************************************/
/*�@�@�@�@   efield.c�v���O����               */
/**********************************************/

/*    2�����^���̃V�~�����[�V�����@�@    �@   */
/*  �d�E���̉דd���q�̃V�~�����[�V�����ł�    */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#define DT 0.001 /*�����̍��ݕ�*/
#define TIMELIMIT 20.0 /*�V�~�����[�V�����ł��؂莞��*/
#define R 0.1 /*����r�̍Œ�l*/
#define BUFSIZE 256 /*���̓o�b�t�@�p�z��̒���*/
#define N 256 /*�z�u�ł���d�ׂ̐��̍ő�l*/

/*���W�l�i2�����x�N�g��)�̕\��*/
struct coordinate {
 double x ;/*x���W*/
 double y ;/*y���W*/
} ;

/*�d��*/
struct charge {
 struct coordinate qxy ;/*�d�ׂ̈ʒu*/
 double q ;/*�d��*/
} ;

/*�֐��̃v���g�^�C�v�̐錾*/
int getdouble(double *x) ;/*�����̓ǂݍ��� */
int inputq(struct charge qi[]) ;/*�d�ׂ̓���*/

/*********************/
/*     main()�֐�    */
/*********************/
int main()
{
 struct coordinate v,x ; /*���_�̑��x�ƈʒu*/
 struct charge qi[N] ; /*�d��qi*/
 int nofq ;/*�d�ׂ̌�*/
 double t=0  ;/*����*/
 double h=DT ;/*�����̍��ݕ�*/
 double rx,ry,r,rmin ;/*�d�ׂƎ��_�̋���*/
 int i ;
 
 /*�W���̓���*/
 fprintf(stderr,"�����xv0x����͂��Ă�������\n") ;
 if(getdouble(&v.x)==EOF) exit(1) ;
 fprintf(stderr,"�����xv0y����͂��Ă�������\n") ;
 if(getdouble(&v.y)==EOF) exit(1) ;
 fprintf(stderr,"�����ʒux.x����͂��Ă�������\n") ;
 if(getdouble(&x.x)==EOF) exit(1) ;
 fprintf(stderr,"�����ʒux.y����͂��Ă�������\n") ;
 if(getdouble(&x.y)==EOF) exit(1) ;
 nofq=inputq(qi) ;/*�d�ׂ̓���*/

 printf("%f\t%f\t%f\t%f\t%f\n",t,x.x,x.y,v.x,v.y) ;/*���ݎ����ƌ��݂̈ʒu*/

 /*2�����^���̌v�Z*/
 while(t<=TIMELIMIT){/*�ł��؂莞�Ԃ܂Ōv�Z*/
  t+=h ;/*�����̍X�V*/
  rmin=DBL_MAX ;/*�����̍ŏ��l��������*/
  for(i=0;i<nofq;++i){
   rx=qi[i].qxy.x-x.x ;/*����rx�̌v�Z*/
   ry=qi[i].qxy.y-x.y ;/*����ry�̌v�Z*/
   r=sqrt(rx*rx+ry*ry) ;/*����r�̌v�Z*/
   if(r<rmin) rmin=r ;/*�����̍ŏ��l���X�V*/ 
   v.x+=(rx/r/r/r*qi[i].q)*h ;/*���xvx�̌v�Z*/
   v.y+=(ry/r/r/r*qi[i].q)*h ;/*���xvy�̌v�Z*/
  }
  x.x+=v.x*h ;/*�ʒuxx�̌v�Z*/
  x.y+=v.y*h ;/*�ʒuxy�̌v�Z*/
  printf("%f\t%f\t%f\t%f\t%f\n",t,x.x,x.y,v.x,v.y) ;/*���ݎ����ƌ��݂̈ʒu*/
  if(rmin<R) break ;/*�d�ׂɔ��ɋ߂Â�����I��*/
 }

 
 return 0 ;
}

/*************************/
/*      inputq()�֐�    */
/*       �d�ׂ̓���      */
/*************************/
int inputq(struct charge qi[])
{
 int i ;

 for(i=0;i<N;++i){
  fprintf(stderr,"�d��%d\n",i) ;
  fprintf(stderr,"�d�ׂ̔z�u�ꏊqxy.x����͂��Ă�������\n") ;
  if(getdouble(&qi[i].qxy.x)==EOF) break ;
  fprintf(stderr,"�d�ׂ̔z�u�ꏊqxy.y����͂��Ă�������\n") ;
  if(getdouble(&qi[i].qxy.y)==EOF) break ;
  fprintf(stderr,"�d�ׂ̒lq����͂��Ă�������\n") ;
  if(getdouble(&qi[i].q)==EOF) break ;
 }
 return i ;
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
