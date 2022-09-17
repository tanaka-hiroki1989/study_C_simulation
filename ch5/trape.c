/**********************************************/
/*�@�@�@�@      trape.c�v���O����             */
/**********************************************/

/* ���l�ϕ��v���O����                         */
/* ��`�������g���Đ��l�ϕ����s���܂�         */
/*�@�g����    $./trape (��ԕ�����N�j�@ �@    */
/*  ��Ԃ�0�`1�ɌŒ肵�Ă���܂�              */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*�֐��̃v���g�^�C�v�̐錾*/
double fx(double x) ;/*�ϕ��Ώۂ̊֐�*/

/*********************/
/*     main()�֐�    */
/*********************/
int main(int argc,char *argv[])
{
 double h  ;/*���ݕ�h*/
 double integral ;/*�ϕ��l*/
 int n ;  /*��ԕ�����N*/
 int i ;  /*�J��Ԃ�����̕ϐ�*/

 /*������N�̏�����*/
 if(argc<2){/*��ԕ�����N�̎w�肪�Ȃ�*/
  fprintf(stderr,"�g�����@trape (��ԕ�����N�j\n") ;
  exit(1) ;
 }
 /*���ݕ�h�̌v�Z*/
 if((n=atoi(argv[1]))<=0){
  fprintf(stderr,"��ԕ�����N���s���ł�(%d)\n",n) ;
  exit(1) ;
 } 
 h=1.0/n ;

 /*�ϕ��l�̌v�Z*/
 integral=fx(0.0)/2.0 ;
 for(i=1;i<n;++i){
  integral+=fx((double)i/n) ;
 }
 integral+=fx(1.0)/2.0 ;
 integral*=h ;

 /*���ʂ̏o��*/
 printf("�ϕ��lI�@%.9lf    4I  %.9lf\n",integral,integral*4.0) ;

 return 0 ;
}

/*************************/
/*   fx()�֐�            */
/*   �ϕ��Ώۂ̊֐�      */
/*************************/
double fx(double x)
{
 return sqrt(1.0-x*x) ;
}
