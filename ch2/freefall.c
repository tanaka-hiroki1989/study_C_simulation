/**********************************************/
/*�@�@�@�@ freefall.c�v���O����               */
/**********************************************/

/*    ���R�����̃V�~�����[�V�����@�@    �@    */
/*  ���R�����̉^���@�������𐔒l�I�ɉ����܂�  */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define BUFSIZE 256 /*���̓o�b�t�@�p�z��̒���*/
#define DT 0.01 /*�����̍��ݕ�*/
#define G  9.80665 /*�d�͉����x*/

/*�֐��̃v���g�^�C�v�̐錾*/
int getdouble(double *x) ;/*�����̓ǂݍ��� */

/*********************/
/*     main()�֐�    */
/*********************/
int main()
{
 double v,x ; /*���x�ƈʒu*/
 double t=0  ;/*����*/
 double h=DT ;/*�����̍��ݕ�*/


 /*�W���̓���*/
 fprintf(stderr,"�����xv0����͂��Ă�������\n") ;
 if(getdouble(&v)==EOF) exit(1) ;
 fprintf(stderr,"�������xx0����͂��Ă�������\n") ;
 if(getdouble(&x)==EOF) exit(1) ;

 printf("%f\t%f\t%f\n",t,x,v) ;/*���ݎ����ƌ��݂̈ʒu*/

 /*���R�����̌v�Z*/
 while(x>0){/*�n�ʂɒB����܂Ōv�Z*/
  t+=h ;/*�����̍X�V*/
  v+=G*h ;/*���x�̌v�Z*/
  x-=v*h ;/*�ʒu�̌v�Z*/
  printf("%f\t%f\t%f\n",t,x,v) ;/*���ݎ����ƌ��݂̈ʒu*/
 }

 /*���ʂ̔���*/
 
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
