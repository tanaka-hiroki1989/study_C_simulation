/**********************************************/
/*�@�@�@�@   lander.c�v���O����               */
/**********************************************/

/*    �����^���̃V�~�����[�V�����@�@    �@    */
/*  �t���˂�����C�����D�̃V�~�����[�V�����ł�*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define BUFSIZE 256 /*���̓o�b�t�@�p�z��̒���*/
#define DT 0.001 /*�����̍��ݕ�*/
#define F 1.5 /*�t���˂̉����x�����肷��W��*/
#define G  9.80665 /*�d�͉����x*/

/*�֐��̃v���g�^�C�v�̐錾*/
int getdouble(double *x) ;/*�����̓ǂݍ��� */
double retrofire(double t,double tf) ;/*�t���˂̐���*/

/*********************/
/*     main()�֐�    */
/*********************/
int main()
{
 double v,x ; /*���x�ƈʒu*/
 double x0 ; /*�������x�ʒu*/
 double t=0  ;/*����*/
 double h=DT ;/*�����̍��ݕ�*/
 double tf=0  ;/*�t���ˊJ�n����*/


 /*�W���̓���*/
 fprintf(stderr,"�����xv0����͂��Ă�������\n") ;
 if(getdouble(&v)==EOF) exit(1) ;
 fprintf(stderr,"�������xx0����͂��Ă�������\n") ;
 if(getdouble(&x0)==EOF) exit(1) ;
 fprintf(stderr,"�t���ˊJ�n����tf����͂��Ă�������\n") ;
 if(getdouble(&tf)==EOF) exit(1) ;

 x=x0 ;/*�������x�̐ݒ�*/
 printf("%f\t%f\t%f\n",t,x,v) ;/*���ݎ����ƌ��݂̈ʒu*/

 /*�����̌v�Z*/
 while((x>0)&&(x<=x0)){/*�n�ʂɒB���邩�������x��荂���Ȃ�܂Ōv�Z*/
  t+=h ;/*�����̍X�V*/
  v+=(G+retrofire(t,tf))*h ;/*���x�̌v�Z*/
  x-=v*h ;/*�ʒu�̌v�Z*/
  printf("%f\t%f\t%f\n",t,x,v) ;/*���ݎ����ƌ��݂̈ʒu*/
 }

 /*���ʂ̔���*/
 
 return 0 ;
}

/*************************/
/*    retrofire()�֐�    */
/*    �t���˂̐���       */
/*************************/
double retrofire(double t,double tf)
{
 double result=0 ;/*�t���˂̉����x*/

 if(t>=tf){/*�t���ˊJ�n�����ȍ~�Ȃ�*/
  result=-F*G ;/*�t����*/
 }
 return result ;
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
